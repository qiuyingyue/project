#include "CGdraw.h"

GLint snowman_display_list;  //一个雪人的显示列表索引
int wallunit = 3;

class ObjectWall wall[NUM_WALL];

void test(){
	/*float m[NUM_WALL][6] = {
			{ 19, CUBE_WIDTH / 2, CUBE_HEIGHT, 10, 1, 0 }, { CUBE_WIDTH / 2, 10, CUBE_HEIGHT, 1, 6, 0 }, { 7, CUBE_WIDTH / 2, CUBE_HEIGHT, 4, 11, 0 },
			{ CUBE_WIDTH / 2, 5, CUBE_HEIGHT, 8, 9, 0 }, { 5, CUBE_WIDTH / 2, CUBE_HEIGHT, 6, 8, 0 }, { CUBE_WIDTH / 2, 5, CUBE_HEIGHT, 4, 6, 0 },
			{ 5, CUBE_WIDTH / 2, CUBE_HEIGHT, 6, 4, 0 }, { CUBE_WIDTH / 2, 2, CUBE_HEIGHT, 8, 4.5, 0 }, { 9, CUBE_WIDTH / 2, CUBE_HEIGHT, 15, 4, 0 },
			{ 3, 5, CUBE_HEIGHT, 12, 6, 0 }, { CUBE_WIDTH / 2, CUBE_WIDTH / 2, CUBE_HEIGHT, 14, 6, 0 }, { 3, 2, CUBE_HEIGHT, 12, 10.5, 0 },
			{ 5, CUBE_WIDTH / 2, CUBE_HEIGHT, 16, 11, 0 }, { CUBE_WIDTH / 2, 11, CUBE_HEIGHT, 19, 6, 0 }, { 3, CUBE_WIDTH / 2, CUBE_HEIGHT, 17, 6, 0 },
			{ 19, 11, CUBE_WIDTH / 10, 10, 6, -CUBE_WIDTH / 10 }, { 6, 3, CUBE_WIDTH / 10, 9.5, 13, -CUBE_WIDTH / 10 }, { 19, 11, CUBE_WIDTH / 10, 10, 6, CUBE_HEIGHT }
	};*/
	float m[NUM_WALL][6] = {
			{ 19, CUBE_WIDTH, CUBE_HEIGHT, 10, 1, 0 }, { CUBE_WIDTH, 10, CUBE_HEIGHT, 1, 6, 0 }, { 7, CUBE_WIDTH, CUBE_HEIGHT, 4.5, 11, 0 },
			{ CUBE_WIDTH, 5, CUBE_HEIGHT, 8, 9, 0 }, { 4, CUBE_WIDTH, CUBE_HEIGHT, 6, 8, 0 }, { CUBE_WIDTH, 5, CUBE_HEIGHT, 4, 6, 0 },
			{ 4, CUBE_WIDTH, CUBE_HEIGHT, 6, 4, 0 }, { CUBE_WIDTH, 2, CUBE_HEIGHT, 8, 4.5, 0 }, { 6, CUBE_WIDTH, CUBE_HEIGHT, 16, 4, 0 },
			{ 3, 5, CUBE_HEIGHT, 12, 6, 0 }, { 2, CUBE_WIDTH, CUBE_HEIGHT, 14, 6, 0 }, { 3, 2, CUBE_HEIGHT, 12, 10.5, 0 },
			{ 6, CUBE_WIDTH, CUBE_HEIGHT, 16, 11, 0 }, { CUBE_WIDTH, 10, CUBE_HEIGHT, 19, 6, 0 }, { 4, CUBE_WIDTH, CUBE_HEIGHT, 17.5, 6, 0 },
			{ 19, 11, CUBE_WIDTH / 10, 10, 6, -CUBE_WIDTH/10 }, { 6, 4, CUBE_WIDTH / 10, 9.5, 12.5, -CUBE_WIDTH/5 }, { 19, 11, CUBE_WIDTH / 10, 10, 6, CUBE_HEIGHT }
	};
	for (int i = 0; i < NUM_WALL; i++){
		wall[i].width = (m[i][0] - CUBE_WIDTH / 2) * wallunit;
		wall[i].length = (m[i][1] - CUBE_WIDTH / 2) * wallunit;
		wall[i].height = (m[i][2]) * wallunit;
		wall[i].x = m[i][3] * wallunit;
		wall[i].y = m[i][4] * wallunit;
		wall[i].h = m[i][5] * wallunit;
	}
}


void ObjectWall::draw(){
	glPushMatrix();
	glScalef(width, height, length);
	glTranslatef(x / width, h / height + 0.5, y / length);
	glTexCubic();
	glPopMatrix();
}

void ObjectWall::glTexCubic(){
	glBegin(GL_QUADS); {
		glTexCoord2i(1, 1); glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, 0.5);
		glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, -0.5);
		glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, -0.5);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glTexCoord2i(1, 1); glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2i(0, 1); glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2i(0, 0); glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, 0.5);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glTexCoord2i(1, 1);	glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2i(0, 1);	glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord2i(0, 0);	glVertex3f(-0.5, -0.5, 0.5);
		glTexCoord2i(1, 0);	glVertex3f(0.5, -0.5, 0.5);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, 0.5);
		glTexCoord2i(0, 0); glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, -0.5);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2i(0, 1); glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2i(0, 0); glVertex3f(0.5, 0.5, -0.5);	
		glTexCoord2i(1, 0); glVertex3f(0.5, -0.5, -0.5);
	}
	glEnd();
	glBegin(GL_QUADS); {
		glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, -0.5);
		glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, 0.5);
		glTexCoord2i(1, 0); glVertex3f(-0.5, -0.5, 0.5);
	}
	glEnd();
}


void drawSnowMan() {
	glColor3f(1.0f, 1.0f, 1.0f);
	//画身体
	glTranslatef(0.0f, 0.75f, 0.0f);
	attachMaterial(2, programs[currentShader]);
	glutSolidSphere(0.75f, 20, 20);

	// 画头
	glTranslatef(0.0f, 1.0f, 0.0f);
	attachMaterial(1, programs[currentShader]);
	glutSolidSphere(0.25f, 20, 20);

	// 画眼睛
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	attachMaterial(3, programs[currentShader]);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// 画鼻子
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	attachMaterial(1, programs[currentShader]);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

GLuint createDL() {
	GLuint snowManDL;
	//生成一个显示列表号
	snowManDL = glGenLists(1);
	// 开始显示列表
	glNewList(snowManDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	drawSnowMan();
	// endList
	glEndList();
	return(snowManDL);
}