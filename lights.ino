
const int NUM_LIGHTS = 5;
const int BIT = 0;
const int PIN = 1;
const int LEFT_RIGHT = 0;
const int RIGHT_LEFT = 1;

int light_to_bit_and_pin[NUM_LIGHTS][2] = {
  {1,12}, // 1 bit, pin 12
  {2,11}, // 2 bit, pin 11
  {4,10}, // 4 bit, pin 10
  {8,9},  // 8 bit, pin 9
  {16,8}  // 16 bit, pin 8
};

int delay_time = 200;
int count = 0;
int Switch1 = 2; 

void setup() {
  // put your setup code here, to run once:
  pinMode(Switch1, INPUT);
  for (int light = 0; light < NUM_LIGHTS; light++) {
    pinMode(light_to_bit_and_pin[light][PIN], OUTPUT);
  }
  digitalWrite(light_to_bit_and_pin[0][PIN], HIGH);
  for (int light = 1; light < NUM_LIGHTS; light++) {
    digitalWrite(light_to_bit_and_pin[light][PIN], LOW);
  }
}

void all_lights(uint8_t value) {
  for (int light = 0; light < NUM_LIGHTS; light++) {
    digitalWrite(light_to_bit_and_pin[light][PIN], value);
  }
} // all_lights()

void scan(int delay_time) {
  sequence(delay_time, RIGHT_LEFT);
  sequence(delay_time, LEFT_RIGHT);
}

void sequence(int delay_time, int direction) {
  int light = 0;
  int step = 1;
  int stop = NUM_LIGHTS;
  if (direction == RIGHT_LEFT) {
    light = NUM_LIGHTS - 1;
    step = -1;
    stop = -1;
  }
  digitalWrite(light_to_bit_and_pin[light][PIN], HIGH);
  delay(delay_time);
  light += step;
  for (; light != stop; light += step) {
    digitalWrite(light_to_bit_and_pin[light][PIN], HIGH);
    digitalWrite(light_to_bit_and_pin[light - step][PIN], LOW);
    delay(delay_time);
  }
  digitalWrite(light_to_bit_and_pin[light - step][PIN], LOW);
  delay(delay_time);
} // sequence()

void loop() {
  // put your main code here, to run repeatedly:
  count = (count + 1) % 17;

  if (digitalRead(Switch1) == HIGH){
    delay_time = 100;
  } else {
    delay_time = 800;
  }

  for (int light = 0; light < NUM_LIGHTS; light++) {
    digitalWrite(light_to_bit_and_pin[light][PIN], (light_to_bit_and_pin[light][BIT] & count) ? HIGH : LOW);
  }
  delay(delay_time);

  if (count == 16) {
    for (int i = 0; i < 16; i++) {
      all_lights(HIGH);
      delay(50);
      all_lights(LOW);
      delay(100);
    } // for

    for (int i = 0; i < 16; i++) {
      sequence(50,LEFT_RIGHT);
    } // for
    for (int i = 0; i < 16; i++) {
      sequence(50,RIGHT_LEFT);
    } // for
    
    for (int i = 0; i < 16; i++) {
      scan(25);
    } //for
  } // if


} // loop()
