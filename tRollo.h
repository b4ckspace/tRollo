#include "WindowBlindActor.h"
#include "Rademacher7105.h"
#include "Rollotron9600.h"

//#define HACKCENTER
#define LOUNGE

#if defined(HACKCENTER)
#define LOCATION "hackcenter"
static uint8_t mac[] = { 0xCA, 0xFF, 0xEB, 0xAB, 0xEE, 0xA0 };
#elif defined(LOUNGE)
#define LOCATION "lounge"
static uint8_t mac[] = { 0xCA, 0xFF, 0xEB, 0xAB, 0xEE, 0xA2 };
#endif

#define HOSTNAME "trollo-" LOCATION

void mqttCallback(char* topic, byte* payload, unsigned int length);

#define MQTT_HOST "mqtt.core.bckspc.de"
#define MQTT_PORT 1883
#define MQTT_MAX_CONNECT_RETRY 42

const char* MQTT_TOPIC_DELIMITER = "/";

const char* MQTT_TOPIC_TROLLO = "actors/trollo/" LOCATION "/#";
const char* MQTT_TOPIC_STATE = "state/trollo/" LOCATION;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
  char* identifier;
  WindowBlindActor* actor;
} t_windowBlinds;

#ifdef LOUNGE
t_windowBlinds windowBlinds[] = {
  {"right",  new Rademacher7105(24, 22)},
  {"center", new Rademacher7105(28, 26)},
  {"left",   new Rademacher7105(32, 30)}
};
#endif

#ifdef HACKCENTER
t_windowBlinds windowBlinds[] = {
  {"left",  new Rollotron9600(13, 12)},
  {"right", new Rollotron9600(8, 9)}
};
#endif

