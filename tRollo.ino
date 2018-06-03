#include <Ethernet.h>
#include <PubSubClient.h>

#include "tRollo.h"

EthernetClient ethernetClient;
PubSubClient mqttClient(MQTT_HOST, MQTT_PORT, mqttCallback, ethernetClient);

uint8_t mqttRetryCounter = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(10, OUTPUT); // set the SS pin as an output (necessary!)
  digitalWrite(10, HIGH); // but turn off the W5100 chip!
  
  Ethernet.begin(mac);
  Serial.println(Ethernet.localIP());
}

WindowBlindActor* getWindowBlindActorByIdentifier(char* identifier) {
  for (uint8_t i = 0; i < ARRAY_SIZE(windowBlinds); i++) {
    if (strncmp(identifier, windowBlinds[i].identifier, strlen(identifier)) == 0) {
      return windowBlinds[i].actor;
    }
  }

  return NULL;
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {  
  char* identifier = topic + strlen(MQTT_TOPIC_TROLLO) - 1;
  
  WindowBlindActor* actor = getWindowBlindActorByIdentifier(identifier);
  if (actor == NULL) {
    Serial.print("Can't find actor: ");
    Serial.println(identifier);
    return;
  }

  char* direction = (char*) payload;
  if (strncasecmp(direction, "UP", length) == 0) {
    actor->up();
  } else if (strncasecmp(direction, "DOWN", length) == 0) {
    actor->down();
  } else if (strncasecmp(direction, "STOP", length) == 0) {
    actor->stop();
  } else {
    Serial.println("Invalid command!");
  }
}

void mqttConnect() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect(HOSTNAME, MQTT_TOPIC_STATE, 1, true, "disconnected")) {
      mqttClient.subscribe(MQTT_TOPIC_TROLLO);
      mqttClient.publish(MQTT_TOPIC_STATE, "connected", true);
      mqttRetryCounter = 0;

      Serial.println("MQTT Connected");
    } else {
      if (mqttRetryCounter++ > MQTT_MAX_CONNECT_RETRY) {
        asm volatile ("jmp 0"); // RESET
      }

      delay(2000);
    }
  }
}

void loop() {
  mqttConnect();
  mqttClient.loop();

  for (uint8_t i = 0; i < ARRAY_SIZE(windowBlinds); i++) {
    windowBlinds[i].actor->loop();
  }

  Ethernet.maintain();
}

