#include <iostream>
#include "glut.h"

double Pi = 3.1415926535;

class Point {
private:
	float X;
	float Y;
public:
	Point();
	Point(float aX, float aY);
	float getX() const;
	float getY() const;
	void setX(float aX);
	void setY(float aY);
	void draw() const;
};

Point::Point() {
	X = 0;
	Y = 0;
}

Point::Point(float aX, float aY) {
	X = aX;
	Y = aY;
}

float Point::getX() const {
	return X;
}

float Point::getY() const {
	return Y;
}

void Point::setX(float aX) {
	X = aX;
}

void Point::setY(float aY) {
	Y = aY;
}

void Point::draw() const {
	glBegin(GL_POINTS);
	glVertex2f(X, Y);
	glEnd();
}

class Vector {
private:
	float X;
	float Y;
	Point P;
	float arrow[4];
	void Arrow();
public:
	Vector();
	Vector(float aX, float aY, Point aP);
	float getX() const;
	float getY() const;
	Point getP() const;
	void setX(float aX);
	void setY(float aY);
	void setP(Point aP);
	void draw() const;
	Vector operator+ (Vector h1);
	Vector operator* (float n);
};

Vector Vector::operator+(Vector h1) {
	return Vector(h1.X + X, h1.Y + Y, h1.P);
}

Vector Vector::operator*(float n) {
	return Vector(n * X, n * Y, this->P);
}

void Vector::Arrow() {
	float x = P.getX() + X;
	float y = P.getY() + Y;
	double a = acos(X / (sqrt(X * X + Y * Y)));
	a *= (Y < 0) ? -1 : 1;
	float f1 = -70 * Pi / 180. + a;
	float f2 = 70 * Pi / 180. + a;
	arrow[0] = -12 * -sin(f1) + x;
	arrow[1] = -12 * cos(f1) + y;
	arrow[2] = 12 * -sin(f2) + x;
	arrow[3] = 12 * cos(f2) + y;
}

Vector::Vector() {
	X = 0;
	Y = 0;
	Arrow();
}

Vector::Vector(float aX, float aY, Point aP) {
	X = aX;
	Y = aY;
	P = aP;
	Arrow();
}

float Vector::getX() const {
	return X;
}

float Vector::getY() const {
	return Y;
}

Point Vector::getP() const {
	return P;
}

void Vector::setX(float aX) {
	X = aX;
	Arrow();
}

void Vector::setY(float aY) {
	Y = aY;
	Arrow();
}

void Vector::setP(Point aP) {
	P = aP;
	Arrow();
}

void Vector::draw() const {
	float x = P.getX() + X;
	float y = P.getY() + Y;
	glBegin(GL_LINES);
		glVertex2f(P.getX(), P.getY());
		glVertex2f(x, y);
		glVertex2f(x, y);
		glVertex2f(arrow[0],arrow[1]);
		glVertex2f(x, y);
		glVertex2f(arrow[2], arrow[3]);
	glEnd();
}

float f = 0;
float k = 1;
float i = 0;
float j = 0;


void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	Point Pani = { -125, -125 };
	Vector hani = { 0, 100, Pani };
	float r = 100;

	hani.setX((r - 10) * cos(f));
	hani.setY((r - 10) * sin(f));
	hani.setP({Pani.getX() + j, Pani.getY() + i});
	hani = hani * k;
	hani.draw();


	Point P1 = { 100, -125 };
	Vector h1 = { 0, 100, P1 };
	Point P2 = { 0, 0 };
	Vector h2 = { 100, 0, P2 };

	h1.draw();
	h2.draw();
	Vector h3 = h1 + h2;  // СЛОЖЕНИЕ ВЕКТОРОВ
	h3 = h3 * 2;		  // УМОЖЕНИЕ НА ЧИСЛО
	h3.draw();



	glFlush();

	// Отправляем на прорисовку
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 'q') {
		f += 0.1;
	}
	if (key == 'e') {
		f -= 0.1;
	}
	if (key == '+') {
		k += 0.1;
	}
	if (key == '-') {
		k -= 0.1;
	}
	if (key == 'w') {
		i += 5;
	}
	if (key == 's') {
		i -= 5;
	}
	if (key == 'a') {
		j -= 5;
	}
	if (key == 'd') {
		j += 5;
	}
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(40, timer, 0);
}

void myInit() {
	glClearColor(1, 1, 1, 0);
	//задание цвета фона (белый)
	glColor3f(0, 0, 0);
	// задание цвета рисования (черный)
	glPointSize(1);
	// размер точки
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320, 320, -320, 320);
	// задание окнной системы координат (Слева снизу начало)

}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	//инициализируем glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//устанавливаем режим дисплея
	glutInitWindowSize(640, 640);
	//устанавливаем размер окна
	glutCreateWindow("OpenGL example");
	//открываем окно на экране
	
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(processNormalKeys);
	glutTimerFunc(40, timer,0);
	

	//регистрируем функцию обратного вызова
	myInit();
	
	glutMainLoop();
	//входим в бесконечный цикл

}