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
  for (int i=0 ; i<8307 ; i++){
    digitalWrite(X_DIR, HIGH); 
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(100); 
    digitalWrite(X_STP, LOW);
    delayMicroseconds(100);
  }
  delay(3000);
  for (int j=0 ; j<7 ; j++){
    for (int i=0 ; i<16614 ; i++){
      digitalWrite(X_DIR, HIGH); 
      digitalWrite(X_STP, HIGH);
      delayMicroseconds(100); 
      digitalWrite(X_STP, LOW);
      delayMicroseconds(100);
    }
    delay(3000);
  }
  delay(1000);
}
