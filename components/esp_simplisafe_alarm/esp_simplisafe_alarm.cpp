#include "esphome.h"                                                                                                                                                                                                                
#include "esp_simplisafe_alarm.h"    
#include "esphome/core/log.h" // Included again for safety, good practice
#include "esphome/core/hal.h" // Required for delay() or other HAL functions

namespace esphome {
namespace espSimplisafeAlarm {
    
String strCommand;                                                                                                                                                                                                                  
bool change_detected;        //This makes sure mode only changes once                                                                                                                                                               
bool current_status;      //Holds the current status of the alarm                                                                                                                                                                   
bool read_status;         //temp variable                                                                                                                                                                                           
byte status_store[2];     //Array of current[0] and last[1] values of the sensor                                                                                                                                                    
int warning_mode_detect; //Detect warning mode                                                                                                                                                                                      
unsigned long debounce_millis; //needed to properly debounce the pushbutton inputs                                                                                                                                                  
unsigned long last_change_millis; //Blinking light indicates warning, not status. Need to track  
 
void esp_simplisafe_alarm::setup() {
    ESP_LOGI(TAG, "Setting up SimpliSafe Alarm component...");
    //Configure GPIO for monitoring
    pinMode(PIN_SENSOR_1, INPUT); // This is the photosensor

    // Set initial conditions for detection logic
    this->armed_sensor_->publish_state(DISARMED);
    this->warning_sensor_->publish_state(INACTIVE);
    change_detected = 1;
     
    Serial.begin(74880); // Used for sending print commands over serial (debugging)
    ESP_LOGI(TAG, "SimpliSafe Alarm component setup complete.");
}   
  
void esp_simplisafe_alarm::update() {
    // This will be called very often after setup time.
    // think of it as the loop() call in Arduino
    read_status = digitalRead(PIN_SENSOR_1); // read the input pin   
    if (read_status != status_store[LAST])      // only act if the button changed state
    {
      debounce_millis = millis();  //keep track of when the button changed state
    }
    if ((millis() - debounce_millis >= MIN_DEBOUNCE_TIME) && (status_store[CURRENT] != read_status))
    {
      strCommand = (read_status == ARMED ?"armed \n":"unarmed\n"); 
      Serial.print(strCommand);      
      status_store[CURRENT] = read_status; //keep current value for proper debounce logic
      last_change_millis = millis();
      if(read_status == ARMED){
        warning_mode_detect = warning_mode_detect<<1 | 1; // Is this warning mode? Armed/Unarmed mode will clear this
      }
      change_detected = 1;
    }
    status_store[LAST] = read_status;  //keep last value for proper debounce logic

    // Determine how to set the Contacts
    if (change_detected && (status_store[CURRENT] == ARMED) && (millis() - last_change_millis >= MIN_ARM_TIME)) 
    {
      Serial.printf("Drive alarm pin low, time = %d\n", last_change_millis);
      warning_mode_detect = 0;
      change_detected = 0;
      this->armed_sensor_->publish_state(ARMED);
      this->warning_sensor_->publish_state(INACTIVE);
      ESP_LOGI(TAG, "SimpliSafe armed and normal");

    }
    else if (change_detected && status_store[CURRENT] == DISARMED && (millis() - last_change_millis >= MIN_ARM_TIME)) 
    {
      Serial.printf("Drive alarm pin high, time = %d\n", last_change_millis);
      warning_mode_detect = 0;
      change_detected = 0;
      this->armed_sensor_->publish_state(DISARMED);
      this->warning_sensor_->publish_state(INACTIVE);
      ESP_LOGI(TAG, "SimpliSafe disarmed and normal");
    }
    else if(change_detected && ((warning_mode_detect&0x1F) == 0xF)){
      // LED has toggled 4 times since an aramed/disarmed was stable, this is warning, flag it as such
      Serial.printf("Drive warning to active, status = %x\n", warning_mode_detect);
      change_detected = 0;
      this->warning_sensor_->publish_state(ACTIVE);
      ESP_LOGI(TAG, "SimpliSafe warning set");
    }
}

void esp_simplisafe_alarm::dump_config() {
    ESP_LOGCONFIG(TAG, "Custom binary sensor");
}

} //namespace espSimplisafeAlarm
} //namespace esphome