//#include <stdlib.h>
//#include <GLUT/GLUT.h>
//#include <stdio.h>
//#include <string.h>
//#include <cmath>
//#include "model.h"
//#include "bmpReader.h"
//#include "Headers.h"
//
//using namespace std;
//float fTranslate;
//float fRotateX=0,fRotateY=0;
//float fScale     = 1.0f;	// set inital scale value to 1.0f
//float fDistance = 0.2f;
//
//bool bAnim = false;
//bool bWire = false;
//
//int wHeight = 0;
//int wWidth = 0;
//
//GLfloat light_pos[] = {0,10,0,1};
//GLfloat lightColor[] = {3.0, 3.0, 3.0, 1.0};
//Model modelManager[4];
//int chosenNum = -1, lastChosen = -1;
//
//unsigned int textureObjects[6];
//unsigned int backgroundTexture[6];
//
//typedef struct m{
//    float x;
//    float z;
//    float rotate;
//    bool isChose;
//}modelInfo;
//modelInfo cowArray[20];
//modelInfo monsterArray[25];
//
//
///************** mouse control begin ****************/
//const GLfloat PI = 3.1415;
//GLboolean mouserdown = GL_FALSE;
//GLboolean mouseldown = GL_FALSE;
//GLboolean mousemdown = GL_FALSE;
//static GLint mousex = 0, mousey = 0;
//GLfloat eye[3] = {20, 40, 20};
//GLfloat center[3] = {0, 0, 0};
//GLfloat direction[3] = {0, 1, 0};
//static GLfloat yrotate = PI/4; // angle between y-axis and look direction
//static GLfloat xrotate = PI/4; // angle between x-axis and look direction
//static GLfloat celength = 40.0f;// lenght between center and eye
//static GLfloat mSpeed = 1.0f; // center move speed
//static GLfloat rSpeed = 0.02f; // rotate speed
//static GLfloat lSpeed = 0.4f; // reserved
//
//
//void CalEyePostion()
//{
//    if(yrotate > PI/1.5) yrotate = PI/1.5;  // 视角限制
//    if(yrotate < 0.01)  yrotate = 0.01;
//    if(xrotate > 2*PI)   xrotate = 0.01;
//    if(xrotate < 0)   xrotate = 2 * PI;
//    if(celength > 100)  celength = 100;     //  缩放距离限制
//    if(celength < 1.5)   celength = 1.5;
//    // 下面利用球坐标系计算 center 的位置，
//    center[0] = eye[0] - celength * sin(yrotate) * cos(xrotate);
//    center[2] = eye[2] - celength * sin(yrotate) * sin(xrotate);
//    center[1] = eye[1] - celength * cos(yrotate);
//}
//
//
//
//void MouseFunc(int button, int state, int x, int y)
//{
//    if(state == GLUT_DOWN)
//    {
//        if(button == GLUT_RIGHT_BUTTON){
//            mouserdown = GL_TRUE;
//        }
//        if(button == GLUT_LEFT_BUTTON){
//            mouseldown = GL_TRUE;
//        }
//        if(button == GLUT_MIDDLE_BUTTON) mousemdown = GL_TRUE;
//    }
//    else
//    {
//        if(button == GLUT_RIGHT_BUTTON) mouserdown = GL_FALSE;
//        if(button == GLUT_LEFT_BUTTON) mouseldown = GL_FALSE;
//        if(button == GLUT_MIDDLE_BUTTON) mousemdown = GL_FALSE;
//    }
//    if(button == 3 || button == 4)
//        cout<<"hei"<<endl;
//    mousex = x, mousey = y;
//}
//
//float rotateState = 0;
//
//void MouseMotion(int x, int y)
//{
//    if(mouserdown == GL_TRUE){
//        if(y>mousey && y>350 && y>x && y+x > 600){                      //south area
//            yrotate -= (y-mousey)/180.0f;        }
//        if(y<mousey && y<250 && y<x && y+x < 600){                      //north area
//            yrotate -= (y-mousey)/180.0f;
//        }
////        if(x<mousex && x<250 && y>x && y+x <600){                      //west area
////            xrotate += (x - mousex) / 300.0f;
////        }
////        if(x>mousex && x>350 && y<x && y+x > 600){                      //east area
////            xrotate += (x - mousex) / 300.0f;
////        }
//        if(x<mousex && x<250 && y>x && y+x <600){                      //west area
//            rotateState += (x-mousex)/300.0f;
//            direction[0] = sin(rotateState);
//            direction[1] = cos(rotateState);
//        }
//        if(x>mousex && x>350 && y<x && y+x > 600){                      //east area
//            rotateState += (x-mousex)/300.0f;
//            direction[0] = sin(rotateState);
//            direction[1] = cos(rotateState);
//            
//        }
//
//
//    }
//    
//    if(mouseldown == GL_TRUE){
//        if(y>mousey && y>350 && y>x && y+x > 600){                      //south area
//            eye[0] += mSpeed * cos(xrotate);
//            eye[1] += mSpeed * cos(yrotate);
//            eye[2] += mSpeed * sin(xrotate);
//        }
//        if(y<mousey && y<250 && y<x && y+x < 600){                      //north area
//            eye[0] -= mSpeed * cos(xrotate);
//            eye[1] -= mSpeed * cos(yrotate);
//            eye[2] -= mSpeed * sin(xrotate);
//
//        }
////        if(x<mousex && x<250 && y>x && y+x <600){                      //west area
////            rotateState += (x-mousex)/300.0f;
////            direction[0] = sin(rotateState);
////            direction[1] = cos(rotateState);
////        }
////        if(x>mousex && x>350 && y<x && y+x > 600){                      //east area
////            rotateState += (x-mousex)/300.0f;
////            direction[0] = sin(rotateState);
////            direction[1] = cos(rotateState);
////
////        }
//        if(x<mousex && x<250 && y>x && y+x <600){                      //west area
//            xrotate += (x - mousex) / 300.0f;
//        }
//        if(x>mousex && x>350 && y<x && y+x > 600){                      //east area
//            xrotate += (x - mousex) / 300.0f;
//        }
//    }
//    mousex = x, mousey = y;
//    CalEyePostion();
//    glutPostRedisplay();
//}
//
//void LookAt()
//{
//    if(mouseldown == true && mousey > 400){
//        eye[0] += mSpeed * cos(xrotate);
//        eye[1] += mSpeed * cos(yrotate);
//        eye[2] += mSpeed * sin(xrotate);
//    }
//    if(mouseldown == true && mousey < 200){
//        eye[0] -= mSpeed * cos(xrotate);
//        eye[1] -= mSpeed * cos(yrotate);
//        eye[2] -= mSpeed * sin(xrotate);
//    }
//    CalEyePostion();
//    gluLookAt(eye[0], eye[1], eye[2],
//              center[0], center[1], center[2],
//              direction[0], direction[1], direction[2]);
//}
///************** mouse control end ******************/
//
//
//void updateView(int width, int height)
//{
//    glViewport(0,0,width,height);						// Reset The Current Viewport
//    
//    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
//    glLoadIdentity();									// Reset The Projection Matrix
//    
//    float whRatio = (GLfloat)width/(GLfloat)height;
//
//    gluPerspective(45,1,1,400);
//    
//    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
//}
//
//void reshape(int width, int height)
//{
//    if (height==0)										// Prevent A Divide By Zero By
//    {
//        height=1;										// Making Height Equal One
//    }
//    
//    wHeight = height;
//    wWidth = width;
//    
//    updateView(wHeight, wWidth);
//}
//
//void idle()
//{
//    glutPostRedisplay();
//}
//
//
//void key(unsigned char k, int x, int y)
//{
//    switch(k)
//    {
//        case 'q': exit(0); break;
//        case '[':                           //降低光源强度
//            for (int i = 0; i < 3; i++) {
//                if(lightColor[i]>1){
//                    lightColor[i]--;
//                }
//                else
//                    break;
//            }
//            break;
//        case ']':                           //提高光源强度
//            for (int i = 0; i < 3; i++) {
//                if(lightColor[i]<4){
//                    lightColor[i]++;
//                }
//                else
//                    break;
//            }
//            break;
//        case ';':
//            for (int i = 0; i < 3; i++) {
//                if(light_pos[i]<500){
//                    light_pos[i]+=20;
//                }
//                else
//                    break;
//            }
//            break;
//        case '\'':
//            for (int i = 0; i < 3; i++) {
//                if(light_pos[i]>0){
//                    light_pos[i]-=20;
//                }
//                else
//                    break;
//            }
//            break;
//        case '.':                           //改变光源颜色
//            for (int i = 1; i < 3; i++) {
//                if(lightColor[i]>0){
//                    lightColor[i]-=1;
//                }
//                else
//                    break;
//            }
//            break;
//        case '/':
//            for (int i = 1; i < 3; i++) {
//                if(lightColor[i]<lightColor[0]){
//                    lightColor[i]+=1;
//                }
//                else
//                    break;
//            }
//            break;
//        case 'j':
//            if (chosenNum > 0) {
//                chosenNum --;
//            }
//            break;
//        case 'k':
//            if (chosenNum < 19) {
//                chosenNum ++;
//            }break;
//        case 'w':
//            if (chosenNum >= 0 && chosenNum <20) {
//                cowArray[chosenNum].x += 2;
//            }break;
//        case 's':
//            if (chosenNum >= 0 && chosenNum <20) {
//                cowArray[chosenNum].x -= 2;
//            }break;
//        case 'a':
//            if (chosenNum >= 0 && chosenNum <20) {
//                cowArray[chosenNum].z += 2;
//            }break;
//        case 'd':
//            if (chosenNum >= 0 && chosenNum <20) {
//                cowArray[chosenNum].z -= 2;
//            }break;
//        case ' ': bAnim = !bAnim; break;
//    }
//    glutPostRedisplay();
//}
//
//void drawSkybox(double D)
//{
////    glColor3f(1,1,1);
//    glPushMatrix();
//    glBindTexture(GL_TEXTURE_2D, backgroundTexture[0]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0,0); glVertex3f(-D,-D+10,-D);
//    glTexCoord2f(1,0); glVertex3f(+D,-D+10,-D);
//    glTexCoord2f(1,1); glVertex3f(+D,+D+10,-D);
//    glTexCoord2f(0,1); glVertex3f(-D,+D+10,-D);
//    glEnd();
//    
//    // Render the left quad
//    glBindTexture(GL_TEXTURE_2D, backgroundTexture[1]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0,0); glVertex3f(+D,-D+10,-D);
//    glTexCoord2f(1,0); glVertex3f(+D,-D+10,+D);
//    glTexCoord2f(1,1); glVertex3f(+D,+D+10,+D);
//    glTexCoord2f(0,1); glVertex3f(+D,+D+10,-D);
//    glEnd();
//    
//    // Render the back quad
//    glBindTexture(GL_TEXTURE_2D, backgroundTexture[2]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0,0); glVertex3f(+D,-D+10,+D);
//    glTexCoord2f(1,0); glVertex3f(-D,-D+10,+D);
//    glTexCoord2f(1,1); glVertex3f(-D,+D+10,+D);
//    glTexCoord2f(0,1); glVertex3f(+D,+D+10,+D);
//    glEnd();
//    
//    // Render the right quad
//    glBindTexture(GL_TEXTURE_2D, backgroundTexture[3]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0,0); glVertex3f(-D,-D+10,+D);
//    glTexCoord2f(1,0); glVertex3f(-D,-D+10,-D);
//    glTexCoord2f(1,1); glVertex3f(-D,+D+10,-D);
//    glTexCoord2f(0,1); glVertex3f(-D,+D+10,+D);
//    glEnd();
//    
//    // Render the top quad
//    glBindTexture(GL_TEXTURE_2D, backgroundTexture[4]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0,0); glVertex3f(-D,+D+10,-D);
//    glTexCoord2f(1,0); glVertex3f(+D,+D+10,-D);
//    glTexCoord2f(1,1); glVertex3f(+D,+D+10,+D);
//    glTexCoord2f(0,1); glVertex3f(-D,+D+10,+D);
//    glEnd();
//    
//    // Render the bottom quad
//    glBindTexture(GL_TEXTURE_2D, backgroundTexture[5]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(1,1); glVertex3f(+D,-D+10,-D);
//    glTexCoord2f(0,1); glVertex3f(-D,-D+10,-D);
//    glTexCoord2f(0,0); glVertex3f(-D,-D+10,+D);
//    glTexCoord2f(1,0); glVertex3f(+D,-D+10,+D);
//    glEnd();
//    glPopMatrix();
//}
//
//void drawFloor(float D){
//    glPushMatrix();
//    glBindTexture (GL_TEXTURE_2D, textureObjects[0]);
//    glBegin( GL_QUADS );
//    {
//        glTexCoord2f(0,0);
//        glVertex3f( D, -1, D );
//        glTexCoord2f(0,1);
//        glVertex3f( -D, -1, D );
//        glTexCoord2f(1,0);
//        glVertex3f( -D, -1, -D);
//        glTexCoord2f(1,1);
//        glVertex3f( D, -1, -D );
//    }
//    glEnd();
//    glPopMatrix();
//}
//
//
//
//void drawCows(){
//    for (int i = 0; i < 20; i++) {
//        glPushMatrix();
//        if(i==chosenNum)
//            glBindTexture(GL_TEXTURE_2D, textureObjects[4]);
//        else
//            glBindTexture (GL_TEXTURE_2D, textureObjects[1]);
//        glTranslatef(cowArray[i].x, 0.0f,cowArray[i].z);
//        glRotatef(cowArray[i].rotate, 0, 1.0f, 0);
//        glRotatef(0, 1, 0, 0);
//        glScalef(2, 2, 2);
//        modelManager[0].drawModel();
//        glPopMatrix();
//    }
//    
//    for (int i = 0; i < 20; i++) {
//        if (bAnim && i == chosenNum) {
//            cowArray[i].rotate += 2;
//            break;
//        }
//    }
//}
//void drawGrass(){
//    glPushMatrix();
//    glBindTexture (GL_TEXTURE_2D, textureObjects[2]);
//    glTranslatef(-5.0f, 0.0f,-1.0f);             // Place the triangle at Center
//    glRotatef(0, 0, 1.0f, 0);			// Rotate around Y axis
//    glRotatef(fRotateY, 1, 0, 0);
//    glScalef(0.5, 0.5, 0.5);
//    modelManager[1].drawModel();
//    glPopMatrix();
//    
//    glPushMatrix();
//    glBindTexture (GL_TEXTURE_2D, textureObjects[2]);
//    glTranslatef(-5.0f, 0.0f,-5.0f);             // Place the triangle at Center
//    glRotatef(0, 0, 1.0f, 0);			// Rotate around Y axis
//    glRotatef(fRotateY, 1, 0, 0);
//    glScalef(0.5, 0.5, 0.5);
//    modelManager[1].drawModel();
//    glPopMatrix();
//    
//    glPushMatrix();
//    glBindTexture (GL_TEXTURE_2D, textureObjects[2]);
//    glTranslatef(5.0f, 0.0f,1.0f);
//    glRotatef(0, 0, 1.0f, 0);
//    glRotatef(fRotateY, 1, 0, 0);
//    glScalef(0.5, 0.5, 0.5);
//    modelManager[1].drawModel();
//    glPopMatrix();
//    
//    glPushMatrix();
//    glBindTexture (GL_TEXTURE_2D, textureObjects[2]);
//    glTranslatef(9.0f, 0.0f,1.0f);
//    glRotatef(0, 0, 1.0f, 0);
//    glRotatef(fRotateY, 1, 0, 0);
//    glScalef(0.6, 0.6, 0.6);
//    modelManager[1].drawModel();
//    glPopMatrix();
//    
//    glPushMatrix();
//    glBindTexture (GL_TEXTURE_2D, textureObjects[2]);
//    glTranslatef(-9.0f, 0.0f,1.0f);
//    glRotatef(0, 0, 1.0f, 0);
//    glRotatef(fRotateY, 1, 0, 0);
//    glScalef(0.6, 0.6, 0.6);
//    modelManager[1].drawModel();
//    glPopMatrix();
//    
//    glPushMatrix();
////    glBindTexture (GL_TEXTURE_2D, textureObjects[2]);
//    glTranslatef(-9.0f, 0.0f,10.0f);
//    glRotatef(0, 0, 1.0f, 0);
//    glRotatef(fRotateY, 1, 0, 0);
//    glScalef(0.6, 0.6, 0.6);
//    modelManager[1].drawModel();
//    glPopMatrix();
//    
//}
//
//void drawMonster(){
//    for (int i = 0; i < 25; i++) {
//        glPushMatrix();
//        glBindTexture (GL_TEXTURE_2D, textureObjects[4]);
//        glTranslatef(monsterArray[i].x, 3.0f,monsterArray[i].z);
//        glRotatef(0, 0, 1.0f, 0);
//        glRotatef(0, 1, 0, 0);
//        glScalef(3, 3, 3);
//        modelManager[3].drawModel();    
//        glPopMatrix();
//    }
//}
//
//void redraw()
//{
//    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();									// Reset The Current Modelview
//    LookAt();
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lightColor);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
//    glEnable(GL_LIGHT0);
//    
//    drawSkybox(150);
//    drawFloor(100);
//    drawCows();
//    drawGrass();
//    drawMonster();
//    Draw_Scene();
//    
//    glPushMatrix();
//    glBindTexture (GL_TEXTURE_2D, textureObjects[3]);
//    glTranslatef(-30.0f, 0.0f,-30.0f);
//    glRotatef(0, 0, 1.0f, 0);
//    glRotatef(fRotateY, 1, 0, 0);
//    glScalef(0.03, 0.03, 0.03);
//    modelManager[2].drawModel();
//    glPopMatrix();
//
//    
//    glutSwapBuffers();
//}
//
//void initCows(){
//    for (int i = 0; i < 20; i++) {
//        cowArray[i].isChose = false;
//        cowArray[i].rotate = 0;
//    }
//    cowArray[0].x = -12; cowArray[0].z = 3;
//    cowArray[1].x = -12; cowArray[1].z = -5;
//    cowArray[2].x = -9; cowArray[2].z = 5;
//    cowArray[3].x = -7; cowArray[3].z = -8;
//    cowArray[4].x = -5; cowArray[4].z = 20;
//    cowArray[5].x = -5; cowArray[5].z = 12;
//    cowArray[6].x = -3; cowArray[6].z = -3;
//    cowArray[7].x = -3; cowArray[7].z = -9;
//    cowArray[8].x = -3; cowArray[8].z = 10;
//    cowArray[9].x = -1; cowArray[9].z = 7;
//    cowArray[10].x = 0; cowArray[10].z = 0;
//    cowArray[11].x = 0; cowArray[11].z = 4;
//    cowArray[12].x = 3; cowArray[12].z = 7;
//    cowArray[13].x = 3; cowArray[13].z = 3;
//    cowArray[14].x = 3; cowArray[14].z = 18;
//    cowArray[15].x = 5; cowArray[15].z = 5;
//    cowArray[16].x = 7; cowArray[16].z = 7;
//    cowArray[17].x = 7; cowArray[17].z = 10;
//    cowArray[18].x = 7; cowArray[18].z = 12;
//    cowArray[19].x = 8; cowArray[19].z = 14;
//}
//
//void initMonster(){
//    for (int i = 0; i < 25; i++) {
//        monsterArray[i].x = 90 - (i/5)*10;
//        monsterArray[i].z = -30 - (i%5)*10;
//        monsterArray[i].rotate = 0;
//    }
//}
//
//bool init(){
//    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
//    modelManager[0].readObj("/Volumes/mac/Mac Download/openglModel-master/objs/Cow_dABF.obj");
//    modelManager[1].readObj("/Volumes/mac/Mac Download/openglModel-master/objs/grass.obj");
//    modelManager[2].readObj("/Volumes/mac/Mac Download/openglModel-master/objs/city.obj");
//    modelManager[3].readObj("/Volumes/mac/Mac Download/openglModel-master/objs/monster.obj");
//    
//    BmpReader bmpManager;
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/floor.bmp");
//    glEnable (GL_TEXTURE_2D);
//    glGenTextures(6, textureObjects);
//    glBindTexture (GL_TEXTURE_2D, textureObjects[0]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/cow.bmp");
//    glBindTexture (GL_TEXTURE_2D, textureObjects[1]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/grass.bmp");
//    glBindTexture (GL_TEXTURE_2D, textureObjects[2]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/city.bmp");
//    glBindTexture (GL_TEXTURE_2D, textureObjects[3]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/chosen.bmp");
//    glBindTexture (GL_TEXTURE_2D, textureObjects[4]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    
//    ///////////////skybox//////////////////////
//    glGenTextures(6, backgroundTexture);
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/right.bmp");
//    glBindTexture (GL_TEXTURE_2D, backgroundTexture[0]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/front.bmp");
//    glBindTexture (GL_TEXTURE_2D, backgroundTexture[1]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/left.bmp");
//    glBindTexture (GL_TEXTURE_2D, backgroundTexture[2]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/back.bmp");
//    glBindTexture (GL_TEXTURE_2D, backgroundTexture[3]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/up.bmp");
//    glBindTexture (GL_TEXTURE_2D, backgroundTexture[4]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    bmpManager.readBMP("/Volumes/mac/Mac Download/openglModel-master/textures/down.bmp");
//    glBindTexture (GL_TEXTURE_2D, backgroundTexture[5]);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
//                  bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
//                  bmpManager.imgdata);
//    bmpManager.clear();
//    
//    initCows();
//    initMonster();
//    return true;
//}
//
//int main (int argc,  char *argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
//    glutInitWindowSize(600,600);
//    int windowHandle = glutCreateWindow("My Model");
//    if(!init())
//        return 0;
//    glutDisplayFunc(redraw);
//    glutReshapeFunc(reshape);
//    glutKeyboardFunc(key);
//    glutMouseFunc(MouseFunc);    //鼠标按键
//    glutMotionFunc(MouseMotion); //鼠标移动
//    glutIdleFunc(idle);
//    
//    glutMainLoop();
//    return 0;
//}