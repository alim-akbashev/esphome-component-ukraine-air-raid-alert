#include "esphome/core/log.h"
#include "air_raid_alert.h"

namespace esphome {
namespace air_raid_alert {

  void AirRaidAlert::update() {
#if defined(USE_ESP32)
    this->http.begin(this->endpoint_);
#elif defined(USE_ESP8266)
    this->http.begin(*this->get_wifi_client_(), this->endpoint_);
#endif
    this->http.addHeader("Authorization", this->token_);
    this->http.addHeader("Accept", "application/json");
    int http_code = this->http.GET();
    const char *body = http.getString().c_str();
    ESP_LOGD("air_raid_alert", "Response code = %d", http_code);

    if (http_code != 200) {
      ESP_LOGW("air_raid_alert", "Error response is = %s", body);
      return;
    }

    ESP_LOGD("air_raid_alert", "Response is %s", body);

    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, body);
    if (error) {
      ESP_LOGW("air_raid_alert", "Deserialization error %s", error.f_str());
      return;
    }
    size_t s = doc[0]["activeAlerts"].as<JsonArray>().size();
    ESP_LOGD("air_raid_alert", "activeAlerts.size() = %d", s);
    publish_state(s > 0);
  }

#ifdef USE_ESP8266
std::shared_ptr<BearSSL::WiFiClientSecure> AirRaidAlert::get_wifi_client_() {
  if (this->wifi_client_secure_ == nullptr) {
    this->wifi_client_secure_ = std::make_shared<BearSSL::WiFiClientSecure>();
    this->wifi_client_secure_->setInsecure();
    this->wifi_client_secure_->setBufferSizes(512, 512);
  }
  return this->wifi_client_secure_;
}
#endif

}
}
