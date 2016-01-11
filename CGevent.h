#ifndef CGevent_h
#define CGevent_h 

extern bool door_open;
BOOL WriteBitmapFile(char * filename, int width, int height, unsigned char * bitmapData);
void SaveScreenShot();
void mousePick(int button, int state, int x, int y);
void processHits(GLint hits, GLuint buffer[]);
void stopPicking(GLuint buffer[]);

void pressKey(unsigned char key, int x, int y);
void releaseKey(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void mouseMove(int x, int y);
#endif /* CGevent_h */