extern int deltaMove;
extern float angle, deltaAngle, ratio; //��y�����ת�ǣ������������������ת������������
extern float x, y, z; //����ĳ�ʼ����
extern float lx, ly, lz;  //�����������ķ���

void changeSize(int w, int h);
void orientMe(float ang);
void moveMeFlat(int direction);
void pressKey(int key, int x, int y);
void releaseKey(int key, int x, int y);
