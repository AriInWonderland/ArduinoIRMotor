#include <Arduino.h>
#line 1 "C:\\Users\\Arif\\Software\\arduino\\IRMotor\\IRMotor.ino"
#include <IRremote.h>

#define LED_1 2
#define LED_2 3
#define LED_3 4
#define MOTOR 5
#define IR_R_PIN 8

#define INCREASE_ALL 0
#define DECREASE_ALL 1
#define TURN_OFF 2
#define TURN_ON 3

#define MIN_SPEED 50
#define MAX_SPEED 255
#define ALT 5

int actual_speed = MAX_SPEED / 2 - 2;
int saved_speed = MAX_SPEED / 2;
int state = 0; // 0 = off, 1 = on

#line 22 "C:\\Users\\Arif\\Software\\arduino\\IRMotor\\IRMotor.ino"
void setup();
#line 27 "C:\\Users\\Arif\\Software\\arduino\\IRMotor\\IRMotor.ino"
void loop();
#line 22 "C:\\Users\\Arif\\Software\\arduino\\IRMotor\\IRMotor.ino"
void setup(){
    Serial.begin(9600);
    IrReceiver.begin(IR_R_PIN); 
}

void loop(){
    int command;
    int i;

    if (IrReceiver.decode()) { 
        IrReceiver.resume();
        command = IrReceiver.decodedIRData.command;

        if(state == 0 && command == TURN_ON){
            Serial.println("Turning on...");
            for(i = MIN_SPEED; i<=saved_speed; i += ALT){
                analogWrite(MOTOR, i);
                Serial.println(i);
                delay(100);
            }
            state = 1;
            actual_speed = saved_speed;
        }
        else if(state == 1)
            switch (command){
                case INCREASE_ALL:
                    if(actual_speed < MAX_SPEED){
                        if(actual_speed % 5 != 0)
                            actual_speed -= actual_speed % 5;
                        actual_speed += ALT;
                        analogWrite(MOTOR, actual_speed); 
                        Serial.println(actual_speed);
                    }
                    break; 
                case DECREASE_ALL:
                    if(actual_speed > MIN_SPEED){
                        if(actual_speed % 5 != 0)
                            actual_speed -= actual_speed % 5;
                        actual_speed -= ALT;
                        analogWrite(MOTOR, actual_speed);
                        Serial.println(actual_speed);
                    }
                    break;
                case TURN_OFF:
                    saved_speed = actual_speed;
                    Serial.println("Saved speed ");
                    Serial.print(saved_speed);
                    actual_speed = 0;
                    state = 0;
                    analogWrite(MOTOR, 0);
                    break;
                default:
                    Serial.println(actual_speed);
                    break;
            } 
    }
}	
