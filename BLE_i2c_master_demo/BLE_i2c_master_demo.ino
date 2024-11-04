#include <Wire.h>

#define I2C_SLAVE_ADDRESS 0x42  // Address of the I2C slave device

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Initialize I2C as master
}

void loop() {
  Serial.println("\n\n Requesting data from I2C slave...");

  // Request 16 bytes from the slave
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 20);

  // Wait until the 16 bytes are received
  if (Wire.available() == 20) {
    uint8_t data[20];
    for (int i = 0; i < 20; i++) {
      data[i] = Wire.read();  // Read each byte into the data array
    }

    // ---- MOKO_S03D (Door Sensor) ----
    uint8_t doorStatus = data[0];
    uint16_t doorBattery = (data[1] << 8) | data[2];

    Serial.print("Door Status: ");
    Serial.println(doorStatus ? "Open" : "Close");
    Serial.print("Door Battery Voltage: ");
    Serial.print(doorBattery);
    Serial.println(" mV");

    // ---- MOKO_S01P (PIR Sensor) ----
    uint8_t motionStatus = data[3];
    uint16_t pirBattery = (data[4] << 8) | data[5];

    Serial.print("Motion Status: ");
    Serial.println(motionStatus ? "Motion Detected" : "No Motion");
    Serial.print("PIR Battery Voltage: ");
    Serial.print(pirBattery);
    Serial.println(" mV");

    // ---- MOKO_H4PRO (Temperature, Humidity, and Battery) ----
    float temperature;
    memcpy(&temperature, &data[6], 4);

    float humidity;
    memcpy(&humidity, &data[10], 4);

    uint16_t thBattery = (data[14] << 8) | data[15];

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.printf("T&H Battery Voltage: %02X %02X:", data[14], data[15]);
    Serial.print(thBattery);
    Serial.println(" mV");

      // ---- MOKO TOF (Ranging Sensor) ----
    uint16_t tofBattery = (data[17] << 8) | data[16];
    uint16_t rangingDistance = (data[19] << 8) | data[18];

    Serial.print("TOF Battery Voltage: ");
    Serial.print(tofBattery);
    Serial.println(" mV");

    Serial.print("Ranging Distance: ");
    Serial.print(rangingDistance);
    Serial.println(" mm");



  } else {
    Serial.println("Failed to read data from I2C slave.");
  }

  delay(2000);  // Request data every 2 seconds
}