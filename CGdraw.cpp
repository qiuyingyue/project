#include "CGdrive.h"

GLint snowman_display_list;  //һ��ѩ�˵���ʾ�б�����

void drawSnowMan() {
	glColor3f(1.0f, 1.0f, 1.0f);
	//������
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// ��ͷ
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// ���۾�
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// ������
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

GLuint createDL() {
	GLuint snowManDL;
	//����һ����ʾ�б��
	snowManDL = glGenLists(1);
	// ��ʼ��ʾ�б�
	glNewList(snowManDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	drawSnowMan();
	// endList
	glEndList();
	return(snowManDL);
}