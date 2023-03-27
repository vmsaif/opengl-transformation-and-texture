

// Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
	Author: Saif Mahmud
	Student ID: 3433058
	Date : 3 / 30 / 2023
	Course: COMP 390
	TME = 3
	Program : 3
	Description: This program draws eight houses with a triangle roofs and a floors using translation, scaling, and rotation to transform the houses. The houses are drawn using shapes and display lists. Also a background texture is added from a bmp format image.
*/

#include <iostream>
#include "glut.h"
#include <fstream>
#include "windows.h"
#include <string>
#include "math.h"

#pragma surpress(warning:C6387)
#pragma surpress(warning:C6386)
using namespace std;

typedef GLdouble vertex3[3];

GLuint hat_list, walls_list, floor_list, house_list; // list for the roof of the house

// image
GLubyte* image;
GLubyte* l_texture;
BITMAPFILEHEADER fileheader;
BITMAPINFOHEADER infoheader;
RGBTRIPLE rgb;
GLuint texName;

// defining the vertices of the cube
vertex3 wall_pt[8] = {
	{0,0,0}, //0
	{0,1,0}, //1
	{1,0,0}, //2
	{1,1,0}, //3
	{0,0,1}, //4
	{0,1,1}, //5
	{1,0,1}, //6
	{1,1,1}  //7
};

// defining the vertices of the floor
vertex3 floor_pt[4] = {
	{-0.75, 0, -0.75}, //back left
	{-0.75, 0, 1.75}, //front left
	{1.75, 0, 1.75}, // front right
	{1.75, 0, -0.75} // back right
};

// defining the vertices of the top floor which will be used to draw the roof triangles
vertex3 top_floor_pt[4] = {
	{-0.2, 1.0, -0.2}, //back left
	{-0.2, 1.0, 1.2}, //front left
	{1.2, 1.0, 1.2}, // front right
	{1.2, 1.0, -0.2} // back right
};

// defining the vertices of the ground
vertex3 back_left = { -8.0, -0.1, -8.0 };
vertex3 back_right = { 8.0, -0.1, -8.0 };
vertex3 front_left = { -8.0, -0.1, 8.0 };
vertex3 front_right = { 8.0, -0.1, 8.0 };

// defining the vertices of the height from the ground for the background texture
vertex3 front_left_height = { -8.0, 10.0, 8.0 };
vertex3 front_right_height = { 8.0, 10.0, 8.0 };
vertex3 back_left_height = { -8.0, 10.0, -8.0 };
vertex3 back_right_height = { 8.0, 10.0, -8.0 };

/**
Description: top_hat This function is responsible for drawing the triangular
roof of the house. It draws four triangles and each triangle has a point where
all the triangles meet. This point is the top point of the roof.
*/
void top_hat() {
	GLdouble hatTopPoint[3] = { 0.5, 1.5, 0.5 }; // the point where all the triangle's tops will meet

	glColor3f(0.0, 0.0, 1.0); // blue color
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
	glBegin(GL_TRIANGLES);

		// triangle 1
		glVertex3dv(top_floor_pt[0]);
		glVertex3dv(top_floor_pt[1]);
		glVertex3dv(hatTopPoint);

		// triangle 2
		glVertex3dv(top_floor_pt[1]);
		glVertex3dv(top_floor_pt[2]);
		glVertex3dv(hatTopPoint);

		// triangle 3
		glVertex3dv(top_floor_pt[2]);
		glVertex3dv(top_floor_pt[3]);
		glVertex3dv(hatTopPoint);

		// triangle 4
		glVertex3dv(top_floor_pt[3]);
		glVertex3dv(top_floor_pt[0]);
		glVertex3dv(hatTopPoint);

	glEnd();

}


/**
Description: This function takes four vertices as input
and draws a wall using these vertices.
It is called by the allWalls() function to draw all the walls of the house.
*/
void wall(GLint n1, GLint n2, GLint n3, GLint n4) {

	glBegin(GL_QUADS);
		glVertex3dv(wall_pt[n1]);
		glVertex3dv(wall_pt[n2]);
		glVertex3dv(wall_pt[n3]);
		glVertex3dv(wall_pt[n4]);
	glEnd();

}

