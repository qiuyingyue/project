#include "CGdrive.h"
#include "CGdraw.h"
#include "CGcamera.h"
#include "CGTexture.h"
#include "ShaderSource.h"
#include "DoorModel.h"
#include "MonitorModel.h"
#include "ObjModel.h"
#include "aviReader.h"
#include "CGevent.h"
#include "Skybox.h"
#include "nurbs.h"

int currentShader;
float frot = 0;
float doorTrans = 0;
bool bNurb = false;
ObjModel Woman;
ObjModel Apple;
ObjModel Dumbbell;
ObjModel Ball;
ObjModel iPad;
ObjModel City;
DoorModel Door;
MonitorModel Monitor;
string filePrefix = "textures/";
GLuint WallList, FloorList, basicList;



void attachMaterial(int ID, int tex, GLint currentProgram){
	glUniform3fv(glGetUniformLocation(currentProgram, "rf"), 1, material.mList[ID].rf);
	glUniform1f(glGetUniformLocation(currentProgram, "roughness"), material.mList[ID].roughness);
	glUniform1i(glGetUniformLocation(currentProgram, "tex"), tex);
}

void attachMaterial(int ID, GLint currentProgram){
	glUniform3fv(glGetUniformLocation(currentProgram, "rf"), 1, material.mList[ID].rf);
	glUniform1f(glGetUniformLocation(currentProgram, "roughness"), material.mList[ID].roughness);
}

void texSolidCube(int mode = 1){
	glColor3f(1.0f, 1.0f, 1.0f);
	attachMaterial(0, WALL, programs[currentShader]);
	glPushMatrix();
	glBegin(GL_QUADS);

	if (mode % 7) {
		glTexCoord2i(0, 0);
		glVertex3f(-1.0, -1.0, -1.0);
		glTexCoord2i(1, 0);
		glVertex3f(-1.0, 1.0, -1.0);
		glTexCoord2i(1, 1);
		glVertex3f(-1.0, 1.0, 1.0);
		glTexCoord2i(0, 1);
		glVertex3f(-1.0, -1.0, 1.0);
	}

	if (mode % 5) {
		glTexCoord2i(0, 0);
		glVertex3f(-1.0, -1.0, -1.0);
		glTexCoord2i(1, 0);
		glVertex3f(1.0, -1.0, -1.0);
		glTexCoord2i(1, 1);
		glVertex3f(1.0, 1.0, -1.0);
		glTexCoord2i(0, 1);
		glVertex3f(-1.0, 1.0, -1.0);
	}

	if (mode % 3) {
		glTexCoord2i(0, 0);
		glVertex3f(1.0, -1.0, -1.0);
		glTexCoord2i(1, 0);
		glVertex3f(1.0, 1.0, -1.0);
		glTexCoord2i(1, 1);
		glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2i(0, 1);
		glVertex3f(1.0, -1.0, 1.0);
	}

	if (mode % 2) {
		glTexCoord2i(0, 0);
		glVertex3f(-1.0, -1.0, 1.0);
		glTexCoord2i(1, 0);
		glVertex3f(1.0, -1.0, 1.0);
		glTexCoord2i(1, 1);
		glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2i(0, 1);
		glVertex3f(-1.0, 1.0, 1.0);
	}

	glEnd();
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);	//关闭纹理texture[0]

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, FloorTexture);  //选择纹理texture[0]
	
	attachMaterial(0, FLOOR, programs[currentShader]);
	glPushMatrix();
	glBegin(GL_QUADS);

	if (mode % 11) {
		glTexCoord2i(0, 0);
		glVertex3f(-1.0, 1.0, -1.0);
		glTexCoord2i(1, 0);
		glVertex3f(1.0, 1.0, -1.0);
		glTexCoord2i(1, 1);
		glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2i(0, 1);
		glVertex3f(-1.0, 1.0, 1.0);
	}

	//铺地板程序
	GLfloat floorSize = 100;
	GLfloat divide = 1;
	GLfloat unit = 2 / divide;
	for (int i = 0; i < divide; i++)
		for (int j = 0; j < divide; j++){
		GLfloat x0 = unit * i - 1.0;
		GLfloat z0 = unit * j - 1.0;
		glTexCoord2i(0, 0);
		glVertex3f(x0, -1.0, z0);
		glTexCoord2i(1, 0);
		glVertex3f(x0 + unit, -1.0, z0);
		glTexCoord2i(1, 1);
		glVertex3f(x0 + unit, -1.0, z0 + unit);
		glTexCoord2i(0, 1);
		glVertex3f(x0, -1.0, z0 + unit);
		}

	glEnd();
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);	//关闭纹理texture[0]
	//glDisable(GL_COLOR_MATERIAL);
}
void drawBasicGeo(){
	glPushMatrix();
	glTranslatef(10 * wallunit, 0, 2 * wallunit);
	drawSnowMan();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18 * wallunit, 0, 3 * wallunit);
	drawSnowMan();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(18 * wallunit, 0, 5 * wallunit);
	drawSnowMan();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7 * wallunit, 0, 9 * wallunit);
	drawSnowMan();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6 * wallunit, wallunit, 6 * wallunit);
	static float rot = 0.0f;
	glRotatef(rot, 0.4, -0.2, 0.8);
	rot+=10;
	attachMaterial(4,WHALE,programs[currentShader]);
	glutSolidTeapot(3);
	glPopMatrix();
}

