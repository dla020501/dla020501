// Arduino pin assignment
#define PIN_IR A0
#define PIN_LED 9
#include <Servo.h>
#define PIN_SERVO 10

Servo myservo;

int a, b; // unit: mm

void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  
// initialize serial port
  Serial.begin(57600);

  a = 65; //70;
  b = 365; //300;

  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(1500);
  delay(1000);
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  
  return val;
}

void loop() {
  float dist_raw = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (dist_raw - a);
  float dist_target = 255;
  float _KP = 0.8;
  float error_dist;
  float control;
  float duty_target;
  float duty_curr;

  
  error_dist = dist_target - dist_cali;
  control = _KP * error_dist;
  duty_target = duty_curr = 1500 + control;

  if (duty_target < 1000){
    duty_target = 1000;
  }
  if (duty_target > 2000){
    duty_target = 2000;
  }
  myservo.writeMicroseconds(duty_target);
  
  Serial.print("dist_ir:");
    Serial.print(dist_cali);
    Serial.print(",pterm:");
    Serial.print(map(error_dist,-1000,1000,510,610));
    Serial.print(",duty_target:");
    Serial.print(map(duty_target,1000,2000,410,510));
    Serial.print(",duty_curr:");
    Serial.print(map(duty_curr,1000,2000,410,510));
    Serial.println(",Min:100,Low:200,dist_target:255,High:310,Max:410");

  
  delay(100);
}
