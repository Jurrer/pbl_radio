#include "driver/i2s.h"
#include "soc/i2s_struct.h"


#define I2S_NUM (I2S_NUM_0) // I2S port number
#define I2S_BCK_IO (25)        // I2S bit clock pin
#define I2S_WS_IO (26)         // I2S word select pin
#define I2S_DO_IO (22)         // I2S data out pin
#define I2S_DI_IO (35)         // I2S data in pin
#define I2S_RX_BLOCK_SIZE (32) // I2S RX block size

// I2S configuration
i2s_config_t i2s_config = {
  .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
  .sample_rate = 44100,
  .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
  .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
  .communication_format = I2S_COMM_FORMAT_I2S_MSB,
  .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
  .dma_buf_count = 8,
  .dma_buf_len = I2S_RX_BLOCK_SIZE
};

// I2S pin configuration
i2s_pin_config_t pin_config = {
  .bck_io_num = I2S_BCK_IO,
  .ws_io_num = I2S_WS_IO,
  .data_out_num = I2S_DO_IO,
  .data_in_num = I2S_DI_IO
};

void setup() {
  // Initialize I2S
  esp_err_t err = i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
  if (err != ESP_OK) {
    Serial.printf("Failed to install I2S driver: %d\n", err);
    return;
  }

  err = i2s_set_pin(I2S_NUM, &pin_config);
  if (err != ESP_OK) {
    Serial.printf("Failed to set I2S pins: %d\n", err);
    return;
  }
}

void loop() {
  // Set up audio input
  int16_t* audio_samples = (int16_t*)malloc(I2S_RX_BLOCK_SIZE * sizeof(int16_t));

  // Read audio samples from SPDIF transmitter
  size_t bytes_read;
  esp_err_t err = i2s_read(I2S_NUM, audio_samples, I2S_RX_BLOCK_SIZE * sizeof(int16_t), &bytes_read, portMAX_DELAY);
  if (err != ESP_OK) {
    Serial.printf("Failed to read audio samples: %d\n", err)
  }
}