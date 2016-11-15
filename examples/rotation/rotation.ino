#include "mpu9250.h"

//Questo sketch mostra:
// - api libreria
// - calibrazione in stato di quiete
// - integrazione numerica

//Questo sketch usa il 20% della program memory ...
//La frequenza di integrazione è circa 700Hz
//La stampa avviene a circa 20Hz

//Il dato in output è la rotazione attorno all'asse Y

//rimuovere la seguente riga per avere dati plottabili da Arduino IDE
#define STAMPA_TEMPO

MPU9250 imu;
float bias;

void setup(){
  Serial.begin(115200);
  Wire.begin();

  while(!imu.online()){
    delay(1000);
    //finchè non si collega il sensore non fare niente
  }

  // Si suppone che il dispositivo rimanga immobile
  // per i primi 1 o 2 sec
  long sumgy = 0;
  for (int i=0; i < 2000; i++){
    imu.updateGyr();
    sumgy+=imu.gyr[1];
    delay(1);
  }
  bias = (float)sumgy / 1000;
}

long  lastPrint  = 0; //per limitare la frequenza di stampa
long  lastIntegr = 0; //per calcolare il dt
float pos        = 0; //valore integrato
float scale = 0.0001;

void loop(){
  if (imu.newData())
  {
    imu.updateAcc();/*
    pos += scale*(( (float)imu.gyr[1]-bias )*( micros()-lastIntegr ));
    lastIntegr = micros();*/
    if (1)//(millis()-lastPrint > 50)
    {
      #ifdef STAMPA_TEMPO
      Serial.print(millis());
      Serial.print('\t');
      #endif

      //ATTENZIONE: unità di misura ignota
      Serial.print(imu.acc[2]);

      Serial.print('\n');
      lastPrint = millis();
    }
  }
}

/* Il resto di questo file rimane da studiare

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
