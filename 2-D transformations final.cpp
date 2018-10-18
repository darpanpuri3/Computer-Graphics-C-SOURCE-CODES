#define GLUT_DISABLE_ATEXIT_HACK
#include<iostream>
#include<conio.h>
#include<math.h>
#include<bits/stdc++.h>
#include <gl/glut.h>
#include<stdio.h>
using namespace std;
double x1,x2,y5,y2; //global variables
double x7,y7; //variables for translation
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
void simpleDDA(double x3,double x4,double y3,double y4)
{
	double xdiff=x4-x3;
	double ydiff=y4-y3;
	double m=max(xdiff,ydiff);
	double e=double(1/m);
	double xinc=e*xdiff;
	double yinc=e*ydiff;
	double x=x3;
	double y=y3;
	data[0][0]=round(x);
	data[1][0]=round(y);
	int o=1,p=1;
	while(1)
	{
		if (round(x)==x4 && round(y)==y4)
		{
			a=o;
			b=p;
			break;
			
		}
		else if (round(x)==x4 and round(y)!=y4)
		{
			y=y+yinc;
			o=o+1;
			data[0][o]=round(x);
			p=p+1;
			data[1][p]=round(y);
			continue;
		}
		else if (round(x)!=x4 and round(y)==y4)
		{
			x=x+xinc;
			o=o+1;
			data[0][o]=round(x);
			p=p+1;
			data[1][p]=round(y);
			continue;
		}
		else
		{
			x=x+xinc;
			y=y+yinc;
			o=o+1;
			data[0][o]=round(x);
			p=p+1;
			data[1][p]=round(y);
			continue;
		}
		
	}
}
//line drawing function
void drawline()
{
	
	int i=0;
	while(i<=a)
	{
		draw_pixel(data[0][i],data[1][i]);
		i++;
	}
	
}
void mouse1(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		::x7=x-250;
		::y7=250-y;
		int i=0;
	int tx,ty;
	/*cout<<"\nEnter translation factor on x-axis:";
	cin>>tx;
	cout<<"\nEnter translation factor on y-axis:";
	cin>>ty;*/
	tx=x7-x1;
	ty=y7-y5;
	x1=x7;
	y5=y7;
	x2=x2+tx;
	y2=y2+ty;
	simpleDDA(x1,x2,y5,y2);
	
	drawline();
}}
//translation function
void translation()
{
	glutMouseFunc(mouse1);

}
//rotation function
void rotation()
{
	double tx, ty;
	double angle;
	if(data[0][0]!=0 && data[1][0]!=0)
	{
		tx=data[0][0];
		ty=data[1][0];
}
	int i;
		for(i=0;i<=a;i++)
	{
		data[0][i]=data[0][i]-tx;
	}
	for(i=0;i<=b;i++)
	{
		data[1][i]=data[1][i]-ty;
	}
	cout<<"Enter the angle by which you want to rotate:";
	cin>>angle;
	angle=angle*0.01745;
	for(i=0;i<=a;i++)
	{
		data[0][i]=((data[0][i]*cos(angle))+(data[1][i]*sin(angle)));
	}
	for(i=0;i<=b;i++)
	{
		data[1][i]=((data[1][i]*cos(angle))-(data[0][i]*sin(angle)));

	}
	for(i=0;i<=a;i++)
	{
		data[0][i]=data[0][i]+tx;
	}
	for(i=0;i<=b;i++)
	{
		data[1][i]=data[1][i]+ty;
	}
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
int i;
		for(i=0;i<=a;i++)
	{
		data[0][i]=data[0][i]-tx;
	}
	for(i=0;i<=b;i++)
	{
		data[1][i]=data[1][i]-ty;
	}
	cout<<"\nEnter the scaling factors:\n"; cout<<"Sx:";cin>>sx;cout<<"\nSy:";cin>>sy;
	for(i=0;i<=a;i++)
	{
		data[0][i]=(data[0][i])*sx;
	}
	for(i=0;i<=b;i++)
	{
		data[1][i]=(data[1][i])*sy;
}
	for(i=0;i<=a;i++)
	{
		data[0][i]=data[0][i]+tx;
	}
	for(i=0;i<=b;i++)
	{
		data[1][i]=data[1][i]+ty;
	}
	
	
	
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
		simpleDDA(x1,x2,y5,y2);
		drawline();
}
	else if(::choice==2)
	{
		translation();
	}
	else if(::choice==3)
	{
		rotation();
		drawline();
	}
	else if(::choice==4)
	{
		scaling();
		drawline();
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
	glutAddMenuEntry("Normal line", 1);
	glutAddMenuEntry("Translated line", 2);
 	glutAddMenuEntry("Rotated line", 3);
 	glutAddMenuEntry("Scaled line", 4);
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

