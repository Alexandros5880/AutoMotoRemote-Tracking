#ifndef GPS_h
#define GPS_h

#ifndef Arduino_h
#include "Arduino.h"
#endif

#ifndef SoftwareSerial_h
#include "SoftwareSerial.h"
#endif

#ifndef TinyGPS++_h
#include "TinyGPS++.h"
#endif

class GPS {
	public:
		GPS(int rx, int tx, int baud);
		void setup(int baud);
		int getSatellites();
		double getLatitude();
		double getLongtitude();
		double getAltitudeMeters();
		double getAltitudeFeets();
		double getSpeedMph();
		double getSpeedKmph();
		double getSpeedKnots();
		String getDate();
		String getTime();
		String getDateTime();
    void   getBaseImfo(int* sat, double* alt, double* late, double* longe);
    int static wait;
	private:
		SoftwareSerial gpsSerial;
		TinyGPSPlus gps;
};

#endif
