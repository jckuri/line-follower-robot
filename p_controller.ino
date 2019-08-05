int pin_in1 = 8;
int pin_in2 = 9;
int pin_ena = 11; // PWM speed control of left motor
int pin_in3 = 6;
int pin_in4 = 7;
int pin_enb = 10; // PWM speed control of right motor
int line0, line1, line2, line3, line4, line = 0, no_line, speed_a, speed_b;
int threshold = (400 + 19) / 2;
int max_speed = 255, loss = 50, turning_speed = 255;

void setup() {   
 pinMode(pin_in1, OUTPUT);   
 pinMode(pin_in2, OUTPUT);   
 pinMode(pin_ena, OUTPUT);   
 pinMode(pin_in3, OUTPUT);   
 pinMode(pin_in4, OUTPUT);   
 pinMode(pin_enb, OUTPUT);  
 pinMode(LED_BUILTIN, OUTPUT);
 setup_motors(1, 1);
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

int read_eye(int eye) {
 int line = analogRead(eye);
 if (line < threshold) return 0;
 return 1;
}

void loop() { 
 line0 = read_eye(0);
 line1 = read_eye(1);
 line2 = read_eye(2);
 line3 = read_eye(3);
 line4 = read_eye(4);
 if ((line0 == 0 and line1 == 0 and line2 == 0 and line3 == 0 and line4 == 0) or 
 (line0 == 1 and line1 == 1 and line2 == 1 and line3 == 1 and line4 == 1)) {
  digitalWrite(LED_BUILTIN, LOW);
  no_line = 1;
  brake();
  if (line < 0) {
   change_speed(turning_speed, turning_speed);
   setup_motors(0, 1);
  }
  if (line > 0) {
   change_speed(turning_speed, turning_speed);
   setup_motors(1, 0);
  }
 } else {
  digitalWrite(LED_BUILTIN, HIGH);
  line = 0;
  if (line0 == 1) line += -4;
  if (line1 == 1) line += -2;
  if (line2 == 1) line += 0;
  if (line3 == 1) line += 2;
  if (line4 == 1) line += 4;  
  line /= (line0 + line1 + line2 + line3 + line4);
  speed_a = max_speed;
  speed_b = max_speed;
  if (line < 0) speed_a += line * loss;
  if (line > 0) speed_b += -line * loss;
  setup_motors(1, 1);
  change_speed(speed_a, speed_b);
 }  
}
