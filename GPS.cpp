#include "GPS.h"

// Contrsuctor
GPS::GPS(int rx, int tx, int baud) : gpsSerial(SoftwareSerial(tx, rx))
{
	this->setup(baud);
}

// Put it in the setup function
void GPS::setup(int baud)
{
	this->gpsSerial.begin(baud);
}

// Get Satellites
int GPS::getSatellites()
{
  int sat;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
  	while ( this->gpsSerial.available() > 0 ) {
  		if ( this->gps.encode(this->gpsSerial.read()) ) {
  			if ( this->gps.satellites.isValid() ) {
          sat = this->gps.satellites.value();
          break;
  			}
  		}
  	}
  }
  return sat;
}

// Get latitude
double GPS::getLatitude()
{
  double lat_s;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
    while ( this->gpsSerial.available() > 0 ) {
      if ( this->gps.encode(this->gpsSerial.read()) ) {
      	if ( this->gps.location.isValid() ) {
      		lat_s = this->gps.location.lat();
         break;
      	}
      }
    }
  }
  return lat_s;
}

// Get Longtitude
double GPS::getLongtitude()
{
  double lon;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
    while ( this->gpsSerial.available() > 0 ) {
    	if ( this->gps.encode(this->gpsSerial.read()) ) {
    		if ( this->gps.location.isValid() ) {
    			lon = this->gps.location.lng();
         break;
    		}
    	}
    }
  }
  return lon;
}

// Get Altitude in meters
double GPS::getAltitudeMeters()
{
  double alt;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
    while ( this->gpsSerial.available() > 0 ) {
    	if ( this->gps.encode(this->gpsSerial.read()) ) {
    		if ( this->gps.altitude.isValid() ) {
    			alt = this->gps.altitude.meters();
          break;
    		}
    	}
    }
  }
  return alt;
}

// Get Altitude in feets
double GPS::getAltitudeFeets()
{
  double alt;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
    while ( this->gpsSerial.available() > 0 ) {
    	if ( this->gps.encode(this->gpsSerial.read()) ) {
    		if ( this->gps.altitude.isValid() ) {
    			alt = this->gps.altitude.feet();
          break;
    		}
    	}
    }
  }
  return alt;
}

// Get Milles per houre
double GPS::getSpeedMph()
{
  double mph_s;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
    while ( this->gpsSerial.available() > 0 ) {
    	if ( this->gps.encode(this->gpsSerial.read()) ) {
    		if ( this->gps.speed.isValid() ) {
    			mph_s = this->gps.speed.mph();
          break;
    		}
    	}
    }
  }
  return mph_s;
}

// Get Kilometers per houre
double GPS::getSpeedKmph()
{
  double kmph_s;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
  	while ( this->gpsSerial.available() > 0 ) {
  		if ( this->gps.encode(this->gpsSerial.read()) ) {
  			if ( this->gps.speed.isValid() ) {
  				kmph_s = this->gps.speed.kmph();
          break;
  			}
  		}
  	}
  }
  return kmph_s;
}

// Get Knots per houre
double GPS::getSpeedKnots()
{
  double knots_s;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
    while ( this->gpsSerial.available() > 0 ) {
    	if ( this->gps.encode(this->gpsSerial.read()) ) {
    		if ( this->gps.speed.isValid() ) {
    			knots_s = this->gps.speed.knots();
          break;
    		}
    	}
    }
  }
  return knots_s;
}

// Get date
String GPS::getDate()
{
  String date_s;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
  	while ( this->gpsSerial.available() > 0 ) {
  		if ( this->gps.encode(this->gpsSerial.read()) ) {
  			if ( this->gps.date.isValid() ) {
  				date_s = String(this->gps.date.year()) + "-" + String(this->gps.date.month()) + "-" + String(this->gps.date.day());
         break;
  			}
  		}
  	}
  }
  return date_s;
}

// Get time
String GPS::getTime()
{
  String time_s;
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
  	while ( this->gpsSerial.available() > 0 ) {
  		if ( this->gps.encode(this->gpsSerial.read()) ) {
  			if ( this->gps.time.isValid() ) {
  				time_s = String(this->gps.time.hour()) + ":" + String(this->gps.time.minute()) + ":" + String(this->gps.time.second());
          break;
  			}
  		}
  	}
  }
  return time_s;
}

// Get Datetime
String GPS::getDateTime()
{
	return this->getDate() + " " + this->getTime();
}

// Get Base Imfo
void GPS::getBaseImfo(int* sat, double* alt, double* late, double* longe) {
  unsigned long nextTime = millis() + GPS::wait;
  while ( millis() < nextTime ) {
    while ( this->gpsSerial.available() > 0 ) {
      if ( this->gps.encode(this->gpsSerial.read()) ) {
        if ( (this->gps.satellites.isValid()) && 
             (this->gps.location.isValid()) && 
             (this->gps.altitude.isValid()) ) {
          *sat = this->gps.satellites.value();
          *alt = this->gps.altitude.meters();
          *late = this->gps.location.lat();
          *longe = this->gps.location.lng();
          break;
        }
      }
    }
  }
}
