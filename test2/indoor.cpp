//
//  indoor.cpp
//  opengltest
//
//  Created by Victor Young on 12/25/15.
//  Copyright (c) 2015 Victor Young. All rights reserved.
//

//model类用于读和画obj
//bmpReader类用于读bmp来画纹理
//需要加入zoom in/out功能 我之前发的world.c并没有实现这个功能，他用的是glTranslatef循环变化z轴，利用棋盘的周期规律做的。。
//纹理这一块有点混乱的，但是用bmpReader.imgdata代入glTexImage2D函数应该是可以用的
//（本来是可以正常加图片纹理的，后来代码增改了，就bug了，我还没改，全注释掉了）


#include <stdlib.h>
#include <stdio.h>
//#include "gl/glew.h"
// #include "glut/glut.h"
#include "simpleDraw.h"
#include "Headers.h"
//#pragma comment (lib, "glew32.lib")

#define checkImageWidth 64
#define checkImageHeight 64
#define KEY_SENSITY 2
#define MOUSE_SENSITIVITY 0.333f
#define STEP .10f  // WALKING SPEED. @ 60 updates/second, walk speed = 6 units/second


static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

// size of window in OS
static int WIDTH = 800;
static int HEIGHT = 400;
// zoom scale, converted to logarithmic
static float ZOOM = 15.0f;     // POLAR PERSPECTIVE

static GLfloat xrot=0;
static GLfloat yrot=0;
static int mouseTotalOffsetX = 0;  // since program began
static int mouseTotalOffsetY = 0;
static int mouseDragOffsetX = 0;  // dragging during one session (between click and release)
static int mouseDragOffsetY = 0;
static int mouseDragStartX, mouseDragStartY, mouseTotalOffsetStartX, mouseTotalOffsetStartY;
// INPUT HANDLING
static unsigned int UP_PRESSED = 0;    // KEY UP:0   KEY DOWN:1
static unsigned int DOWN_PRESSED = 0;
static unsigned int RIGHT_PRESSED = 0;
static unsigned int LEFT_PRESSED = 0;
static unsigned int PLUS_PRESSED = 0;
static unsigned int MINUS_PRESSED = 0;
static unsigned int COMMA_PRESSED = 0;
static unsigned int PERIOD_PRESSED = 0;
static unsigned int FLOAT_UP_PRESSED = 0;
static unsigned int FLOAT_DOWN_PRESSED = 0;
// PERSPECTIVES
static float originX = 0.0f;
static float originY = 0.0f;
static float originZ = 0.0f;

Model modelManager[4];
unsigned int textureObjects[6];
char bmppath[] = "/Volumes/mac/Mac Download/openglModel-master/textures/";
char objpath[] = "/Volumes/mac/Mac Download/openglModel-master/objs/";
//绘制地面纹理图案
void makeCheckImage(void)
{
    int i, j, c;
    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = ((((i&0x16)==0)^((j&0x16))==0))*255;
            checkImage[i][j][0] = (GLubyte) c;
            checkImage[i][j][1] = (GLubyte) c;
            checkImage[i][j][2] = (GLubyte) c;
            checkImage[i][j][3] = (GLubyte) 255;
        }
    }

}

////////////////////////////////////////////////////
// MANAGE PERSPECTIVE
//     first persion perspective, polar, orthographic
typedef enum{
    FPP,  POLAR,  ORTHO
} perspective_t;

static perspective_t POV = FPP;

