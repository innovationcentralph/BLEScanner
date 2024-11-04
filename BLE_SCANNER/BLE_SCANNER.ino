#include <Arduino.h>
#include <Wire.h>
#include "SensorData.h"
#include "I2CSlaveHandler.h"
#include "BLEScanHandler.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Setting up...");

    initializeBLEScan();  // Initialize BLE scanning

    // Initialize mutex
    sensorDataMutex = xSemaphoreCreateMutex();
    if (sensorDataMutex == NULL) {
        Serial.println("Failed to create sensor data mutex.");
    }

    // Create a FreeRTOS task for BLE scanning
    xTaskCreatePinnedToCore(
        bleScanTask,           // Task function
        "BLE Scan Task",       // Name of the task
        4096,                  // Stack size 
        NULL,                  // Parameter passed to the task
        1,                     // Task priority
        NULL,                  // Task handle - no need for now
        1                      // Run Core 1
    );

    // Create the I2C slave task
    xTaskCreatePinnedToCore(
        i2cSlaveTask,          // Task function
        "I2C Slave Task",      // Name of the task
        2048,                  // Stack size in bytes
        NULL,                  // Task input parameter
        2,                     // Priority of the task
        NULL,                  // Task handle
        1                      // Run Core 1
    );
}

void loop() {
    // Empty loop as tasks handle everything
}