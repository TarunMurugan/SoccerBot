#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String data = "";
int left_raw,right_raw,shoot,leftpin[2]={12,14},rightpin[2]={27,26};
unsigned long t=0;



void out(int rawval,int pin[2]){
  if(rawval>0){
  digitalWrite(pin[1],1);
  analogWrite(pin[0],rawval);
  }
  else{
  digitalWrite(pin[1],0);
  analogWrite(pin[0],-rawval); 
  }
}

//left motor dir:14
//left motor pwm:12
//right motor dir:26
//right motor pwm:27

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(25,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(26,OUTPUT);
}




void loop() {
 if(SerialBT.available() > 0)   
   {
      data = SerialBT.readStringUntil(',');  
      left_raw=data.toInt(); 
      data = SerialBT.readStringUntil(',');  
      right_raw=data.toInt();
      data = SerialBT.readStringUntil('\n');  
      shoot=data.toInt();
      t=millis();

   }

if(millis()-t>=1000){
left_raw=0;
right_raw=0;
}

out(left_raw,leftpin);
out(right_raw,rightpin);
Serial.print(left_raw); 
Serial.print(",");
Serial.print(right_raw);


delay(50);

}