void Draw_Scene(){

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glCallList(WallList);

	//glUseProgram(0);
	glPushMatrix();
	glTranslatef(-5, -3 - Woman.getBottom(), -5);
	//
	Woman.draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(50,10, 50);
	glScalef(30, 30, 30);
	glRotatef(90, 1.0, 0.0, 0.0);
	attachMaterial(3, WHALE, programs[currentShader]);
	Dumbbell.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, -3 - Apple.getBottom(), -5);
	//
	Apple.draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-5, -3 - Ball.getBottom(), 5);
	Ball.draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-3, -3 - iPad.getBottom(), 0);
	iPad.draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 5*City.getBottom(), 63);
	glScalef(50.0, 50.0, 50.0);
	attachMaterial(1, WHALE, programs[currentShader]);
	City.draw();
	glPopMatrix();

	attachMaterial(0, IBL, programs[currentShader]);
	glPushMatrix();
	glTranslatef(0, -3 - Door.getBottom(), 126);
	glScalef(10.0, 10.0, 10.0);
	Door.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -3 - Monitor.getBottom(), 0);
	Monitor.draw();
	glPopMatrix();

}

void renderScene(void) {
	updateCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	//Use Shader
	GLint currentProgram = programs[currentShader];
	if (currentShader == 0)
		glUseProgram(currentProgram);
	else
		glUseProgram(0);
	glUniform1i(glGetUniformLocation(currentProgram, "lightNum"), currentlight);
	//glutSolidTeapot(1);
	RefreshLight(currentProgram);
	//画了一个光源
	glPushMatrix();
	glTranslatef(light[1].lightPosition[0], light[1].lightPosition[1], light[1].lightPosition[2]);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//...见后面
	//glShadeModel(GL_SMOOTH);

	glPushMatrix();
	videoTexInit();
	attachMaterial(0, videotext, programs[currentShader]);
	glPushMatrix();
	glTranslatef(10 * wallunit, 0, 20 * wallunit);
	glScalef(8.0f, 5.0f, 6.0f);
	glBegin(GL_QUADS); {
		glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, 0.5);
		glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, 0.5);
		glTexCoord2i(0, 0); glVertex3f(0.5, 0.5, 0.5);
	}
	glEnd();
	glPopMatrix();
	
	if (bNurb){
		glPushMatrix();
		attachMaterial(1, WALL, programs[currentShader]);
		glPushMatrix();
		glTranslatef(x + lx*wallunit, y + ly*wallunit, z + lz*wallunit);
		drawNurb();
		wave();
		glPopMatrix();
	}

	drawScene();
	
	glCallList(basicList);
	
	ObjectWall wall;
	wall.width = 0.01;
	wall.length = 2 * wallunit;
	wall.height = CUBE_HEIGHT*0.8*wallunit;
	wall.x = 13 * wallunit;
	wall.y = 9 * wallunit;
	wall.h = 0;
	attachMaterial(4, WALL, programs[currentShader]);
	glPushMatrix();
	glScalef(wall.width, wall.height, wall.length);
	glTranslatef(wall.x / wall.width, wall.h / wall.height + 0.5, wall.y / wall.length);
	glRotatef(frot, 0.0f, 1.0f, 0.0f);
	if (!door_open){
		frot += 0.1;
		frot = (frot > 360) ? 0 : frot;
	}
	
	if (door_open && doorTrans < 1 * wallunit){
		doorTrans += 0.001;
		
	}
	glTranslatef(0.0, 0.0, doorTrans);
	wall.glTexCubic();
	glPopMatrix();

    Draw_Scene();
	glutSwapBuffers();
	glutPostRedisplay();
}

void initOBJ(){
	Dumbbell.loadOBJ(filePrefix + "Models/whale", "whale.obj");
	Dumbbell.unitize();

	//iPad.loadOBJ(filePrefix + "Models/", "lion.obj");
	//iPad.unitize();

	//Woman.loadOBJ(filePrefix + "Models/bed", "bed.obj");
	//Woman.unitize();

	//Apple.loadOBJ(filePrefix + "Models/IKEA_sofa_TIDAFORS", "51ccdee7080b11dde21111e385a0661f_obj0_object.obj");
	//Apple.unitize();
	////
	City.loadOBJ(filePrefix + "Models/city", "The City.obj");
	City.unitize();

	//Door.loadOBJ(filePrefix + "Models/Monitor", "New York City, State Street.obj");
	//Door.unitize();

	WallList = glGenLists(1);
	glNewList(WallList, GL_COMPILE);
	test();
	int k = 0;
	attachMaterial(2, WALL, programs[currentShader]);
	for (k = 0; k < NUM_WALL-3; k++){
		wall[k].draw();
	}

	attachMaterial(0, FLOOR, programs[currentShader]);
	glNewList(FloorList, GL_COMPILE);
	test();
	for (k = NUM_WALL-3; k < NUM_WALL; k++){
		wall[k].draw();
	}
	glEndList();
	
	basicList = glGenLists(1);
	glNewList(basicList, GL_COMPILE);
	drawBasicGeo();
	glEndList();
}

