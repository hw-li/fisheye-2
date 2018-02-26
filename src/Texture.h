#pragma once

// GL Includes
#define GLEW_STATIC

#define IMG_SIZE 262144
#include <GL/glew.h>

#include <vector>
#include <fstream>

class TextureLoading
{
public:
    /*static GLuint LoadTexture( GLchar *path )
    {
        //Generate texture ID and load texture data
        GLuint textureID;
        glGenTextures( 1, &textureID );
        
        int imageWidth, imageHeight;
        
        unsigned char *image = SOIL_load_image( path, &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
        
        // Assign texture to ID
        glBindTexture( GL_TEXTURE_2D, textureID );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
        glGenerateMipmap( GL_TEXTURE_2D );
        
        // Parameters
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glBindTexture( GL_TEXTURE_2D,  0);
        
        SOIL_free_image_data( image );
        
        return textureID;
    }*/
    
    static GLuint LoadCubemap( vector<const GLchar * > faces) {
        GLuint textureID;
        glGenTextures( 1, &textureID );
        
        int imageWidth, imageHeight;
        unsigned char *image;
        
        glBindTexture( GL_TEXTURE_CUBE_MAP, textureID );
        
		for (GLuint i = 0; i < faces.size(); i++) {
			unsigned char *temp = SOIL_load_image(faces[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
			image = SOIL_load_image( faces[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
			//glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
			
			/*image = (unsigned char*)malloc(imageWidth*imageHeight * sizeof(unsigned char) * 3);
			for (int i = 0; i < imageWidth*imageHeight; i++) {
				image[i * 3] = temp[i];
			}*/
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            SOIL_free_image_data( image );
        }
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        glBindTexture( GL_TEXTURE_CUBE_MAP, 0);
        
        return textureID;
    }

	/*unsigned char *temp = SOIL_load_image(faces[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
	cout << imageWidth << endl;
	cout << imageHeight << endl;
	//image = SOIL_load_image( faces[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
	//glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	image = (unsigned char*)malloc(imageWidth*imageHeight * sizeof(unsigned char) * 3);
	for (int i = 0; i < imageWidth*imageHeight; i++) {
	image[i * 3] = temp[i];
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);*/

	/*static GLuint LoadCubemap(vector<const GLchar * > faces) { 
		GLuint textureID;
		glGenTextures(1, &textureID);

		int imageWidth = 512, imageHeight = 512;

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		char *tempBuffer = new char[IMG_SIZE];
		//GLfloat *tempBuffer = new GLfloat[IMG_SIZE];
		unsigned char* image = new unsigned char[(IMG_SIZE)];
		//GLfloat *image = new GLfloat[(IMG_SIZE) * 3];
		//int *image = new int[(IMG_SIZE) * 3];
		for (GLuint i = 0; i < faces.size(); i++) {
			std::cout << "file name: " << faces[i] << std::endl;
			ifstream myFile(faces[i], ios::in | ios::binary);
			if (!myFile.read(tempBuffer, IMG_SIZE)) {
				std::cerr << "Reading file failed: " << faces[i] << std::endl;
				std::cerr << "read file status: " << myFile.gcount();
			}

			for (int i = 0; i < 32; i++) {
				std::cout << "data: " << (int)tempBuffer[i] << std::endl;
			}
			
			for (int i = 0; i < IMG_SIZE; i++) {
				image[i] = tempBuffer[i];
			}
			myFile.close();
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R8, imageWidth, imageHeight, 0, GL_RED, GL_UNSIGNED_BYTE, image);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		delete[] tempBuffer;
		delete[] image;
		return textureID;
	}*/

	/*static int saveCubemap(const char *filename, int image_type
			, int width, int height, int channels
			, const unsigned char* const data, int quality) {
		return SOIL_save_image_quality(
			filename, image_type, width, height, channels
		);
	}*/

	
};
