#define GLUT_DISABLE_ATEXIT_HACK
#include<iostream>
#include<conio.h>
#include<math.h>
#include<bits/stdc++.h>
#include <gl/glut.h>
#include<stdio.h>
using namespace std;
double x1,x2,y5,y2;
int choice;
int counter=0;
int color;
int algo;
//Window Initialisation
void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
}


//drawpixel function
void draw_pixel(double x, double y) {
	if(color==1)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if(color==2)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 1.0f);


	
	if (::choice==1)
	{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	
}
else if(::choice==2)
{
	if(::counter%8==0)
	{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	::counter+=1;
	return;
	}
	else
	{
		::counter+=1;
		return;
	}
}
else if(::choice==3)
{
	if(::counter%16==0)
	{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	::counter+=1;
	return;
	}
	else
	{
		::counter+=1;
		return;
	}
}
else
{
	if(::counter%16>8)
	{
	::counter=::counter+1;
	return;
	}
	else
	{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	::counter+=1;
	return;
	}
}
}
//midpoint algorithm
void midpoint(float x3,float x4,float y3,float y4)
{
	float xdiff=x4-x3;
	float ydiff=y4-y3;
	float m=(y4-y3)/(x4-x3);
	float x=x3,y=y3;
	float p1=(2*ydiff)-xdiff;
	float p2=(2*xdiff)-ydiff;
	float pk1=p1;
	float pk2=p2;
	
	if(m<1)
	{
		while(x<x2)
		{
			if(pk1>=0)
				{
					pk1=pk1+(ydiff)-(xdiff);
					x=x+1.0;
					y=y+1.0;
				draw_pixel(x,y);

					
				}
				else
				{
					pk1=pk1+(ydiff);
					x=x+1.0;
				draw_pixel(x,y);

				}
		}
	}
	else if (m>1)
	{
		while(y<y2)
		{
			if(pk2>=0)
				{
					pk2=pk2-(ydiff)+(xdiff);
					x=x+1.0;
					y=y+1.0;
				draw_pixel(x,y);

					
				}
				else
				{
					pk2=pk2+(xdiff);
					y=y+1.0;
				draw_pixel(x,y);
				}
		}
		
	}
	else
	{
		while(x<x2)
		{
			x=x+1.0;y=y+1.0;
				draw_pixel(x,y);
		}
	}
}
//bresenham algorithm
void bresenham(float x3,float x4,float y3,float y4)
{
	float xdiff=abs(x4-x3);
	float ydiff=abs(y4-y3);
	float m=(ydiff)/(xdiff);
	float x=x3,y=y3;
	float pk1=(2*ydiff)-xdiff;
	float pk2=(2*xdiff)-ydiff;
	float pk3=(2*ydiff)-xdiff;
	
	if(m<1)
	{
		while(x<x2)
		{
			
			if(pk1>=0)
				{
					pk1=pk1+(2*ydiff)-(2*xdiff);
					x=x+1.0;
					y=y+1.0;
				draw_pixel(x,y);

					
				}
				else
				{
					pk1=pk1+(2*ydiff);
					x=x+1.0;
				draw_pixel(x,y);

				}
		}
	}
	else if (m>1)
	{
		while(y<y2)
		{
			if(pk2>=0)
				{
					pk2=pk2-(2*ydiff)+(2*xdiff);
					x=x+1.0;
					y=y+1.0;
				draw_pixel(x,y);

					
				}
				else
				{
					pk2=pk2+(2*xdiff);
					y=y+1.0;
				draw_pixel(x,y);
				}
		}
		
	}
	else
	{
		while(x<x2)
		{
			x=x+1.0;y=y+1.0;
				draw_pixel(x,y);
		}
	}
}
//symmetricdda algorithm
void symmetricDDA(double x3,double x4,double y3,double y4)
{
	double xdiff=x4-x3;
	double ydiff=y4-y3;
	double m=max(xdiff,ydiff);
	double n=1;
	while(1)
	{
		if(pow(2,n-1)<=m && m<pow(2,n))
		{
			break;
		}
		else
		{
			n=n+1;
		}
	}
	double xinc=double(xdiff*pow(2,-n));
	double yinc=double(ydiff*pow(2,-n));
	double x=x3;
	double y=y3;
	draw_pixel(round(x),round(y));

	while(1)
	{
		if (round(x)==x4 && round(y)==y4)
		{
			break;
		}
		else if (round(x)==x4 and round(y)!=y4)
		{
			y=y+yinc;
			draw_pixel(round(x),round(y));
			continue;
		}
		else if (round(x)!=x4 and round(y)==y4)
		{
			x=x+xinc;
			draw_pixel(round(x),round(y));
			continue;
		}
		else
		{
			x=x+xinc;
			y=y+yinc;
			draw_pixel(round(x),round(y));
			continue;
		}
		
	}
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
		
	draw_pixel(round(x),round(y));

	while(1)
	{
		if (round(x)==x4 && round(y)==y4)
		{
			break;
		}
		else if (round(x)==x4 and round(y)!=y4)
		{
			y=y+yinc;
			draw_pixel(round(x),round(y));
			continue;
		}
		else if (round(x)!=x4 and round(y)==y4)
		{
			x=x+xinc;
			draw_pixel(round(x),round(y));
			continue;
		}
		else
		{
			x=x+xinc;
			y=y+yinc;
			draw_pixel(round(x),round(y));
			continue;
		}
		
	}
	
	
}
void bres()
{bresenham(::x1,::x2,::y5,::y2);	::counter=0;
	bresenham(::x1-2.0,::x2-2.0,::y5,::y2);	::counter=0;
bresenham(::x1-1.0,::x2-1.0,::y5,::y2);	::counter=0;

	bresenham(::x1+1.0,::x2+1.0,::y5,::y2);	::counter=0;

	bresenham(::x1+2.0,::x2+2.0,::y5,::y2);		::counter=0;

	
}
void mid()
{
		midpoint(::x1,::x2,::y5,::y2);	::counter=0;

	midpoint(::x1-2,::x2-2,::y5,::y2);	::counter=0;

	midpoint(::x1-1,::x2-1,::y5,::y2);	::counter=0;

	midpoint(::x1+1,::x2+1,::y5,::y2);	::counter=0;

	midpoint(::x1+2,::x2+2,::y5,::y2);		::counter=0;

}
void simple()
{
	simpleDDA(::x1,::x2,::y5,::y2); 	::counter=0;

	simpleDDA(::x1-2,::x2-2,::y5,::y2);	::counter=0;

	simpleDDA(::x1-1,::x2-1,::y5,::y2);	::counter=0;

	simpleDDA(::x1+1,::x2+1,::y5,::y2);	::counter=0;

	simpleDDA(::x1+2,::x2+2,::y5,::y2);		::counter=0;
}
void symm()
{
	symmetricDDA(::x1,::x2,::y5,::y2);	::counter=0;

	symmetricDDA(::x1-2,::x2-2,::y5,::y2);	::counter=0;

	symmetricDDA(::x1-1,::x2-1,::y5,::y2);	::counter=0;

	symmetricDDA(::x1+1,::x2+1,::y5,::y2);	::counter=0;

	symmetricDDA(::x1+2,::x2+2,::y5,::y2);		::counter=0;
}

