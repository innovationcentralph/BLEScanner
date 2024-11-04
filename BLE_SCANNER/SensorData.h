#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <stdint.h>
#include <stdbool.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

// Define device types as an enum
enum DeviceType {
  MOKO_S03D,
  MOKO_S01P,
  MOKO_H4PRO,
  MOKO_S02R,
  UNKNOWN_DEVICE
};


// Struct for MOKO_S03D device data (Open/Close state and battery)
typedef struct MokoS03DData {
  bool isOpen;            // true = Open, false = Close
  uint16_t battery;       // Battery level in mV
};

// Struct for MOKO_S01P device data (Motion state and battery)
typedef struct MokoS01PData {
  bool isMotionDetected;  // true = Motion, false = No Motion
  uint16_t battery;       // Battery level in mV
};

// Struct for MOKO_H4PRO device data (Temperature, Humidity, and battery)
typedef struct MokoH4ProData {
  float temperature;      // Temperature in °C
  float humidity;         // Humidity in %
  uint16_t battery;       // Battery level in mV
};

// Struct for MOKO SO2R device data
typedef struct MokoTOFData {
    uint16_t battery;
    uint16_t distance;
};

// Union to hold data for any device type
union DeviceSpecificData {
  MokoS03DData s03dData;
  MokoS01PData s01pData;
  MokoH4ProData h4ProData;
};



// Main struct to hold device data along with its type
struct DeviceData {
  DeviceType deviceType;          // Type of the device or site location or device set -> not used for now
  DeviceSpecificData deviceData;  // Device-specific data
};

// Global instance of DeviceData
//extern DeviceData deviceData;
extern MokoS03DData s03dData;
extern MokoS01PData s01pData;
extern MokoH4ProData h4ProData;
extern MokoTOFData tofData;
extern SemaphoreHandle_t sensorDataMutex;


#endif // SENSORDATA_H