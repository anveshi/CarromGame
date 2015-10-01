#include <bits/stdc++.h>
#include "Scoreboard.h"
#include <GL/glut.h>
using namespace std;
void drawthinRectangle( pair<float,float> p1,pair <float,float> p2){
		glColor3f(0.0,0.0,0.0);
		glLineWidth(45.8);
		glBegin(GL_LINES);
		glVertex3f(p1.first,p1.second,-8.0);
		glVertex3f(p2.first,p2.second,-8.0);
		glEnd();
}
void Scoreboard :: drawDigit(float x,float y,int value){
	if(value==0 || value ==2 ||value==6|| value==8)
		drawthinRectangle(make_pair(x,y),make_pair(x,y+0.35));//
	if(value==0 || value==4|| value==5|| value==6|| value==8|| value==9)
		drawthinRectangle(make_pair(x,y+0.35),make_pair(x,y+0.7));
	if(value==-1||value==2 || value==3 || value==4|| value==5||value==6||value==8||value==9)
		drawthinRectangle(make_pair(x,y+0.35),make_pair(x+0.3,y+0.35)); //beech
	if(value==0||value==2||value==3||value==5||value==6||value==7||value==8||value==9)
		drawthinRectangle(make_pair(x,y+0.7),make_pair(x+0.3,y+0.7)); //upar
	if(value==0||value==2||value==3||value==5||value==6||value==8||value==9)
		drawthinRectangle(make_pair(x,y),make_pair(x+0.3,y));//neeche
	if(value==0||value==1||value==3||value==4||value==5||value==6||value==7||value==8||value==9)
		drawthinRectangle(make_pair(x+0.3,y),make_pair(x+0.3,y+0.35));
	if(value==0||value==1||value==2||value==3||value==4||value==7||value==8||value==9)
		drawthinRectangle(make_pair(x+0.3,y+0.35),make_pair(x+0.3,y+0.7));
	return ;
}
void Scoreboard :: drawScoreboard(float x,float y ,float off,int value){
	glColor4f(0.1,0.5,1.0,0.5);
	glBegin(GL_QUADS);
	glVertex3f(x-0.2,y-0.2,-8.0);
	glVertex3f(x-0.2,y+0.9,-8.0);
	glVertex3f(x+1.5,y+0.9,-8.0);
	glVertex3f(x+1.5,y-0.2,-8.0);
	glEnd();
	if(value<100){
	if(value<0){
		drawDigit(x,y,-1);
		value =-1*value;
	}
	else
	drawDigit(x,y,0);
	drawDigit(x+off,y,value/10);
	drawDigit(x+2*off,y,value%10);
	}
	else{
		drawDigit(x,y,value/100);
		value%=100;
		drawDigit(x+off,y,value/10);
		drawDigit(x+2*off,y,value%10);
	}
	glColor3f(1.0,1.0,1.0);
	drawthinRectangle(make_pair(x-0.2,y-0.2),make_pair(x-0.2,y+0.9));
	drawthinRectangle(make_pair(x-0.3,y+0.9),make_pair(x+1.6,y+0.9));
	drawthinRectangle(make_pair(x+1.5,y+0.9),make_pair(x+1.5,y-0.2));
	drawthinRectangle(make_pair(x-0.3,y-0.2),make_pair(x+1.6,y-0.2));
}
