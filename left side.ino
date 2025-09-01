#include <Servo.h>

#define MOTOR_A_DIR D1      // Dir Left
#define MOTOR_B_DIR D2      // Dir Right
#define MOTOR_A_SPEED D3    // (PWM left)
#define MOTOR_B_SPEED D4    // (PWM right)

#define SENSOR_1 D6         // far left
#define SENSOR_2 D7         // left
#define SENSOR_3 A0         // centre 
#define SENSOR_4 D8         // right
#define SENSOR_5 10         // far right (I2C SD3)

int junction = 0;                 // count junction detection
bool sensorBeforeActive = false;  // save 5 sensor active before
bool flag = false;                // flaf for stoped if detection case
bool passedCase4 = false;
bool passedCase6 = false;
bool passedCase7 = false;
bool passedCase9 = false;
bool passedCase10 = false;
bool passedCase12 = false;
bool passedCase13 = false;
bool passedCase15 = false;
bool passedCase16 = false;

Servo myServo1;
Servo myServo2;

void setup() {
  myServo1.attach(16, 500, 2500);
  myServo2.attach(14, 500, 2500);
  
  Serial.begin(9600); // comunication serial begin  

  Serial.println("servo rotate");
  myServo1.write(180); 
  myServo2.write(130);

  pinMode(MOTOR_A_DIR, OUTPUT);
  pinMode(MOTOR_B_DIR, OUTPUT);
  pinMode(MOTOR_A_SPEED, OUTPUT);
  pinMode(MOTOR_B_SPEED, OUTPUT);

  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);
  pinMode(SENSOR_4, INPUT);
  pinMode(SENSOR_5, INPUT);
}

