import esphome.config_validation as cv
import esphome.codegen as cg

CODEOWNERS = ["@abriggs"]
DEPENDENCIES = [ ]
AUTO_LOAD = [ ]
MULTI_CONF = True

# C++ namespace
ns = cg.esphome_ns.namespace("espSimplisafeAlarm")
esp_simplisafe_alarm = ns.class_("esp_simplisafe_alarm", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(esp_simplisafe_alarm),
    # Schema definition, containing the options available for the component
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    # Code generation
    pass