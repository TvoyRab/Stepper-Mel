/*
  StepperMel.h - Library for stepper motor.
  Created by Azamat and Robert, December 29, 2020.
  Released into the public domain.
*/
/*
	StepperMel - производительная библиотека для управления шаговыми моторами
         Реализация 2 режимов работы: линейное перемещение и управление вращением
         Управление углом поворота вала шагового двигателя
         Поддержка всех возможных дроблений шага
         Управление линейным перемещением в относительной и абсолютной системе координат
         Установка текущей позиции мотора
         Управление ускорением движения мотора
	- Режимы работы:
		- Вращение с заданной скоростью. Плавный разгон и торможение с ускорением
		- Следование к позиции с ускорением и ограничением скорости
		- Следование к позиции с заданной скоростью (без ускорения)
	- Быстрый алгоритм управления шагами
	- Два алгоритма плавного движения
*/
#include <Arduino.h>


class StepperMel {
  public:
    StepperMel(int pStep,int pDir,int pMS1,int pMS2,int pMS3);
	void attach(int pStep,int pDir,int pMS1,int pMS2,int pMS3);
	void setStep(int stepLength); // установка шага
	void moveStep(float dir,int pause,int moveCount); //   линейное перемещение и управление вращением
	void moveAccStep(float dir,int pause,int moveCount); // Управление ускорением движения мотора
	void moveAngle(float speed,float angle, bool acc); //Управление углом поворота вала шагового двигателя
	void moveVector(float speed,int _length, bool acc); // Управление линейным перемещением в относительной и абсолютной системе координат
	void movePosition(float speed,int newPos, bool acc); // Установка текущей позиции мотора
	void moveHome();
	int getPosition();
private:
const float ONE_ROTATE=4.8; //мм за оборот
const float RATIO=38/90;    //коэффициент зубчатой передачи
const float STEPPER_SPEED=2500; // скорость шага
const float STEPPER_ANGLE=900;
float k=STEPPER_SPEED*ONE_ROTATE*RATIO;

int PIN_STEP=3; // пин для генерации импульсов для движения двигателей (каждый импульс – шаг), можно регулировать скорость двигателя
int PIN_DIR=2; // пин  для установка направления  вращения
int PIN_MS1=4; // контакты для установки микрошага
int PIN_MS2=5; // контакты для установки микрошага
int PIN_MS3=6; // контакты для установки микрошага
int pos=0;
int currentStep=0;
int a=20;
const int MS[5][3]={{0,0,0}, // дробление шага 
               {1,0,0},
               {0,0,1},
               {1,0,1},
               {1,1,1}};	
};	