/**
Description:This function is responsible for drawing the floor
of the house. It takes four vertices as input and uses them
to draw a floor.
*/
void floor() {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex3dv(floor_pt[0]);
		glVertex3dv(floor_pt[1]);
		glVertex3dv(floor_pt[2]);
		glVertex3dv(floor_pt[3]);
	glEnd();
}

/**
Description:This function calls the wall() function with the
appropriate vertices to draw all the walls of the house.
*/
void allWalls() {
	glColor3f(1.0, 0.0, 0.0);
	wall(6, 2, 3, 7); //rightSideWall
	wall(5, 1, 0, 4); //leftSideWall
	wall(7, 3, 1, 5); //topWall
	wall(4, 0, 2, 6); //bottomWall
	wall(2, 0, 1, 3); //backWall
	wall(7, 5, 4, 6); //frontWall
}

/**
Description:This function draws the ground on which the houses are built.
It uses the GL_QUADS primitive to draw a surface and fills it with a light gray color.
*/
void drawTownLand() {
	// draw the town land
	glColor3f(0.65, 0.65, 0.65); // light gray
	glBegin(GL_QUADS);
		glVertex3dv(back_left); // backLeft
		glVertex3dv(front_left); // frontLeft
		glVertex3dv(front_right); // frontRight
		glVertex3dv(back_right); // backRight
	glEnd();
}

// This function is responsible for drawing the background texture
void drawBackgroundTexture() {
	
	glEnable(GL_TEXTURE_2D); // enable texture mapping
	// drawing the landscape texture.
		glBindTexture(GL_TEXTURE_2D, texName);

		// left half of the background
		glBegin(GL_QUADS);

			glTexCoord2d(0.0, 0.0); // bottom left
			glVertex3dv(front_left); // frontLeft of the ground

			glTexCoord2d(0.5, 0.0); // bottom right
			glVertex3dv(back_left); // backLeft of the ground

			glTexCoord2d(0.5, 1.0); // top right
			glVertex3dv(back_left_height);

			glTexCoord2d(0.0, 1.0); // top left
			glVertex3dv(front_left_height);

		glEnd();


		// right half of the background
		glBegin(GL_QUADS);

			glTexCoord2d(0.5, 0.0); // bottom left
			glVertex3dv(back_left); // backLeft of the ground

			glTexCoord2d(1.0, 0.0); // bottom right
			glVertex3dv(back_right); // backRight of the ground

			glTexCoord2d(1.0, 1.0); // top right
			glVertex3dv(back_right_height); // X, Z at backRight of the ground

			glTexCoord2d(0.5, 1.0); // top left
			glVertex3dv(back_left_height); // X, Z at backLeft of the ground

		glEnd();

	glDisable(GL_TEXTURE_2D);
}

/**
* Description: This function creates a display list for the floor.
*/
void initFloorDisplayList() {
	floor_list = glGenLists(1);
	glNewList(floor_list, GL_COMPILE);
		floor();
	glEndList();
}

/**
* Description: This function creates a display list for the hat.
*/
void initHatDisplayList() {
	hat_list = glGenLists(1);
	glNewList(hat_list, GL_COMPILE);
		top_hat();
	glEndList();
}

/**
* Description: This function creates a display list for the walls.
*/
void initWallsDisplayList() {
	walls_list = glGenLists(1);
	glNewList(walls_list, GL_COMPILE);
		allWalls();
	glEndList();
}


/**
Description: This function calls all the lists responsible
for drawing the individual parts of 1 house. It includs the
floor, walls, and roof.
*/
void drawHouse() {

	glCallList(floor_list);
	glCallList(walls_list);
	glCallList(hat_list);
	
}


