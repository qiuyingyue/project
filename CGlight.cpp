#include "ShaderSource.h"
#include "CGcamera.h"

int LightSource::lightNum(1);
int movu = 1;
GLint currentlight;
float density = 0.6;
LightSource light[10];

// init the light number
void initLightlist(int num){
	currentlight = num;
	light[1].lightPosition[0] = 10;
	light[1].lightPosition[1] = -5;
	light[1].lightPosition[2] = 66;

}

// Refresh the light
void RefreshLight(GLuint currentProgram){
	glUniform1f(glGetUniformLocation(currentProgram, "density"), density);
	float pos[3] = { x + lx*wallunit/2, y + ly*wallunit/2, z + (lz+2)*wallunit/2 };
	light[0].lightPosition[0] = pos[0];
	light[0].lightPosition[1] = pos[1];
	light[0].lightPosition[2] = pos[2];
	//light[1].lightPosition[0] = 471;
	//light[1].lightPosition[1] = 0;
	//light[1].lightPosition[2] = 476;
	light[0].lightDiffuse[0] = light[0].lightDiffuse[1] = light[0].lightDiffuse[2] = 50.0f;
	light[1].lightDiffuse[0] = light[1].lightDiffuse[1] = light[1].lightDiffuse[2] = 100.0f;
	if (currentlight >= 0){
		glLightfv(GL_LIGHT0, GL_POSITION, light[0].lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light[0].lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light[0].lightDiffuse);
	}
	if (currentlight >= 1){
		glLightfv(GL_LIGHT1, GL_POSITION, light[1].lightPosition);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light[1].lightAmbient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light[1].lightDiffuse);
	}
	if (currentlight >= 2){
		glLightfv(GL_LIGHT2, GL_POSITION, light[2].lightPosition);
		glLightfv(GL_LIGHT2, GL_AMBIENT, light[2].lightAmbient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light[2].lightDiffuse);
	}
	if (currentlight >= 3){
		glLightfv(GL_LIGHT3, GL_POSITION, light[3].lightPosition);
		glLightfv(GL_LIGHT3, GL_AMBIENT, light[3].lightAmbient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light[3].lightDiffuse);
	}
}


LightSource::LightSource(){
	const float dAmbient[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	const float dDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const float dDirection[3] = { -0.57735f, -0.57735f, -0.57735f };
	const float dPostion[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const float dDistance = 10.0f;
	lightAmbient = new float[4];
	lightDiffuse = new float[4];
	lightDirection = new float[4];
	lightPosition = new float[4];
	lightDistance = dDistance;
	for (int i = 0; i < 4; i++)
		lightAmbient[i] = dAmbient[i];
	for (int i = 0; i < 4; i++)
		lightDiffuse[i] = dDiffuse[i];
	for (int i = 0; i < 3; i++)
		lightDirection[i] = dDirection[i];
	for (int i = 0; i < 4; i++)
		lightPosition[i] = dPostion[i];
}

void lightpressKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT: {
		light[currentlight].lightPosition[0] += movu;
		break; }
	case GLUT_KEY_LEFT: {
		light[currentlight].lightPosition[0] -= movu;
		break; }
	case GLUT_KEY_UP: {
		light[currentlight].lightPosition[1] += movu;
		break; }
	case GLUT_KEY_DOWN: {
		light[currentlight].lightPosition[1] -= movu;
		break; }
	case GLUT_KEY_PAGE_UP: {
		light[currentlight].lightPosition[2] += movu;
		break; }
	case GLUT_KEY_PAGE_DOWN: {
		light[currentlight].lightPosition[2] -= movu;
		break; }
	case GLUT_KEY_HOME: {
		density += 0.1;
		if (density > 1.0) density = 1.0;
		break; }
	case GLUT_KEY_END: {
		density -= 0.1;
		if (density < 0.1) density = 0.1;
		break; }
	}
	printf("%lf %lf %lf\n", light[currentlight].lightPosition[0], light[currentlight].lightPosition[1], light[currentlight].lightPosition[2]);
}