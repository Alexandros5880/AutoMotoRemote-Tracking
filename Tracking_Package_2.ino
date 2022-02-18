#include "GPS.h"
#include "myGSM.h"
#include "OLED.h"
#include <avr/wdt.h>
#include <TimedAction.h>


// Casper Server
// "AT+HTTPPARA=\"URL\",\"http://116.203.233.23/blog/alex/index.php?id=171265875&lat=37.8232222&lon=23.8227222\""
// Strait to salesorce org
// "AT+HTTPPARA=/"URL/",/"https://trackingempire-developer-edition.eu29.force.com/TrackingEmpire/services/apexrest/Tracking_Device?id=171265875&latitude=33.05876&longtitude=37.034568/""
// My Server
// "AT+HTTPPARA=/"URL/",/"https://trackingpackage.000webhostapp.com/?id=171265875&lat=33.05876&lon=37.034568/""



// Product Id
String product_id = "171265875";
// Server URL
String requestURL = "https://trackingpackage.000webhostapp.com";
int satelallites = 0;
double latitude = 0,
      longtitude = 0,
      _altitude = 0,
      latitude_bef = 0,
      longtitude_bef = 0,
      _altitude_bef = 0;




void _display_lines(String title = "", String line1 = "", String line2 = "", String line3 = "");
void _display(String msg, int siz, int x, int y);
void gps_run();
void request();
void _delay(int milliseconds);
void reboot();

const int gsm_rx_pin = 11;
const int gsm_tx_pin = 10;
const int gsm_led = 8;
const int gps_rx_pin = 4;
const int gps_tx_pin = 3;
const int gps_led = 7;

// Set the time for the gps search loop
int GPS::wait = 5000;



SoftwareSerial SIM900(gsm_tx_pin, gsm_rx_pin);
void send_receive_sim() {
  if (SIM900.available()) {
    char c = SIM900.read();
    Serial.write(c);
  }
  if (Serial.available()) {
    String str = Serial.readString();
    SIM900.println(str);
    Serial.println(str);
  }
}
TimedAction send_receive_sim_TH = TimedAction(33,send_receive_sim);




void setup() {
  Serial.begin(115200);
  pinMode(gsm_led, OUTPUT);
  pinMode(gps_led, OUTPUT);
  
  SIM900.begin(9600);
  _delay(3000);
  
  Serial.println("START");
}





void loop() {

  
  //send_receive_sim_TH.check();
  

  
  // Get from gps the values
  //gps_run();


  /*
  // If Values Change or are difrient from 0 send with gsm
  if ( (latitude != latitude_bef) && 
       (longtitude != longtitude_bef) && 
       (_altitude != _altitude_bef) && 
       (latitude != 0.000000) && 
       (longtitude != 0.000000) ) {
  */
  
    // Send with GSM
    //request();

   /*
    // Setup the variables_bef
    latitude_bef = latitude;
    longtitude_bef = longtitude;
    _altitude_bef = _altitude;
  }
  */
  
  //reboot();
}





















// Display 4 Lines in the OLED SCREEN
void _display_lines(String title = "", String line1 = "", String line2 = "", String line3 = "") {
  OLED * screen = new OLED(); // PINS: SDA = A4 , SCK = A5
  screen->displaySetup();
  screen->displayPrint4Lines(title, line1, line2, line3);
  delete screen;
}

// Display One Line Set Size , X, Y
void _display(String msg, int siz, int x, int y) {
  OLED * screen = new OLED(); // PINS: SDA = A4 , SCK = A5
  screen->displaySetup();
  screen->displayPrint(msg, siz, x, y);
  delete screen;
}

// Get Values From GPS
void gps_run() {
  digitalWrite(gps_led, HIGH);
  //_display("GPS Get", 2, 19, 10);
  int rx = gps_rx_pin;
  int tx = gps_tx_pin;
  GPS * gps = new GPS(tx, rx, 9600);
  gps->getBaseImfo(&satelallites, &_altitude, &latitude, &longtitude);
  delete gps;
  digitalWrite(gps_led, LOW);
  // Display on the screen
  _display_lines("Satellites: " + String(satelallites, DEC), 
                 "Lat: " + String(latitude, 6), 
                 "Lon: " + String(longtitude, 6), 
                 "Alt: " + String(_altitude, 6));
}


// Send Data Via GSM To Salesforce End Url
void request() {
  digitalWrite(gsm_led, HIGH);
  //_display("GSM Send", 2, 13, 13);
  int rxPin = gsm_rx_pin;
  int txPin = gsm_tx_pin;
  int resetPin = 2;
  myGSM * gsm = new myGSM(txPin, rxPin, resetPin, 9600);
  //gsm->reset_();
  gsm->makeRequest(requestURL, product_id, String(latitude, 8), String(longtitude, 8));
  delete gsm;
  digitalWrite(gsm_led, LOW);
}


// Real Time Dellay
void _delay(int milliseconds) {
  int wait = millis() + milliseconds;
  while (millis() < wait);
}


// Arduino Reboot
void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}
















/*

  requestARG = {"id=171265875", "lat=37.8232222", "lon=23.8227222"};
  gsm.makeGETRequest(requestURL, requestARG, len);

*/
/*
satelallites = gps->getSatellites();
latitude = gps->getLatitude();
longtitude = gps->getLongtitude();
_altitude = gps->getAltitudeMeters();
*/
/*
  gps.getLatitude();
  gps.getLongtitude();
  gps.getAltitude();
  gps.getDate();
  gps.getTime();
  gps.getDateTime();
*/
