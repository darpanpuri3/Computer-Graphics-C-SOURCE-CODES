#define GLUT_DISABLE_ATEXIT_HACK
#include<iostream>
#include<conio.h>
#include<cmath>
#include<math.h>
#include<bits/stdc++.h>
#include <gl/glut.h>
using namespace std;
double x2,y2,a,b; //global variables
int choice=0;

//Window Initialisation
void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
}

//drawpixel function
void draw_pixel(double x, double y) {
	glPointSize(2);
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
void ellipse(double xc,double yc,double rx,double ry)
 {
   int x, y, p;
   x=0;
   y=ry;
   p=(ry*ry)-(rx*rx*ry)+((rx*rx)/4);
   while((2*x*ry*ry)<(2*y*rx*rx))
   {
        draw_pixel(xc+x,yc-y);
        draw_pixel(xc-x,yc+y);
        draw_pixel(xc+x,yc+y);
        draw_pixel(xc-x,yc-y);

        if(p<0)
        {
     x=x+1;
     p=p+(2*ry*ry*x)+(ry*ry);
        }
        else
        {
     x=x+1;
     y=y-1;
     p=p+(2*ry*ry*x+ry*ry)-(2*rx*rx*y);
        }
   }
   p=((float)x+0.5)*((float)x+0.5)*ry*ry+(y-1)*(y-1)*rx*rx-rx*rx*ry*ry;

         while(y>=0)
   {
        draw_pixel(xc+x,yc-y);
        draw_pixel(xc-x,yc+y);
        draw_pixel(xc+x,yc+y);
        draw_pixel(xc-x,yc-y);

        if(p>0)
        {
     y=y-1;
     p=p-(2*rx*rx*y)+(rx*rx);

        }
        else
        {
     y=y-1;
     x=x+1;
     p=p+(2*ry*ry*x)-(2*rx*rx*y)-(rx*rx);
        }
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
	ellipse(x2,y2,a,b);
	glFlush();
}

int main(int argc, char **argv)
{
	cout<<"Enter the x-coordinate of centre:";
	cin>>::x2;
	cout<<"Enter the y-coordinate of centre:";
	cin>>::y2;
	cout<<"\nhorizontal axis:";
	cin>>::a;
	cout<<"\nvertical axis:";
	cin>>::b;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ellipse");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	myInit();
	glutMouseFunc(mouse);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}

