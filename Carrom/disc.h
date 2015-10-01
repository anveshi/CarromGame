#include<bits/stdc++.h>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;
class disc{
public:   
    float dmass;
    float dradius;
    pair<float,float> dvelocity;
    pair<float,float> dposition;
    bool isdead;
    string dtype;
    disc(){
        dvelocity = make_pair(0.0,0.0);
        dtype="white";
    }
    disc(float dmass_,float dradius_,pair<float,float> dvelocity_,pair<float,float> dposition_
        ,string dtype_){
        dmass = dmass_;
        dradius = dradius_;
        dvelocity = dvelocity_;
        dposition = dposition_;
        dtype = dtype_;
    }
    void drawDisc(bool c);
    void handleWallCollision(float box_len);
    void handleCollision(disc& _disc,float dt);
    void advance(float t);
    bool colliding_with(const disc& _disc);
    bool isapproaching(const disc& _disc);
    void reset(float x,float y);
    bool inpot(float x);
    void remove_disc(float x,float  );
    void drawlineof();

};
