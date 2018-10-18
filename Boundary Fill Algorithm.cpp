#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;
int arr[100][2];
int count=0;
int n;
float r,g,b;
void delay(float ms){
    clock_t goal = ms + clock();
    while(goal>clock());
}
//window initialisation
void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
}
//boundary fill algorithm
void bound_it(int x, int y, float* fillColor, float* bc){
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(
     color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2])){
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
        bound_it(x+1,y,fillColor,bc);
        bound_it(x-2,y,fillColor,bc);
        bound_it(x,y+2,fillColor,bc);
        bound_it(x,y-2,fillColor,bc);
    }
}
//function for boundary fill polygon drawing
void world(){
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    ::count=0;
    for(int i=1;i<=n;i++)
    
	{
		if (count==n-1)
		{
			glBegin(GL_LINES);
        glVertex2i(arr[count][0],arr[count][1]);
        glVertex2i(arr[0][0],arr[0][1]);
        count=count+1;
    glEnd();	
		}
		else
		{
		glBegin(GL_LINES);
        glVertex2i(arr[count][0],arr[count][1]);
        glVertex2i(arr[count+1][0],arr[count+1][1]);
        count=count+1;
    glEnd();	
		}
	
    glFlush();

}
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
void mouse(int btn, int state, int x, int y){
    y = 500-y;
    if(btn==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
        	if(::count==::n)
            {
            	world();
            	::count=count+1;
            	
			}
			else if(::count==::n+1)
			
		{
				float bCol[] = {1,0,0};
            	float color[] = {r,g,b};
            	//glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,intCol);
            	bound_it(x,y,color,bCol);
		}
			else
			{
				arr[::count][0]=x;
            arr[::count][1]=y;
            ::count=::count+1;
            cout<<"\n"<<x<<" "<<y<<" "<<count;
			}
            
            
        }
    }
    
}
void display()
{
	
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Boundary Fill Algorithm");
    cout<<"Enter number of points you want to enter in the polygon:";
    cin>>n;
    init();
	createMenu();    
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
