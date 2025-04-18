import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import UNIT_EMPTY, ICON_EMPTY


CODEOWNERS = ["@abriggs"]
DEPENDENCIES = [ ]
AUTO_LOAD = [ ]
MULTI_CONF = True

# C++ namespace
ns = cg.esphome_ns.namespace("espSimplisafeAlarm")
esp_simplisafe_alarm = ns.class_("esp_simplisafe_alarm", cg.PollingComponent)

CONFIG_SCHEMA = cv.sensor_schema({
    cv.GenerateID(): cv.declare_id(esp_simplisafe_alarm),
    # Schema definition, containing the options available for the component
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    # Code generation
    pass