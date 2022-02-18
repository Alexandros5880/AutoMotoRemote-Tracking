#ifndef SoftwareSerial.h
#include <SoftwareSerial.h>
#endif

#ifndef myGSM_h
#define myGSM_h
#include "Arduino.h"
class myGSM {
	public:
		myGSM(int txPin, int rxPin, int resete_pin, int baud);
		void GSMsetup(int baud);
    void _delay(int milliseconds);
		void reset_();
		void ShowSerialData();
    void SendSerialData( String msg );
    void _resete_arduino();
		void makeRequest(String url, String id, String latitude, String longtitude);
	private:
		int resetePin;
    SoftwareSerial gsm;
};
#endif


// SETUP
/*
GSMsetup();
*/

//                url                 id          latitude      longtitude
//makeRequest("shorturl.at/gkyBE", "171265875", "37.8232222", "23.8227222");
//                url      {"id=xx",arg="yy"}   2
// makeGETRequest(String url, String arg[], int len);



// LOOP
/*
if (Serial.available()) {
	SendSerialData(Serial.readString());
	ShowSerialData();
}
*/