/**
Description:This function is responsible for drawing the entire town.
It calls the drawTownLand() function to draw the ground and uses
glPushMatrix() and glPopMatrix() to transform and draw eight instances
of the drawHouse() function with different positions, rotations, and scales.
*/
void drawTown() {

	// draw the ground
	drawTownLand();

	// draw the first house
	glPushMatrix();
		glTranslated(3.0, 0.0, -4.0);
		drawHouse();
	glPopMatrix();

	// draw the second house using translation
	glPushMatrix();
		glTranslated(0.0, 0.0, -4.0);
		drawHouse();
	glPopMatrix();

	// draw the third house using translation and then scaling
	drawHouse();

	// draw the fourth house using translation and then rotation
	glPushMatrix();
		glTranslated(-3.0, 0.0, 0.0);
		glScaled(0.5, 0.9, 0.9);
		drawHouse();
	glPopMatrix();

	// draw the fifth house using translation, rotation and then scaling
	glPushMatrix();
		glTranslated(3.0, 0.0, 0.0);
		drawHouse();
	glPopMatrix();

	// draw the sixth house using translation, rotation and then scaling
	glPushMatrix();
		glTranslated(3.0, 0.0, 4.0);

		// rotate the house 45 degrees around the y axis
		glRotated(45, 0.0, 1.0, 0.0);
		drawHouse();
	glPopMatrix();


	// draw the seventh house using translation, rotation and then scaling
	glPushMatrix();
		glTranslated(0.0, 0.0, 4.0);

		// rotate the house 45 degrees around the Y axis
		glRotated(45, 0.0, 1.0, 0.0);
		glScaled(0.5, 0.9, 0.9);
		drawHouse();
	glPopMatrix();

	// draw the eighth house
	glPushMatrix();
		glTranslated(-3.0, 0.0, 4.0);

		// rotate the house 45 degrees and scaled around the y, x axis
		glRotated(45, 0.0, 1.0, 0.0);
		glScaled(0.5, 2.0, 0.9);
		drawHouse();
	glPopMatrix();
}


// called every time the window is redrawn
void render() {
	//set backbround Color
	glColor3f(0.0, 0.0, 0.0);
	drawBackgroundTexture();
	drawTown();
}

// display registry 
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
	glLoadIdentity(); // reset the modelview matrix
	// viewing
	gluLookAt(5.0, 5.5, 13.0, 0.0, 0.0, 3.0, 0.0, 1.0, 0.0); // set the camera position and orientation
	render(); // render the scene
	glFlush(); // flush the OpenGL pipeline to the viewport
	glutSwapBuffers(); //Swap the front and back buffers

}

// reshape registry
// called when window is resized to change the viewport
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the client window area
	glMatrixMode(GL_PROJECTION); // set the projection matrix mode
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0); // set the projection frustum
	glMatrixMode(GL_MODELVIEW); // set the modelview matrix mode

}

// Loads the texture from a bitmap file
void makeImage(void) {

	int i, j = 0;
	FILE* l_file;
	string fn = "side.bmp";

	const char* filename = fn.c_str();
	// open image file, return if error

	fopen_s(&l_file, filename, "rb");

	if (l_file == NULL) return;

	// read file header and header info

	fread(&fileheader, sizeof(fileheader), 1, l_file);
	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	// allocate space for the image file

	l_texture = (GLubyte*)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

	// read da data

	j = 0;

	for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);
		l_texture[j + 0] = (GLubyte)rgb.rgbtRed; // Red component
		l_texture[j + 1] = (GLubyte)rgb.rgbtGreen; // Green component
		l_texture[j + 2] = (GLubyte)rgb.rgbtBlue; // Blue component
		l_texture[j + 3] = (GLubyte)255; // Alpha value
		j += 4; // Go to the next position
	}

	fclose(l_file); // Closes the file stream
}

// initialize the display lists, load the image and textures
void initialize() {
	// set background color 
	glClearColor(0.5, 0.7, 0.5, 0.0);

	// initialize the lists.
	initFloorDisplayList();
	initHatDisplayList();
	initWallsDisplayList();

	// image loading 

	makeImage();

	// texture loading
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,	infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	
}

// main program 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //set display mode to double buffer
	glutInitWindowPosition(100, 100); //set top-left display-window position
	glutInitWindowSize(500, 500); //set display-window width and height
	glutCreateWindow("TME 3 _ Q3"); //create display window

	glutDisplayFunc(display); //call display function
	glutReshapeFunc(reshape); // call reshape function
	initialize(); // initialize OpenGL

	glutMainLoop(); //display everything and wait

	return EXIT_SUCCESS;
}

