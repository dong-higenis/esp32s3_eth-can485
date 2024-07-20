#include "canTest.h"

void CanTest::setup()
{
  Serial.begin(115200);
  pinMode(CAN_EN_PIN, OUTPUT);
  digitalWrite(CAN_EN_PIN, LOW); // CAN Transceiver Standby!  
  
  twai_general_config_t general_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_PIN, RX_GPIO_PIN, TWAI_MODE_NORMAL);

  general_config.tx_queue_len = 0;
  general_config.rx_queue_len = 1000;
  
  twai_timing_config_t timing_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t filter_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&general_config, &timing_config, &filter_config) == ESP_OK)
  {
    if (twai_start() == ESP_OK)
    {
      Serial.println("Driver started");
      uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA | TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_ERROR | TWAI_ALERT_RX_QUEUE_FULL;
      // uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA | TWAI_ALERT_RX_QUEUE_FULL;

      if (twai_reconfigure_alerts(alerts_to_enable, NULL) == ESP_OK)
      {
        Serial.println("CAN alerts reconfigured");
        driver_installed = true;
      }
      else
        Serial.println("Failed to reconfigure alerts");
    }
    else
      Serial.println("Failed to start driver");
  }
  else
  {
   Serial.println("Failed to install driver");
  }
}


void CanTest::loop()
{
  static bool busErrorFlag = false;
  static uint32_t nextTm = 0;
  if(millis() < nextTm)
  {
    return;
  }  

  // put your main code here, to run repeatedly:
  if (driver_installed)
  {
    uint32_t alerts_triggered;
    twai_status_info_t status_info;

    // Check if alert triggered
    twai_read_alerts(&alerts_triggered, pdMS_TO_TICKS(DEFULT_INTERVAL));
    twai_get_status_info(&status_info);

    if((alerts_triggered & TWAI_ALERT_ERR_PASS) || 
      (alerts_triggered & TWAI_ALERT_BUS_ERROR) ||
      (alerts_triggered & TWAI_ALERT_RX_QUEUE_FULL))
    {
      // Handle the alerts
      if (alerts_triggered & TWAI_ALERT_ERR_PASS)
      {
        Serial.println("error passive.");
      }
      else if (alerts_triggered & TWAI_ALERT_BUS_ERROR)
      {
        if(!busErrorFlag)
        {
          Serial.printf("bus error count: %d\n", status_info.bus_error_count);
          busErrorFlag = true;
        }
      }
      else if (alerts_triggered & TWAI_ALERT_RX_QUEUE_FULL)
      {
        Serial.printf("err rx queue full(r:%d,m:%d,o:%d)\n", status_info.msgs_to_rx, status_info.rx_missed_count, status_info.rx_overrun_count);
      }
      nextTm = millis();
    }
    else if (alerts_triggered & TWAI_ALERT_RX_DATA)
    {
      busErrorFlag = false;
      twai_message_t message;
      while (twai_receive(&message, 0) == ESP_OK)
      Serial.printf("[%d]RX ID:%x:", millis(), message.identifier);
      if (!message.rtr)
      {
        for (int i = 0; i < message.data_length_code; i++)
          Serial.printf(" %02x", message.data[i]);                  
      }  
      Serial.printf("DLC: %d\n", message.data_length_code);
      nextTm = millis();
    }
    else
    {
      //normal send
      static uint8_t count = 0;
      uint8_t data[] = {0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, count};
      count++;
      // configure message to transmit
      twai_message_t message = {
        .identifier = 0x04, //id 
        .data_length_code = 8, //data length
      };

      memcpy(message.data, data, 8);      
      esp_err_t result = twai_transmit(&message, portMAX_DELAY);
      nextTm = millis() + DEFULT_INTERVAL;
    }
  }
  else
  {
    nextTm = millis() + DEFULT_INTERVAL;
  }
}

