#ifndef __ROLLOTRON_9600_H__
#define __ROLLOTRON_9600_H__

#include "Arduino.h"
#include "WindowBlindActor.h"

class Rollotron9600 final : public virtual WindowBlindActor {

    static const uint16_t BUTTON_RELEASE_TIME_MS = 200;

    private:
          uint8_t pinUp;
          uint8_t pinDown;
          unsigned long resetMillis;

          void reset();

    public:
          Rollotron9600(uint8_t pinUp, uint8_t pinDown);
            
          void stop();
          void up();
          void down();
          void loop();

};

#endif
