#include "src/HeptaSat.h"

HeptaCdh    cdh;
HeptaEps    eps;
HeptaSensor sensor;

void setup() {
  cdh.begin();
  eps.init();
  sensor.begin();
}

void loop() {
  GpggaData gga;
  if (sensor.gps_get_gpgga(&gga)) {
    cdh.printf("GPGGA utc=%.3f lat=%.6f lon=%.6f alt=%.2f fix=%u sat=%u hdop=%.2f\n",
               gga.utc_time, gga.lat, gga.lon, gga.alt,
               gga.fix_quality, gga.sat_num, gga.hdop);
  } else {
    cdh.println("GPGGA: no fix");
  }

  GprmcData rmc;
  if (sensor.gps_get_gprmc(&rmc)) {
    cdh.printf("GPRMC utc=%.3f vel=%.2f heading=%.2f date=%s\n",
               rmc.utc_time, rmc.velocity, rmc.heading, rmc.date);
  } else {
    cdh.println("GPRMC: no fix");
  }

  delay(1000);
}
