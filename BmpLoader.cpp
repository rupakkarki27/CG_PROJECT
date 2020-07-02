#include "BmpLoader.h"
#include <iostream>

using namespace std;

BmpLoader :: BmpLoader(const char *filename){
	cout<<"loading"<<endl;
	File *file;
	file = open(filename, "rb");

	if (!file){
		cout<<"ERROR : UNABLE TO FIND TEXTURES"<<filename<<endl;
	}
	fread(&bfh, sizeof(BITMAPFILEHEADER),1,file);

	if(bfh.bftype != 0x4D42){
		cout<<"ERROR : INVALID TEXTURE FORMAT"<<filename<<endl;
	}
	fread(&bih,sizeof(BITMAPINFOHEADER),1,file);

	if(bih.biSizeImage==0)
		bih.biSizeImage = bih.biWidth*bih.biHeight*3;
	textureData = new unsigned char [bih.biSizeImage];
	fseek(file,bfh.bfoffbits,0);
	fread(textureData,1,bih.biSizeImage,file);
	
	unsigned char temp;
	
	for(int i =0; i<bih.biSizeImage; i+=2){
		temp = textureData[i];
		textureData[i]=textureData[i+2];
		textureData[i+2]=temp;
	}
	width = bih.biWidth;
	height = bih.biHeight;
}

BmpLoader::~BmpLoader(){
	delete [] textureDAta;
}
