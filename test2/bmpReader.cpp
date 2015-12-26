#include "bmpReader.h"
bool BmpReader::readBMP(const char* filename){
    FILE *fpi;
    fpi=fopen(filename,"rb");
    if(fpi != NULL){
        //先读取文件类型
        fread(&bfType,1,sizeof(WORD),fpi);
        if(0x4d42!=bfType) {
            cout<<"Error: The file is not a bmp image!"<<endl;
            cout<<filename<<endl;
            return false;
        }
        //读取bmp文件的文件头和信息头
        fread(&strHead,1,sizeof(tagBITMAPFILEHEADER),fpi);
        fread(&strInfo,1,sizeof(tagBITMAPINFOHEADER),fpi);
       	h=strInfo.biHeight;
       	w=strInfo.biWidth;
        
       	size=strInfo.biSizeImage/3;
        
        imgdata=new DATA[size];
        fread(imgdata,1,sizeof(DATA)*size,fpi);//读取bmp数据信息
        fclose(fpi);
    }
    else{
        cout<<filename<<" ";
        cout<<"Can't open the input file!"<<endl;
        return false;
    }
    return true;
}
void BmpReader::clear(){
    w = 0;
    h = 0;
    size = 0;
    memset(&strHead, 0, sizeof(strHead));
    memset(&strInfo, 0, sizeof(strInfo));
    memset(&bfType, 0, sizeof(bfType));
    delete [] imgdata;
}