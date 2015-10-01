#include<bits/stdc++.h>
#include <GL/glut.h>
#include "Board.h"

int dx[]={-1,1,1,-1};
int dy[]={-1,-1,1,1};
float tri_x = 0.0f;
float tri_y = 0.0f;
float hole_rad;
float innerradius,outerradius;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;


void Board :: drawInnerpattern(){
	hole_rad = (ball_rad)*1.3f*( box_len )/5.0;
    glBegin(GL_LINES);
    for(int i=-30;i<0;i++){
        glVertex3f(hole_rad*cos(2*PI*i/360.0),hole_rad*sin(2*PI*i/360),0.0f);
        glVertex3f(innerradius*cos(2*PI*0/360.0),innerradius*sin(2*PI*0/360),0.0f);
    }
    glEnd();
   /* glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
         for(int i=0;i<30;i++){
            glVertex3f(hole_rad*cos(2*PI*i/360.0),hole_rad*sin(2*PI*i/360),0.0f);
            glVertex3f(innerradius*cos(2*PI*0/360.0),innerradius*sin(2*PI*0/360),0.0f);
        }
    glEnd();*/
}


void Board :: render(){
	hole_rad = (ball_rad)*1.3f*( box_len )/5.0;
	glLoadIdentity();
    glPushMatrix();
        glTranslatef(0.0f,0.0f,-8.0f);
        //glColor3f(0.64,0.16,0.16); //brown
        glColor3f(0.32,0.16,0.16); //brown

        drawBox(box_len+0.8*(box_len/5.0));
        glColor3f(1.0f,0.8f,0.6f);   //skin color
        drawBox(box_len);
    glPopMatrix();

    for(int i=0;i<4;i++){//holes
        glPushMatrix();
            glColor3f(0.32f,0.16f,0.16f);
            glTranslatef((dx[i])*((box_len-0.25*(box_len/5.0))/2),(dy[i])*((box_len-0.25*(box_len/5.0))/2),-8.0f);
            drawBall(hole_rad*(box_len)/5.0);
        glPopMatrix();
    }
    glTranslatef(0.0,0.0,-8.0);
    glColor3f(1.0,0.0,0.0); //red
    drawCenterPattern();

    glLoadIdentity();
    glColor3f(0.0,0.0,0.0);
    for(int i=0;i<4;i++){
        glPushMatrix();
        glRotatef(90.0*i, 0.0, 0.0, 1.0);
        drawArrow(-(box_len/5.0)*0.8,-(box_len/5.0)*0.8,-(box_len/5.0)*2.0,-(box_len/5.0)*2.0,-8.0f);
        glPopMatrix();
    } // arrow design

}

void Board :: drawCircle(float rad){
    glPointSize(2.8);
    glBegin(GL_POINTS);
    for(int i=0;i<1000;++i){
        glVertex3f(rad*cos(2*PI*i/1000.0),rad*sin(2*PI*i/1000.0),0.0f);
    }
    glEnd();
}

