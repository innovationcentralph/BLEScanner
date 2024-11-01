// PWX_BLEDevice.h
#ifndef PWX_BLEDEVICE_H
#define PWX_BLEDEVICE_H

#include <BLEDevice.h>
#include "DeviceType.h"

// Define a struct for each device in the whitelist
struct PWX_BLEDevice {
  esp_bd_addr_t macAddress;
  const char* deviceName;
  DeviceType deviceType;
};

// Define whitelist as an array of PWX_BLEDevice structs
extern PWX_BLEDevice whitelist[];
extern const int whitelistSize;

// Function to find the device info based on MAC address
const PWX_BLEDevice* getDeviceInfo(const esp_bd_addr_t macAddress);

// Function to check if the MAC address is in the whitelist
bool isWhitelisted(const esp_bd_addr_t macAddress);

#endif // PWX_BLEDEVICE_H
