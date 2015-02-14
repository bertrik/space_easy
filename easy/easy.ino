#define RF_PIN 5
#define LED_PIN 13

#define PULSE_SHORT  250
#define PULSE_LONG  1250
#define PULSE_PKT  10000

void setup()
{
  pinMode(RF_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

static void pulse(int delay_us)
{
  digitalWrite(RF_PIN, 1);
  delayMicroseconds(PULSE_SHORT);
  digitalWrite(RF_PIN, 0);
  delayMicroseconds(delay_us);
}

static void send_command(const char *data)
{
  int i;
  
  digitalWrite(LED_PIN, HIGH);
  for (i = 0; i < 6; i++) {
    // long start pulse
    pulse(PULSE_PKT);
    
    int j;
    for (j = 0; j < 57; j++) {
      int index = j / 8;
      int bitn = j % 8;
      uint8_t b = data[index];
      if ((b & (128 >> bitn)) == 0) {
        pulse(PULSE_SHORT);
      } else {
        pulse(PULSE_LONG);
      }
    }
  }
  digitalWrite(LED_PIN, LOW);
}
  
void loop()
{
  const char l_on[] =  {0xC7, 0x8F, 0x36, 0x5C, 0xE9, 0xB7, 0x31, 0x80};
  const char l_off[] = {0xC7, 0x8F, 0x36, 0x5C, 0xE9, 0xB6, 0xB1, 0x80};
  const char r_on[] =  {0xC7, 0x8F, 0x36, 0x5C, 0xE9, 0xB7, 0x32, 0x80};
  const char r_off[] = {0xC7, 0x8F, 0x36, 0x5C, 0xE9, 0xB6, 0xB2, 0x80};
  
  send_command(l_on);
  delay(2500);
  send_command(r_on);
  delay(2500);
  send_command(l_off);
  delay(2500);
  send_command(r_off);
  delay(2500);
}
