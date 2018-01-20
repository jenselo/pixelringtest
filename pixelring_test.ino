#include <Adafruit_NeoPixel.h>

#define LED_PIN 6 // NeoPixel LED strand is connected to this pin
#define MIC_PIN A10

#define START 21
#define NUM_PIXELS 61
#define NUM_COLOURS 3
#define DELAY 100
#define NUM_RINGS 5

static uint8_t *rings[5];
static uint8_t ringsize[5] = {1, 8, 12, 16, 24};
static bool pixelstatus[NUM_PIXELS];

Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup_rings() {
  unsigned p;
  unsigned i;

  // From the middle:
  // 1
  rings[0][0] = 20;

  // 8
  for (i = 12, p = 0; i < 12 + 8; i++, p++) {
    rings[1][p] = i;
  }

  // 12
  for (i = 0, p = 0; i < 0 + 12; i++, p++) {
    rings[2][p] = i;
  }

  // 16
  for (i = 45, p = 0; i < 45 + 16; i++, p++) {
    rings[3][p] = i;
  }

  // 24
  for (i = 21, p = 0; i < 21 + 24; i++, p++) {
    rings[4][p] = i;
  }

}

void setup() {
  unsigned i;
  analogReference(DEFAULT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(MIC_PIN, INPUT);
  Serial.begin(9600);

  for (i = 0; i < NUM_RINGS; i++) {
    rings[i] = (uint8_t*)calloc(ringsize[i], sizeof(uint8_t));
  }

  for (i = 0; i < NUM_PIXELS; i++) {
    pixelstatus[i] = false;
  }

  ring.begin();
  ring.setBrightness(60);
  ring.show();

  setup_rings();

  for (i = 0; i < NUM_PIXELS; i++) {
    ring.setPixelColor(i, 0, 0, 0);
  }
  ring.show();
  delay(10);
}

bool alreadyLit(int pixelnum) {
  return pixelstatus[pixelnum];
}

bool allLit() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    if (alreadyLit(i) == false) {
      return false;
    }
  }

  return true;
}

static bool direction = true;
int pixels_colored = 0;

void loop() {

  int val = analogRead(MIC_PIN);
  Serial.println(val);

  int pixelnum = random(0, NUM_PIXELS);

  if (pixels_colored == NUM_PIXELS) {
    for (int i = 0; i < NUM_PIXELS; i++) {
      pixelstatus[i] = false;
      ring.setPixelColor(i, 0, 0, 0);
    }
    ring.show();
    pixels_colored = 0;
  }

  while(alreadyLit(pixelnum) == direction) {
    pixelnum = random(0, NUM_PIXELS);
  }

  pixels_colored++;
  pixelstatus[pixelnum] = direction;

  int r = random(0, 255);
  int g = random(0, 255);
  int b = random(0, 255);

  //ring.setPixelColor(pixelnum, r, g, b);
  //ring.show();

  delay(300);
}