void initScene() {
	initShaderList();
	initLightlist(1);
	RefreshLight(programs[0]);
	glEnable(GL_DEPTH_TEST);
	snowman_display_list = createDL();
	currentShader = 0;
	//Texture initial
	initTextureList();
	initAvi("Morning Buddy.avi");
	initOBJ();
	initSkybox();
	initNurbs();
	for (int i = 0; i < textpoint; i++){
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureObjects[i]);
	}
	glUniform1i(glGetUniformLocation(programs[0], "env_brdf"), IBL);
	glActiveTexture(GL_TEXTURE0 + ITEM);
}

int main(int argc, char **argv)	
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutCreateWindow("CGcourse");
	glewInit();
	initScene();
	
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(lightpressKey);
	//glutSpecialUpFunc(releaseKey);
	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutReshapeFunc(changeSize);

	glutMainLoop();

	return(0);
}



/*attachMaterial(0, FLOOR, currentProgram);
glBegin(GL_QUADS);
glVertex3f(100.0f, 0.0f, -100.0f); glTexCoord2f(0.0f, 1.0f);
glVertex3f(100.0f, 0.0f, 100.0f); glTexCoord2f(0.0f, 0.0f);
glVertex3f(-100.0f, 0.0f, 100.0f); glTexCoord2f(1.0f, 0.0f);
glVertex3f(-100.0f, 0.0f, -100.0f); glTexCoord2f(1.0f, 1.0f);
glEnd();
glDisable(GL_TEXTURE_2D);
attachMaterial(0, FLOOR, currentProgram);
glPushMatrix();
glTranslatef(light[currentlight].lightPosition[0], light[currentlight].lightPosition[1], light[currentlight].lightPosition[2]);
glutSolidSphere(1, 20, 20);
glPopMatrix();

//画了36个雪人
int k = 0;
for (int i = -3; i < 3; i++)
	for (int j = -3; j < 3; j++, k++) {
	attachMaterial(k % 5, FLOOR, currentProgram);
	glPushMatrix();
	glTranslatef(i*10.0, 0, j * 10.0);
	glCallList(snowman_display_list);;
	glPopMatrix();
	}
	
	
	//glPushMatrix();
	//glScalef(10, 4, 10);
	//texSolidCube(10);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, 0, 20);
	//glScalef(10, 4, 10);
	//texSolidCube(30);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, 0, 40);
	//glScalef(10, 4, 10);
	//texSolidCube(10);
	//glPopMatrix();

	////21:LR
	//glPushMatrix();
	//glTranslatef(20, 0, 20);
	//glScalef(10, 4, 10);
	//texSolidCube(21);
	//glPopMatrix();

	////14:RF
	//glPushMatrix();
	//glTranslatef(40, 0, 20);
	//glScalef(10, 4, 10);
	//texSolidCube(14);
	//glPopMatrix();

	////15:BL
	//glPushMatrix();
	//glTranslatef(40, 0, 40);
	//glScalef(10, 4, 10);
	//texSolidCube(15);
	//glPopMatrix();

	////2310:all
	//glPushMatrix();
	//glTranslatef(60, 0, 40);
	//glScalef(10, 4, 10);
	//glScalef(0.2, 1, 0.2);
	//texSolidCube(2310);
	//glPopMatrix();

	////2310:all
	//glPushMatrix();
	//glTranslatef(70, 0, 40);
	//glScalef(10, 4, 10);
	//glScalef(0.2, 1, 0.2);
	//texSolidCube(2310);
	//glPopMatrix();
	//glPushMatrix();
	//glScalef(10, 4, 10);
	//texSolidCube(10);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, 0, 20);
	//glScalef(10, 4, 10);
	//texSolidCube(30);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, 0, 40);
	//glScalef(10, 4, 10);
	//texSolidCube(10);
	//glPopMatrix();

	////21:LR
	//glPushMatrix();
	//glTranslatef(20, 0, 20);
	//glScalef(10, 4, 10);
	//texSolidCube(21);
	//glPopMatrix();

	////14:RF
	//glPushMatrix();
	//glTranslatef(40, 0, 20);
	//glScalef(10, 4, 10);
	//texSolidCube(14);
	//glPopMatrix();

	////15:BL
	//glPushMatrix();
	//glTranslatef(40, 0, 40);
	//glScalef(10, 4, 10);
	//texSolidCube(15);
	//glPopMatrix();

	////2310:all
	//glPushMatrix();
	//glTranslatef(60, 0, 40);
	//glScalef(10, 4, 10);
	//glScalef(0.2, 1, 0.2);
	//texSolidCube(2310);
	//glPopMatrix();

	////2310:all
	//glPushMatrix();
	//glTranslatef(70, 0, 40);
	//glScalef(10, 4, 10);
	//glScalef(0.2, 1, 0.2);
	//texSolidCube(2310);
	//glPopMatrix();

	int checkbump[19][14] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
	{1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	}

	*/