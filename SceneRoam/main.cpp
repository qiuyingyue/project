
#include <iostream>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include "LoadTexture.hpp"
#include "ObjModel.hpp"
#include "DoorModel.hpp"
#include "MonitorModel.hpp"
using namespace std;


ObjModel Woman;
ObjModel Apple;
ObjModel Dumbbell;
ObjModel Ball;
ObjModel iPad;
ObjModel City;

DoorModel Door;
MonitorModel Monitor;

string filePrefix = "/Users/Victor/Desktop/githubtest/";

float fTranslate;
float fRotate;
float fScale  = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;


int wHeight = 0;
int wWidth = 0;


GLuint WallList;

double angle=0;


void texSolidCube(){
    
    
    GLuint FloorTexture, WallTexture;
    
    glGenTextures(1, &FloorTexture);
    glGenTextures(1, &WallTexture);
    string texfile = filePrefix + "Floor.bmp";
    texload(FloorTexture, texfile.c_str());
    texfile = filePrefix + "Wall.bmp";
    texload(WallTexture, texfile.c_str());
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    float low_shininess = 1.0f;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, WallTexture);  //选择纹理texture[0]
    
    glPushMatrix();
    glBegin(GL_QUADS);
    
    glTexCoord2i(0, 0);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2i(1, 0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2i(1, 1);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    
//    glTexCoord2i(0, 0);
//    glVertex3f(-1.0, -1.0, -1.0);
//    glTexCoord2i(1, 0);
//    glVertex3f(1.0, -1.0, -1.0);
//    glTexCoord2i(1, 1);
//    glVertex3f(1.0, 1.0, -1.0);
//    glTexCoord2i(0, 1);
//    glVertex3f(-1.0, 1.0, -1.0);
    
    
    glTexCoord2i(0, 0);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2i(1, 0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2i(1, 1);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex3f(1.0, -1.0, 1.0);
    
    glTexCoord2i(0, 0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2i(1, 0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2i(1, 1);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex3f(-1.0, 1.0, 1.0);
    
//    glTexCoord2i(0, 0);
//    glVertex3f(-1.0, -1.0, 1.0);
//    glTexCoord2i(1, 0);
//    glVertex3f(1.0, -1.0, 1.0);
//    glTexCoord2i(1, 1);
//    glVertex3f(1.0, 1.0, 1.0);
//    glTexCoord2i(0, 1);
//    glVertex3f(-1.0, 1.0, 1.0);
    
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);	//关闭纹理texture[0]
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, FloorTexture);  //选择纹理texture[0]
    
    glPushMatrix();
    glBegin(GL_QUADS);
    
    
    
    //铺地板程序
    GLfloat floorSize = 3;
    GLfloat divide = 20;
    GLfloat unit = 2 / divide;
    for (int i = 0; i < divide; i++)
        for (int j = 0; j < divide; j++){
            GLfloat x0 = unit * i - 1.0;
            GLfloat z0 = unit * j - 1.0;
            glTexCoord2i(0, 0);
            glVertex3f(x0, -1.0, z0);
            glTexCoord2i(1, 0);
            glVertex3f(x0 + unit, -1.0, z0);
            glTexCoord2i(1, 1);
            glVertex3f(x0 + unit, -1.0, z0 + unit);
            glTexCoord2i(0, 1);
            glVertex3f(x0, -1.0, z0 + unit);
        }
    
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);	//关闭纹理texture[0]
    glDisable(GL_COLOR_MATERIAL);
}


void Draw_Scene()
{
    
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    glCallList(WallList);

    glPushMatrix();
    glTranslatef(-5, -3 - Woman.getBottom(), -5);
    Woman.draw();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(5, -3 - Dumbbell.getBottom(), 0);
    Dumbbell.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, -3 - Apple.getBottom(), -5);
    Apple.draw();
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef(-5, -3 - Ball.getBottom(), 5);
    Ball.draw();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-3, -3 - iPad.getBottom(), 0);
    iPad.draw();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(0, -15 - City.getBottom(), -126);
    City.draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -3 - Door.getBottom(), 0);
    Door.draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2, -3 - Monitor.getBottom(), 0);
    Monitor.draw();
    glPopMatrix();
    
}



void updateView(int width, int height)
{
    glViewport(0,0,width,height);						// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width/(GLfloat)height;
    
//    if (bPersp) {
        gluPerspective(80.0f, whRatio,0.1f,300.0f);
//    } else {
//        glOrtho(-3 ,3, -3, 3,-100,100);
//    }
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }
    
    wHeight = height;
    wWidth = width;
    updateView(wHeight, wWidth);
}


void idle()
{
    glutPostRedisplay();
}


float eye[] = {0, 0, 5};
float center[] = {0, 0, 0};


