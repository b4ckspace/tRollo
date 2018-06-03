#ifndef __RADEMACHER_7105_H__
#define __RADEMACHER_7105_H__

#include "Arduino.h"
#include "WindowBlindActor.h"

class Rademacher7105 final : public virtual WindowBlindActor {

    static const uint16_t BUTTON_RELEASE_TIME_MS = 2000;

    private:
          uint8_t pinUp;
          uint8_t pinDown;
          unsigned long resetMillis;

          void reset();

    public:
          Rademacher7105(uint8_t pinUp, uint8_t pinDown);
            
          void stop();
          void up();
          void down();
          void loop();

};

#endif