void loop() {
  int s1 = digitalRead(SENSOR_1);  // far left
  int s2 = digitalRead(SENSOR_2);  // left
  int s3_analog = analogRead(SENSOR_3); // read analog value (0-1023)
  int s3 = (s3_analog > 500) ? 1 : 0;    // in threshold 500, write 1(HIGH).
  int s4 = digitalRead(SENSOR_4);  // right
  int s5 = digitalRead(SENSOR_5);  // far right

  Serial.print("S1: ");
  Serial.print(s1);
  Serial.print(" S2: ");
  Serial.print(s2);
  Serial.print(" S3: ");
  Serial.print(s3);
  Serial.print(" S4: ");
  Serial.print(s4);
  Serial.print(" S5: ");
  Serial.println(s5);


  // --- JIKA KONDISI SPESIAL AKTIF (SKIP ke CASE 7) ---
  if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0 && junction == 0) {
    Serial.println("Go to case 7");

    // Tandai semua case sebelumnya sebagai sudah dilewati
    passedCase4 = true;
    passedCase6 = true;
    passedCase7 = true;
    
    sensorBeforeActive = true; // agar tidak mendeteksi junction ulang
    flag = true;

    junction = 7;  // Langsung mulai dari junction ke-7
    myServo2.write(130);
    digitalWrite(MOTOR_A_DIR, 1);
    digitalWrite(MOTOR_B_DIR, 1);
    analogWrite(MOTOR_A_SPEED, 250); 
    analogWrite(MOTOR_B_SPEED, 222); 
    delay(350);

    return; // keluar dari loop untuk mencegah konflik
  }


  // --- PRIORITAS CASE 10 Marble 2 turn left ---
  if (!passedCase10 && s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0 && s5 == 0 && passedCase9 && !sensorBeforeActive) {
  Serial.println("turn left marble 2");
  sensorBeforeActive = true;
  flag = true;

      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 250);     
      analogWrite(MOTOR_B_SPEED, 222);   
      delay(450);

      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 0);     
      analogWrite(MOTOR_B_SPEED, 250);   
      delay(650);

      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 250);     
      analogWrite(MOTOR_B_SPEED, 250);   
      delay(150);

  junction = 10;
  passedCase10 = true;  // Tambahkan ini
  flag = false;        // Reset
  return;
}
  // --- PRIORITAS CASE 13 Marble 3 turn right ---
  if (!passedCase13 && s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1 && s5 == 1 && passedCase12 && !sensorBeforeActive) {
    Serial.println("turn right marble 3");
    sensorBeforeActive = true;
    flag = true;
      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 250);     
      analogWrite(MOTOR_B_SPEED, 222);   
      delay(450);
      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 250);     
      analogWrite(MOTOR_B_SPEED, 0);   
      delay(650);
      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 250);     
      analogWrite(MOTOR_B_SPEED, 250);   
      delay(100);
    junction = 13;
    passedCase13 = true; 
    flag = false;
    return;
  }

   // --- PRIORITAS CASE 16 Marble 4 turn left ---
   if (!passedCase16 &&s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0 && s5 == 0 && passedCase15 && !sensorBeforeActive) {
  Serial.println("turn left marble 4");
  sensorBeforeActive = true;
  flag = true;

      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 250);     
      analogWrite(MOTOR_B_SPEED, 222);   
      delay(450);

      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 0);     
      analogWrite(MOTOR_B_SPEED, 250);   
      delay(650);

      digitalWrite(MOTOR_A_DIR, 1);
      digitalWrite(MOTOR_B_DIR, 1);
      analogWrite(MOTOR_A_SPEED, 250);     
      analogWrite(MOTOR_B_SPEED, 250);   
      delay(150);

  junction = 16;
  passedCase16 = true;  // Tambahkan ini
  flag = false;        // Reset
  return;
}
  
  if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
    if (!sensorBeforeActive) {    
      junction++;                  // juntion Plus status
      sensorBeforeActive = true;   // mark the sensor is active
      Serial.print("junction: ");
      Serial.println(junction);    // Debugging junction value
    }

    if (!flag) {
      flag = true;  // Set flag running for run program case
    }
    
    // handel junction appropiate value case 
    switch (junction) {
      case 1:  //start(forward)
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250); 
        analogWrite(MOTOR_B_SPEED, 250); 
        delay(10);
        break;
      case 2:  // turn right
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);
        analogWrite(MOTOR_B_SPEED, 222);
        delay(400);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);  
        analogWrite(MOTOR_B_SPEED, 0);
        delay(560);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250); 
        analogWrite(MOTOR_B_SPEED, 250); 
        delay(250);
        break;
      case 3: //take tree, bacward, turn right
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0); 
        analogWrite(MOTOR_B_SPEED, 0); 
        delay(250);

        Serial.println("lower gripper");
        myServo2.write(170); 
        myServo1.write(57); 
        delay(500);
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 175);  
        analogWrite(MOTOR_B_SPEED, 170);  
        delay(700);
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);  
        analogWrite(MOTOR_B_SPEED, 0);  
        delay(200);

        Serial.println("take a tree");
        myServo2.write(135); 
        delay(500);
        smoothMove(myServo1, 57, 170, 2); 
        delay(500);

        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);
        analogWrite(MOTOR_B_SPEED, 0);
        delay(100);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);   
        analogWrite(MOTOR_B_SPEED, 0); 
        delay(600);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);
        analogWrite(MOTOR_B_SPEED, 222);
        delay(200);
        break;
       case 5:  //put a tree, backward, and turn right
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);  
        analogWrite(MOTOR_B_SPEED, 0);  
        delay(500);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 170);
        analogWrite(MOTOR_B_SPEED, 180);
        delay(500);
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0); 
        analogWrite(MOTOR_B_SPEED, 0);
        delay(200);

        Serial.println("put a tree"); 
        smoothMove(myServo1, 150, 40, 2); 
        delay(500);
        myServo2.write(150); 
        delay(500);                 

        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);
        analogWrite(MOTOR_B_SPEED, 0);
        delay(165);

        myServo1.write(180); 
        delay(1000);
  
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 250);   
        analogWrite(MOTOR_B_SPEED, 0); 
        delay(800);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);  
        analogWrite(MOTOR_B_SPEED, 222);  
        delay(300);
        break;
      
      
      case 8:  //take a marble 1
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(560);
        myServo2.write(170);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 157);   
        delay(500);
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(600);

        Serial.println("take a marble 1");
        smoothMove(myServo1, 180, 28, 5); 
        delay(500);
        smoothMove(myServo2, 170, 120, 5);   
        delay(500);
        myServo1.write(120);
        delay(500);
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(630);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 254);     
        analogWrite(MOTOR_B_SPEED, 220);   
        delay(100);
        break;

      case 9:  //put marble 1 in basket
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(300);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 155);   
        delay(500);
        
        smoothMove(myServo1, 120, 105, 1); 
        delay(100);
        
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(400);

        Serial.println("put marble 1");
        myServo2.write(170); 
        delay(600); 
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(650);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 250);   
        delay(1180);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 254);     
        analogWrite(MOTOR_B_SPEED, 220);   
        delay(100);
        passedCase9 = true;  //tandai bahwa case 9 sudah dilewati
        break;

      case 11: //take a marbel 2
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(630);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 164);   
        delay(500);
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(600);

        Serial.println("take marble 2");
        smoothMove(myServo1, 105, 28, 5); 
        delay(500);
        smoothMove(myServo2, 170, 120, 5);   
        delay(500);
        myServo1.write(120);
        delay(500);
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(670);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 250);   
        delay(650);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);     
        analogWrite(MOTOR_B_SPEED, 222);   
        delay(300);
        break;

      case 12: //put a marble 2 
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(300);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 155);   
        delay(500);

        smoothMove(myServo1, 120, 105, 5); 
        delay(100);

        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(400);

        Serial.println("put marble 1");
        myServo2.write(170); 
        delay(600); 
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(650);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 250);   
        delay(1180);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 254);     
        analogWrite(MOTOR_B_SPEED, 220);   
        delay(100);
        passedCase12 = true;  // tandai bahwa case 10 sudah dilewati
        break;

      case 14: //take marble 3
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(630);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 163);   
        delay(500);
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(600);

        Serial.println("take marble 3");
        smoothMove(myServo1, 105, 28, 5); 
        delay(500);
        smoothMove(myServo2, 170, 120, 5);   
        delay(500);
        myServo1.write(120);
        delay(500);
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(550);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(620);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 254);     
        analogWrite(MOTOR_B_SPEED, 220);   
        delay(100);
        break;

      case 15: //put marble 3 
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(300);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 154);   
        delay(500);

        smoothMove(myServo1, 120, 105, 5); 
        delay(100);

        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(400);

        Serial.println("put marble 3");
        myServo2.write(170); 
        delay(600);         

        myServo1.write(120);
        delay(100);

        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 150);   
        delay(100);
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(1180);
        passedCase15 = true;
        break;

      case 17:  //take marble 4
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(630);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 163);   
        delay(500);
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(600);

        Serial.println("take marble 4");
        smoothMove(myServo1, 105, 28, 5); 
        delay(500);
        smoothMove(myServo2, 170, 120, 5);   
        delay(500);
        myServo1.write(120);
        delay(500);
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(670);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 250);   
        delay(600);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 254);     
        analogWrite(MOTOR_B_SPEED, 220);   
        delay(50);
        break;
    case 18: //put marble 4
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);      
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(300);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 150);     
        analogWrite(MOTOR_B_SPEED, 155);   
        delay(500);

        smoothMove(myServo1, 120, 105, 5); 
        delay(100);

        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(400);

        Serial.println("put marble 4");
        myServo2.write(170); 
        delay(600); 
        
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(800);
        digitalWrite(MOTOR_A_DIR, 0);
        digitalWrite(MOTOR_B_DIR, 0);
        analogWrite(MOTOR_A_SPEED, 0);     
        analogWrite(MOTOR_B_SPEED, 0);   
        delay(10000);
        default:
        Serial.println(" case not handled!!");    
        break;
    }
  } else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 0 && (!passedCase4 || !passedCase6)) {//case turn right
    if (!sensorBeforeActive) {        
      junction++;
      sensorBeforeActive = true;
      Serial.print("junction: ");
      Serial.println(junction);
    }
    if (!flag) {
      flag = true;
    }
    switch (junction) {
      case 4:  //turn left before put a tree
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);
        analogWrite(MOTOR_B_SPEED, 222);
        delay(500);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0); 
        analogWrite(MOTOR_B_SPEED, 250);  
        delay(600);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250); 
        analogWrite(MOTOR_B_SPEED, 222); 
        delay(350);
        passedCase4 = true;
        break;
      case 6: //turn left in roundabout
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);
        analogWrite(MOTOR_B_SPEED, 222);
        delay(500);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0); 
        analogWrite(MOTOR_B_SPEED, 250);  
        delay(600);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250); 
        analogWrite(MOTOR_B_SPEED, 222); 
        delay(350);
        passedCase6 = true;
        break;
      default:
        Serial.println(" case not handled!!");
        break;
    }
  }  else if (s1 == 0 && s2 == 1 && s3 == 1 && passedCase6 && !passedCase7) { //case turn left
    if (!sensorBeforeActive) {        
      junction++;
      sensorBeforeActive = true;
      Serial.print("junction: ");
      Serial.println(junction);
    }
    if (!flag) {
      flag = true;
    }
    switch (junction) {
      case 7:  //turn left after roundabout
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250);
        analogWrite(MOTOR_B_SPEED, 222);
        delay(500);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 0); 
        analogWrite(MOTOR_B_SPEED, 250);  
        delay(600);
        digitalWrite(MOTOR_A_DIR, 1);
        digitalWrite(MOTOR_B_DIR, 1);
        analogWrite(MOTOR_A_SPEED, 250); 
        analogWrite(MOTOR_B_SPEED, 222); 
        delay(350);
        passedCase7 = true;
        break;
      default:
        Serial.println(" case not handled!!");
        break;
    }
  } else {
    sensorBeforeActive = false;
    flag = false;
  }

  // Decision-making based on sensor values 
  if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 0 && s5 == 0) {  
    forward();
  } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 0) {  
    forward();
  } else if (s1 == 1 && s2 == 1 && s3 == 1) {  
    forward();
  } else if (s3 == 1 && s4 == 1 && s5 == 1) {  
    forward();
  } else if (s2 == 1 && s3 == 1) {  
    turnLeft();
  } else if (s3 == 1 && s4 == 1) {  
    turnRight();
  } else if (s1 == 1 && s2 == 1) {
    turnLeftMax();
  } else if (s1 == 1 || s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0) {
    turnLeft();
  } else if (s4 == 1 && s5 == 1) {  
    turnRightMax();
  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 || s5 == 1) {  
    turnRight();
  } else {  
    backward();
  }
}

