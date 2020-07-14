#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "stb_image.cpp"

unsigned int trackTex,grassTex,skyTex;

GLuint loadTexture(const char * filename){
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data) {
       std::cout<<"Texture Loaded...\n\n";
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
	GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	return texture;
}

namespace models{
	void track(){
		if(trackTex == 0)
			trackTex=loadTexture("assets/train2.bmp");

		glBindTexture(GL_TEXTURE_2D,trackTex);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0,0.0); glVertex3f(-0.7,0.0,10.0);
			glTexCoord2f(1.0,0.0); glVertex3f(0.7,0.0,10.0);
			glTexCoord2f(1.0,50.0); glVertex3f(0.7,0.0,-190.0);
			glTexCoord2f(0.0,50.0); glVertex3f(-0.7,0.0,-190.0);
		}glEnd();
	}

	void greenGround(){
		if(grassTex==0)
			grassTex=loadTexture("assets/grass4.bmp");
		glBindTexture(GL_TEXTURE_2D,grassTex);
		glColor3f(0.0,1.0,0.0);
		glPushMatrix();
		glTranslatef(0.0,-1,0.0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0,0.0); glVertex3f(-5.0,0.0,5.0);
			glTexCoord2f(5.0,0.0); glVertex3f(5.0,0.0,5.0);
			glTexCoord2f(5.0,50.0); glVertex3f(5.0,0.0,-195.0);
			glTexCoord2f(0.0,50.0); glVertex3f(-5.0,0.0,-195.0);

		}glEnd();
		glPopMatrix();
	}

	void sky(){
		if(skyTex==0)
			skyTex = loadTexture("assets/sky_new.jpg");
		glBindTexture(GL_TEXTURE_2D,skyTex);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glPushMatrix();
		glTranslatef(0.0,-140.0,-300.0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0,0.0); glVertex2f(-280.0,-280.0);
			glTexCoord2f(1.0,0.0); glVertex2f(280.0,-280.0);
			glTexCoord2f(1.0,1.0); glVertex2f(280.0,280.0);
			glTexCoord2f(0.0,1.0); glVertex2f(-280.0,280.0);
		}glEnd();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPopMatrix();
	}
}
