#include "ParsingFunctions.h"
#include "SensorData.h"

void parseMokoS03D(uint8_t* payload, size_t payloadLength) {
  Serial.printf("[%lu ms] Parsing MOKO S03D data...\n", millis());

  if (xSemaphoreTake(sensorDataMutex, portMAX_DELAY) == pdTRUE) {
    uint8_t deviceStatus = payload[9];
    s03dData.isOpen = ((deviceStatus >> 3) & 0x01);

    Serial.printf("[%lu ms] Updated Door Status: %s\n", millis(), s03dData.isOpen ? "Open" : "Close");

    s03dData.battery = (payload[23] << 8) | payload[24];
    Serial.printf("[%lu ms] Updated Door Battery Voltage (mV): %d\n", millis(), s03dData.battery);

    xSemaphoreGive(sensorDataMutex);
  } else {
    Serial.println("Failed to acquire mutex for parseMokoS03D.");
  }
}

// Parsing function for MOKO_S01P devices
void parseMokoS01P(uint8_t* payload, size_t payloadLength) {
  Serial.println("Parsing MOKO S03D data...");
  // for (size_t i = 0; i < payloadLength; i++) {
  //   Serial.printf("%02X ", payload[i]);
  // }
  // Serial.println();

  if (xSemaphoreTake(sensorDataMutex, portMAX_DELAY) == pdTRUE) {
    uint8_t deviceStatus = payload[9];
    s01pData.isMotionDetected = (deviceStatus & 0x01); // true = Motion, false = No Motion

    // Debug output
    Serial.printf("Motion Status: %s \t", s01pData.isMotionDetected ? "Motion Detected" : "No Motion");

    // Bytes 23-24: Battery Voltage
    s01pData.battery = (payload[23] << 8) | payload[24];
    Serial.printf("Battery Voltage (mV): %d\n", s01pData.battery);
    
    // Release the mutex
    xSemaphoreGive(sensorDataMutex);
  }else {
    Serial.println("Failed to acquire mutex for parseMokoS03D.");
  }


}

// Parsing function for MOKO_H4PRO devices
void parseMokoH4Pro(uint8_t* payload, size_t payloadLength) {
  Serial.println("Parsing MOKO H4 PRO data...");
  // for (size_t i = 0; i < payloadLength; i++) {
  //   Serial.printf("%02X ", payload[i]);
  // }
  // Serial.println();

  if (xSemaphoreTake(sensorDataMutex, portMAX_DELAY) == pdTRUE) {
    // Byte 19: Device Type
    uint8_t deviceType = payload[19];
    if (deviceType == 0x02) {
      //deviceData.deviceType = MOKO_H4PRO;

      // Byte 13-14: Sampling Temperature
      int16_t rawTemperature = (payload[13] << 8) | payload[14];
      h4ProData.temperature = rawTemperature / 10.0;  // °C

      // Byte 15-16: Sampling Humidity
      uint16_t rawHumidity = (payload[15] << 8) | payload[16];
      h4ProData.humidity = rawHumidity / 10.0;  // %

      // Byte 17-18: Battery Voltage
      h4ProData.battery = (payload[17] << 8) | payload[18];

      // Debug output
      Serial.printf("Temperature: %.1f °C\t",     h4ProData.temperature);
      Serial.printf("Humidity: %.1f %%\t",        h4ProData.humidity);
      Serial.printf("Battery Voltage (mV): %d\n", h4ProData.battery);
    } else {
      Serial.println("Device Type / Payload: Not equipped with T&H sensor");
    }
    // Release the mutex
    xSemaphoreGive(sensorDataMutex);
  }else {
    Serial.println("Failed to acquire mutex for parseMokoS03D.");
  }

}

// Parsing function for MOKO TOF devices
void parseMokoTOF(uint8_t* payload, size_t payloadLength) {
    Serial.println("Parsing MOKO TOF data...");
  
    for (size_t i = 0; i < payloadLength; i++) {
      Serial.printf("%02X ", payload[i]);
    }
    Serial.println();

    if (xSemaphoreTake(sensorDataMutex, portMAX_DELAY) == pdTRUE) {
        // Byte 18: Sub Type - Verify if it's a TOF Sensor
        uint8_t subType = payload[18];
        if (subType == 0x01) {
            // Byte 9-10: Tag Battery
            uint16_t batteryVoltage = (payload[10] << 8) | payload[9];
            tofData.battery = batteryVoltage;

            // Byte 14-15: Ranging Distance
            uint16_t rangingDistance = (payload[15] << 8) | payload[14];
            tofData.distance = rangingDistance;

            // Debug output
            Serial.printf("Battery Voltage (mV): %d\n", tofData.battery);
            Serial.printf("Ranging Distance (mm): %d\n", tofData.distance);
        } else {
            Serial.println("Sub Type / Payload: Not a TOF Sensor");
        }
        
        // Release the mutex
        xSemaphoreGive(sensorDataMutex);
    } else {
        Serial.println("Failed to acquire mutex for parseMokoTOF.");
    }
}
