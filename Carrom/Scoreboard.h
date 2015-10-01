#include <bits/stdc++.h>
class Scoreboard{
	public :
		float xorigin,yorigin;
		int display;
		Scoreboard(float x,int y,int value){
			xorigin = x;
			yorigin = y;
			display = value;
		}
		void drawDigit(float x,float y,int value);
		void drawScoreboard(float x,float y,float off,int value);
};