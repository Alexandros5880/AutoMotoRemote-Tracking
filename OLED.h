
#ifndef OLED_h
#define OLED_h

#ifndef Arduino_h
#include "Arduino.h"
#endif

#ifndef SPI_h
#include "SPI.h"
#endif

#ifndef Wire_h
#include "Wire.h"
#endif

#ifndef Adafruit_GFX_h
#include "Adafruit_GFX.h"
#endif

#ifndef Adafruit_SSD1306_h
#include "Adafruit_SSD1306.h"
#endif

class OLED {
	public:
		OLED();
		void displaySetup(); // PINS: SDA = A4 , SCK = A5
		void displayPrint(String message, int size_ = 1, int cusorX = 0, int cursorY = 0);
    void OLED::displayPrint4Lines(String line1 = "", String line2 = "", String line3 = "", String line4 = "");
    void clear();
    void _delay(int milliseconds);
	private:
		Adafruit_SSD1306 display;
};

#endif
