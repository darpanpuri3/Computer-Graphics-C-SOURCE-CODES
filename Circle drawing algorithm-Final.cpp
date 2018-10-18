#define GLUT_DISABLE_ATEXIT_HACK
#include<iostream>
#include<conio.h>
#include<cmath>
#include<math.h>
#include<bits/stdc++.h>
#include <gl/glut.h>
#include<stdio.h>
using namespace std;
double x1,x2,y5,y2; //global variables
double x7,y7; //variables for translation
int r;
double data[2][1000]; //data structure for storing points
int choice; //choice of transformation
int a,b;


//Window Initialisation
void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
}

//drawpixel function
void draw_pixel(double x, double y) {
	glPointSize(1);
	if (::choice==1)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if(::choice==2)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else if(::choice==3)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
	}
	else if(::choice==4)
	{
		glColor3f(0.0f, 0.3f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);

	}
	
	
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
//simpledda
void circle()
{
	
	
	r=floor(sqrt(pow(x2-x1,2)+pow(y2-y5,2)));
	int x=0;
	int y=r;
	int Pk=1-r;
	data[0][0]=x;
	data[1][0]=y;
	
	int o=1,p=1;
	while(x<y)
            {
                if(Pk<0)
                    {
                        x=x+1;
                        Pk=Pk+(2*x)+1;
                    }
                else
                    {
                        x=x+1;
                        y=y-1;
                        Pk=Pk+(2*x)-(2*y)+1;
                    }
                    data[0][o]=x;
                    data[1][p]=y;
                    o++;p++;
            }
            a=o;
            b=p;
}
//line drawing function
void drawline()
{
	
	int i=0;
	while(i<=a)
	{
		int c=data[0][i];
		int d=data[1][i];
		draw_pixel(x1+c,y5+d);
		draw_pixel(x1+d,y5+c);
		draw_pixel(x1-d,y5-c);
		draw_pixel(x1-c,y5-d);
		draw_pixel(x1+c,y5-d);
		draw_pixel(x1+d,y5-c);
		draw_pixel(x1-c,y5+d);
		draw_pixel(x1-d,y5+c);


		i++;
	}
	
}
void mouse1(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		::x7=x-250;
		::y7=250-y;
		cout<<"x7="<<::x7<<" "<<"y7="<<::y7<<"\n";
		
		int tx=x7-x1;
		int ty=y7-y5;
		x1=x7;
		y5=y7;
		x2=x2+tx;
		y2=y2+ty;
		circle();
		drawline();
	}
	
}
//translation function
void translation()
{
	glutMouseFunc(mouse1);
	
}
//rotation function
void rotation()
{
	double angle;
	cout<<"Enter the angle by which you want to rotate:";
	cin>>angle;
	angle=angle*0.01745;
	int p=x1,q=x2,r=y5,s=y2;
	x1=((p*cos(angle))+(r*sin(angle)));
	x2=((q*cos(angle))+(s*sin(angle)));
	y5=((r*cos(angle))-(p*sin(angle)));
	y2=((s*cos(angle))-(q*sin(angle)));
	circle();
	drawline();
	
}
//scaling function
void scaling()
{
	double sx,sy;
	double tx,ty;
	if(data[0][0]!=0 && data[1][0]!=0)
	{
		tx=data[0][0];
		ty=data[1][0];
}

	x1=x1-tx;
	x2=x2-tx;
	y5=y5-ty;
	y2=y2-ty;
	cout<<"\nEnter the scaling factors:\n"; cout<<"Sx:";cin>>sx;cout<<"\nSy:";cin>>sy;

	int p=x1,q=x2,r=y5,s=y2;
	x1=sx*x1;x2=sx*x2;y5=sy*y5;y2=sy*y2;
	x1=x1+tx;
	x2=x2+tx;
	y5=y5+ty;
	y2=y2+ty;
	circle();
	drawline();
	
	
}
//display function()
void myDisplay() 
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(-250, 0);
	glVertex2i(250,0);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(0,-250);
	glVertex2i(0,250);
	glEnd();
	if (::choice==1)
	{
		circle();
		drawline();
}
	else if(::choice==2)
	{
		translation();
	}
	else if(::choice==3)
	{
		rotation();
	}
	else if(::choice==4)
	{
		scaling();
	}
	else
	{
		cout<<"";
	}
	glFlush();
}
//menu function
void menu(int value){
	switch(value)
	{
		case 1:
			::choice=1;
			break;
		case 2:
			::choice=2;
			break;
		case 3:
			::choice=3;;
			break;
		case 4:
			::choice=4;;
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
	glutAddMenuEntry("Normal circle", 1);
	glutAddMenuEntry("Translated circle", 2);
 	glutAddMenuEntry("Rotated circle", 3);
 	glutAddMenuEntry("Scaled circle", 4);
 	glutAddMenuEntry("quit", 5);
 	glutAttachMenu(GLUT_RIGHT_BUTTON);
 
 
}
//mouseclick function
void mouse(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		::x1=x-250;
		::y5=250-y;
		cout<<"x1="<<::x1<<" "<<"y1="<<::y5<<"\n";
	}
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		::x2=x-250;
		::y2=250-y;
		cout<<"x2="<<::x2<<" "<<"y2="<<::y2<<"\n\n";
}
}

int main(int argc, char **argv)
{
	//cout<<"\nEnter the transformations you want to perform on the line:\n1)Translation\n2)Rotation\n3)Scaling\n";
	//cin>>::choice;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2-D Transformations");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	myInit();
	glutMouseFunc(mouse);
	createMenu();
	glutDisplayFunc(myDisplay);
	
	glutMainLoop();
	return 0;
}

