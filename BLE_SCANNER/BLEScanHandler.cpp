// BLEScanHandler.cpp

#include "BLEScanHandler.h"
#include "AdvertisedDeviceCallbacks.h"
#include <Arduino.h>

// BLEScan instance and scan time setting
BLEScan *pBLEScan;
int scanTime = 5;  // Scan time in seconds

void initializeBLEScan() {
    Serial.println("Initializing BLE Scan...");

    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();  // Create a new scan instance
    pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);  // Active scan uses more power but gets results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);  // Window should be less than or equal to interval
}

// BLE scan task that runs in FreeRTOS
void bleScanTask(void *parameter) {
    while (true) {
        BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);
        Serial.print("Devices found: ");
        Serial.println(foundDevices->getCount());
        Serial.println("Scan done!");
        pBLEScan->clearResults();  // Clear results to free up memory
        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay for 2 seconds
    }
}
