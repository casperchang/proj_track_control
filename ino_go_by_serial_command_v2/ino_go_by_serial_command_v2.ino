// 軌道套組

#define X_DIR    5   //第5腳位控制X轴馬達方向
#define X_STP    2   //第2腳位控制X轴馬達步數
#define en       8   //馬達使能
#define ES_1     9   //第9腳位為最小值機械開關接收訊號

int read_data = 0;
int collect_time_second = 5;

void setup() {
  pinMode(X_DIR,OUTPUT);       
  pinMode(X_STP,OUTPUT);   
  pinMode(en,OUTPUT);   
  digitalWrite(en,LOW);
  pinMode(ES_1, INPUT);
    
  Serial.begin(9600);
}

void go_to_limit_switch() {
  while(digitalRead(ES_1)==HIGH){
    digitalWrite(X_DIR, LOW); 
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(100); 
    digitalWrite(X_STP, LOW);
    delayMicroseconds(100);
  }
}

void go_forward(int step) {
  for (int j = 0; j < step; j++) {  
    for (int i=0 ; i< int(8307/3) ; i++){
      digitalWrite(X_DIR, HIGH); 
      digitalWrite(X_STP, HIGH);
      delayMicroseconds(1000); 
      digitalWrite(X_STP, LOW);
      delayMicroseconds(100);
    }
    delay(2000);  
  }
}

void run_cm(int cm) {
  // this HW config: 3200 steps = 40 mm = 4cm 
  int steps = int(cm / 4.0 * 3200);
  for (int i = 0; i < steps; i++) {
      // once high-low stands for one step
      digitalWrite(X_DIR, HIGH); 
      digitalWrite(X_STP, HIGH);
      delayMicroseconds(1000); 
      digitalWrite(X_STP, LOW);
      delayMicroseconds(100);
  }
  delay(500); // small delay for system stable
}

void loop() {
  
  // first reset (limit switch)
  go_to_limit_switch();
  delay(1000);

  while (true) {

    if (Serial.available()) {
      String str = Serial.readString();
      //str.trim();
      Serial.println(str);
      if (str == "limit") {
        go_to_limit_switch();
        delay(1000);
      }
      else {
        int d = str.toInt();
        Serial.println(d);
        run_cm(d);
      }
    }
    
    /*
    // wait for the command from serial port
    if (Serial.available()) {
      //read_data = int(Serial.read() - '0');
      read_data = int(Serial.read());
      if (int(read_data)==999) {
        go_to_limit_switch();
        delay(1000);
      }
      else if (int(read_data)==903) {
        collect_time_second = 30;
      }
      else if (int(read_data)==901) {
        collect_time_second = 10;
      }
      else if (int(read_data)==906) {
        collect_time_second = 60;
      }
      else if (int(read_data)==902) {
        collect_time_second = 20;
      }    
      else if (int(read_data)==909) {
        collect_time_second = 120;
      }    
      else{
        //go_forward(read_data);
        if (int(read_data) <= 180) {
          run_cm(int(read_data));
          Serial.print(read_data);
          // sleep(ms) = stay at the position of cage to collect data
          //delay(1000);
          delay(collect_time_second*1000);
        }
      }
    }
    */
  }
}
