#define ONBOARDLED (1<<PB2)
#define RXPIN 9
#define TXPIN 10 
#define latchPin PB0
#define clockPin PB1
#define dataPin PB2

#define WDTps2K     0<<WDP3|0<<WDP2|0<<WDP1|0<<WDP0    // ~16ms
#define WDTps4K     0<<WDP3|0<<WDP2|0<<WDP1|1<<WDP0    // ~32ms
#define WDTps8K     0<<WDP3|0<<WDP2|1<<WDP1|0<<WDP0    // ~16ms
#define WDTps16K    0<<WDP3|0<<WDP2|1<<WDP1|1<<WDP0    // ~0.125s
#define WDTps32K    0<<WDP3|1<<WDP2|0<<WDP1|0<<WDP0    // ~0.25s
#define WDTps64K    0<<WDP3|1<<WDP2|0<<WDP1|1<<WDP0    // ~0.5s
#define WDTps128K   0<<WDP3|1<<WDP2|1<<WDP1|0<<WDP0    // ~1s
#define WDTps256K   0<<WDP3|1<<WDP2|1<<WDP1|1<<WDP0    // ~2s
#define WDTps512K   1<<WDP3|0<<WDP2|0<<WDP1|0<<WDP0    // ~4s
#define WDTps1024K  1<<WDP3|0<<WDP2|0<<WDP1|1<<WDP0    // ~8s

uint8_t characterMap[] {
  0x3F,
  0x06,
  0x5B,
  0x4F,
  0x66,
  0x6D,
  0x7D,
  0x07,
  0x7F,
  0x67,
  0x77,
  0x7C,
  0x39,
  0x5E,
  0x79,
  0x71
};

void LEDOn(uint8_t anodePin, uint8_t cathodePin) {
  pinMode(anodePin, OUTPUT);
  pinMode(cathodePin, OUTPUT);
  digitalWrite(anodePin, HIGH);
  digitalWrite(cathodePin, LOW);
}

void LEDOff(uint8_t anodePin, uint8_t cathodePin) {
  pinMode(anodePin, OUTPUT);
  pinMode(cathodePin, OUTPUT);
  digitalWrite(anodePin, LOW);
  digitalWrite(cathodePin, LOW);
}



void onBoardLED (uint8_t state) {
  DDRB |= ONBOARDLED;
  if (state)
    PORTB |= ONBOARDLED;
  else
    PORTB &= ~ONBOARDLED;
}

void outShift(uint8_t shiftData,uint8_t bitOrder) {
  DDRB |= 1 << dataPin;         
  DDRB |= 1 << latchPin;
  DDRB |= 1 << clockPin;        
  uint8_t selectedBit = 0;
  if (bitOrder)
    selectedBit = 128;
  else
    selectedBit = 1;
  while (selectedBit) {
    if (shiftData & selectedBit)
      PORTB |= 1 << dataPin;
    else
      PORTB &= ~(1 << dataPin);
    PORTB |= 1 << clockPin;
    PORTB &= ~(1 << clockPin);
    if (bitOrder)
      selectedBit >>= 1;
    else
      selectedBit <<= 1;
  }
  PORTB |= 1 << latchPin;
  PORTB &= ~(1 << latchPin);
}

void setupWDT(uint8_t ps) {
  // WD conditioning...
  //  clear the WD interrupt flag,
  //  enable the WD interrupt
  //  scale the WD oscillator using a predefine
  WDTCSR = 1 << WDIF | 1 << WDIE | ps;
}
