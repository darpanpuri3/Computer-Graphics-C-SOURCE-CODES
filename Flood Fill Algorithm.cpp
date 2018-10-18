#define GLUT_DISABLE_ATEXIT_HACK
#include<iostream>
#include<conio.h>
#include<cmath>
#include<math.h>
#include<bits/stdc++.h>
#include <gl/glut.h>
using namespace std;
int arr[10][2];
int count=0;
float r,g,b;
struct Point {
    GLint x;
    GLint y;
};

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,400,0,400);
}
  //this function is used for getting color of pixel
Color getPixelColor(GLint x, GLint y) {
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
    Color color;
    color = getPixelColor(x, y);

    if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
    {
        setPixelColor(x, y, newColor);
        floodFill(x+1, y, oldColor, newColor);
        floodFill(x-2, y, oldColor, newColor);
        floodFill(x, y+2, oldColor, newColor);
        floodFill(x, y-2, oldColor, newColor);
    }
    return;
}


void rectangle(int xa,int ya,int xb,int yb)
{
	glPointSize(2);
	int height=yb-ya;
	int width=xb-xa;
	glBegin(GL_POLYGON);
	if (::count==2)
	{
		glColor3f(0.0f, 1.0f, 0.0f);

	}
	else if(::count==4)
	{
		glColor3f(1.0f, 0.0f, 0.0f);

	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	glVertex2i(xa,ya);
	glVertex2i(xa+width,ya);
	glVertex2i(xa+width,ya+height);
	glVertex2i(xa,ya+height);
	glEnd();
	glFlush();
	
}


void display(void) {
	
    
}
//menu function
void menu(int value){
	switch(value)
	{
		case 1:
			r=0;
			g=0;
			b=1.0;
			break;
		case 2:
			r=0;
			g=1.0;
			b=0.0;
			
			break;
		case 3:
			r=1.0;g=0.0;b=1.0;
			break;
		case 4:
			r=0.0;g=1.0;b=0.0;
			break;
		case 5:
			exit(0);
			break;
	}
	glutPostRedisplay();
}

//createmenu function
void createMenu(void){
	int algorithms= glutCreateMenu(menu);
	glutAddMenuEntry("Color 1", 1);
	glutAddMenuEntry("Color2", 2);
 	glutAddMenuEntry("Color3", 3);
 	glutAddMenuEntry("Color4", 4);
 	glutAddMenuEntry("quit", 5);
 	glutAttachMenu(GLUT_RIGHT_BUTTON);
 
 
}
void mouse(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		int a=x,b=400-y;
		arr[::count][0]=a;
		arr[::count][1]=b;
		::count=::count+1;
		if (::count==2)
		{
			rectangle(arr[0][0],arr[0][1],arr[1][0],arr[1][1]);
		}
		if (::count==4)
		{
			rectangle(arr[2][0],arr[2][1],arr[3][0],arr[3][1]);

		}
		if(::count==6)
		{
			rectangle(arr[4][0],arr[4][1],arr[5][0],arr[5][1]);

		}
		
	Color newColor = {r, g, b};
    Color oldColor = {1.0f, 1.0f, 1.0f};

    floodFill(a, b, oldColor, newColor);
	}

}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Filling Algorithms");
	init();
	createMenu();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
