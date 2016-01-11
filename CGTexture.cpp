#include "CGTexture.h"
unsigned int textureObjects[MAXTEX];
int textpoint;

void soil_texture(int item, GLuint& ID, const char* filepath){
	ID = SOIL_load_OGL_texture(
		filepath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
		);
	glActiveTexture(GL_TEXTURE0 + item);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void initTextureList(){
	//glEnable(GL_TEXTURE_2D);
	glGenTextures(MAXTEX, textureObjects);
	//IBL.bmp
	//bmpManager.readBMP("textures/IBL.bmp");
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpManager.w,
		bmpManager.h, 0, GL_RGB, GL_UNSIGNED_BYTE,
		bmpManager.imgdata);
	bmpManager.clear();*/

	//floor.bmp
	//bmpManager.readBMP("textures/chosen.bmp");
	soil_texture(IBL,textureObjects[IBL], "textures/1.bmp");
	soil_texture(FLOOR,textureObjects[FLOOR], "textures/city.bmp");
	soil_texture(WALL, textureObjects[WALL], "textures/floor.bmp");
	soil_texture(BED, textureObjects[BED], "textures/down.bmp");
	soil_texture(WHALE, textureObjects[WHALE], "textures/cow.bmp");
	textpoint = ITEM;
}