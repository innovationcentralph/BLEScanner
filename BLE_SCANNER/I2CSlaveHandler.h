// I2CSlaveHandler.h

#ifndef I2CSLAVEHANDLER_H
#define I2CSLAVEHANDLER_H

#include <Arduino.h>
#include <Wire.h>
#include "SensorData.h"  // Include the sensor data definitions

#define I2C_SLAVE_ADDRESS 0x42  // Define the I2C address for the slave

// Declare the I2C functions
void onI2CRequest();
void i2cSlaveTask(void *parameter);

#endif  // I2CSLAVEHANDLER_H
