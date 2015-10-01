#include "Powermeter.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;
void Powermeter :: drawPowermeter(float bar_length){
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	float bRight = (box_len/2)+ 2.0f;
	float bLeft = (box_len/2)+ 1.6f;
	float bBottom = -(box_len/2);
	glBegin(GL_POLYGON);
	glColor3f(0.2,0.5,0.7);
	glVertex3f(bLeft-0.25,bBottom-0.25,-8.0f);
    glVertex3f(bRight+0.25,bBottom-0.25,-8.0f);
    glVertex3f(bRight+0.25,bBottom,-8.0f);
    glVertex3f(bLeft-0.25,bBottom,-8.0f);
    glEnd();


	for (int i = 0; i < bar_length; ++i) {
            bBottom = -(box_len/2) +i*0.5f;
            glBegin(GL_POLYGON);
            float c1=(i*25)/255.00;
            float c2=(1.0-c1);
            glColor3f(c1,c2,0.2f);
            glVertex3f(bLeft,bBottom,-8.0f);
            glVertex3f(bRight,bBottom,-8.0f);
            glVertex3f(bRight,bBottom+0.40f,-8.0f);
            glVertex3f(bLeft,bBottom+0.40f,-8.0f);
            glEnd();
	}
glDisable(GL_LINE_SMOOTH);
}