// --- Fungsi-fungsi bantuan (Tidak diubah) ---
void forward() {
  digitalWrite(MOTOR_A_DIR, 1);
  digitalWrite(MOTOR_B_DIR, 1);
  analogWrite(MOTOR_A_SPEED, 250);
  analogWrite(MOTOR_B_SPEED, 216);
}

void forwardMax() {
  digitalWrite(MOTOR_A_DIR, 1);
  digitalWrite(MOTOR_B_DIR, 1);
  analogWrite(MOTOR_A_SPEED, 251);
  analogWrite(MOTOR_B_SPEED, 242);
}

void turnLeftMax() {
  digitalWrite(MOTOR_A_DIR, 1);
  digitalWrite(MOTOR_B_DIR, 1);
  analogWrite(MOTOR_A_SPEED, 0);   
  analogWrite(MOTOR_B_SPEED, 250); 
} 

void turnLeft() {
  digitalWrite(MOTOR_A_DIR, 1);
  digitalWrite(MOTOR_B_DIR, 1);
  analogWrite(MOTOR_A_SPEED, 150);
  analogWrite(MOTOR_B_SPEED, 250);
}

void turnRight() {
  digitalWrite(MOTOR_A_DIR, 1);
  digitalWrite(MOTOR_B_DIR, 1);
  analogWrite(MOTOR_A_SPEED, 250);   
  analogWrite(MOTOR_B_SPEED, 150);     
}

void turnRightMax() {
  digitalWrite(MOTOR_A_DIR, 1);
  digitalWrite(MOTOR_B_DIR, 1);
  analogWrite(MOTOR_A_SPEED, 250);   
  analogWrite(MOTOR_B_SPEED, 0);     
}

void stop() {
  digitalWrite(MOTOR_A_DIR, 0);
  digitalWrite(MOTOR_B_DIR, 0);
  analogWrite(MOTOR_A_SPEED, 0);
  analogWrite(MOTOR_B_SPEED, 0);
}

void backward() {
  analogWrite(MOTOR_A_SPEED, 0);
  analogWrite(MOTOR_B_SPEED, 0);
}

// Fungsi smoothMove DIUBAH untuk menggunakan microseconds
void smoothMove(Servo& servo, int startAngle, int endAngle, int step) {
  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle += step) {
      // Konversi sudut ke mikrosekon dan tulis ke servo
      servo.writeMicroseconds(map(angle, 0, 180, 500, 2500));
      delay(15);
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle -= step) {
      // Konversi sudut ke mikrosekon dan tulis ke servo
      servo.writeMicroseconds(map(angle, 0, 180, 500, 2500));
      delay(15);
    }
  }
}
