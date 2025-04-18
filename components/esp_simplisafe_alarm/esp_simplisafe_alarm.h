#pragma once

#include "esphome/core/component.h" // Required for PollingComponent
#include "esphome/components/binary_sensor/binary_sensor.h" // Required for BinarySensor
#include "esphome/core/log.h" // Required for logging

// This is the photosensor pin
#define PIN_SENSOR_1              D2                                                                                                                                                                                                
                                                                                                                                                                                            
                                                                                                                                                                                                                                    
#define MIN_DEBOUNCE_TIME 50 //Prevent any bouncing on changes                                                                                                                                                                      
#define MIN_ARM_TIME 3000 //Track to make sure this isn't a warning                                                                                                                                                                 
#define CURRENT 0                                                                                                                                                                                                                   
#define LAST 1                                                                                                                                                                                                                      
#define ARMED false                                                                                                                                                                                                                   
#define DISARMED true                                                                                                                                                                                                               
#define ACTIVE true                                                                                                                                                                                                                 
#define INACTIVE false      

static const char* const TAG = "espSimplisafeAlarm";

// Namesapce definitions
namespace esphome {
namespace espSimplisafeAlarm {
    
class esp_simplisafe_alarm : public PollingComponent {

  public:    
    // Standard component functions to override
    void setup() override;
    void update() override;
    void loop() override;
    void dump_config() override;
    
    void set_armed_sensor  (esphome::binary_sensor::BinarySensor *sensor) {
        this->armed_sensor_ = sensor;
    }
    void set_warning_sensor(esphome::binary_sensor::BinarySensor *sensor) {
        this->warning_sensor_ = sensor;
    }

  protected:
    // Internal fields definition    
    esphome::binary_sensor::BinarySensor *armed_sensor_{nullptr};
    esphome::binary_sensor::BinarySensor *warning_sensor_{nullptr};
};

}  // namespace espSimplisafeAlarm
}  // namespace esphome