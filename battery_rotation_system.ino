#include <Servo.h>

Servo vertical; // вертикальный серво крутится на 180 градусов
int anglevert = 90; // изначальная позиция в 90 градусах

Servo horizontal; // горизонтальный серво крутится на 360 градусов

// пины фоторезисторов
int lefttop = A1;
int righttop = A0;
int leftbottom = A2;
int rightbottom = A3;

void setup() {
  vertical.attach(5); // подключаем вертикальный серво к 5му пину
  delay(100);
  vertical.write(anglevert);
}

void loop() {

  /*чем больше значение, тем меньше освещенность
  чем меньше значение, тем больше освещенность*/
  
  int lt = analogRead(lefttop);
  int rt = analogRead(righttop);
  int lb = analogRead(leftbottom);
  int rb = analogRead(rightbottom);

  // средние значения наверху, внизу, слева, справа
  int avt = (lt + rt)/2;
  int avb = (lb + rb)/2;
  int avl = (lt + lb)/2;
  int avr = (rt + rb)/2;

  // ПО ВЕРТИКАЛИ
  // 10 - погрешность измерения
  if (abs(avt-avb) > 10) { // если значения отличаются больше чем на 10
    if (avt > avb) { // если ср.знач. сверху > ср.знач снизу
      anglevert = plusAngle(anglevert, 3);
    } else if (avb > avt) { // если ср.знач. снизу > ср.знач. сверху
      anglevert = minusAngle(anglevert, 3);
    }
  }


  // ПО ГОРИЗОНТАЛИ
  // 10 - погрешность измерения
  if (abs(avl-avr) > 20) { // если значения отличаются больше чем на 10
    if (avr > avl) { // если ср.знач. справа > ср.знач слева
      rotateServo360(1400);
    } else if (avl > avr) { // если ср.знач. слева > ср.знач справа
      rotateServo360(1600);
    }
  }

  vertical.write(anglevert);
  delay(100);
}


int plusAngle(int angle, int val) {
  /* метод, appending к углу значение и checking, чтобы угол был в промежутке [0;180] при increasing angle */
  if (angle >= 180 || angle+val >= 180) {
    return 179;
  } if (angle <= 0) {
    return 1;
  }

  return angle+val;
}

int minusAngle(int angle, int val) {
  /* метод, вычитающий из угла значение и проверяющий, чтобы угол был в промежутке [0;180] при decreasing angle */
  if (angle >= 180) {
    return 179;
  } if (angle <= 0 || angle-val <= 0) {
    return 1;
  }

  return angle-val;
}

void rotateServo360(int direction) {
  /* метод, поворачивающий горизонтальный серво */
  horizontal.attach(3);
  horizontal.write(direction);
  delay(25);
  horizontal.detach();
}
