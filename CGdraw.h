#include "CGdrive.h"
extern GLint snowman_display_list;  //一个雪人的显示列表索引
extern class ObjectWall wall[NUM_WALL];

GLuint createDL();
void drawSnowMan();
void drawMonitor();

class ObjectWall{
public:
	float width;
	float height;
	float length;
	float x;
	float y;
	float h;
	void draw();
	void glTexCubic();
	ObjectWall(){};
};

void test();