#include <AlfredoCRSF.h>
#include <HardwareSerial.h>

const uint8_t ledPin = PF1;
const uint8_t currentPin = PA3;
const uint8_t voltagePin = PA2;

const int measurementPeriodMs = 100;
const int adcNumberOfSamples = 50;
float currentOffset = 0.0;

AlfredoCRSF crsf;

void setup() {
  pinMode(ledPin, OUTPUT_OPEN_DRAIN);
  pinMode(currentPin, INPUT);
  pinMode(voltagePin, INPUT);

  //Serial1.begin(115200);
  Serial1.begin(CRSF_BAUDRATE, SERIAL_8N1);
  crsf.begin(Serial1);
  analogReadResolution(12);
  delay(100);
  currentOffset = (analogReadVolt(currentPin) - 1.6956) / 0.0101;
}

void printDebug(float voltage, float current, float capacity, int measurementPeriodMs) {
  Serial1.print("voltage: ");
  Serial1.print(voltage);
  Serial1.print(" V, current: ");
  Serial1.print(current);
  Serial1.print(" A, capacity: ");
  Serial1.print(capacity);
  Serial1.print(" mAh, loopDuration: ");
  Serial1.print(measurementPeriodMs);
  Serial1.println(" ms");
}

float analogReadVolt(uint8_t pin) {
  uint32_t sumOfSamples = 0;
  analogRead(pin);
  for (int i = 0; i < adcNumberOfSamples; i++)
    sumOfSamples += analogRead(pin);
  return (sumOfSamples / adcNumberOfSamples) * 3.3f / 4095;
}

void loop() {
  float voltage = 0.0;
  float current = 0.0;
  static bool led = false;
  static float capacity = 0.0;
  static unsigned long loopMillisCounter = 0;

  if ((millis() - loopMillisCounter) >= measurementPeriodMs) {
    float voltage = analogReadVolt(voltagePin) * 21.0;
    float current = abs(((analogReadVolt(currentPin) - 1.6956) / 0.0101) - currentOffset);
    capacity += (current / (3.6 * (1000.0 / measurementPeriodMs)));
    loopMillisCounter = millis();
    //printDebug(voltage, current, capacity, measurementPeriodMs);
    sendRxBattery(voltage, current, capacity);
    digitalWrite(ledPin, led = !led);
  }

  crsf.update();
}

static void sendRxBattery(float voltage, float current, float capacity) {
  crsf_sensor_battery_t crsfBatt = { 0 };
  crsfBatt.voltage = htobe16((uint16_t)(voltage * 10.0));  //Volts
  crsfBatt.current = htobe16((uint16_t)(current * 10.0));  //Amps
  crsfBatt.capacity = htobe16((uint16_t)(capacity)) << 8;  //mAh
  crsf.queuePacket(CRSF_SYNC_BYTE, CRSF_FRAMETYPE_BATTERY_SENSOR, &crsfBatt, sizeof(crsfBatt));
}