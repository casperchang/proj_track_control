// 軌道套組

#define X_DIR    5   //第5腳位控制X轴馬達方向
#define X_STP    2   //第2腳位控制X轴馬達步數
#define en       8   //馬達使能
#define ES_1     9   //第9腳位為最小值機械開關接收訊號

void setup() {
  pinMode(X_DIR,OUTPUT);       
  pinMode(X_STP,OUTPUT);   
  pinMode(en,OUTPUT);   
  digitalWrite(en,LOW);
  pinMode(ES_1, INPUT);
}

void run_cm(int cm) {
  // this HW config: 3200 steps = 40 mm = 4cm 
  int steps = int(cm / 4.0 * 3200);
  for (int i = 0; i < steps; i++) {
      // once high-low stands for one step
      digitalWrite(X_DIR, HIGH); 
      digitalWrite(X_STP, HIGH);
      delayMicroseconds(100); 
      digitalWrite(X_STP, LOW);
      delayMicroseconds(100);
  }
}

void loop() {
  //先歸零直到觸發歸零限位開關就停止
  while(digitalRead(ES_1)==HIGH){
    digitalWrite(X_DIR, LOW); 
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(100); 
    digitalWrite(X_STP, LOW);
    delayMicroseconds(100);
  }
  delay(3000);
  // run 23cm * 4 = 92cm for the short version track, 20200628
  for (int i = 0; i < 4; i++) {
    run_cm(23);
    delay(2000);
  }
  delay(1000);
}
