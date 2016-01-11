#include "ShaderSource.h"
#define MATERIAL_NUM 5
MaterialList material;

MaterialList::MaterialList(){
	//Read the material file
	//or just simplily initial it
	mNum = MATERIAL_NUM;
	mList = new MaterialSource[MATERIAL_NUM];
	//In here to INIT all the Material
	//Material 0: Aluminum
	mList[0].SetParameter(0.91f, 0.92f, 0.92f, 1.0f);
	//Material 1: Gold
	mList[1].SetParameter(1.00f, 0.71f, 0.29f, 0.4f);
	//Material 2: Copper
	mList[2].SetParameter(0.95f, 0.64f, 0.54f, 0.6f);
	//Material 3: Diamond
	mList[3].SetParameter(0.17f, 0.17f, 0.17f, 0.5f);
	//Material 4: Silver
	mList[4].SetParameter(0.95f, 0.93f, 0.88f, 0.8f);
}