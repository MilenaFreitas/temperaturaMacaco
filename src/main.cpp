#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
OneWire pino(19);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
LiquidCrystal_I2C visor(0x3F,20,4);
const int contatora=23;
int cont=0;
int tempoDelay=1000*60*1;
void setup(){
  Serial.begin(115200);
  pinMode(contatora, OUTPUT);
  barramento.begin();
  barramento.getAddress(sensor, 0);  // inicia sensor de temp pelo pino
  visor.init();  //tamanho da tela 20x4
  visor.setBacklight(HIGH); //luz de fundo ligada
}
void loop(){
  visor.clear();
  Serial.println ("sensorTemp inicio do LOOP");
  //busca temp 
  barramento.requestTemperatures(); 
  float temperatura = barramento.getTempC(sensor);
  if(temperatura>=40){          //verifica temperatura 
    //liga contatora
    digitalWrite(contatora, HIGH);
  } else{
    digitalWrite(contatora, LOW);
  }
  visor.setCursor(1,0); //SETA A POSIÇÃO DO CURSOR
  visor.print("TEMPERATURA ATUAL:"); //IMPRIME O TEXTO NO DISPLAY LCD
  visor.setCursor(7,1); //SETA A POSIÇÃO DO CURSOR
  visor.print(temperatura);
  visor.setCursor(13,1); //SETA A POSIÇÃO DO CURSOR
  visor.print("C");
  visor.setCursor(1, 2);
  visor.print("STATUS CONTATORA:");
  visor.setCursor(10,3); //SETA A POSIÇÃO DO CURSOR
  visor.print(digitalRead(contatora));
  visor.setCursor(18,3); //SETA A POSIÇÃO DO CURSOR
  visor.print(cont);
  cont=cont+1;
  Serial.println("RODOU");
  if(cont>50){
    cont=0;
  }
  delay(tempoDelay); //2 min para verificar novamente
}