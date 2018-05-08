/*************************************************************/

/*  CSCI 250 Computer Graphics                               */

/*  Spring 2018 Program #1                                   */

/*  Author: Christopher Smith                                */

/*  Date: 2 February 2018                                    */

/*  This file contains code to generate images using         */

/*  raytracing lines via coordinates.                        */

/*************************************************************/


// Modified from one of the GLUT sample files by Mark Kilgard simple.c
#include <iostream>
#include <complex.h>
#include <math.h>
#include "glut.h"
using namespace std;

#define PI 3.14159265359

void display(void)
{
	double Sides = 5;
	double Divisions = 6;
	double xa = 1;
	double ya = 2;
	double xb = 1;
	double yb = 2;
	int input = 3;

	cout << "\n How many sides would you like this shape to have? > "; // Prompt user for inputs.
	cin >> input; 
	if (input > 2) // 3 sides is a triangle, minimum needed for shape with volume.
	{
		Sides = input; // Implement user input.
	}
	else
	{
		cout << "\n I'm afraid that's too few sides for a shape to have. Using default value of " << Sides; // Prevent users from creating line or incomprehensible shape
	}

	cout << "\n How many subdivisions would you like this shape to have? (0 or 1 do nothing) > "; // Prompt user for inputs.
	cin >> input; 
	if (input > -1)
	{
		Divisions = input; // Implement user input.
	}
	else
	{
		cout << "\n I'm afraid that's an invalid number. Using default value of " << Divisions; // Prevent users from incomprehensible input
	}
	

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES); // Draw outer shell
		for (int i = 0; i < Sides; i++) // Builds outer shell
		{
				xa = (double)(cos(((i * 2 * PI / (Sides))) + PI / 2)) - 0.02;   // Determines points based on X and Y values from cos and sin formulas, radius is always 1
				ya = (double)(sin(((i * 2 * PI / (Sides))) + PI / 2)) - 0.02;
				xb = (double)(cos((((i + 1) * 2 * PI / (Sides))) + PI / 2)) - 0.02;
				yb = (double)(sin((((i + 1) * 2 * PI / (Sides))) + PI / 2)) - 0.02;

				glColor3f(0.8, 0.4, 0); // Color changes with each point
				glVertex2f(xa, ya); // Connects to current point
				glVertex2f(xb, yb); // Connects to next point FROM current point
				glVertex2f(0, 0); // Return to center FROM next point
				glVertex2f(xa, ya); // Connects to current point FROM center
		} // End of outer shell
	glEnd();

	glBegin(GL_LINES); // Draw inner divisions shell
	for (int i = 0; i < Sides; i++) // First loop is for each side
	{
		xa = (double)(cos(((i * 2 * PI / (Sides))) + PI / 2)) - 0.02; // Determines points based on X and Y values from cos and sin formulas, radius is always 1
		ya = (double)(sin(((i * 2 * PI / (Sides))) + PI / 2)) - 0.02;
		xb = (double)(cos((((i + 1) * 2 * PI / (Sides))) + PI / 2)) - 0.02;
		yb = (double)(sin((((i + 1) * 2 * PI / (Sides))) + PI / 2)) - 0.02;

		for (int j = 1; j <= Divisions; j++) // Draw subdivisions going counterclockwise
		{
			if (j != Divisions) // Don't overlap existing line
			{
				glColor3f(0, ((Divisions - j) / Divisions), 1);	// Determine color via RGB code... in this case bluish, changes
				glVertex2f(xa*((Divisions - j) / Divisions), ya*((Divisions - j) / Divisions)); // Connects to current point increments
				glVertex2f(xa + ((Divisions - j) / Divisions)*(xb - xa), ya + ((Divisions - j) / Divisions)*(yb - ya)); // Connects to next point FROM current point
			}
			
		}

		for (int j = 1; j <= Divisions; j++) // Draw subdivisions going clockwise
		{
			if (j != Divisions) // Don't overlap existing line
			{
				glColor3f(1, ((Divisions - j) / Divisions), 0);	// Determine color via RGB code... in this case magenta, changes
				glVertex2f(xb*((Divisions - j) / Divisions), yb*((Divisions - j) / Divisions)); // Connects to next point increments
				glVertex2f(xb + ((Divisions - j) / Divisions)*(xa - xb), yb + ((Divisions - j) / Divisions)*(ya - yb)); // Connects to current point FROM next point	
			}
		}
	} // End of outer shell
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("Drawn Shape");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}