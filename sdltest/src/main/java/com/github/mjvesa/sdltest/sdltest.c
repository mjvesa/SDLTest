#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#define PI 3.14159265358979323846264338327

SDL_Surface *screen;
GLuint textureHandle;


void tri(float x1, float y1, float z1, float tx1, float ty1, float x2, float y2,
		float z2, float tx2, float ty2, float x3, float y3, float z3, float tx3,
		float ty3) {

	glTexCoord2f(tx1, ty1);
	glVertex3f(x1, y1, z1);

	glTexCoord2f(tx2, ty2);
	glVertex3f(x2, y2, z2);

	glTexCoord2f(tx3, ty3);
	glVertex3f(x3, y3, z3);
}

float height_value(float x, float y) {
	return (sin(4 * y * PI / 16) + sin(4 * x * PI / 16)) / 10.0 + 0.5;
}

void drawframe(int t) {

	float y, angle;
	float r1, r2, r3, r4;
	float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, - 2.0f);
	glRotatef(t, 0, 0 ,1);
	glRotatef(t, 1, 0 ,0);
	glRotatef(t, 0, 1 ,0);


	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);

	for (y = 0; y < 32; y++) {
		for (angle = 0; angle < 32; angle++) {

			// Get radius for all points
			r1 = height_value(angle, y) * sin(y / 32 * PI);
			r2 = height_value(angle + 1, y) * sin(y / 32 * PI);
			r3 = height_value(angle + 1, y + 1) * sin((y + 1) / 32 * PI);
			r4 = height_value(angle, y + 1) * sin((y + 1) / 32 * PI);

			// Point 1
			x1 = cos(angle * PI / 16) * r1;
			z1 = sin(angle * PI / 16) * r1;
			y1 = (y - 16) / 16;

			// Point 2
			x2 = cos((angle + 1) * PI / 16) * r2;
			z2 = sin((angle + 1) * PI / 16) * r2;
			y2 = (y - 16) / 16;

			// Point 3
			x3 = cos((angle + 1) * PI / 16) * r3;
			z3 = sin((angle + 1) * PI / 16) * r3;
			y3 = (y + 1 - 16) / 16;

			// Point 4
			x4 = cos(angle * PI / 16) * r4;
			z4 = sin(angle * PI / 16) * r4;
			y4 = (y + 1 - 16) / 16;

			// Triangles
			tri(x1, y1, z1, angle / 32, y / 32,
			    x2, y2, z2, (angle + 1) / 32, y / 32,
			    x3, y3, z3, (angle + 1) / 32, (y + 1) / 32);

			tri(x1, y1, z1, angle / 32, y  / 32,
			    x3, y3, z3, (angle + 1) / 32, (y + 1) / 32,
			    x4, y4, z4, angle / 32, (y + 1) / 32);
		}
	}

	glEnd();

}

void genTexture() {

	int x, y, c;
	unsigned short * texture;

	texture = (unsigned short *) malloc(512 * 512 * 2);

	// Generate traditional xor-texture
	for (y = 0; y < 512; y++) {
		for (x = 0; x < 512; x++) {
			c = (x ^ y) & 255;
			texture[y * 512 + x] = (c >> 3) + ((c >> 2) << 5) + ((c >> 3) << 11);
		}
	}

	//Allocate handle for texture and upload it
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB,
			GL_UNSIGNED_SHORT_5_6_5, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	free(texture);
}

void init() {
	screen = SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE | SDL_OPENGL);
    glViewport (0, 0, (GLsizei) 1024, (GLsizei) 768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum  (-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST );

	genTexture();
}

