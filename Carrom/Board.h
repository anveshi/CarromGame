#include<bits/stdc++.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
class Board{
public:
	float ball_rad;
	float box_len;
	Board(float bl,float br){
		box_len = bl;
		ball_rad = br;
	}
	void drawInnerpattern();
	void render();
	void drawArrow(float x1,float y1,float x2,float y2,float z);
	void drawCenterPattern();
	void drawBox(float len);
	void drawBall(float rad);
	void drawCircle(float rad);
	void drawTriangle();
};