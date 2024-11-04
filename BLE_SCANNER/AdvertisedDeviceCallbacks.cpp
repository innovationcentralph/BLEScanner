// MyAdvertisedDeviceCallbacks.cpp
#include "AdvertisedDeviceCallbacks.h"
#include "PWX_BLEDevice.h"
#include "ParsingFunctions.h"

void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
  const esp_bd_addr_t *macAddress = advertisedDevice.getAddress().getNative();  // Get MAC as esp_bd_addr_t array

  if (isWhitelisted(*macAddress)) {
    // Get the device info from the whitelist
    const PWX_BLEDevice* device = getDeviceInfo(*macAddress);

    Serial.print("Device MAC Address (Whitelisted): ");
    for (int i = 0; i < ESP_BD_ADDR_LEN; i++) {
      Serial.printf("%02X", device->macAddress[i]);
      if (i < ESP_BD_ADDR_LEN - 1) Serial.print(":");
    }
    Serial.printf("\n");

    Serial.print("Device Name: ");
    Serial.println(device->deviceName);

    uint8_t* payload = advertisedDevice.getPayload();
    size_t payloadLength = advertisedDevice.getPayloadLength();
    // Print the device type
    Serial.print("Device Type: ");
    switch (device->deviceType) {
      case MOKO_S03D:
        Serial.println("MOKO S03D");
        parseMokoS03D(payload, payloadLength);
        break;
      case MOKO_S01P:
        Serial.println("MOKO S01P");
        parseMokoS01P(payload, payloadLength);
        break;
      case MOKO_H4PRO:
        Serial.println("MOKO H4 PRO");
        parseMokoH4Pro(payload, payloadLength);
      case MOKO_S02R:
        Serial.println("MOKO S02R");
        parseMokoTOF(payload, payloadLength);
        break;
      default:
        Serial.println("Unknown device type. No specific parsing function available.");
        break;
    }

    Serial.println("\n\n");

  }
}
