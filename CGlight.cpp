#include "ShaderSource.h"

int LightSource::lightNum(1);
int movu = 1;
GLint currentlight;
LightSource light[10];

void initLightlist(){
	currentlight = 0;
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
	/*float l = sqrtf(powf(lightDirection[0], 2) + powf(lightDirection[1], 2) + powf(lightDirection[2], 2));
	lightPosition[0] = -lightDistance*lightDirection[0] / l;
	lightPosition[1] = -lightDistance*lightDirection[1] / l;
	lightPosition[2] = -lightDistance*lightDirection[2] / l;
	lightPosition[3] = 1.0f;*/
}

void inputKey(unsigned char key, int x, int y) {
	switch (key) {
	case 'd': {
		light[currentlight].lightPosition[0] += movu;
		break; }
	case 'a': {
		light[currentlight].lightPosition[0] -= movu;
		break; }
	case 'w': {
		light[currentlight].lightPosition[1] += movu;
		break; }
	case 's': {
		light[currentlight].lightPosition[1] -= movu;
		break; }
	case 'z': {
		light[currentlight].lightPosition[2] += movu;
		break; }
	case 'x': {
		light[currentlight].lightPosition[2] -= movu;
		break; }
	}
}