//mydisplay function

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
	glFlush();
}
//menu function
void menu(int value){
	switch(value)
	{
		case 1:
			exit(0);
		case 2:
			algo=1;
			break;
		case 3:
			algo=2;
			break;
		case 4:
			algo=3;
			break;
		case 5:
			algo=4;
			break;
		case 7:
			color=1;
			break;
		case 8:			
		color=2;
		break;
		case 9:
		color=3;
			break;
		case 10:
			choice=1;
			break;
		case 11:
			choice=2;
			break;
		case 12:
			choice=3;
			break;
		case 13:
			choice=4;
			break;
			
			
	}
	glutPostRedisplay();
}

//createmenu function
void createMenu(void){
	int algorithms= glutCreateMenu(menu);
	glutAddMenuEntry("Quit", 1);
	glutAddMenuEntry("Bresenham", 2);
 	glutAddMenuEntry("Midpoint", 3);
 	glutAddMenuEntry("Simple DDA", 4);
 	glutAddMenuEntry("Symmetric DDA", 5);
 	int colors=glutCreateMenu(menu);
 	glutAddMenuEntry("Red", 7);
 	glutAddMenuEntry("Green", 8);
 	glutAddMenuEntry("Blue", 9);
	int pattern=glutCreateMenu(menu);
	glutAddMenuEntry("Normal", 10);
 	glutAddMenuEntry("Dotted", 11);
 	glutAddMenuEntry("Big Dotted", 12);
 	glutAddMenuEntry("Dashed", 13);
	int main=glutCreateMenu(menu);
 	glutAddSubMenu("Algorithms",algorithms);
 	glutAddSubMenu("Colors",colors);
 	glutAddSubMenu("Patterns", pattern);
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
		if(algo==1)
		{
			bres();
		}
		else if(algo==2)
		{
			mid();
		}
		else if(algo==3)
		{
			simple();
		}
		else
		{
			symm();
		}
	}
	
	

}

int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line Drawing Algorithms");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	myInit();
	glutMouseFunc(mouse);
	createMenu();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
	


	
		
