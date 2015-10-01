#include<bits/stdc++.h>
#include <GL/glut.h>
#include "disc.h"
#include "Board.h"
#include "Powermeter.h"
#include "Scoreboard.h"
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define NO_OF_DISCS 20
using namespace std;

enum STATES{STATIC,DYNAMIC,SET_STRIKER};
STATES BOARDSTATE=SET_STRIKER;

float theeta = DEG2RAD(75);
float box_len = 5.0f;
float ball_rad = 0.2f;
int bar_length=5;
int blackdead=0;
int whitedead=0;
int playerturn = 0;
int whiteplayerscore=100000;
int blackplayerscore=100000;
float v_xx,v_yy;

void drawalldiscs();
void initialisediscarray();
void drawScene();
void update(int value);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void drawDandi(int value);

vector <disc> discs(NO_OF_DISCS);
vector <disc> deaddiscs;
Board carrom_board(box_len,ball_rad);
Powermeter powermeter(box_len,bar_length);
Scoreboard scoreboard(1,1,1);

void displayText(float x,float y ,float space,string& str){
    int len = str.length();
    for(int i=0;i<len;i++){
        glPushMatrix(); 
            glRasterPos3f(x+i*space,y,-8.0);
            glutBitmapCharacter(  GLUT_BITMAP_TIMES_ROMAN_24  , str[i]);
        glPopMatrix();
    }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);    
    if(playerturn==0 && BOARDSTATE==SET_STRIKER)
        whiteplayerscore-=20;
    else if(playerturn==1 && BOARDSTATE==SET_STRIKER)
        blackplayerscore-=20;
    carrom_board.render();
    drawalldiscs();
    powermeter.drawPowermeter(bar_length);
    scoreboard.drawScoreboard(-box_len/2-2.5,-2.6,0.5,whiteplayerscore/1000);
    scoreboard.drawScoreboard(-box_len/2-2.5,1.85,0.5,blackplayerscore/1000);
    string p_1="PLAYER1",p_2="PLAYER2";
    glColor3f(0.1,0.0,0.0);
    displayText(-4.6,1.47,0.1,p_1);
    displayText(-4.6,-1.6,0.1,p_2);
    glutSwapBuffers();
    glLoadIdentity();
}

void initialisediscarray(){
    float disc_rdius = ball_rad - (0.03)*(box_len/5.0);
    float teetha = DEG2RAD(60);
    float meetha = DEG2RAD(30);
    discs[1].dtype="striker";discs[0].dtype="queen";discs[0].dmass=1;discs[1].dmass=2;
    discs[0].dposition = make_pair(0.0,0.0);
    discs[1].dposition = make_pair(0.0,(-box_len/2+0.72));
    discs[0].dradius=disc_rdius;discs[1].dradius=ball_rad;
    discs[0].isdead = 0; discs[1].isdead = 0;
    for(int i=2;i<NO_OF_DISCS;i++){
        discs[i].isdead = 0;
        discs[i].dmass = 1;
        discs[i].dradius = disc_rdius;
        if(i&1)
            discs[i].dtype = "black";
        else
            discs[i].dtype = "white";
        if(i<8)
            discs[i].dposition = make_pair(2*disc_rdius*cos((i-2)*teetha),2*disc_rdius*sin((i-2)*teetha));
        else{
            float off;
            if(i&1)off=4;
            else off=3.464;
            discs[i].dposition = make_pair(off*disc_rdius*cos((i-7)*meetha),off*disc_rdius*sin((i-7)*meetha));
        }
    } 
}

void drawalldiscs(){
    for(int i=0;i<NO_OF_DISCS;i++){
        if(playerturn==0)       
            discs[i].drawDisc(0);
        else
            discs[i].drawDisc(1);
    }
    if(BOARDSTATE==SET_STRIKER)
        drawDandi(10);  
}

