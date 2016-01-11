#include "MonitorModel.h"
#include "CGTexture.h"

void MonitorModel::setVideo(string mtl, int nFrame, string pic){
    materials[mtl].isVideo = true;
    for (int i = 0; i < nFrame; i++){
        stringstream ss;
        string str;
        ss << i;
        ss >> str;
        
        GLuint texture;
        
        glGenTextures(1, &texture);
        
        string texPath = filePath + "/" + pic + str + ".bmp";
        
        char ch[30];
        strcpy(ch, texPath.c_str());
        //texload(texture, ch);
		//soil_texture(texture, ch);

        
        materials[mtl].videoFrames.push_back(texture);
    }
    materials[mtl].curFrame = 0;
}



void MonitorModel::draw(){
    for (int i = 0; i < groups.size(); i++){
        ObjGroup group = groups[i];
        if (!group.material.empty()){
            ObjMaterial material = materials[group.material];
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
            
            if (material.texture < 1000){
                //glEnable(GL_COLOR_MATERIAL);
                //glEnable(GL_TEXTURE_2D);
                if (playing && material.isVideo){
                    GLuint texture = material.videoFrames[material.curFrame];
                    material.curFrame++;
                    if (material.curFrame >= material.videoFrames.size())
                        material.curFrame = 0;
                    materials[group.material].curFrame = material.curFrame;
                    glBindTexture(GL_TEXTURE_2D, texture);  //选择纹理texture[0]
                }
                else
                    glBindTexture(GL_TEXTURE_2D, material.texture);  //选择纹理texture[0]
            }
        }
        
        
        glPushMatrix();
        
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < group.triangles.size(); j++){
            ObjTriangle triangle = group.triangles[j];
            for (int k = 0; k < 3; k++){
                ObjPoint point = triangle.points[k];
                
                
                if (point.normal.x != -100)
                    glNormal3f(point.normal.x, point.normal.y, point.normal.z);
                if (point.texCoord.x != -100)
                    glTexCoord2f(point.texCoord.x, 1 - point.texCoord.y);
                glVertex3f(point.vertex.x, point.vertex.y, point.vertex.z);
            }
        }
        glEnd();
        
        glBegin(GL_QUADS);
        for (int j = 0; j < group.quads.size(); j++){
            ObjQuad quad = group.quads[j];
            for (int k = 0; k < 4; k++){
                ObjPoint point = quad.points[k];
                
                if (point.normal.x != -100)
                    glNormal3f(point.normal.x, point.normal.y, point.normal.z);
                if (point.texCoord.x != -100){
                    glTexCoord2f(point.texCoord.x, 1 - point.texCoord.y);
                }
                glVertex3f(point.vertex.x, point.vertex.y, point.vertex.z);
            }
        }
        glEnd();
        
        glPopMatrix();
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_TEXTURE_2D);
    }
}