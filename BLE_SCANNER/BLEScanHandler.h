// BLEScanHandler.h

#ifndef BLESCANHANDLER_H
#define BLESCANHANDLER_H

#include <BLEDevice.h>

extern BLEScan *pBLEScan;
extern int scanTime;

void initializeBLEScan();
void bleScanTask(void *parameter);

#endif // BLESCANHANDLER_H
