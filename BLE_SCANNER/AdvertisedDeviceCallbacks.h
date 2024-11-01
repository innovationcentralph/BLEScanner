// MyAdvertisedDeviceCallbacks.h
#ifndef MYADVERTISEDDEVICECALLBACKS_H
#define MYADVERTISEDDEVICECALLBACKS_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "PWX_BLEDevice.h"

class AdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) override;
};

#endif // MYADVERTISEDDEVICECALLBACKS_H
