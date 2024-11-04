// I2CSlaveHandler.cpp

#include "I2CSlaveHandler.h"

// Function to handle I2C requests from the master
void onI2CRequest() {
    Serial.printf("[%lu ms] I2C Master has requested data.\n", millis());

    if (xSemaphoreTake(sensorDataMutex, portMAX_DELAY) == pdTRUE) {
        uint8_t data[20];

        // ---- MOKO_S03D (Door Sensor) ----
        data[0] = s03dData.isOpen ? 1 : 0;
        data[1] = s03dData.battery >> 8;
        data[2] = s03dData.battery & 0xFF;

        // ---- MOKO_S01P (PIR Sensor) ----
        data[3] = s01pData.isMotionDetected ? 1 : 0;
        data[4] = s01pData.battery >> 8;
        data[5] = s01pData.battery & 0xFF;

        // ---- MOKO_H4PRO (Temperature, Humidity, and Battery) ----
        memcpy(&data[6], &h4ProData.temperature, 4);
        memcpy(&data[10], &h4ProData.humidity, 4);
        data[14] = h4ProData.battery >> 8;
        data[15] = h4ProData.battery & 0xFF;

        // ---- MOKO TOF (Ranging Sensor) ----
        data[16] = tofData.battery & 0xFF;        // Low byte for battery
        data[17] = tofData.battery >> 8;          // High byte for battery
        data[18] = tofData.distance & 0xFF;       // Low byte for distance
        data[19] = tofData.distance >> 8;         // High byte for distance

        xSemaphoreGive(sensorDataMutex);
        Wire.write(data, 20);
    } else {
        Serial.println("Failed to acquire mutex for onI2CRequest.");
    }
}

// I2C task that sets up slave mode and listens for requests
void i2cSlaveTask(void *parameter) {
    Wire.begin(I2C_SLAVE_ADDRESS);    // Initialize I2C in slave mode with the specified address
    Wire.onRequest(onI2CRequest);     // Register the request callback function

    Serial.println("I2C Slave Task Initialized.");

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Task delay to prevent tight loop
    }
}
