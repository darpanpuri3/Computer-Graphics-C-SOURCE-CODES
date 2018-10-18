#define GLUT_DISABLE_ATEXIT_HACK
#include<windows.h>
#include<GL/glut.h>
#include<iostream>
using namespace std;
float x1,y3,x2,y2;
float u1=0,u2=1;
int xmin=-100,ymin=-100,xmax=100,ymax=100;
double p[4],q[4];  // changed from int to double thats it
int choice=0;
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250,250,-250,250);
}
void clip(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1,i;
    double t;
    p[0]=-dx;q[0]=x1-xmin;
    p[1]=dx;q[1]=xmax-x1;
    p[2]=-dy;q[2]=y1-ymin;
    p[3]=dy;q[3]=ymax-y1;

    for(i=0;i<4;i++)
    {
        if(p[i]==0 && q[i]<0)
            return;
        if(p[i]<0)
        {
            t=(q[i])/(p[i]);  // This calculation was returning a zero because both q and p were int
            if(t>u1 && t<u2)
                {u1=t;}
        }
        else if(p[i]>0)
        {
            t=(q[i])/(p[i]);  // This calculation was returning a zero because both q and p were int
            if(t>u1 && t<u2)
                {u2=t;}
        }
    }
    if(u1<u2)
    {
        x1=x1+u1*(x2-x1);
        y1=y1+u1*(y2-y1);
        x2=x1+u2*(x2-x1);
        y2=y1+u2*(y2-y1);
        glBegin(GL_LINES);
            glVertex2i(x1,y1);
            glVertex2i(x2,y2);
        glEnd();
        glFlush();
    }
}
void display()
{
	glPointSize(5);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.0f);
	
    
}

void mouse1(int bin, int state , int x , int y) {
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		::x1=x-250;
		::y3=250-y;
		cout<<"\n"<<"x1="<<x1<<" y1="<<y3;
	}
	if(bin == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		::x2=x-250;
		::y2=250-y;
		cout<<"\nx2="<<x2<<" y2="<<y2;
		choice=1;
	}
	
}
void menu(int value){
	switch(value)
	{
		case 1:
			exit(0);
		case 2:
			glBegin(GL_LINES);
        	glVertex2i(x1,y3);
    		glVertex2i(x2,y2);
        	glEnd();
        	glFlush();
			break;
		case 3:
        	glColor3f(0.0,0.0,0.0);
        	glBegin(GL_LINES);
            glVertex2i(-100,-100);
            glVertex2i(-100,100);
            glVertex2i(-100,100);
            glVertex2i(100,100);
            glVertex2i(100,100);
            glVertex2i(100,-100);
            glVertex2i(100,-100);
            glVertex2i(-100,-100);
        	glEnd();
        	glFlush();
        	clip(x1,y3,x2,y2);
	}
	glutPostRedisplay();
}
void createMenu(void){
	int clipping= glutCreateMenu(menu);
	glutAddMenuEntry("Exit", 1);
	glutAddMenuEntry("Draw line", 2);
	glutAddMenuEntry("Clipping", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Clip");
    glutMouseFunc(mouse1);
    createMenu();
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
