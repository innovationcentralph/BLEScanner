#include "SensorData.h"

// Initialize the global deviceData instance with UNKNOWN_DEVICE type
//DeviceData deviceData = {UNKNOWN_DEVICE};

MokoS03DData s03dData;
MokoS01PData s01pData;
MokoH4ProData h4ProData;
MokoTOFData tofData;

SemaphoreHandle_t sensorDataMutex;