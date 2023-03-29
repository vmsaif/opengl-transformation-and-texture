// Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
	Author: Saif Mahmud
	Student ID: 3433058
	Date : 3 / 22 / 2023
	Course: COMP 390
	TME = 3
	Program : 1
	Purpose: To develop a program to light a sphere using OpenGL's lighting features.
	The program defines three light sources originating from the top left corner,
	top right corner, and directly behind the viewer. Each light source should shed a
	white, red, blue, or green light, as selected by the user. Three different
	surface materials are available for selection for the sphere. Options for
	choosing lighting elements are available. Implementing a menu system that
	can be activated by clicking the right button of the mouse. Using the glutSolidSphere
	command to generate the sphere to test the menu.
*/

#include <iostream>
#include "glut.h"

static int menu_id1, menu_id2, menu_id3, menu_id4, menu_id5, menu_id6;
static int selectedLight;
static int sub_menu_id1, sub_menu_id2, sub_menu_id3, sub_menu_id4, sub_menu_id5;
GLfloat *light_location, *selectedColor, *ambient, *diffuse, *specular, *shininess;

// lights
GLfloat light_position0[] = { -10.0, 10.0, 10.0, 0.0 }; // light 0 position. It is at the top left corner
GLfloat light_position1[] = { 10.0, 10.0, 10.0, 0.0 };  // light 1 position. It is at the top right corner
GLfloat light_position2[] = { 0.0, 0.0, 4.0, 0.0 };   // light 2 position. It is behind the viewer

//Light Colors
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat green_light[] = { 0.2, 1.0, 0.2, 1.0 };
GLfloat red_light[] = { 1.0, 0.4, 0.4, 1.0 };
GLfloat blue_light[] = { 0.2, 0.2, 1.0, 1.0 };

GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

// gold

GLfloat gold_ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };
GLfloat gold_diffuse[] = { 0.75164, 0.60648, 0.22658, 1.0 };
GLfloat gold_specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };
GLfloat gold_shininess[] = { 51.2 };

// silver
GLfloat silver_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
GLfloat silver_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
GLfloat silver_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
GLfloat silver_shininess[] = { 51.2 };

// copper
GLfloat copper_ambient[] = { 0.2295, 0.08825, 0.0275, 1.0 };
GLfloat copper_diffuse[] = { 0.5508, 0.2118, 0.066, 1.0 };
GLfloat copper_specular[] = { 0.580594, 0.223257, 0.0695701, 1.0 };
GLfloat copper_shininess[] = { 51.2 };

GLfloat disable[] = { 0.0, 0.0, 0.0, 1.0 }; // diffuse light color


/**
Description: This function initializes the background color, depth test, and lighting.
@return none
*/
void initialize() {

	// set background color
	glClearColor(0.5, 0.7, 0.5, 0.0);

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	//// enable lighting
	glEnable(GL_LIGHTING);
	
	// set light model 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}

/**
This function handles the user selection in the lighting menu. It sets the selected light and position based on the ID,
turns off the light if the user selects the off option, and sets the light color based on the user's color selection.
@param id (integer) - the ID of the selected menu option
@return none
*/
void light_menu_func(int id) {

	// set the light and position
	if (id == 1 || id == 2 || id == 3 || id == 4 || id == 5) {
		selectedLight = GL_LIGHT0;
		light_location = light_position0;
	}
	else if (id == 6 || id == 7 || id == 8 || id == 9 || id == 10) {
		selectedLight = GL_LIGHT1;
		light_location = light_position1;
	}
	else if (id == 11 || id == 12 || id == 13 || id == 14 || id == 15) {
		selectedLight = GL_LIGHT2;
		light_location = light_position2;
	}

	// off function
	if (id == 1 || id == 6 || id == 11) {
		glDisable(selectedLight);
	}
	else {
		// select the color
		if (id == 2 || id == 7 || id == 12) {
			selectedColor = white_light;
		}
		else if (id == 3 || id == 8 || id == 13) {
			selectedColor = red_light;
		}
		else if (id == 4 || id == 9 || id == 14) {
			selectedColor = blue_light;
		}
		else if (id == 5 || id == 10 || id == 15) {
			selectedColor = green_light;
		}
		ambient = selectedColor;
		diffuse = selectedColor;
		specular = selectedColor;
		glLightfv(selectedLight, GL_POSITION, light_location);
		glLightfv(selectedLight, GL_AMBIENT, ambient);
		glLightfv(selectedLight, GL_DIFFUSE, diffuse);
		glLightfv(selectedLight, GL_SPECULAR, specular);
		glEnable(selectedLight);
	}
	glutPostRedisplay();
}

/** 
This function handles the user selection in the material menu. It sets the material's ambient, 
diffuse, specular, and shininess values based on the ID.

@param id (integer) - the ID of the selected menu option
@return none
*/
void material_func(int id) {
	if (id == 1) {
		//Gold
		ambient = gold_ambient;
		diffuse = gold_ambient;
		specular = gold_specular;
		shininess = gold_shininess;
	}
	else if (id == 2) {
		//silver
		ambient = silver_ambient;
		diffuse = silver_ambient;
		specular = silver_specular;
		shininess = silver_shininess;
	}
	else if (id == 3) {
		//copper
		ambient = copper_ambient;
		diffuse = copper_ambient;
		specular = copper_specular;
		shininess = copper_shininess;
	}

	// set the material accordingly.
	glLightfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glutPostRedisplay();
}

/** 
This function handles the user selection in the elements menu. It sets the mode between ambient, diffuse, 
specular which can be togather or separate based on the ID.
@param id (integer) - the ID of the selected menu option
@return none
*/
void element_func(int id) {
	if (id == 1) {
		//Ambient only, disable other 2.
		glLightfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, disable);
		glMaterialfv(GL_FRONT, GL_SPECULAR, disable);
	}
	else if (id == 2) {
		//Ambient and Diffuse
		glLightfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, disable);
	}
	else if (id == 3) {
		// all 3 enable
		glLightfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	}
	glutPostRedisplay();
}

