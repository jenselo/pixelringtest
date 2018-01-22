#include <Adafruit_NeoPixel.h>
#include <stdint.h>

#define SAMPLE_RATE 9000
#define FFT_SIZE 256
#define MIN_DB 50
#define MAX_DB 100

#define LED_PIN 6
#define MIC_PIN A10

Adafruit_NeoPixel strip =
  Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

float time_samples[FFT_SIZE * 2];
float fft_data[FFT_SIZE];
uint32_t sample_counter = 0;

unsigned uint32_t start_time = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(MIC_PIN, INPUT);

  memset(time_samples, 0, sizeof(time_samples));
  memset(fft_data, 0, sizeof(fft_data));

  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(255);
  strip.show();
  last_time = micros();
}

void loop() {
  /* Does this condition need a std deviation? */
  if (micros() - last_time >= 100) {
    time_samples[sample_counter] = analogRead(MIC_PIN);
    reset time
    sample_counter++;
    last_time();
  }

  if (sample_counter >= FFT_SIZE * 2) {
    // do the fft

    // color the leds

    sample_counter = 0;
  }
}