//初始化
void SetupRC(void)
{
    glEnable(GL_LIGHTING);		//启用灯源
    glEnable(GL_LIGHT0);		//启用0号灯
    glShadeModel(GL_SMOOTH);    //设置光滑着色模式
    glEnable(GL_DEPTH_TEST);	//启用深度测试
    glEnable(GL_NORMALIZE);		//启用法向量
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   //为色彩缓冲区指定用于清除的值

    //设置表面材料的属性
    GLfloat mat_ambient[] = {0.6f,0.6f,0.6f,1.0f};
    GLfloat mat_diffuse[] = {0.5inf,0.5f,0.5f,1.0f};
    GLfloat mat_specular[] = {1.0f,1.0f,1.0f,1.0f,};
    GLfloat mat_shininess[] = {40.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);		//指定环境泛光的强度
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);		//漫反射的强度
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//镜面反射的强度
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);	//镜面反射光的会聚强度

    //纹理
    makeCheckImage();						//绘制地面纹理图案
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	//控制像素存储模式
    glGenTextures(1, &texName);				//用来生成纹理的数量为1
    glBindTexture(GL_TEXTURE_2D, texName);	//绑定纹理

    //纹理滤波，图象从纹理图象空间映射到帧缓冲图象空间
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                 checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
    
    
    BmpReader bmpManager;
    
    
    bmpManager.readBMP(strcat(bmppath,"floor.bmp"));
//    glEnable (GL_TEXTURE_2D);
    glGenTextures(6, textureObjects);
//    glBindTexture (GL_TEXTURE_2D, textureObjects[0]);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                  bmpManager.imgdata);
    bmpManager.clear();
    

    modelManager[0].readObj(strcat(objpath,"Cow_dABF.obj"));
//    modelManager[1].readObj(strcat(objpath,"grass.obj"));
//    modelManager[2].readObj(strcat(objpath,"city.obj"));
//    modelManager[3].readObj(strcat(objpath,"monster.obj"));

}

//float modulusContext(float complete, int modulus){
//    double wholePart;
//    double fracPart = modf(complete, &wholePart);
//    return ( ((int)wholePart) % modulus ) + fracPart;
//}

// when mouse button state changes
void mouseButtons(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(!state){  // button down
            mouseDragStartX = x;
            mouseDragStartY = y;
            mouseTotalOffsetStartX = mouseTotalOffsetX;
            mouseTotalOffsetStartY = mouseTotalOffsetY;
        }
        else { }    // button up
    }
    // else if(button == GLUT_MIDDLE_BUTTON){}
    // else if(button == GLUT_RIGHT_BUTTON){}
}

// when mouse is dragging screen
void mouseMotion(int x, int y){
    mouseDragOffsetX = mouseDragStartX - x;
    mouseDragOffsetY = mouseDragStartY - y;
    mouseTotalOffsetX = mouseTotalOffsetStartX + mouseDragOffsetX;
    mouseTotalOffsetY = mouseTotalOffsetStartY + mouseDragOffsetY;
    glutPostRedisplay();
}

