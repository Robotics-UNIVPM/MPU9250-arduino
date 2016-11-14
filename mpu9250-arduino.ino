#include "mpu9250.h"

//Questo esempio fa solo uso di funzioni mpu9250 ricostruite da noi
//Riesce a leggere una terna grezza dell'accelerometro a oltre 500Hz

MPU9250 imu;

void setup(){
  Serial.begin(4000000); //4MBaud non sono necessari in realtà
  Wire.begin();

  while(!imu.online()){
    Serial.println("Device missing");
    delay(1000);
  }
}
void loop(){
  if (imu.newData())
  {
    imu.updateGyr();
    Serial.print(millis());
    Serial.print('\t');
    Serial.print(imu.gyr[0]);
    Serial.print('\t');
    Serial.print(imu.gyr[1]);
    Serial.print('\t');
    Serial.println(imu.gyr[2]);
  }
}
/*

void setup()
{
  Wire.begin();
  // TWBR = 12;  // 400 kbit/sec I2C speed
  Serial.begin(115200);


}

void loop()
{

  if (imu.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {
    imu.readAccelData(imu.accelCount);  // Read the x/y/z adc values
    imu.getAres();

    // Now we'll calculate the accleration value into actual g's
    // This depends on scale being set
    imu.ax = (float)imu.accelCount[0]*imu.aRes; // - accelBias[0];
    imu.ay = (float)imu.accelCount[1]*imu.aRes; // - accelBias[1];
    imu.az = (float)imu.accelCount[2]*imu.aRes; // - accelBias[2];

    imu.readGyroData(imu.gyroCount);  // Read the x/y/z adc values
    imu.getGres();

    // Calculate the gyro value into actual degrees per second
    // This depends on scale being set
    imu.gx = (float)imu.gyroCount[0]*imu.gRes;
    imu.gy = (float)imu.gyroCount[1]*imu.gRes;
    imu.gz = (float)imu.gyroCount[2]*imu.gRes;

    imu.readMagData(imu.magCount);  // Read the x/y/z adc values
    imu.getMres();
    // User environmental x-axis correction in milliGauss, should be
    // automatically calculated
    imu.magbias[0] = +470.;
    // User environmental x-axis correction in milliGauss TODO axis??
    imu.magbias[1] = +120.;
    // User environmental x-axis correction in milliGauss
    imu.magbias[2] = +125.;

    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental
    // corrections
    // Get actual magnetometer value, this depends on scale being set
    imu.mx = (float)imu.magCount[0]*imu.mRes*imu.magCalibration[0] -
               imu.magbias[0];
    imu.my = (float)imu.magCount[1]*imu.mRes*imu.magCalibration[1] -
               imu.magbias[1];
    imu.mz = (float)imu.magCount[2]*imu.mRes*imu.magCalibration[2] -
               imu.magbias[2];
  } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)


  float g = imu.ax*imu.ax+imu.ay*imu.ay+imu.az*imu.az;
  Serial.println(g);

}
/**/
