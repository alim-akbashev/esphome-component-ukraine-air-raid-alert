#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <WiFiClientSecure.h>
#include "ESP8266HTTPClient.h"

namespace esphome {
namespace air_raid_alert {

class AirRaidAlert : public PollingComponent, public binary_sensor::BinarySensor {
 public:
    float get_setup_priority() const override { return esphome::setup_priority::AFTER_CONNECTION; }

    void setup() override {
      snprintf_P(
        this->endpoint_,
        sizeof(this->endpoint_),
        PSTR("https://api.ukrainealarm.com/api/v3/alerts/%d"),
        this->region_id_
      );
    }

    void update() override;

    void set_token(const char *token) { this->token_ = token; }
    void set_region_id(int region_id) { this->region_id_ = region_id; }

  protected:
    const char *token_{nullptr};
    int region_id_;
    char endpoint_[64];

#ifdef USE_ESP8266
  std::shared_ptr<BearSSL::WiFiClientSecure> wifi_client_secure_;
  std::shared_ptr<BearSSL::WiFiClientSecure> get_wifi_client_();
#endif
    HTTPClient http = HTTPClient();
    WiFiClientSecure wifi = BearSSL::WiFiClientSecure();
};

}
}