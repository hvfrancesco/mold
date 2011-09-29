# include "ormon.h"

void Ormon::setup(float x, float y)
{

dead = false;

position.x = x;
position.y = y;

}

void Ormon::randomGenerate(ofVec2f center, float radius)
{

dead = false;
float r = ofRandom(0, radius);
float angle = ofRandom(0, 2*PI);
position.x = center.x + (cos(angle)*r);
position.y = center.y + (sin(angle)*r);

}

void Ormon::update()
{

}

void Ormon::draw()
{
    if (!dead) {
        ofSetColor(255,255,255);
        /*
        ofFill();
        ofEnableAlphaBlending();
        ofCircle(position.x, position.y, 1);
        ofDisableAlphaBlending();
        ofNoFill();
        */
    }
    else {
        ofSetColor(20,20,20);
        /*
        ofFill();
        ofEnableAlphaBlending();
        ofCircle(position.x, position.y, 1);
        ofDisableAlphaBlending();
        ofNoFill();
        */
    }


}