void Board :: drawCenterPattern(){
	hole_rad = (ball_rad)*1.3f*( box_len )/5.0;
    innerradius = (0.75*(box_len)/5.0);
    outerradius = (0.80*(box_len)/5.0);
    glColor3f(0.0,0.0,0.0);
    drawCircle(innerradius);;
    drawCircle(outerradius); // circles on centre
    glColor3f(1.0,0.0,0.0);
    drawCircle(hole_rad);

    drawBall(hole_rad - (0.05));
    for(int i=0;i<8;i++){
        glPushMatrix();
        glRotatef(45.0*i, 0.0, 0.0, 1.0);
        if(i&1)
            glColor3f(1.0,0.0,0.0);
        else
            glColor3f(0.0,0.0,0.0);
        drawInnerpattern();
        glPopMatrix();
    }
    glColor3f(1.0,0.0,0.0);
    drawCircle( innerradius );
    glColor3f(0.0,0.0,0.0);
    drawCircle(hole_rad - (0.05));
}
void Board :: drawArrow(float x1,float y1,float x2,float y2,float z){
    glLineWidth(2.8);
    glPushMatrix();
    float radius,radiusdash,xdash,ydash;
    radius = 0.2f;
    radiusdash = 0.707*radius;
    xdash = x1- radiusdash;
    ydash = y1 - radiusdash;
    glTranslatef(xdash,ydash,z);
    glRotatef(-90,0.0f,0.0f,1.0f);
    glBegin(GL_POINTS);
    for(int i=0;i<750;++i){
        glVertex3f(radius*cos(2*PI*i/1000.0),radius*sin(2*PI*i/1000.0),0.0);
    }
    glEnd();
    glPopMatrix();
    glBegin(GL_LINES);
        glVertex3f(x1,y1,z);
        glVertex3f(x2,y2,z);
    glEnd();

    glPushMatrix();
        glTranslatef(x2,y2,z);
        glRotatef(-15, 0.0f, 0.0f, 1.0f);
        glScalef(0.05f, 0.05f, 0.05f);
        drawTriangle();
    glPopMatrix();

    float cir_x,cir_y,rr,RR;
    cir_x = (2*x2+x1)/3;rr=0.1f*(box_len/5.0);
    cir_y = (2*y2+y1)/3;RR=1.4*rr;

     glPushMatrix();
        float R_x,R_y;
        R_x=cir_x+(rr+RR)*0.707f;
        R_y=cir_y-(rr+RR)*0.707f;
        glTranslatef(R_x, R_y, -8.0f);
        //glColor3f(1.0f, 0.0f, 0.0f);

        drawCircle(RR);

        glColor3f(1.0,0.0,0.0);
        drawBall(RR-0.03*(box_len/5.0));
        glColor3f(0.0,0.0,0.0);

        glLoadIdentity();
    glPopMatrix();

    glPushMatrix();
      R_x=cir_x-(rr+RR)*0.707f;
        R_y=cir_y+(rr+RR)*0.707f;
        glTranslatef(R_x, R_y, -8.0f);
        drawCircle(RR);
                glColor3f(1.0,0.0,0.0);

        drawBall(RR-0.03*(box_len/5.0));
                glColor3f(0.0,0.0,0.0);

         glLoadIdentity();
    glPopMatrix();
    float width_c = (2.9)*(box_len)/5.0;
    glPushMatrix();
     glBegin(GL_LINES);
            glVertex3f(R_x-RR,R_y,z);
            glVertex3f(R_x-RR,R_y+width_c,z);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glBegin(GL_LINES);
            glVertex3f(R_x+RR,R_y,z);
            glVertex3f(R_x+RR,R_y+width_c,z);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(cir_x,cir_y,-8.0f);
        glRotatef(45,0.0,0.0,1.0);
        glBegin(GL_POLYGON);
            for(int i=0;i<500;++i){
            glVertex3f(rr*cos(2*PI*i/1000.0),rr*sin(2*PI*i/1000.0),0.0);
            }
        glEnd();
        glBegin(GL_POINTS);
        for(int i=500;i<1000;++i){
            glVertex3f(rr*cos(2*PI*i/1000.0),rr*sin(2*PI*i/1000.0),0.0);
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(xdash,ydash-radius,-8.0f);
        glRotatef(60, 0.0f, 0.0f, 1.0f);
        glScalef(0.05f, 0.05f, 0.05f);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(xdash-radius,ydash,-8.0f);
        glRotatef(30, 0.0f, 0.0f, 1.0f);
        glScalef(0.05f, 0.05f, 0.05f);
        drawTriangle();

    glPopMatrix();
    glLoadIdentity();
}
void Board :: drawBox(float len) {
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
}

void Board :: drawBall(float rad) {
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void Board :: drawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.865f, 0.0f);
    glVertex3f(-0.5f, -0.865f, 0.0f);
    glEnd();
}