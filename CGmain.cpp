#include "CGdrive.h"
#include "CGdraw.h"
#include "CGcamera.h"
#include "ShaderSource.h"

float rf[] = { 0.91f, 0.92f, 0.92f };
float roughness = 1.0f;
void renderScene(void) {
	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	pan();
	zoomToFit();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	//Use Shader
	glLightfv(GL_LIGHT0, GL_POSITION, light[currentlight].lightPosition);
	GLint currentProgram = programs[currentShader];
	if (currentShader == 0)
		glUseProgram(currentProgram);
	else
		glUseProgram(0);
	glUniform3fv(glGetUniformLocation(currentProgram, "lightPos"), 1, light[currentlight].lightPosition);	
	glUniform3fv(glGetUniformLocation(currentProgram, "ambient"), 1, light[currentlight].lightAmbient);
	glUniform3fv(glGetUniformLocation(currentProgram, "diffuse"), 1, light[currentlight].lightDiffuse);
	glUniform3fv(glGetUniformLocation(currentProgram, "rf"), 1, rf);
	glUniform1f(glGetUniformLocation(currentProgram, "roughness"), roughness);
	//glutSolidTeapot(1);
	GLfloat white[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat highwhite[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };//{ 0.95, 0.60, 0.75 ,1.0}; //pink
	GLfloat dark[] = { 0.0, 0.0, 0.0, 1.0 };
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, highwhite);
	glEnable(GL_LIGHT0);
	//画了一个地面
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(light[currentlight].lightPosition[0], light[currentlight].lightPosition[1], light[currentlight].lightPosition[2]);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//画了36个雪人

	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
		glPushMatrix();
		glTranslatef(i*10.0, 0, j * 10.0);
		glCallList(snowman_display_list);;
		glPopMatrix();
		}
	glutSwapBuffers();
	glutPostRedisplay();
}

void initScene() {
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	snowman_display_list = createDL();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutCreateWindow("SnowMen from 3D-Tech");
	glewInit();
		
	initShaderList();
	initLightlist();
	initScene();

	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(pressKey);		//Move Control by Keyboard
	glutSpecialUpFunc(releaseKey);	//Move Control by Keyboard
	glutKeyboardFunc(lightpressKey);		//Light Control
	glutMouseFunc(mouseClick);		//Move Control by Mouse click
	glutMotionFunc(mouseMove);		//Move Control by Mouse move

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutReshapeFunc(changeSize);

	glutMainLoop();

	return(0);
}



