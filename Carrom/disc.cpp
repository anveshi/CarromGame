#include<bits/stdc++.h>
#include <GL/glut.h>
#include "disc.h"
#define PI 3.141592653589
#define EPS 0.0000
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;

float magnitude(pair<float,float> p){
    return(sqrt(p.first * p.first + p.second * p.second));
}

float distance2d(pair<float,float>p1,pair<float,float>p2){
    pair<float,float> pp;
    pp.first = p1.first - p2.first;
    pp.second = p1.second -p2.second;
    float ans = magnitude(pp);
    return ans;
}

float angle(pair<float,float> p1,pair<float,float> p2){

    float adotb = p1.first * p2.first + p1.second * p2.second ;
    float moda,modb;
    moda = magnitude(p1);
    modb = magnitude(p2);
    return acos(adotb/(moda*modb));
}

void disc :: advance(float t){
    float mag = magnitude(dvelocity);
    if(mag < 0.001){
        dvelocity = make_pair(0.0,0.0);
        return ;
    }
    float x_change,y_change;
    x_change = 0.001 * fabs((dvelocity.first))/mag;
    y_change = 0.001 * fabs((dvelocity.second))/mag;
    if(fabs(dvelocity.first)< x_change)dvelocity.first =0;
    else if(dvelocity.first>=0)dvelocity.first-=x_change;
    else dvelocity.first+=x_change;

    if(fabs(dvelocity.second)< y_change)dvelocity.second =0;
    else if(dvelocity.second>=0)dvelocity.second-=y_change;
    else dvelocity.second+=y_change;
    
    dposition.first = dposition.first + (dvelocity.first *t)/1000.0;
    dposition.second = dposition.second + (dvelocity.second *t)/1000.0;

}

void disc:: handleWallCollision(float box_len){
    if(dposition.first + dradius > box_len/2 || dposition.first - dradius < -box_len/2)
        dvelocity.first *= -1;   
    if(dposition.second + dradius > box_len/2 || dposition.second - dradius < -box_len/2)
        dvelocity.second *= -1;
    dposition.first = dposition.first + (dvelocity.first)/10;    
    dposition.second = dposition.second + (dvelocity.second)/10;

}


void disc:: handleCollision(disc& _disc,float dt){
    pair <float,float > p1,p2,p3,p4;
    float z1,z2,u1,u2,v1,v2,q11,q22,z,m1,m2,e=0.7;
    z1 = _disc.dposition.first -  dposition.first ;
    z2 =  _disc.dposition.second - dposition.second ;
    z = sqrt(z1*z1+z2*z2);
    u1 =(z1*dvelocity.first + z2*dvelocity.second)/z;
    u2 =(z1*_disc.dvelocity.first + z2*_disc.dvelocity.second)/z;
    m1 = dmass;m2=_disc.dmass;
    v2=(u2*(m2-e*m1)+(1+e)*m1*u1)/(m1+m2);
    v1=(u1*(m1-e*m2)+(1+e)*m2*u2)/(m1+m2);
    q11 = (z2*dvelocity.first - z1*dvelocity.second)/z;
    q22 = (z2*_disc.dvelocity.first - z1*_disc.dvelocity.second)/z;
    dvelocity.first = (v1*z1+q11*z2)/z;
    dvelocity.second = (v1*z2 - q11*z1)/z;
    _disc.dvelocity.first = (v2*z1+q22*z2)/z;
    _disc.dvelocity.second = (v2*z2 - q22*z1)/z;

}

bool disc :: colliding_with(const disc& _disc){
    if( distance2d(dposition, _disc.dposition) > dradius + _disc.dradius +0.070  )
        return false;
    else
        return true;
}
bool disc :: isapproaching(const disc& _disc){
    float k1,k2;
    k1 = 2*(dposition.first - _disc.dposition.first)*(dvelocity.first -_disc.dvelocity.first);
    k2 = 2*(dposition.second - _disc.dposition.second)*(dvelocity.second - _disc.dvelocity.second);
    if(k1+k2<=0.0)
        return true;
    return false;
}
void disc:: reset(float x,float y){
    dposition.first = x;
    dposition.second = y;
    return ;
}

void disc::drawDisc(bool c) {
    glPushMatrix();
    glTranslatef(dposition.first,dposition.second,-8.0);
    if(dtype=="queen")
        glColor3f(1.0,0.078,0.576);
    else if(dtype=="white")
        glColor3f(1.0,1.0,1.0);
    else if (dtype=="black")
        glColor3f(0.439,0.547,0.568); //gray
    else if(dtype=="striker" && c==0)
            glColor3f(0.4,0.7,0.5);
    else if(dtype=="striker" && c==1)
        glColor3f(0.5,0.07,0.3);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0 ; i<360 ; i++) {
       glVertex3f(dradius* cos(DEG2RAD(i)), dradius * sin(DEG2RAD(i)),0.0);
    }
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(0.0,0.0,0.0);
    glPointSize(1.0);
    glBegin(GL_POINTS);
    for(int i=0;i<1000;++i){
        glVertex3f(dradius*cos(2*PI*i/1000.0),dradius*sin(2*PI*i/1000.0),0.0f);
    }
    glEnd();
    glPopMatrix();
    return ;
}

void disc :: drawlineof(){
    float xpos = dposition.first;
    float ypos = dposition.second;
    glBegin(GL_LINES);
        glVertex3f(xpos,ypos,-8.0);
        glVertex3f(0,0,-8.0);
    glEnd();
    return;
}

void disc :: remove_disc(float x,float y){
    dposition = make_pair(x,y); 
    dvelocity = make_pair(0,0);
    return ;
}
bool disc :: inpot(float x){
    float xp = dposition.first;
    float yp = dposition.second;
    if(xp>x && yp>x)
        return true;
    if(xp>x && yp<-x)
        return true;
    if(xp<-x && yp>x)
        return true;
    if(xp<-x && yp< -x)
        return true;
    return false;
}