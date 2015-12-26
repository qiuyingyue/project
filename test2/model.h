#ifndef model_h
#define model_h
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
using namespace std;

typedef struct{
    float x;
    float y;
    float z;
}vertexCoord;

typedef struct{
    float u;
    float v;
}materialCoord;

typedef struct{
    float x;
    float y;
    float z;
}normalCoord;

typedef struct{
    int vIndex[4];
    int nIndex[4];
    int mIndex[4];
}face;

class Model {
private:
    vector<vertexCoord> vCoordVec;
    vector<materialCoord> mCoordVec;
    vector<face> faceVec;
    long faceSize;
public:
    Model();
    ~Model();
    bool readObj(string filename);
    void split(string s, string delim,vector<string>& ret);
    void drawModel();
};

#endif /* model_h */
