#include "Adafruit_ILI9341.h"

class QRcode
{
	private:
		Adafruit_ILI9341 *display;
		void render(int x, int y, int color);

	public:
		QRcode(Adafruit_ILI9341 *display);

		void init();
		void debug();
		void screenwhite();
		void create(String message);
};
