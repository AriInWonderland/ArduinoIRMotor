# 1 "C:\\Users\\Arif\\Software\\arduino\\IRMotor\\IRMotor.ino"
# 2 "C:\\Users\\Arif\\Software\\arduino\\IRMotor\\IRMotor.ino" 2
# 18 "C:\\Users\\Arif\\Software\\arduino\\IRMotor\\IRMotor.ino"
int actual_speed = 255 / 2 - 2;
int saved_speed = 255 / 2;
int state = 0; // 0 = off, 1 = on

void setup(){
    Serial.begin(9600);
    IrReceiver.begin(8);
}

void loop(){
    int command;
    int i;

    if (IrReceiver.decode()) {
        IrReceiver.resume();
        command = IrReceiver.decodedIRData.command;

        if(state == 0 && command == 3){
            Serial.println("Turning on...");
            for(i = 50; i<=saved_speed; i += 5){
                analogWrite(5, i);
                Serial.println(i);
                delay(100);
            }
            state = 1;
            actual_speed = saved_speed;
        }
        else if(state == 1)
            switch (command){
                case 0:
                    if(actual_speed < 255){
                        if(actual_speed % 5 != 0)
                            actual_speed -= actual_speed % 5;
                        actual_speed += 5;
                        analogWrite(5, actual_speed);
                        Serial.println(actual_speed);
                    }
                    break;
                case 1:
                    if(actual_speed > 50){
                        if(actual_speed % 5 != 0)
                            actual_speed -= actual_speed % 5;
                        actual_speed -= 5;
                        analogWrite(5, actual_speed);
                        Serial.println(actual_speed);
                    }
                    break;
                case 2:
                    saved_speed = actual_speed;
                    Serial.println("Saved speed ");
                    Serial.print(saved_speed);
                    actual_speed = 0;
                    state = 0;
                    analogWrite(5, 0);
                    break;
                default:
                    Serial.println(actual_speed);
                    break;
            }
    }
}
