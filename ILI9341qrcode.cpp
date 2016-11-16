#include <Arduino.h>
#include "ILI9341qrcode.h"
#include "qrencode.h"

int offsetsX = 7;
int offsetsY = 7;

int screenwidth = 320;
int screenheight = 240;
bool QRDEBUG = false;

QRcode::QRcode(Adafruit_ILI9341 *display){
	this->display = display;
}

void QRcode::init(){
	if(QRDEBUG)
		Serial.println("QRcode init");
	display->begin();
}

void QRcode::debug(){
	QRDEBUG = true;
}

void QRcode::render(int x, int y, int color){
  x=(x+offsetsX) * 4;
  y=(y+offsetsY) * 4;
  if(color==1) {
    for(int i=0; i<4 ; i++) {
      for (int j=0; j<4; j ++) {
        display->drawPixel(x + i, y + j, ILI9341_BLACK);
      }
    }
  }
  else {
    for(int i=0; i<4 ; i++) {
      for (int j=0; j<4; j ++) {
        display->drawPixel(x + i, y + j, ILI9341_WHITE);
      }
    }     
  }
}

void QRcode::screenwhite(){
  display->fillScreen(ILI9341_WHITE);
  display->fillRect(0, 0, screenwidth, screenheight, ILI9341_WHITE);

}

void QRcode::create(String message) {

  // create QR code
  message.toCharArray((char *)strinbuf,260);
  qrencode();
  screenwhite();

  if(QRDEBUG){
	Serial.println("QRcode render");
	Serial.println();
  }
  // print QR Code
  for (byte x = 0; x < WD; x+=2) {
    for (byte y = 0; y < WD; y++) {
      if ( QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // black square on top of black square
        if(QRDEBUG)
			Serial.print("@");
        render(x, y, 1);
        render((x+1), y, 1);
      }
      if (!QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // white square on top of black square
        if(QRDEBUG)
			Serial.print(" ");
        render(x, y, 0);
        render((x+1), y, 1);
      }
      if ( QRBIT(x,y) && !QRBIT((x+1),y)) {
        // black square on top of white square
        if(QRDEBUG)
			Serial.print("@");
        render(x, y, 1);
        render((x+1), y, 0);
      }
      if (!QRBIT(x,y) && !QRBIT((x+1),y)) {
        // white square on top of white square
        if(QRDEBUG)
			Serial.print(" ");
        render(x, y, 0);
        render((x+1), y, 0);
      }
    }
    Serial.println();
  }
  Serial.println();
}
