static void simulate_normal_message()
{
  static uint8_t count = 0;
  uint8_t data[] = {0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, count};
  count++;
  transmit_normal_message(0x04, data);
}

static void simulate_loop_back_message()
{
  uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

  transmit_loop_back_message(0x01, data);
}

static void simulate_remote_transmission_request_message()
{
  uint8_t data[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};

  transmit_remote_transmission_request_message(0x02, data);
}