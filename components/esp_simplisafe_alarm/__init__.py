from esphome.components import binary_sensor
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = []
AUTO_LOAD = ["binary_sensor"]

esp_simplisafe_alarm_ns = cg.esphome_ns.namespace("espSimplisafeAlarm")
EspSimplisafeAlarm = esp_simplisafe_alarm_ns.class_("esp_simplisafe_alarm", cg.PollingComponent)

CONF_ARMED = "armed"
CONF_WARNING = "warning"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(EspSimplisafeAlarm),
        cv.Optional(CONF_ARMED): binary_sensor.binary_sensor_schema(),
        cv.Optional(CONF_WARNING): binary_sensor.binary_sensor_schema(),
    }
).extend(cv.polling_component_schema("15s"))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if CONF_ARMED in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_ARMED])
        cg.add(var.set_armed_sensor(sens))

    if CONF_WARNING in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_WARNING])
        cg.add(var.set_warning_sensor(sens))