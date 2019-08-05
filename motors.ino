int pin_in1 = 8;
int pin_in2 = 9;
int pin_ena = 11; // PWM speed control
int pin_in3 = 6;
int pin_in4 = 7;
int pin_enb = 10; // PWM speed control
int FULL = 255;

void setup() { 
 pinMode(pin_in1, OUTPUT); 
 pinMode(pin_in2, OUTPUT); 
 pinMode(pin_ena, OUTPUT); 
 pinMode(pin_in3, OUTPUT); 
 pinMode(pin_in4, OUTPUT); 
 pinMode(pin_enb, OUTPUT); 
 pinMode(LED_BUILTIN, OUTPUT); 
}

void brake() {
 digitalWrite(pin_in1, HIGH); // make left motor A brake
 digitalWrite(pin_in2, HIGH);
 digitalWrite(pin_in3, HIGH); // make right motor B brake
 digitalWrite(pin_in4, HIGH);
}

void setup_motors(int forward_a, int forward_b) {
 if (forward_a == 1) {
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
 } else {
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
 }
 if (forward_b == 1) {
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
 } else {
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
 }
}

void change_speed(int speed_a, int speed_b) {
 analogWrite(pin_ena, speed_a); 
 analogWrite(pin_enb, speed_b); 
}
 
void loop() { 
 change_speed(FULL, FULL);
 digitalWrite(LED_BUILTIN, HIGH); 
 // forwards 
 setup_motors(1, 1);
 delay(1000); 
 brake(); delay(200);
 // backwards 
 setup_motors(0, 0);
 delay(1000); 
 brake(); delay(200);
 digitalWrite(LED_BUILTIN, LOW); 
 // turn left 
 setup_motors(0, 1);
 delay(2000); 
 brake(); delay(200);
 // turn right 
 setup_motors(1, 0);
 delay(2000); 
 brake(); delay(200);
}
