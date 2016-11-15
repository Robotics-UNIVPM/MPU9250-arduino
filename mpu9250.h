#ifndef _MPU9250_H_
#define _MPU9250_H_

#include <Wire.h>
#include "mpu9250-registers.h"

struct vec{
  float x,y,z;
};

class MPU9250 {

public:
  bool newData();
  bool online();

  void updateAcc();
  void updateGyr();
  void updateAll();

  int16_t acc[3]; // unit depends on set scale
  int16_t gyr[3]; // unit depends on set scale


  vec facc(); // implementazione da completare
  vec fgyr(); // implementazione da completare


private:
  void writeByte(uint8_t, uint8_t);
  uint8_t readByte(uint8_t);
  void readBytes(uint8_t, uint8_t, uint8_t *);

  float aRes, gRes;
};
/*

  // Set initial input parameters
  enum Ascale {
    AFS_2G = 0,
    AFS_4G,
    AFS_8G,
    AFS_16G
  };

  enum Gscale {
    GFS_250DPS = 0,
    GFS_500DPS,
    GFS_1000DPS,
    GFS_2000DPS
  };

  // Specify sensor full scale
  uint8_t Gscale = GFS_250DPS;
  uint8_t Ascale = AFS_2G;

  // Scale resolutions per LSB for the sensors

  // Bias corrections for gyro and accelerometer
  float gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0};
  float SelfTest[6];

public:
  void init();

  void getGres();
  void getAres();
  void calibrate(float * gyroBias, float * accelBias);
  void MPU9250SelfTest(float * destination);

};  // class MPU9250


/**/
#endif // _MPU9250_H_
