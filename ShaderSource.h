#include "CGdrive.h"
class LightSource{
public:
	static int lightNum;
	float* lightAmbient;// [4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float* lightDiffuse;// [4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float* lightPosition;
	float* lightDirection;// [3] = { -0.57735f, -0.57735f, -0.57735f };
	float lightDistance;// = 10.0f;
	LightSource();
	LightSource(float *dDiffuse, float *dPostion){

	};
	~LightSource(){
		delete[] lightAmbient;
		delete[] lightDiffuse;
		delete[] lightDirection;
		delete[] lightPosition;
	};
};

class MaterialSource{
public:
	float *rf;				// The parameters of the Schlick fresnel item
	float roughness = 1.0f;	// The parameters of the materail roughness
	MaterialSource(){
		rf = new float[3];
	}
	void SetParameter(float r, float g, float b, float rn){
		rf[0] = r; rf[1] = g; rf[2] = b;
		roughness = rn;
	}
	~MaterialSource(){
		delete[] rf;
	}
};

//The list of the Material
class MaterialList{
public:
	MaterialSource *mList;
	int mNum;
	MaterialList();
	~MaterialList(){
		delete[] mList;
	};
};

extern LightSource light[10];
extern MaterialList material;
extern GLuint programs[NUM_SHADERS];
extern GLint currentlight;

void initShaderList();
void initLightlist(int num);
void RefreshLight(GLuint currentShader);

char *textFileRead(const char *fileName);
GLuint setupShaders(char *shaderName);
void lightpressKey(int key, int x, int y);
