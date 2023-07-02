import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL
from esphome.core import CORE

DEPENDENCIES = ["network"]

CONF_TOKEN = "token"
CONF_REGION_ID = "region_id"

air_raid_alert_ns = cg.esphome_ns.namespace('air_raid_alert')

AirRaidAlert = air_raid_alert_ns.class_('AirRaidAlert', binary_sensor.BinarySensor, cg.PollingComponent)

CONFIG_SCHEMA = binary_sensor.BINARY_SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(AirRaidAlert),
    cv.Required(CONF_TOKEN): cv.string,
    cv.Required(CONF_REGION_ID): cv.positive_int,
}).extend(cv.polling_component_schema("60s"))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield binary_sensor.register_binary_sensor(var, config)

    if CONF_UPDATE_INTERVAL in config:
        cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_token(config[CONF_TOKEN]))
    cg.add(var.set_region_id(config[CONF_REGION_ID]))

    if CORE.is_esp32:
        cg.add_library("WiFiClientSecure", None)
        cg.add_library("HTTPClient", None)
    if CORE.is_esp8266:
        cg.add_library("ESP8266WiFi", None)
        cg.add_library("ESP8266HTTPClient", None)