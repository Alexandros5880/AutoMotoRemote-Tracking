#include "Arduino.h"
#include "OLED.h"


OLED::OLED() : display(Adafruit_SSD1306(-1))
{
  
}

// In setup function
void OLED::displaySetup()
{
	this->display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	//this->display.display();
  this->_delay(2000);
	this->display.clearDisplay();
}


// Real Time Delay
void OLED::_delay(int milliseconds) {
  int wait = millis() + milliseconds;
  while (millis() < wait);
}

// Function to display text  (message, textSize, curdor x, cursor y)
void OLED::displayPrint(String message, int size_ = 1, int cusorX = 0, int cursorY = 0)
{
	this->display.clearDisplay();
	this->display.setTextSize(size_);
	this->display.setTextColor(WHITE);
	this->display.setCursor(cusorX, cursorY);
  this->display.println(message);
	this->display.display();
}



// Function to display text  (message, textSize, curdor x, cursor y)
void OLED::displayPrint4Lines(String line1 = "", String line2 = "", String line3 = "", String line4 = "")
{
  this->display.clearDisplay();
  this->display.setTextSize(1);
  this->display.setTextColor(WHITE);
  this->display.setCursor(0, 0);
  this->display.println(line1);
  this->display.println(line2);
  this->display.println(line3);
  this->display.println(line4);
  this->display.display();
}

// Clear Screen Function
void OLED::clear()
{
  this->display.clearDisplay();
  this->display.display();
}