void reshape(int w, int h){
    WIDTH = w;
    HEIGHT = h;
    float a = (float)WIDTH / HEIGHT;
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(POV == FPP || POV == POLAR)
        glFrustum (-.1, .1, -.1/a, .1/a, .1, 100.0);
    else if (POV == ORTHO)
        glOrtho(-ZOOM, ZOOM,
                -ZOOM/a, ZOOM/a,
                -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// process input devices if in first person perspective mode
void update(){
    float lookAzimuth = 0;
    // map movement direction to the direction the person is facing
    if(POV == FPP)
        lookAzimuth = (mouseTotalOffsetX * MOUSE_SENSITIVITY)/180.*M_PI;
    
    if(UP_PRESSED){
        originX += STEP * sinf(lookAzimuth);
        originY += STEP * -cosf(lookAzimuth);
    }
    if(DOWN_PRESSED){
        originX -= STEP * sinf(lookAzimuth);
        originY -= STEP * -cosf(lookAzimuth);
    }
    if(LEFT_PRESSED){
        originX -= STEP * sinf(lookAzimuth+M_PI_2);
        originY -= STEP * -cosf(lookAzimuth+M_PI_2);
    }
    if(RIGHT_PRESSED){
        originX += STEP * sinf(lookAzimuth+M_PI_2);
        originY += STEP * -cosf(lookAzimuth+M_PI_2);
    }
    if(FLOAT_UP_PRESSED){
        // float x =  sinf(lookAzimuth+M_PI_HALF);
        // float y = cosf(lookAzimuth+M_PI_HALF);
        // xPos += x;
        // yPos += y;
        originZ -= STEP;
    }
    if(FLOAT_DOWN_PRESSED){
        // float x =  sinf(lookAzimuth+M_PI_HALF);
        // float y = cosf(lookAzimuth+M_PI_HALF);
        // xPos += x;
        // yPos += y;
        originZ += STEP;
    }
    if(MINUS_PRESSED){
        ZOOM += STEP;
        reshape(WIDTH, HEIGHT);
        glutPostRedisplay();
    }
    if(PLUS_PRESSED){
        ZOOM -= STEP;
        if(ZOOM < 0)
            ZOOM = 0;
        reshape(WIDTH, HEIGHT);
        glutPostRedisplay();
    }
    // if(COMMA_PRESSED)
    // 	ZOOM -= STEP * .25;
    // if(PERIOD_PRESSED)
    // 	ZOOM += STEP * .25;
    
    
    glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y){
    if(key == 27)  // ESCAPE key
        exit (0);
    // W A S D
    else if(key == 119) // W
        UP_PRESSED = 1;
    else if(key == 115) // S
        DOWN_PRESSED = 1;
    else if(key == 97) // A
        RIGHT_PRESSED = 1;
    else if(key == 100)  // D
        LEFT_PRESSED = 1;
    else if(key == 113)  // Q
        FLOAT_UP_PRESSED = 1;
    else if (key == 122) // Z
        FLOAT_DOWN_PRESSED = 1;
//    else if(key == '+' || key == '=') // PLUS
//        PLUS_PRESSED = 1;
//    else if(key == '-' || key == '_') // MINUS
//        MINUS_PRESSED = 1;
//    else if(key == ',' || key == '<') // COMMA
//        COMMA_PRESSED = 1;
//    else if(key == '.' || key == '>') // PERIOD
//        PERIOD_PRESSED = 1;
//    else if(key == ' '){  // SPACE BAR
//        landscape = (landscape+1)%3;
//        if(landscape == 2)
//            originX = originY = originZ = 0.0f;
//        reshape(WIDTH, HEIGHT);
//        glutPostRedisplay();
//    }
//    else if(key == 'f'){
//        if(!FULLSCREEN)
//            glutFullScreen();
//        else{
//            reshape(WIDTH, HEIGHT);
//            glutPositionWindow(0,0);
//        }
//        FULLSCREEN = !FULLSCREEN;
//    }
    else if(key == '1'){
        POV = FPP;
        // mouseTotalOffsetX = mouseTotalOffsetY = 0;
        reshape(WIDTH, HEIGHT);
        glutPostRedisplay();
    }
//    else if(key == '2'){
//        POV = POLAR;
//        // mouseTotalOffsetX = mouseTotalOffsetY = 0;
//        reshape(WIDTH, HEIGHT);
//        glutPostRedisplay();
//    }
//    else if(key == '3'){
//        POV = ORTHO;
//        mouseTotalOffsetX = mouseTotalOffsetY = 0;
//        reshape(WIDTH, HEIGHT);
//        glutPostRedisplay();
//    }
    
    // anything that affects the screen and requires a redisplay
    // put it in this if statement
    if(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED || PLUS_PRESSED || MINUS_PRESSED || PERIOD_PRESSED || COMMA_PRESSED || FLOAT_UP_PRESSED || FLOAT_DOWN_PRESSED){
        glutIdleFunc(update);
    }
}

void keyboardUp(unsigned char key,int x,int y){
    if(key == 119) // W
        UP_PRESSED = 0;
    else if(key == 115) // S
        DOWN_PRESSED = 0;
    else if(key == 97) // A
        RIGHT_PRESSED = 0;
    else if(key == 100) // D
        LEFT_PRESSED = 0;
    else if(key == 113)  // Q
        FLOAT_UP_PRESSED = 0;
    else if (key == 122) // Z
        FLOAT_DOWN_PRESSED = 0;
//    else if(key == '+' || key == '=') // PLUS
//        PLUS_PRESSED = 0;
//    else if(key == '-' || key == '_') // MINUS
//        MINUS_PRESSED = 0;
//    else if(key == ',' || key == '<') // COMMA
//        COMMA_PRESSED = 0;
//    else if(key == '.' || key == '>') // PERIOD
//        PERIOD_PRESSED = 0;
    
    if(!(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED || PLUS_PRESSED || MINUS_PRESSED || PERIOD_PRESSED || COMMA_PRESSED || FLOAT_UP_PRESSED || FLOAT_DOWN_PRESSED))
        glutIdleFunc(NULL);
}


void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
    glPushMatrix();
//    glRotatef(10*MOUSE_SENSITIVITY, 0, 0, 1);

    switch(POV){
        case FPP:
            glRotatef(-mouseTotalOffsetY * MOUSE_SENSITIVITY, 1, 0, 0);
            glRotatef(-mouseTotalOffsetX * MOUSE_SENSITIVITY, 0, 1, 0);
            // raise POV 1.0 above the floor, 1.0 is an arbitrary value
            glTranslatef(0.0f, 0.0f, -1.0f);
            break;
            
        case POLAR:
            glTranslatef(0, 0, -ZOOM);
            glRotatef(-mouseTotalOffsetY * MOUSE_SENSITIVITY, 1, 0, 0);
            glRotatef(-mouseTotalOffsetX * MOUSE_SENSITIVITY, 0, 0, 1);
            break;
            
        case ORTHO:
            glTranslatef(-mouseTotalOffsetX * (ZOOM/400.0f), mouseTotalOffsetY * (ZOOM/400.0f), 0.0f);
            break;
    }
    glPushMatrix();

//    float newX = modulusContext(originX, 4);
//    float newY = modulusContext(originY, 4);
//    float newZ = modulusContext(originZ, 2);
    glTranslatef(originX, originY, originZ);
    
    glEnable(GL_TEXTURE_2D);		//开启纹理
        glBindTexture (GL_TEXTURE_2D, textureObjects[0]);


    GLfloat light_position[]={2.0f, 6.0f, 3.0f, 0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);  //指定0号光源的位置

    glMatrixMode(GL_PROJECTION);                       //对投影矩阵应用随后的矩阵操作
    glLoadIdentity();			                       //将当前的用户坐标系的原点移到了屏幕中心
    GLfloat h = 1.0;			                       //窗口的一半高度
    glOrtho(-h*64/48.0, h*64/48.0, -h, h, 0.1, 100.0); //将当前的可视空间设置为正投影空间：左，右，下，上，近，远。

    glMatrixMode(GL_MODELVIEW);	                       //对模型视景矩阵堆栈应用随后的矩阵操作
//    glLoadIdentity();
    gluLookAt(14, 4.6, 14, 0, 0.2, 0, 0, 1, 0);		//设置观察坐标系

    //开始绘制
//    glRotatef(xrot, 1.0f, 0.0f, 0.0f);				//旋转轴经过原点，方向为(1,0,0),旋转角度为xrot，方向满足右手定则
//    glRotatef(yrot, 0.0f, 1.0f, 0.0f);              //旋转轴经过原点，方向为(0,1,0)，旋转角度为yrot
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    
    glRotated(90.0, 0.0, 0.0, 1.0);

    DrawWall();				//绘制一面墙壁
    glPopMatrix();

    glPushMatrix();

    glRotated(-90.0, 1.0, 0.0, 0.0);
    DrawWall();				//绘制另一面墙壁
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.4, 0, 0.4);
    DrawTable();			//绘制桌子
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.4, 0.4, 0.4);
    glScaled(0.2, 0.2, 0.2);
    modelManager[0].drawModel();
