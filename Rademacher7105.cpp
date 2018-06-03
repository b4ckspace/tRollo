#include "Rademacher7105.h"

Rademacher7105::Rademacher7105(uint8_t pinUp, uint8_t pinDown) : pinUp(pinUp), pinDown(pinDown) {
  pinMode(this->pinUp, OUTPUT);
  pinMode(this->pinDown, OUTPUT);

  this->reset();
}

void Rademacher7105::reset(void) {
  digitalWrite(this->pinUp, LOW);
  digitalWrite(this->pinDown, LOW);
}

void Rademacher7105::up(void) {
  digitalWrite(this->pinDown, LOW);
  digitalWrite(this->pinUp, HIGH);
  this->resetMillis = millis() + Rademacher7105::BUTTON_RELEASE_TIME_MS;
}

void Rademacher7105::down(void) {
  digitalWrite(this->pinUp, LOW);
  digitalWrite(this->pinDown, HIGH);
  this->resetMillis = millis() + Rademacher7105::BUTTON_RELEASE_TIME_MS;
}

void Rademacher7105::stop(void) {
  // Not implemented
}

void Rademacher7105::loop() {
  if (millis() > this->resetMillis) {
    this->resetMillis = 0;
    this->reset();
  }
}

