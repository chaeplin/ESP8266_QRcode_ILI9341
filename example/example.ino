#include "ILI9341qrcode.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"


// For the Adafruit shield, these are the default.
#define TFT_DC 4
#define TFT_CS 5

Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);
QRcode qrcode (&display);

void setup() {

    Serial.begin(115200);
    Serial.println("");
    Serial.println("Starting...");

    display.begin();

    qrcode.init();
    qrcode.create("Hello World");

}

void loop() { }
