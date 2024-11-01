#include "ParsingFunctions.h"

// Parsing function for MOKO_S03D devices
void parseMokoS03D(uint8_t* payload, size_t payloadLength) {
  Serial.println("Parsing MOKO S03D data...");
  // for (size_t i = 0; i < payloadLength; i++) {
  //   Serial.printf("%02X ", payload[i]);
  // }
  // Serial.println();

  // Byte 9: Device Status
  uint8_t deviceStatus = payload[9];
  String doorStatus = ((deviceStatus >> 3) & 0x01) ? "Open" : "Close";
  Serial.printf("Door Status: %s \t", doorStatus); 

  // Bytes 23-24: Battery Voltage
  uint16_t batteryVoltage = (payload[23] << 8) | payload[24];
  Serial.printf("Battery Voltage (mV): %d", batteryVoltage);

}

// Parsing function for MOKO_S01P devices
void parseMokoS01P(uint8_t* payload, size_t payloadLength) {
  Serial.println("Parsing MOKO S03D data...");
  // for (size_t i = 0; i < payloadLength; i++) {
  //   Serial.printf("%02X ", payload[i]);
  // }
  // Serial.println();

  // Byte 9: Device Status
  uint8_t deviceStatus = payload[9];
  String pirSensorDetectionStatus = (deviceStatus & 0x01) ? "1" : "0";
  Serial.printf("Motion Status: %s \t", pirSensorDetectionStatus); 

  // Bytes 23-24: Battery Voltage
  uint16_t batteryVoltage = (payload[23] << 8) | payload[24];
  Serial.printf("Battery Voltage (mV): %d", batteryVoltage);
}

// Parsing function for MOKO_H4PRO devices
void parseMokoH4Pro(uint8_t* payload, size_t payloadLength) {
  Serial.println("Parsing MOKO H4 PRO data...");
  // for (size_t i = 0; i < payloadLength; i++) {
  //   Serial.printf("%02X ", payload[i]);
  // }
  // Serial.println();

  // Byte 19: Device Type
  uint8_t deviceType = payload[19];
  Serial.print("Device Type: 0x");
  Serial.println(deviceType, HEX);

  // Check if the device type is 0x02 (T&H sensor)
  if (deviceType == 0x02) {

    // Byte 13-14: Sampling Temperature
    int16_t rawTemperature = (payload[13] << 8) | payload[14];
    float temperature = rawTemperature / 10.0;  // 0.1°C per digit
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Byte 15-16: Sampling Humidity
    uint16_t rawHumidity = (payload[15] << 8) | payload[16];
    float humidity = rawHumidity / 10.0;  // 0.1% per digit
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Byte 17-18: Battery Voltage
    uint16_t batteryVoltage = (payload[17] << 8) | payload[18];
    Serial.print("Battery Voltage (mV): ");
    Serial.println(batteryVoltage);

  } else {
    Serial.println("Device Type / Payload: Not equipped with T&H sensor");
  }
  
}
