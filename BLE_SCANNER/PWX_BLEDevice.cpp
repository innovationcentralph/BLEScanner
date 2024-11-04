// PWX_BLEDevice.cpp
#include "PWX_BLEDevice.h"

// Define whitelist as an array of PWX_BLEDevice structs
PWX_BLEDevice whitelist[] = {
  { {0xCF, 0x37, 0x67, 0xC6, 0xE4, 0x6A}, "MOKO DOOR ENTRANCE" , MOKO_S03D},
  { {0xCA, 0x4C, 0x59, 0xDB, 0xB9, 0xF1}, "MOKO RHTEMP"   , MOKO_H4PRO },
  { {0xF9, 0xB3, 0x2C, 0x5A, 0xB9, 0x94}, "MOKO PIR", MOKO_S01P },
  { {0xD8, 0x07, 0x0B, 0x34, 0xC3, 0xDA}, "MOKO TOF", MOKO_S02R }
};

const int whitelistSize = sizeof(whitelist) / sizeof(whitelist[0]);

// Function to find the device info based on MAC address
const PWX_BLEDevice* getDeviceInfo(const esp_bd_addr_t macAddress) {
  for (int i = 0; i < whitelistSize; i++) {
    bool match = true;
    for (int j = 0; j < ESP_BD_ADDR_LEN; j++) {
      if (whitelist[i].macAddress[j] != macAddress[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      return &whitelist[i];  // Return pointer to the matched device
    }
  }
  return nullptr;  // Return nullptr if no match found
}

// Function to check if the MAC address is in the whitelist
bool isWhitelisted(const esp_bd_addr_t macAddress) {
  return getDeviceInfo(macAddress) != nullptr;
}