void key(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; break; }
            
        case ' ': {bAnim = !bAnim; break;}
        case 'o': {bWire = !bWire; break;}
            
        case 'a': {
            eye[0] -= 1.5f;
            center[0] -= 1.5f;
            break;
        }
        case 'd': {
            eye[0] += 1.5f;
            center[0] += 1.5f;
            break;
        }
        case 'w': {
            eye[1] += 1.5f;
            center[1] += 1.5f;
            break;
        }
        case 's': {
            eye[1] -= 1.5f;
            center[1] -= 1.5f;
            break;
        }
        case 'z': {
            eye[2] -= 0.3f*cos(angle);
            eye[0] -= 0.3f*sin(angle);
            center[2] -= 0.3f*cos(angle);
            center[0] -= 0.3f*sin(angle);
            break;
        }
        case 'c': {
            eye[2] += 1.5f;
            center[2] += 1.5f;
            break;
        }
            
        case 'u': {
            if (Door.isOpen())
                Door.close();
            else
                Door.open();
            break;
        }
            
    }
    
    updateView(wHeight, wWidth);
}



void Light0(){
    float position[] = {0.0, 3.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    float color_write[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, color_write);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color_write);
    glLightfv(GL_LIGHT0, GL_SPECULAR, color_write );
    glLightfv(GL_LIGHT0, GL_EMISSION, color_write );
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.03f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
    
    glEnable(GL_LIGHT0);
}


void Light1(){
    float position[] = {0.0, 100.0, 0.0, 0.0};
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    
    float color_write[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_AMBIENT, color_write);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color_write);
    glLightfv(GL_LIGHT1, GL_SPECULAR, color_write );
    glLightfv(GL_LIGHT1, GL_EMISSION, color_write );
    
    glEnable(GL_LIGHT1);
}




void redraw()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
    
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    Light0();
    //Light1();

    glRotatef(fRotate, 0, 1.0f, 0);
    
    glShadeModel(GL_SMOOTH);
    
    Draw_Scene();
    
    if (bAnim) fRotate += 0.4f;
    glutSwapBuffers();
}





void init(){
    
    Dumbbell.loadOBJ(filePrefix + "Models/airboat", "airboat.obj");
    Dumbbell.unitize();
    
//    Ball.loadOBJ(filePrefix +"Models/", "chair.obj");
//    Ball.unitize();
    
    iPad.loadOBJ(filePrefix +"Models/", "lion.obj");
    iPad.unitize();
    
    Woman.loadOBJ(filePrefix +"Models/bed", "bed.obj");
    Woman.unitize();

    Apple.loadOBJ(filePrefix +"Models/whale", "whale.obj");
    Apple.unitize();
//
//    City.loadOBJ(filePrefix +"Models/bed", "bed.obj");
    
//    Monitor.loadOBJ(filePrefix +"Models/Monitor", "Monitor.obj");
//    Monitor.unitize();
//    Monitor.setVideo("screen", 7, "video");
//    Monitor.play();
    
    Door.loadOBJ(filePrefix +"Models/Door", "Door.obj");
    Door.unitize();

    
    WallList = glGenLists(1);
    glNewList(WallList, GL_COMPILE);
    glPushMatrix();
    glScalef(10, 3, 10);
    texSolidCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, 20);
    glScalef(10, 3, 10);
    texSolidCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, 20);
    glScalef(10, 3, 10);
    texSolidCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, 20);
    glScalef(10, 3, 10);
    texSolidCube();
    glPopMatrix();
    
    glEndList();
    
}

struct str
{
    int x,y;
}oldpt;

void Mouse(int button, int state, int x, int y)        /*当鼠标按下或拿起时会回调该函数*/
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
//        l_button_down = TRUE;                /*当l_button_down为true时才可改变相机位置*/
        oldpt.x=x;                      /*记录旧坐标，以便移动发生时计算鼠标移动方向*/
        oldpt.y=y;
        printf("鼠标左键按下\n");
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
//        l_button_down = FALSE;        /*拿起时不能改变摄像机位置*/
        printf("鼠标左键松开\n");
    }
}

void OnMouseMove(int x, int y)          /*当鼠标移动时会回调该函数*/
{
    angle-=(x-oldpt.x)/100.0;
    center[1]-=(y-oldpt.y)/50.0;
    oldpt.x=x;
    oldpt.y=y;
    center[0]=-5.0f*sin(angle)+eye[0];
    center[2]=-5.0f*cos(angle)+eye[2];
    printf("%lf %lf\n",center[0],center[2]);
    printf("鼠标移动\n");
}

int main (int argc,  char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640,640);
    int windowHandle = glutCreateWindow("Simple GLUT App");
    
    init();
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    //zzzzzzzzzzzzzzzzzzzzzzzzz
    glutMouseFunc(Mouse);
    glutMotionFunc(OnMouseMove);
    //yyyyyyyyyyyyyyyyyyyyyyyyy
    glutIdleFunc(idle);
    
    
    glutMainLoop();
    return 0;
}


