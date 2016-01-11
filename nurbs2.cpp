
//
//  nurbs2.cpp
//  opengltest
//
//  Created by Victor Young on 1/10/16.
//  Copyright (c) 2016 Victor Young. All rights reserved.
//

//see http://www.glprogramming.com/red/chapter12.html



#include"nurbs.h"
#include <stdlib.h>
#include"CGdrive.h"

GLfloat ctrlpoints[5][5][3] = 
{ { { -5, 0, 0 },  { -3, 0, 0 }, {-1, 0, 0 },  { 1, 0, 0 }, { 3, 0, 0 }    },
{ { -5, 0, -1 },  { -3, 0, -1 },{ -1, 0, -1 },{ 1, 0, -1 },  { 3, 0, -1 }   },
{ { -5, 0, -2 },  { -3, 0, -2 },{ -1, 0, -2 },{ 1, 0, -2 },  { 3, 0, -2 }   },
{ { -5, 0, -3 },  { -3, 0, -3 },{ -1, 0, -3 },{ 1, 0, -3 },  { 3, 0, -3 }   },
{ { -5, 0, -4 },  { -3, 0, -4 },{ -1, 0, -4 },{ 1, 0, -4 },  { 3, 0, -4 }    } };//
bool showPoints = false;
float initheta = 0;
GLUnurbsObj *theNurb;

void init_surface(void)
{
    int u, v;
   /* for (u = 0; u < 4; u++) {
        for (v = 0; v < 4; v++) {
            ctlpoints[u][v][0] = 2.0*((GLfloat)u - 1.5);
            ctlpoints[u][v][1] = 2.0*((GLfloat)v - 1.5);
            
            if ( (u == 1 || u == 2) && (v == 1 || v == 2))
                ctlpoints[u][v][2] = 3.0;
            else
                ctlpoints[u][v][2] = -3.0;
        }
    }*/
	//¿ØÖÆµã
}
void wave(void){
	

	initheta += 0.005;
	float ph1 = 3.1415 /4; float ph2 = 3.1415 / 6;

	
	//printf("%lf,", err);
	if (initheta > 3.1415*2)initheta = 0;
	for (int i = 0; i < 5; i++){
		
		for (int j = 0; j < 5; j++){
			float ratio = j / 5.0*1.5;
			srand(time(0)*i*j);
			float err = ((float)rand() / RAND_MAX);
			ctrlpoints[i][j][1] = sin(initheta + ph1 *j + ph2*i + err)*(1+cos(initheta + ph1 *j + ph2*i + err))*ratio;
		}
		

	}
	
}


void initNurbs(void)
{
    GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    
    init_surface();
    
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
    //gluNurbsCallback(theNurb, GLU_ERROR,
          //           (GLvoid (*)()) nurbsError);
}

void drawNurb(void)
{
    //GLfloat knots[6] = {0.0, 0.0, 0.0,  1.0, 1.0, 1.0};
	GLfloat knots[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

    int i, j;
    
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(90.0, 1.,0.,0.);
	//glTranslatef(5.0,0, 5.0);
    glScalef (0.2, 0.2, 0.2);
    
    gluBeginSurface(theNurb);
   /* gluNurbsSurface(theNurb,
                    8, knots, 8, knots,
                    4 * 3, 3, &ctlpoints[0][0][0],
                    4, 4, GL_MAP2_VERTEX_3);*/
	gluNurbsSurface(theNurb, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	//gluNurbsSurface(theNurb, 6, knots, 6, knots, 3 * 3, 3, &ctrlpoints[0][0][0], 3, 3, GL_MAP2_VERTEX_3);

    gluEndSurface(theNurb);
    
    if (showPoints) {
        glPointSize(5.0);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (i = 0; i <5; i++) {
            for (j = 0; j < 5; j++) {
				glVertex3f(ctrlpoints[i][j][0],
					ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
            }
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}


