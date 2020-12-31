/* пример программы для шагового двигателя
*/
 
#include <StepperMel.h>

StepperMel stepper(3, 2, 4, 5, 6); //указываем порты

void setup() {
// put your setup code here, to run once:
//stepper.attach(3, 2, 4, 5, 6);
stepper.setStep(0);
Serial.begin(9600);

}

void loop() {
if (Serial.available() > 0) {
int x = Serial.read();
switch (x) {
case '1':
stepper.moveVector(5, 2, 1); //moveVector(скорость, расстояние, ускорение (0 или 1))
Serial.println(stepper.getPosition());
break;

case '2':
stepper.moveVector(2, -2, 0);
Serial.println(stepper.getPosition());
break;

case '3':
stepper.movePosition(1, 5, 0);//movePosition(скорость, позиция, ускорение)
Serial.println(stepper.getPosition());
break;

case '4':
stepper.moveHome(); //moveHome() - движение на точку Home
Serial.println(stepper.getPosition());
break;

case '5':
stepper.moveAngle(5, -90, 0);
Serial.println(stepper.getPosition());
break;

case '6':
stepper.moveAngle(5, 270, 0);
Serial.println(stepper.getPosition());
break;

case '7':
stepper.moveAngle(5, -270, 1);
Serial.println(stepper.getPosition());
break;

}

}

}
