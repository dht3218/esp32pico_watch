/* Edge Impulse ingestion SDK
 * Copyright (c) 2023 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
#include <pico_detect_inferencing.h>

#include "edge-impulse-sdk/dsp/image/image.hpp"
#include <Audio.h>

/** Audio buffers, pointers and selectors */
typedef struct {
    signed short *buffers[2];
    unsigned char buf_select;
    unsigned char buf_ready;
    unsigned int buf_count;
    unsigned int n_samples;
} inference_t;

/* Private variables ------------------------------------------------------- */
static inference_t inference;
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal
static AudioClass *theAudio;
static int32_t buffer_size = 1536; /*768sample,1ch,16bit*/
static char *s_buffer;
static int print_results = -(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW);

/* Recording bit rate
 * Set in bps.
 */
static const int32_t recording_bitrate = ei_default_impulse.impulse->frequency;
/**
 * number of channels
 */
static const uint8_t recording_channels = ei_default_impulse.impulse->raw_samples_per_frame;

/* Function definitions ------------------------------------------------------- */
static void audio_attention_cb(const ErrorAttentionParam *atprm);
static void microphone_inference_end(void);
static bool microphone_inference_record(void);
static bool microphone_inference_start(void);
static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr);

/**
* @brief      Arduino setup function
*/
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);

    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);
    Serial.println("Edge Impulse Inferencing Demo");

    // summary of inferencing settings (from model_metadata.h)
    ei_printf("Inferencing settings:\n");
    ei_printf("\tInterval: %.4f ms.\n", (float)EI_CLASSIFIER_INTERVAL_MS);
    ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    ei_printf("\tSample length: %d ms.\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT / 16);
    ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) / sizeof(ei_classifier_inferencing_categories[0]));

    if (microphone_inference_start() == false) {
        ei_printf("ERR: Could not allocate audio buffer (size %d), this could be due to the window length of your model\r\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT);
        return;
    }

}

/**
* @brief      Get data and run inferencing
*
* @param[in]  debug  Get debug info if true
*/
void loop()
{
    if (AUDIOLIB_ECODE_OK != theAudio->startRecorder()) {
        return false;
    }

    if (microphone_inference_record() == false) {
        ei_printf("ERR: Failed to record audio...\n");
        return;
    }

    theAudio->stopRecorder();

    signal_t signal;
    signal.total_length = ei_default_impulse.impulse->slice_size * ei_default_impulse.impulse->raw_samples_per_frame;
    signal.get_data = &microphone_audio_signal_get_data;
    ei_impulse_result_t result = {0};

    EI_IMPULSE_ERROR r = run_classifier_continuous(&signal, &result, debug_nn);
    if (r != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", r);
        return;
    }

    if (++print_results >= (EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW >> 1)) {
        // print the predictions
        ei_printf("Predictions ");
        ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
            result.timing.dsp, result.timing.classification, result.timing.anomaly);
        ei_printf(": \n");
        for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
            ei_printf("    %s: %.5f\n", result.classification[ix].label,
                      result.classification[ix].value);
        }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif

        print_results = 0;
    }
}

/**
 * @brief
 *
 * @param n_samples
 * @return true
 * @return false
 */
static bool microphone_inference_start(void)
{
    inference.buffers[0] = (int16_t *)ei_aligned_calloc(32, ei_default_impulse.impulse->slice_size * sizeof(int16_t) * recording_channels);
    inference.buffers[1] = (int16_t *)ei_aligned_calloc(32, ei_default_impulse.impulse->slice_size * sizeof(int16_t) * recording_channels);

    buffer_size *= recording_channels;
    s_buffer = (char *)ei_aligned_calloc(32, buffer_size);

    if ((inference.buffers[0] == NULL) || (inference.buffers[1] == NULL) || (s_buffer == NULL)) {
        return false;
    }

    inference.buf_select = 0;
    inference.buf_count  = 0;
    inference.n_samples  = ei_default_impulse.impulse->slice_size;
    inference.buf_ready  = 0;

    theAudio = AudioClass::getInstance();

    theAudio->begin(audio_attention_cb);

    /* Select input device as microphone */
    if (theAudio->setRecorderMode(AS_SETRECDR_STS_INPUTDEVICE_MIC, 220, SIMPLE_FIFO_BUF_SIZE, false) != 0) {
        return false;
    }

    if (theAudio->initRecorder(AS_CODECTYPE_PCM, "/mnt/sd0/BIN", recording_bitrate, recording_channels) != 0)  {
        return false;
    }

    return true;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
static bool microphone_inference_record(void)
{
    uint32_t length;
    err_t err;
    int16_t *samples = (int16_t *)s_buffer;

    inference.buf_ready = 0;

    do {
        err = theAudio->readFrames(s_buffer, buffer_size, &length);
        if ((err != AUDIOLIB_ECODE_OK) && (err != AUDIOLIB_ECODE_INSUFFICIENT_BUFFER_AREA)) {
            return false;
        }
        for (uint32_t i = 0; i < (length >> 1); i++) {
            inference.buffers[inference.buf_select][inference.buf_count++] = samples[i];

            if (inference.buf_count >= (inference.n_samples * recording_channels)) {  // n_samples is per channel
                inference.buf_select ^= 1;
                inference.buf_count = 0;
                inference.buf_ready = 1;
            }
        }
    } while (inference.buf_ready == 0);

    return true;
}

/**
 * Get raw audio signal data
 */
static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr)
{
    ei::numpy::int16_to_float(&inference.buffers[inference.buf_select ^ 1][offset], out_ptr, length);

    return 0;
}

/**
 * @brief
 *
 */
static void microphone_inference_end(void)
{
    theAudio->stopRecorder();

    theAudio->setReadyMode();
    theAudio->end();

    ei_free(inference.buffers[0]);
    ei_free(inference.buffers[1]);
    ei_free(s_buffer);
}

/**
 * @brief Audio attention callback
 *
 * When audio internal error occurs, this function will be called back.
 */

static void audio_attention_cb(const ErrorAttentionParam *atprm)
{
    ei_printf("Audio error: %d\n", atprm->error_code);

    while(1){

    }
}

#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_MICROPHONE
#error "Invalid model for current sensor."
#endif