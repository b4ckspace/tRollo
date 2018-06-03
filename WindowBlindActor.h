#ifndef __WINDOW_BLIND_ACTOR_H__
#define __WINDOW_BLIND_ACTOR_H__

class WindowBlindActor {
  public: 
    virtual void stop() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void loop() = 0;
};

#endif
