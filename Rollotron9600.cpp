#include "Rollotron9600.h"

Rollotron9600::Rollotron9600(uint8_t pinUp, uint8_t pinDown) : pinUp(pinUp), pinDown(pinDown) {
  pinMode(this->pinUp, OUTPUT);
  pinMode(this->pinDown, OUTPUT);

  this->reset();
}

void Rollotron9600::reset(void) {
  digitalWrite(this->pinUp, LOW);
  digitalWrite(this->pinDown, LOW);
}

void Rollotron9600::up(void) {
  digitalWrite(this->pinDown, LOW);
  digitalWrite(this->pinUp, HIGH);
  this->resetMillis = millis() + Rollotron9600::BUTTON_RELEASE_TIME_MS;
}

void Rollotron9600::down(void) {
  digitalWrite(this->pinUp, LOW);
  digitalWrite(this->pinDown, HIGH);
  this->resetMillis = millis() + Rollotron9600::BUTTON_RELEASE_TIME_MS;
}

void Rollotron9600::stop(void) {
  // Not implemented
}

void Rollotron9600::loop() {
  if (millis() > this->resetMillis) {
    this->resetMillis = 0;
    this->reset();
  }
}

