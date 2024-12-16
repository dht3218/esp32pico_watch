#include "AisassistantLocal.h"
#include <pico_detect_inferencing.h>
#include <driver/i2s.h>

// If your target is limited in memory remove this macro to save 10K RAM
#define EIDSP_QUANTIZE_FILTERBANK 0
#define SAMPLE_RATE EI_CLASSIFIER_FREQUENCY  // 16000

#ifndef I2S_IN_PORT
// INMP441 config
#define I2S_IN_PORT I2S_NUM_0
#define I2S_IN_BCLK 14
#define I2S_IN_LRC 2
#define I2S_IN_DIN 27
#endif

/** Audio buffers, pointers and selectors */
typedef struct
{
  int16_t *buffer;
  uint8_t buf_ready;
  uint32_t buf_count;
  uint32_t n_samples;
} inference_t;

static inference_t inference;
static const uint32_t sample_buffer_size = 2048;
static signed short sampleBuffer[sample_buffer_size];
static bool debug_nn = false;  // Set this to true to see e.g. features generated from the raw signal
static bool record_status = true;

static void audio_inference_callback(uint32_t n_bytes) {
  for (int i = 0; i < n_bytes >> 1; i++) {
    inference.buffer[inference.buf_count++] = sampleBuffer[i];

    if (inference.buf_count >= inference.n_samples) {
      inference.buf_count = 0;
      inference.buf_ready = 1;
    }
  }
}

int capwait = 0;  // waitfor next capture task

static void capture_samples(void *arg) {
  
  const int32_t i2s_bytes_to_read = (uint32_t)arg;
  size_t bytes_read = i2s_bytes_to_read;
  Serial.println(record_status);
  while (record_status) {Serial.print("-1 ");
    if (capwait == 1) {  // 得到识别结果后，抑制一段时间，防止误识别
      vTaskDelay(786);
      capwait = 0;
    }Serial.print("0 ");
    i2s_zero_dma_buffer(I2S_IN_PORT);Serial.print("1 ");
    i2s_read(I2S_IN_PORT, (void *)sampleBuffer, i2s_bytes_to_read, &bytes_read, 100);
Serial.print("2 ");
    // if (capwait == 1) {
    //   continue;
    // }
    if (bytes_read <= 0) {Serial.print("3 ");
      ei_printf("Error in I2S read : %d", bytes_read);
    } else {Serial.print("4 ");
      if (bytes_read < i2s_bytes_to_read) {
        ei_printf("Partial I2S read");
      }
Serial.print("5 ");
      // scale the data (otherwise the sound is too quiet)
      for (int x = 0; x < i2s_bytes_to_read / 2; x += 1) {

        sampleBuffer[x] = (int16_t)(sampleBuffer[x]) * 16;  // 与数据采集时匹配
                                                            // Serial.println(sampleBuffer[x]);
      }
Serial.print("6 ");
      if (record_status) {
        audio_inference_callback(i2s_bytes_to_read);
      } else {
        break;
      }
    }
  }
  vTaskDelete(NULL);
  Serial.print("end ");
}
TaskHandle_t CaptureSamples_task;
/**
 * @brief      Init inferencing struct and setup/start PDM
 *
 * @param[in]  n_samples  The n samples
 *
 * @return     { description_of_the_return_value }
 */
static bool microphone_inference_start(uint32_t n_samples) {
  inference.buffer = (int16_t *)malloc(n_samples * sizeof(int16_t));

  if (inference.buffer == NULL) {
    return false;
  }

  inference.buf_count = 0;
  inference.n_samples = n_samples;
  inference.buf_ready = 0;

  ei_sleep(100);
  record_status = true;
  xTaskCreate(capture_samples, "CaptureSamples", 1024 * 32, (void *)sample_buffer_size, 10, &CaptureSamples_task);

  return true;
}

/**
 * @brief      Wait on new data
 *
 * @return     True when finished
 */
static bool microphone_inference_record(void) {
  bool ret = true;

  while (inference.buf_ready == 0) {
    delay(10);
  }
Serial.println("buf_ready");
  inference.buf_ready = 0;
  return ret;
}

/**
 * Get raw audio signal data
 */
static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr) {
  numpy::int16_to_float(&inference.buffer[offset], out_ptr, length);

  return 0;
}

/**
 * @brief      Stop PDM and release buffers
 */
static void microphone_inference_end(void) {
  free(sampleBuffer);
  ei_free(inference.buffer);
}

#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_MICROPHONE
#error "Invalid model for current sensor."
#endif

const char *AILocalloop() {
  ei_printf("Recording...\n");
  int aicount = 0;
  while (1) {
    if (aicount > 5) return "";
    aicount += 1;
    Serial.print("aicount");
    Serial.println(aicount);
    bool m = microphone_inference_record();
    if (!m) {
      Serial.println("ERR: Failed to record audio...");
      return "";
    }
    //Serial.println("1");
    signal_t signal;
    signal.total_length = EI_CLASSIFIER_RAW_SAMPLE_COUNT;
    signal.get_data = &microphone_audio_signal_get_data;
    ei_impulse_result_t result = { 0 };
    //Serial.println("2");
    EI_IMPULSE_ERROR r = run_classifier(&signal, &result, debug_nn);
    //Serial.println("3");
    if (r != EI_IMPULSE_OK) {
      Serial.println("ERR: Failed to run classifier");
      ei_printf("ERR: Failed to run classifier (%d)\n", r);
      return "";
    }
    int pred_index = 3;       // Initialize pred_index
    float pred_value = 0.34;  // Initialize pred_value

    // print the predictions
    Serial.print("Predictions ");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
      // ei_printf("    %s: ", result.classification[ix].label);
      // ei_printf_float(result.classification[ix].value);
      // ei_printf("\n");

      if (result.classification[ix].value > pred_value) {
        pred_index = ix;
        // pred_value = result.classification[ix].value;
      }
    }
    if (pred_index != 3) {
      Serial.print(result.classification[pred_index].label);
      //capwait = 1;
      //record_status = 0;
      vTaskDelete(CaptureSamples_task);
      return result.classification[pred_index].label;
    }
    Serial.println(" ");
  }
}

void AILocalsetup() {
  Serial.begin(115200);
  // enable mircophone disable sound
  pinMode(20, OUTPUT);
  digitalWrite(20, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  // comment out the below line to cancel the wait for USB connection (needed for native USB)
  record_status = 1;
  // Initialize I2S for audio input
  i2s_config_t i2s_config_in = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = (i2s_bits_per_sample_t)16,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = -1,
  };
  i2s_pin_config_t pin_config_in = {
    .bck_io_num = I2S_IN_BCLK,
    .ws_io_num = I2S_IN_LRC,
    .data_out_num = -1,
    .data_in_num = I2S_IN_DIN
  };
  i2s_driver_install(I2S_IN_PORT, &i2s_config_in, 0, NULL);
  i2s_set_pin(I2S_IN_PORT, &pin_config_in);

  if (microphone_inference_start(EI_CLASSIFIER_RAW_SAMPLE_COUNT) == false) {
    ei_printf("ERR: Could not allocate audio buffer (size %d), this could be due to the window length of your model\r\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT);
    return;
  }


  const char *result = AILocalloop();
  Serial.println(result);
}
