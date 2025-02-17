#include <driver/i2s.h>
#include <Arduino.h>

// INMP441 config
#define I2S_IN_PORT I2S_NUM_0
#define I2S_IN_BCLK 14
#define I2S_IN_LRC 2
#define I2S_IN_DIN 27

// Settings
#define SAMPLE_RATE 16000U  // Sample rate in Hz
#define SAMPLE_BITS 16      // Sample bits (16 for 16-bit audio)
#define RECORD_TIME_SEC 5   // Record for 1 second
#define VOLUME_GAIN 4       // Volume gain factor
const char signature[] = "%";
const char signatureStart[] = "#";
void setup() {
  Serial.begin(115200);  // Serial for debugging
  Serial.println("Starting setup...");
  pinMode(20, OUTPUT);
  digitalWrite(20, HIGH);
  // Initialize I2S for audio input
  i2s_config_t i2s_config = {
    .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 16,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_IN_BCLK,
    .ws_io_num = I2S_IN_LRC,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_IN_DIN
  };

  // Install and configure I2S driver
  i2s_driver_install(I2S_IN_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_IN_PORT, &pin_config);

  Serial.println("Setup complete.");
}

void loop() {
  uint32_t sample_size = (SAMPLE_RATE * SAMPLE_BITS / 8) * RECORD_TIME_SEC;
  uint8_t *rec_buffer = (uint8_t *)ps_malloc(sample_size);  // Buffer for 1 second of audio at 16-bit mono

  if (rec_buffer == NULL) {
    Serial.println("Failed to allocate memory!");
    return;
  }
  Serial.write(signatureStart, strlen(signatureStart));
  // Start recording
  size_t bytes_read = 0;
  i2s_read(I2S_IN_PORT, rec_buffer, sample_size, &bytes_read, portMAX_DELAY);

  if (bytes_read == 0) {
    Serial.println("Record Failed!");
  } else {
    // Increase volume
    for (uint32_t i = 0; i < bytes_read; i += SAMPLE_BITS / 8) {
      (*(uint16_t *)(rec_buffer + i)) <<= VOLUME_GAIN;
    }
    Serial.write(signature, strlen(signature));
    // Send audio data through serial
    Serial.write(rec_buffer, bytes_read);

    //Serial.println("1 second of audio data sent");
  }

  // Free the memory
  free(rec_buffer);
  delay(2000);  // Wait for 1 second before recording again
}