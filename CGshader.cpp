#include "ShaderSource.h"

GLuint vShader, fShader;
GLuint programs[NUM_SHADERS];
int currentShader;
// To read the shader text file for binding shader
char *textFileRead(const char *fileName)
{
	char *shaderText = NULL;
	GLint shaderLength = 0;
	FILE *fp;
	fp = fopen(fileName, "r");
	if (fp != NULL){
		//get the char length
		while (fgetc(fp) != EOF){
			shaderLength++;
		}
		rewind(fp);
		shaderText = (GLchar*)malloc(shaderLength);
		if (shaderText != NULL){
			fread(shaderText, 1, shaderLength, fp);
		}
		shaderText[shaderLength] = '\0';
		fclose(fp);
	}	
	return shaderText;
}

// Setup a shader with fragment and vertex shader file
GLuint setupShaders(char *shaderName){
	char vshaderFile[120];
	char fshaderFile[120];
	//Renew the filename for read
	sprintf(vshaderFile, "%s.vert", shaderName);
	sprintf(fshaderFile, "%s.frag", shaderName);
	//Read the shader file
	const GLchar *vShaderSource = textFileRead(vshaderFile);
	const GLchar *fShaderSource = textFileRead(fshaderFile);
	//Create null shader source
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Binding the shader file to the shader source
	glShaderSource(vShader, 1, &vShaderSource, NULL);
	glShaderSource(fShader, 1, &fShaderSource, NULL);
	//To check that if shader is successful used
	int success;
	//Compile the shader
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	//Print error infomation
	if (!success){
		char info_log[5000];
		glGetShaderInfoLog(vShader, 5000, NULL, info_log);
		printf("Error in vertex shader compilation!\n");
		printf("Info Log: %s\n", info_log);
	}
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success){
		char info_log[5000];
		glGetShaderInfoLog(fShader, 5000, NULL, info_log);
		printf("Error in fragment shader compilation!\n");
		printf("Info Log: %s\n", info_log);
	}
	//Create a shader program
	GLuint program = glCreateProgram();
	//Attach the shader to the program
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	//Link the program
	glLinkProgram(program);
	return program;
}

// Init the shader array
void initShaderList(){
	programs[0] = setupShaders("Cook-Torrorence");
	//for (int i = 1; i < NUM_SHADERS ; i++)
		//programs[i] = setupShaders("Cook-Torrorence");
	currentShader = 1;
}