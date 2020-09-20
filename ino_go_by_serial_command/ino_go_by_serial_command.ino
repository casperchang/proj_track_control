// 軌道套組

#define X_DIR    5   //第5腳位控制X轴馬達方向
#define X_STP    2   //第2腳位控制X轴馬達步數
#define en       8   //馬達使能
#define ES_1     9   //第9腳位為最小值機械開關接收訊號

int read_data = 0;

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
    for (int i=0 ; i< int(8307/3.0) ; i++){
      digitalWrite(X_DIR, HIGH); 
      digitalWrite(X_STP, HIGH);
      delayMicroseconds(100); 
      digitalWrite(X_STP, LOW);
      delayMicroseconds(100);
    }
    delay(2000);  
  }
}

void loop() {
  
  // first reset (limit switch)
  go_to_limit_switch();
  delay(1000);


  while (true) {
    if (Serial.available()) {
      read_data = int(Serial.read() - '0');
      go_forward(read_data);
      delay(1000);
    }
  }

  
  // wait for the command from serial port
//  if (Serial.available()) {
//    read_data = Serial.read() - '0';
//    go_forward(read_data);
//    delay(1000);
//  }
}