//    Draw_Scene();			//绘制桌子
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.2, 0.1, 0.85);
    glScaled(0.8, 0.8, 1.0);
    glutSolidCube(0.2);		//绘制箱子
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.6, 0.38, 0.6);
    glRotated(-100, 0, 1, 0);
    glutSolidTeapot(0.1);	//绘制茶壶
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.3, 0.33, 0.5);
    glRotated(180, 0, 180, 180);
    glutSolidTorus(0.02f, 0.05, 25, 50);//绘制手镯 【丝状花环】
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.45, 0.42, 0.3);
    glutSolidSphere(0.1, 15, 50);		//绘制球体
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 0.35, 0.3);
    glScaled(0.03, 0.7, 0.03);
    glutSolidCube(1.0);					//绘制灯柱
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0, 0.7, 0.3);
    glRotated(190, 180, 200, 270);
    glutSolidCone(0.15, 0.25f, 30, 25);	//绘制圆锥型灯罩
    glPopMatrix();

    //绘制纹理
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//映射方式

    glBegin(GL_QUADS);				//绘制地面
    //绘制四边形并给出当前顶点所对应的纹理坐标
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(0.0, 0.0, 10.4);
    glTexCoord2f(2.0, 2.0); glVertex3f(10.4, 0.0, 10.4);
    glTexCoord2f(2.0, 0.0); glVertex3f(10.4, 0.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);		//关闭纹理
    glPopMatrix();
    glPopMatrix();

    glFlush();					//绘图结果显示到屏幕上
}

