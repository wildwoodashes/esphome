#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

#define PIN_CONTACT_1             D1  //Armed                                                                                                                                                                                       
#define PIN_CONTACT_2             D3  //Warning                                                                                                                                                                                     
#define PIN_SENSOR_1              D2                                                                                                                                                                                                
#define WARNING_PIN               D5                                                                                                                                                                                                
#define ARMING_PIN                D6                                                                                                                                                                                                
                                                                                                                                                                                                                                    
#define MIN_DEBOUNCE_TIME 50 //Prevent any bouncing on changes                                                                                                                                                                      
#define MIN_ARM_TIME 3000 //Track to make sure this isn't a warning                                                                                                                                                                 
#define CURRENT 0                                                                                                                                                                                                                   
#define LAST 1                                                                                                                                                                                                                      
#define ARMED LOW                                                                                                                                                                                                                   
#define DISARMED HIGH                                                                                                                                                                                                               
#define ACTIVE HIGH                                                                                                                                                                                                                 
#define INACTIVE LOW      

# Namespace definition
namespace esphome {
namespace espSimplisafeAlarm {

class esp_simplisafe_alarm : public binary_sensor::BinarySensor, public PollingComponent {

  public:
     // Constructor
    void esp_simplisafe_alarm(void);

    // Standard component functions to override
    void setup() override;
    void loop() override;
    void dump_config() override;

  protected:
    # Internal fields definition    
};

}  // namespace espSimplisafeAlarm
}  // namespace esphome