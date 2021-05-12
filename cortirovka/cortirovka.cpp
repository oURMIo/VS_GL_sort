#include "stdafx.h"
#include <Windows.h>
#include "GL/glut.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;


#define N 100


const int left = -100, right = 100, bottom = -100, top = 100, far_ = -100, near_ = 100;
void reshape(int w, int h) // функция обработки изменения размеров окна
{
	glClearColor(1.0, 0.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-240.0, 240.0, -240.0, 240.0, -360.0, 360.0);
	glOrtho(0.0, N, 0.0, N, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void renderBitmapString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

static int initialized = 0;


void keyboard(unsigned char Key, int X, int Y)
{
	if (Key == 27) exit(30);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//glRotatef(0.001, 0.0, 0.0, 1.0);
	//glOrtho(0.0, 1000.0, 0.0, 1000.0, 0.0, 1.0);


	static int a[N], temp;

	static int i = 0;
	static int j = 0;
	static int k;

	if (initialized == 0)
	{
		srand(i); /// МЕШАЛКА
		for (i = 0; i < N; i++) a[i] = rand() % N;

		k = 1;
		initialized = 1;
	}

	// ПУЗЫРЕК BK ///////////////
	for (j = 0; j<N; j++)
	{
		if (a[j] > a[j + 1])
		{
			k++;
			temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
		}
	}
	i++;

	char str1[32];
	sprintf_s(str1, "comparings: %3d", k);
	renderBitmapString(10, N - 10, 0, GLUT_BITMAP_TIMES_ROMAN_24, str1);

	for (k = 0; k < N; k++)
	{
		if (k == j)
		{
			glColor3f(1.0, 0.0, 0.0);
		}
		else
		{
			if (k == i) glColor3f(0.0, 1.0, 0.0);
			else glColor3f(1.0, 1.0, 1.0);
		}
		glColor3f(0, 1, 5);
		glBegin(GL_QUADS);
		glVertex3f(k, 0, 0);
		glVertex3f(k, a[k], 0);
		glVertex3f(k + 0.9, a[k], 0);
		glVertex3f(k + 0.9, 0, 0);
		glEnd();
	}

	// пауза
	for (int qq = 0; qq<7000; qq++)
		for (int qqq = 0; qqq<7000; qqq++);


	// окончание работы с кадром
	glFlush();
	glFinish();
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		glColor3f(0.0, 1.0, 0.0);
	}
}


void mouseMove(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(x / 5, 0, 0);
	glVertex3f(x / 5, y / 5, 0);
	glVertex3f(0, y / 5, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	;
}


void timer(int value)
{

	initialized = 0;
	glutTimerFunc(12000, timer, 0);
}

//=====================================

int main(int argc, char **argv)
{
	// инициализация GLUT, создание окна
	glutInit(&argc, argv);

	glutInitWindowSize(840, 840);
	glutInitWindowPosition(40, 40);

	//glDepthFunc(GL_LESS);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("GLUT window");

	// списки функций-обработчиков
	glutDisplayFunc(display);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	// новая функция для регистрации
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(12000, timer, 0);

	glutMainLoop();

	return 0;
}