//处理按键交互信息
void SpecialKeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:		//上键
            xrot += 1.0*KEY_SENSITY;
            break;
        case GLUT_KEY_DOWN:		//下键
            xrot -= 1.0*KEY_SENSITY;
            break;
        case GLUT_KEY_LEFT:		//左键
            yrot += 1.0*KEY_SENSITY;
            break;
        case GLUT_KEY_RIGHT:	//右键
            yrot -= 1.0*KEY_SENSITY;
            break;
            
        default:
            break;
    }
    glutPostRedisplay();		//标记当前窗口需要重新绘制
//    glutSwapBuffers();
    glFlush();					//绘图结果显示到屏幕上
}

////改变窗口大小
//void ChangeSize(int w, int h)
//{
//    GLfloat lightPos[] = {-50.f, 50.0f, 100.0f, 1.0f};
//    GLfloat nRange = 1.9f;
//
//    if (h == 0)
//        h = 1;
//
//    glViewport(0, 0, w, h);		//重新设置屏幕上的窗口大小
//
//    glMatrixMode(GL_PROJECTION);//后继操作都在投影变换范围内
//    glLoadIdentity();			//设置当前矩阵为单位矩阵
//
//    //正交投影
//    if (w <= h)
//        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
//    else
//        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
//
//    glMatrixMode(GL_MODELVIEW);			//选择模型观察矩阵
//    glLoadIdentity();					//设置当前矩阵为单位矩阵
//
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);//重新定义光源
//}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	//双缓存
    glutInitWindowSize(600, 400);		//窗口大小
    glutInitWindowPosition(300, 100);	//窗口位置
    glutCreateWindow("xdy room");		//创建窗口，名为xdy room

    SetupRC();							//自定义的初始化函数
    glutDisplayFunc(RenderScene);		//显示回调函数，用于绘图
    glutKeyboardUpFunc(keyboardUp);
    glutKeyboardFunc(keyboardDown);
    glutMouseFunc(mouseButtons);
    glutMotionFunc(mouseMotion);

    glutReshapeFunc(reshape);		//处理改变窗口大小
    glutSpecialFunc(SpecialKeys);		//处理按键交互信息

    glutMainLoop();						//让GLUT框架开始运行, 处理交互事件
}
