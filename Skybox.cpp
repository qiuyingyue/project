//
//  Skybox.cpp
//  opengltest
//
//  Created by Victor Young on 1/11/16.
//  Copyright (c) 2016 Victor Young. All rights reserved.
//

#include "Skybox.h"
#include "CGTexture.h"
#include <iostream>
using namespace std;

GLuint skybox[6];
int skytexture;

void initSkybox(void)
{
    /*
     SKY_FRONT 0
     SKY_RIGHT 1
     SKY_LEFT 2
     SKY_BACK 3
     SKY_UP 4
     SKY_DOWN 5
     */
    
	string prefix = "skybox/";
	skytexture = textpoint;
	string temp = prefix + "txStormydays_right.bmp";
	soil_texture(textpoint++, skybox[SKY_RIGHT], temp.c_str());
    temp = prefix + "txStormydays_front.bmp";
    soil_texture(textpoint++,skybox[SKY_FRONT],temp.c_str());
    temp = prefix + "txStormydays_left.bmp";
	soil_texture(textpoint++, skybox[SKY_LEFT], temp.c_str());
    temp = prefix + "txStormydays_back.bmp";
	soil_texture(textpoint++, skybox[SKY_BACK], temp.c_str());
    temp = prefix + "txStormydays_up.bmp";
	soil_texture(textpoint++, skybox[SKY_UP], temp.c_str());
    temp = prefix + "txStormydays_down.bmp";
	soil_texture(textpoint++, skybox[SKY_DOWN], temp.c_str());
}

void drawScene()
{
    drawSkybox(3.5*100);
}

/*
 *  drawSkybox(double D)
 *  ------
 *  Draws the skybox around the entire screen
 */
void drawSkybox(double D)
{
    float white[]={1,1,1,1};

    glColor3fv(white);
    glEnable(GL_TEXTURE_2D);
    
    /* Sides */
	int i = 0;
	glActiveTexture(GL_TEXTURE0 + skytexture + i);
	attachMaterial(0, skytexture + i, programs[currentShader]);
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
	glEnd();
	i++;
	glActiveTexture(GL_TEXTURE0 + skytexture + i);
	attachMaterial(0, skytexture + i, programs[currentShader]);
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
	glEnd();
	i++;
	glActiveTexture(GL_TEXTURE0 + skytexture + i);
	attachMaterial(0, skytexture + i, programs[currentShader]);
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
	glEnd();
	i++;
	glActiveTexture(GL_TEXTURE0 + skytexture + i);
	attachMaterial(0, skytexture + i, programs[currentShader]);
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
    glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
    glEnd();
    
    /* Top and Bottom */
	i++;
	glActiveTexture(GL_TEXTURE0 + skytexture + i);
	attachMaterial(0, skytexture + i, programs[currentShader]);
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_UP]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
	glEnd();
	i++;
	glActiveTexture(GL_TEXTURE0 + skytexture + i);
	attachMaterial(0, skytexture + i, programs[currentShader]);
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_DOWN]);
    glBegin(GL_QUADS);
    glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
    glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
    glEnd();
    
    //glDisable(GL_TEXTURE_2D);
}