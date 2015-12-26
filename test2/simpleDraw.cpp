//
//  simpleDraw.cpp
//  test2
//
//  Created by Victor Young on 12/26/15.
//  Copyright (c) 2015 FrozenShore. All rights reserved.
//

//这个文件里面存简单的glutSolidCube画出来的东西吧

#include "simpleDraw.h"
extern unsigned int textureObjects[6];
//void Draw_Leg()
//{
//    glScalef(1, 1, 3);
//    glutSolidCube(1.0);
//}
//
//void Draw_Scene()
//{
////    glBindTexture (GL_TEXTURE_2D, textureObjects[0]);
//    glPushMatrix();
//    glTranslatef(0, 0, 3.5);
//    glScalef(5, 4, 1);
//    glutSolidCube(1.0);
//    glPopMatrix();
//    
//    glPushMatrix();
//    glTranslatef(1.5, 1, 1.5);
//    Draw_Leg();
//    glPopMatrix();
//    
//    glPushMatrix();
//    glTranslatef(-1.5, 1, 1.5);
//    Draw_Leg();
//    glPopMatrix();
//    
//    glPushMatrix();
//    glTranslatef(1.5, -1, 1.5);
//    Draw_Leg();
//    glPopMatrix();
//    
//    glPushMatrix();
//    glTranslatef(-1.5, -1, 1.5);
//    Draw_Leg();
//    glPopMatrix();
//    
//}

//绘制墙壁
void DrawWall(void)
{
    glPushMatrix();                //矩阵堆栈压入
    glTranslated(8.2, 0.01, 8.2);  //将变换矩阵与当前矩阵相乘,使原点移动到（参数值坐标）
    glScaled(16.4, 0.02, 16.4);      //将比例矩阵与当前矩阵相乘,将当前图形沿x,y,z轴分别放大为原来的（参数值）倍
    glutSolidCube(1.0);            //size=1.0的实心立方体
    glPopMatrix();                 //矩阵堆栈弹出
}

//绘制立方柱体
void DrawPillar(void)
{
    glPushMatrix();
    glTranslated(0, 0.15, 0);
    glScaled(0.02, 0.3, 0.02);
    glutSolidCube(1.0);
    glPopMatrix();
}

//绘制桌子
void DrawTable(void)
{
    glPushMatrix();
//        glBindTexture (GL_TEXTURE_2D, textureObjects[0]);

    glTranslated(0.05, 0.3, 0.05);
    glScaled(0.6, 0.02, 0.6);
    glutSolidCube(1.0);		//绘制桌面
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0.275, 0, 0.275);
    DrawPillar();			//绘制桌腿
    glTranslated(0, 0, -0.45);
    DrawPillar();			//绘制桌腿
    glTranslated(-0.45, 0, 0.45);
    DrawPillar();			//绘制桌腿
    glTranslated(0, 0, -0.45);
    DrawPillar();			//绘制桌腿
    glPopMatrix();
}