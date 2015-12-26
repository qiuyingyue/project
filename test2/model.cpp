#include "model.h"
using namespace std;

Model::Model(){
    vCoordVec.clear();
    mCoordVec.clear();
    faceVec.clear();
}

Model::~Model(){
    vCoordVec.clear();
    mCoordVec.clear();
    faceVec.clear();
}

bool Model::readObj(string filename){
    ifstream fin(filename.c_str());
    if(!fin.is_open()){
        cout<<"Can't open the file: "<<filename<<endl;
        return false;
    }
    vector<string> tempArray;
    vector<string> slashArray;
    vertexCoord vc;
    materialCoord mc;
    face f;
    while (!fin.eof()) {
        string temp;
        getline(fin,temp);
        if(temp=="")
            continue;
        split(temp, " ", tempArray);
        if(tempArray[0]=="v"){
            vc.x = atof(tempArray[1].c_str());
            vc.y = atof(tempArray[2].c_str());
            vc.z = atof(tempArray[3].c_str());
            vCoordVec.push_back(vc);
        }
        else if (tempArray[0]=="vt"){
            mc.u = atof(tempArray[1].c_str());
            mc.v = atof(tempArray[2].c_str());
            mCoordVec.push_back(mc);
        }
        else if (tempArray[0]=="f"){
            for (int i = 0; i < tempArray.size()-1; i++) {
                split(tempArray[i+1], "/", slashArray);
                if(slashArray.size()==2){
                    f.vIndex[i] = atoi(slashArray[0].c_str());
                    f.mIndex[i] = atoi(slashArray[1].c_str());
                }
                else if(slashArray.size()==3){
                    f.vIndex[i] = atoi(slashArray[0].c_str());
                    f.nIndex[i] = atoi(slashArray[1].c_str());
                    f.mIndex[i] = atoi(slashArray[2].c_str());
                }
            }
            if (tempArray.size()==4) {
                f.vIndex[3]=0;
            }
            faceVec.push_back(f);
        }
        else
            continue;
    }
    faceSize = faceVec.size();
    return true;
}

void Model::drawModel()
{
   
    for(int i = 0; i < faceSize; i++){
        if(faceVec[i].vIndex[3]==0){
            glBegin (GL_TRIANGLES);
            glTexCoord2f(mCoordVec[faceVec[i].mIndex[0]-1].u,mCoordVec[faceVec[i].mIndex[0]-1].v );
            glVertex3f(vCoordVec[faceVec[i].vIndex[0]-1].x, vCoordVec[faceVec[i].vIndex[0]-1].y, vCoordVec[faceVec[i].vIndex[0]-1].z);
            glTexCoord2f(mCoordVec[faceVec[i].mIndex[1]-1].u,mCoordVec[faceVec[i].mIndex[1]-1].v );
            glVertex3f(vCoordVec[faceVec[i].vIndex[1]-1].x, vCoordVec[faceVec[i].vIndex[1]-1].y, vCoordVec[faceVec[i].vIndex[1]-1].z);
            glTexCoord2f(mCoordVec[faceVec[i].mIndex[2]-1].u,mCoordVec[faceVec[i].mIndex[2]-1].v );
            glVertex3f(vCoordVec[faceVec[i].vIndex[2]-1].x, vCoordVec[faceVec[i].vIndex[2]-1].y, vCoordVec[faceVec[i].vIndex[2]-1].z);
            glEnd ();
        }
        else{
            glBegin (GL_POLYGON);
            glTexCoord2f(mCoordVec[faceVec[i].mIndex[0]-1].u,mCoordVec[faceVec[i].mIndex[0]-1].v );
            glVertex3f(vCoordVec[faceVec[i].vIndex[0]-1].x, vCoordVec[faceVec[i].vIndex[0]-1].y, vCoordVec[faceVec[i].vIndex[0]-1].z);
            glTexCoord2f(mCoordVec[faceVec[i].mIndex[1]-1].u,mCoordVec[faceVec[i].mIndex[1]-1].v );
            glVertex3f(vCoordVec[faceVec[i].vIndex[1]-1].x, vCoordVec[faceVec[i].vIndex[1]-1].y, vCoordVec[faceVec[i].vIndex[1]-1].z);
            glTexCoord2f(mCoordVec[faceVec[i].mIndex[2]-1].u,mCoordVec[faceVec[i].mIndex[2]-1].v );
            glVertex3f(vCoordVec[faceVec[i].vIndex[2]-1].x, vCoordVec[faceVec[i].vIndex[2]-1].y, vCoordVec[faceVec[i].vIndex[2]-1].z);
            glTexCoord2f(mCoordVec[faceVec[i].mIndex[3]-1].u,mCoordVec[faceVec[i].mIndex[3]-1].v );
            glVertex3f(vCoordVec[faceVec[i].vIndex[3]-1].x, vCoordVec[faceVec[i].vIndex[3]-1].y, vCoordVec[faceVec[i].vIndex[3]-1].z);
            glEnd ();
        }
    }
   }

void Model::split(string s, string delim,vector<string>& ret)
{
    ret.clear();
    size_t last = 0;
    size_t index=s.find_first_of(delim,last);
    while (index!=std::string::npos)
    {
        ret.push_back(s.substr(last,index-last));
        last=index+1;
        index=s.find_first_of(delim,last);
    }
    if (index-last>0)
    {
        ret.push_back(s.substr(last,index-last));
    }
}