float d2D(float x1,float y1,float x2,float y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void drawCircle(float rad){
    glPointSize(2.8);
    glBegin(GL_POINTS);
    for(int i=0;i<1000;++i){
        glVertex3f(rad*cos(2*PI*i/1000.0),rad*sin(2*PI*i/1000.0),0.0f);
    }
    glEnd();
}

void drawDandi(int value){
    float xpos = discs[1].dposition.first;
    float ypos = discs[1].dposition.second;
    float x1,y1;
    if(playerturn==0)
        glColor3f(1.0,1.0,1.0);
    else
        glColor3f(0.0,0.0,0.0);
    glLineWidth(1.0);
    glPushMatrix();
    glBegin(GL_POINTS);
        for(int i=0;;i++){
            int f=0;            
            x1 = xpos + (i*(cos(theeta)))/1000;
            y1 = ypos + (i*(sin(theeta)))/1000;
            if(2* fabs(x1)>box_len || 2* fabs(y1)>box_len)
                f=1;
            int discs_size = discs.size();
            for(int j=0;j<discs_size;j++){
                if(j==1)continue;
                float d;
                d = d2D(x1,y1,discs[j].dposition.first,discs[j].dposition.second);
                if(d - discs[j].dradius <0.0){
                    f=1;
                    break;
                }
            }
            if(f)
                break;
            glVertex3f(x1,y1,-8.0);
        }
    glPushMatrix();
    glTranslatef(x1,y1,-8.0);
    drawCircle(2);
    glPopMatrix();
    glEnd();
    glPopMatrix();
    return ;
}

void strikerreset(int value){
    discs[1].reset(0.0,(-box_len/2+0.72*(box_len)/5.0));
    BOARDSTATE = SET_STRIKER;
    for(int i=0;i<(int)discs.size();i++){
        if(!discs[i].isdead && discs[i].dtype!="striker"){
            discs[i].dposition.first *=-1;
            discs[i].dposition.second *=-1; 
        }
    }
    playerturn^=1;
}

void update(int value) {
    int size = discs.size();    
    for(int i=0;i<size;i++){
        for(int j=i+1;j<=size;j++){
            if(discs[i].colliding_with(discs[j]) && discs[i].isapproaching(discs[j])){
                discs[i].handleCollision(discs[j],5);
            }
            discs[i].handleWallCollision(box_len);
        }
        discs[i].advance(2);
    }
   
    for(int i=0;i<size;i++){
        if(discs[i].inpot(box_len/2 -0.25) && discs[i].dtype!="striker" && discs[i].isdead==0){
            if(discs[i].dtype=="queen"){
                if(playerturn==0)
                    whiteplayerscore+=20000;
                else
                    blackplayerscore+=20000;
            }
            else if(discs[i].dtype=="white"){
                if(playerturn==0)
                    whiteplayerscore+=10000;
                else
                    blackplayerscore-=5000;
            }
            else if(discs[i].dtype=="black"){
                if(playerturn==1)
                    blackplayerscore+=10000;
                else
                    whiteplayerscore-=5000;
            }
            discs[i].isdead = 1;
            discs[i].dvelocity = make_pair(0,0);
            float zz=1;
            if(playerturn==0){
                if(whitedead>5)zz=zz-2*discs[i].dradius;
                discs[i].remove_disc(-box_len/2-1.1-2*(whitedead%6)*discs[i].dradius,-zz);
                whitedead++;
            }
            else if(playerturn==1){
                if(blackdead>5)zz=zz-2*discs[i].dradius;
                discs[i].remove_disc(-box_len/2-1.1-2*(blackdead%6)*discs[i].dradius,zz);
                blackdead++;
            }
            deaddiscs.push_back(discs[i]);
        }
    } 
    BOARDSTATE = STATIC ;
    for(int i=0;i<NO_OF_DISCS;i++){
        if(discs[i].dvelocity.first!=0 || discs[i].dvelocity.second !=0){
            BOARDSTATE = DYNAMIC;
            break;
        }
    }
    if(BOARDSTATE == STATIC){
        glutTimerFunc(2000,strikerreset,0); 
        return;
    }
    glutTimerFunc(5, update, 0);
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(1.0,1.0,1.0,1.0); // Setting a background color
    deaddiscs.clear(),blackdead=0,whitedead = 0;
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if (key == 32 && BOARDSTATE == SET_STRIKER){
        BOARDSTATE = DYNAMIC ;
        float v_x,v_y;
        v_x = 0.03*(bar_length)* cos(theeta);
        v_y = 0.03*(bar_length)* sin(theeta);
        discs[1].dvelocity = make_pair(v_x,v_y);
        glutTimerFunc(5, update, 0);
    }
    if(key == 97 && BOARDSTATE == SET_STRIKER && theeta<DEG2RAD(180))
        theeta+=0.01;
    if(key == 99 && BOARDSTATE == SET_STRIKER && theeta>DEG2RAD(0))
        theeta-=0.01;
}

void handleKeypress2(int key, int x, int y) {
    if(BOARDSTATE == SET_STRIKER){
        if (key == GLUT_KEY_LEFT  ){
            if(discs[1].dposition.first>(-box_len/2)+1.1*(box_len)/5.0)
            discs[1].dposition.first -= 0.05;
        }
       if (key == GLUT_KEY_RIGHT )
            if(discs[1].dposition.first<(box_len/2)-(1.1)*box_len/5.0)
            discs[1].dposition.first += 0.05;
        if (key == GLUT_KEY_UP)
            if(bar_length<10)
                bar_length = (bar_length+1);
        if (key == GLUT_KEY_DOWN)
            if(bar_length>1)
                bar_length -= 1;
    }
}
float angle2D(pair<float,float>p1,pair<float,float>p2){
    return atan(((p2.second-p1.second)/(p2.first-p1.first)));
}
void upvelocity(int value){
     discs[1].dvelocity = make_pair(v_xx,v_yy);
    glutTimerFunc(5, update, 0);
}
int mouseMiddleState=0; //0 represents mouseMiddle not clicked 1 represents clicked
int DragX,DragY;
int c1=0,c2=0;
int rightclickstate;
int leftMouseDoubleClick=0;
void handleMouseclick(int button, int state, int x, int y) {
    if(state== GLUT_UP){    
        if(button == GLUT_MIDDLE_BUTTON)
            mouseMiddleState=0;
    }
    if(button == GLUT_RIGHT_BUTTON && BOARDSTATE==SET_STRIKER){
            DragX = x;
            rightclickstate=1;
    }
    if (state == GLUT_DOWN && BOARDSTATE == SET_STRIKER)
    {
        if(button == GLUT_MIDDLE_BUTTON){
            mouseMiddleState=1;
            DragX=x;
            DragY=y;
        }
        if (button == GLUT_LEFT_BUTTON && BOARDSTATE==SET_STRIKER){
                GLdouble ox=0.0,oy=0.0,oz=0.0;
                GLint viewport[4];
                GLdouble modelview[16],projection[16];
                GLfloat wx=x,wy,wz;
                glGetIntegerv(GL_VIEWPORT,viewport);
                y=viewport[3]-y;
                wy=y;
                glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
                glGetDoublev(GL_PROJECTION_MATRIX,projection);
                glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
                gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);
                ox*=250/3.14;
                oy*=250/3.14;
                    float angle = angle2D(make_pair(ox,oy),discs[1].dposition);
                    if(angle<0.0)
                        angle+=DEG2RAD(180);
                    if((((ox-discs[1].dposition.first)>0&&(oy-discs[1].dposition.second)>0)) ||
                        (((ox-discs[1].dposition.first)<0&&(oy-discs[1].dposition.second)>0)) ){
                        theeta=angle;
                    v_xx = 0.03*(bar_length)* cos(theeta);
                    v_yy = 0.03*(bar_length)* sin(theeta);
                    glutTimerFunc(300,upvelocity,0);
                }
                    glutPostRedisplay();
            
            }
    }
}
void handleMouseDrag(int x,int y){
    if(mouseMiddleState && BOARDSTATE==SET_STRIKER){  
        if(y<DragY && bar_length<10 ){
         if(c1==20) {bar_length++;c1=0;}
         else c1++;
        }
        if(y>DragY && bar_length>0){
            if(c2==20) {bar_length--;c2=0;}
            else c2++; 
        }
        DragX=x;
        DragY=y;
    }
    if(rightclickstate && BOARDSTATE==SET_STRIKER){
        discs[1].dposition.first +=(x-DragX)*0.0062f;
        if((discs[1].dposition.first)>=((box_len/2)-(1.1)*box_len/5.0))
            discs[1].dposition.first = ((box_len/2)-(1.1)*box_len/5.0);
        else if(discs[1].dposition.first<=-(box_len)/2+1.1*box_len/5.0)
            discs[1].dposition.first = (-box_len/2+1.1*box_len/5.0);
        DragX=x;
    }
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;
    string p1,p2;
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
    glutCreateWindow("Carrom board");  // Setup the window
    initRendering();
    initialisediscarray();

    glutFullScreen();
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutMotionFunc(handleMouseDrag);
    glutReshapeFunc(handleResize);
    glutMainLoop();
    return 0;
}