/**
This function handles the user selection in the main menu. It calls the appropriate menu function based on the ID.
@param id (integer) - the ID of the selected menu option
@return none
*/
void main_menu_handler(int menu_id) {
	if (menu_id == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
		exit(0);
	}
}

/** 
This function creates all menus and submenues. Then attaches right mouse button for activating.
@param none
@return none
*/
void create_menus() {

	//create the submenus
	sub_menu_id1 = glutCreateMenu(light_menu_func);
	glutAddMenuEntry("Off", 1);
	glutAddMenuEntry("White", 2);
	glutAddMenuEntry("Red", 3);
	glutAddMenuEntry("Blue", 4);
	glutAddMenuEntry("Green", 5);

	sub_menu_id2 = glutCreateMenu(light_menu_func);
	glutAddMenuEntry("Off", 6);
	glutAddMenuEntry("White", 7);
	glutAddMenuEntry("Red", 8);
	glutAddMenuEntry("Blue", 9);
	glutAddMenuEntry("Green", 10);

	sub_menu_id3 = glutCreateMenu(light_menu_func);
	glutAddMenuEntry("Off", 11);
	glutAddMenuEntry("White", 12);
	glutAddMenuEntry("Red", 13);
	glutAddMenuEntry("Blue", 14);
	glutAddMenuEntry("Green", 15);

	sub_menu_id4 = glutCreateMenu(material_func);
	glutAddMenuEntry("Gold", 1);
	glutAddMenuEntry("Silver", 2);
	glutAddMenuEntry("Copper", 3);

	sub_menu_id5 = glutCreateMenu(element_func);
	glutAddMenuEntry("Ambient only", 1);
	glutAddMenuEntry("Ambient and Diffuse", 2);
	glutAddMenuEntry("Ambient, Diffuse and Specular", 3);
	
	//create the main menu
	menu_id1 = glutCreateMenu(main_menu_handler);
	glutAddSubMenu("Light 1", sub_menu_id1);
	glutAddSubMenu("Light 2", sub_menu_id2);
	glutAddSubMenu("Light 3", sub_menu_id3);
	glutAddSubMenu("Material Properties", sub_menu_id4);
	glutAddSubMenu("Light Element", sub_menu_id5);
	glutAddMenuEntry("Quit", 0);
	
	// Attach menus to right-click button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
}


// renders the sphare.
void render() {

	glPushMatrix();
		glutSolidSphere(1.0, 64, 10);
	glPopMatrix();

}


// display registry, clears the color and depth buffers, sets camera position and orientation and calls the render function 
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
	glLoadIdentity(); // reset the modelview matrix
	// viewing
	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 3.0, 0.0, 1.0, 0.0); // set the camera position and orientation
	render(); // render the scene
	glutSwapBuffers(); //Swap the front and back buffers

}


// reshape registry
// called when window is resized to change the viewport
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the client window area
	glMatrixMode(GL_PROJECTION); // set the projection matrix mode
	glLoadIdentity(); // reset the projection matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0); // set the projection frustum
	glMatrixMode(GL_MODELVIEW); // set the modelview matrix mode

}



// main program 
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //set display mode to double buffer
	glutInitWindowPosition(100, 100); //set top-left display-window position
	glutInitWindowSize(500, 500); //set display-window width and height
	glutCreateWindow("TME 3 _ Q1"); //create display window

	glutDisplayFunc(display); //call display function
	glutReshapeFunc(reshape); // call reshape function
	initialize(); // initialize OpenGL
	create_menus();
	glutMainLoop(); //display everything and wait

	return EXIT_SUCCESS;

}