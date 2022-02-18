#include "Arduino.h"
#include "myGSM.h"

// Constructor 1
myGSM::myGSM(int txPin, int rxPin, int resete_pin, int baud) : gsm(SoftwareSerial(txPin,rxPin))
{
  this->resetePin = resete_pin;
  this->GSMsetup(baud);
}

// myGSM SETUP
void myGSM::GSMsetup(int baud)
{
	this->gsm.begin(baud);
  this->_delay(3000);
}

// Real Time Delay
void myGSM::_delay(int milliseconds) {
  int wait = millis() + milliseconds;
  while (millis() < wait);
}

// GSM RESET
void myGSM::reset_()
{
	digitalWrite(this->resetePin, HIGH);
  this->_delay(2000);
	digitalWrite(this->resetePin, LOW);
	//Serial.println("Set pin 9 low and wait 3 secs.");
  this->_delay(1000);
}


// SHOW RESPONCE
void myGSM::ShowSerialData()
{
	while( this->gsm.available() ) {
    Serial.write(this->gsm.read());
	}
  Serial.write("\n");
}


// SEND DATA
void myGSM::SendSerialData( String msg )
{
  for (int i = 0; i < msg.length(); i++) {
    this->gsm.write(msg[i]);
    Serial.write(msg[i]);
  }
  this->gsm.write("\n");
  Serial.write("\n");
}


// MAKE REQUEST GET REST
void myGSM::makeRequest(String url, String _id, String latitude, String longtitude)
{
  this->SendSerialData("AT+CSQ");
  this->_delay(1500);
  ShowSerialData();
  this->SendSerialData("AT+SAPBR=3,1,\"APN\",\"gint.b-online.gr\"");
  this->_delay(1500);
	ShowSerialData();
  this->SendSerialData("AT+SAPBR=1,1");
  this->_delay(1500);
	ShowSerialData();
  this->SendSerialData("AT+HTTPINIT");
  this->_delay(1500);
	ShowSerialData();
  this->SendSerialData("AT+HTTPPARA=\"URL\",\"" + url + "?id=" + _id + "&lat=" + latitude + "&lon=" + longtitude + "\"");
  //this->SendSerialData("AT+HTTPPARA=\"URL\",\"" + url + "?id=" + _id + "&lat=15.123456&lon=15.123456\"");
  this->_delay(3000);
	ShowSerialData();
  this->SendSerialData("AT+HTTPACTION=0");
  this->_delay(1500);
	ShowSerialData();
  this->SendSerialData("AT+HTTPREAD");
  this->_delay(5000);
	ShowSerialData();
  this->SendSerialData("AT+HTTPTERM");
  this->_delay(1500);
  ShowSerialData();
  this->SendSerialData("AT+SAPBR=0,1");
  this->_delay(1500);
	ShowSerialData();
  //this->reset_();
}
