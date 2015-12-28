#include "CGdrive.h"
#define NUM_SHADERS 1
class LightSource{
public:
	static int lightNum;
	float* lightAmbient;// [4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float* lightDiffuse;// [4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float* lightPosition;
	float* lightDirection;// [3] = { -0.57735f, -0.57735f, -0.57735f };
	float lightDistance;// = 10.0f;
	LightSource();
	~LightSource(){
		delete[] lightAmbient;
		delete[] lightDiffuse;
		delete[] lightDirection;
		delete[] lightPosition;
	}
};

extern LightSource light[10];
extern GLuint programs[NUM_SHADERS];
extern GLint currentShader;
extern GLint currentlight;

void initShaderList();
void initLightlist();
char *textFileRead(const char *fileName);
GLuint setupShaders(char *shaderName);
void inputKey(unsigned char key, int x, int y);
