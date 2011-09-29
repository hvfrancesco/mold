#include "testApp.h"
#include "ofxSimpleGuiToo.h"

//--------------------------------------------------------------
void testApp::setup()
{

    ofSetBackgroundAuto(true);
    ofBackground(0,0,0);
    bBackground = false;
    bRecord = false;
    bGo = false;

    // cam init stuff
    camWidth = 640;
    camHeight = 480;
    cam.setVerbose(true);
    cam.initGrabber(camWidth, camHeight);
    snapPixels = new unsigned char [camWidth*camHeight*3];

    // dark-bright thresholds
    darkThreshold = 0.9;
    brightThreshold = 0.5;
    //deadIterations = 0;

    //hormonSize = 2;
    hormonDeadZoneRadius = 10;
    //budSize = 1;
    //growthStep = 5;
    //splitChance = 0.05;

    //margin = 50;
    numHormons = 10000;
    numBuds = 1;

    center.x = ofGetWindowWidth()/2;
    center.y = ofGetWindowHeight()/2;
    radius = ofGetWindowHeight()*0.4;
    ofSetCircleResolution(36);
    deadIterations = 0;

    ormons = list<Ormon>() ;
    buds = list<Bud>();

    /*
    for (int i = 0; i < numHormons; i++)
    {
        Ormon o;
        o.randomGenerate(center, radius);
        ormons.push_back(o);
    }

    for (int i = 0; i < numBuds; i++)
    {
        Bud b;
        b.randomGenerate(center, radius, &buds);
        buds.push_back(b);
    }
    */

}

//--------------------------------------------------------------
void testApp::update()
{

    // grabs video frame from camera

    if (cam.getHeight() > 0)  // isLoaded check
    {
        cam.grabFrame();
        if (cam.isFrameNew())
        {
            pixels = cam.getPixels();
        }

    }
    if (bGo)
    {
        for (list<Bud>::iterator bi = buds.begin(); bi != buds.end(); bi++)
        {
            Bud * b = &*bi;
            b->associatedOrmons.clear();
        }

        for (list<Ormon>::iterator oi = ormons.begin(); oi != ormons.end(); oi++)
        {
            Ormon * o = &*oi;
            if (!o->dead)
            {
                associateBud(o);
                o->update();
            }
        }

        for (list<Bud>::iterator bi = buds.begin(); bi != buds.end(); bi++)
        {
            Bud * b = &*bi;
            b->update();
        }
    }
}

//--------------------------------------------------------------
void testApp::draw()
{

    cam.draw(0,0);

    if(bGo)
    {
        for (list<Bud>::iterator bi = buds.begin(); bi != buds.end(); bi++)
        {
            Bud * b = &*bi;
            b->drawLinks();
        }

        for (list<Ormon>::iterator oi = ormons.begin(); oi != ormons.end(); oi++)
        {
            Ormon * o = &*oi;
            o->draw();
        }

        for (list<Bud>::iterator bi = buds.begin(); bi != buds.end(); bi++)
        {
            Bud * b = &*bi;
            b->draw();
        }
    }

    if (bRecord)
    {
        ofSaveFrame();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    // takes snapshot
    if ( key == ' ')
    {
        snapshot();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}

//--------------------------------------------------------------
void testApp::associateBud(Ormon * o)
{

    float minDist = 0;
    Bud * closestBud;
    for (list<Bud>::iterator bi = buds.begin(); bi != buds.end(); bi++)
    {
        Bud * b = &*bi;
        if (!b->dead)
        {
            ofVec2f distVector = o->position - b->position;
            float dist = distVector.length();
            if ((minDist == 0) || (dist < minDist))
            {
                closestBud = &*bi;
                minDist = dist;
            }
        }
    }
    if (minDist < hormonDeadZoneRadius)
    {
         o->dead = true;
    }
    closestBud->associatedOrmons.push_back(*o);
}

//--------------------------------------------------------------
void testApp::snapshot()
{

    buds.clear();
    ormons.clear();
    int totalBrightness = 0;
    float mediumBrightness;

    for (int j = 0; j<camWidth*camHeight; j++)
    {
        snapPixels[j*3+0] = pixels[j*3+0];
        snapPixels[j*3+1] = pixels[j*3+1];
        snapPixels[j*3+2] = pixels[j*3+2];
        totalBrightness += (pixels[j*3+0]+pixels[j*3+1]+pixels[j*3+2]);
    }

    mediumBrightness = totalBrightness/(camWidth*camHeight*765.0);
    cout << "medium brightness "<< mediumBrightness << endl;

    for (int y = 0; y < camHeight; y+=10)
    {
        for (int x = 0; x < camWidth; x+=10)
        {
            int i = (y*camWidth+x);
            int r = snapPixels[i+0];
            int g = snapPixels[i+1];
            int b = snapPixels[i+2];
            float brightness = (r+g+b)/765.0;

            if (brightness > mediumBrightness - (mediumBrightness*brightThreshold))
            {
                Ormon newOrmon;
                newOrmon.setup(x+camWidth,y);
                ormons.push_back(newOrmon);
            }
            else if (brightness <= mediumBrightness + (mediumBrightness*darkThreshold))
            {
                Bud newBud;
                newBud.setup(x+camWidth, y, &buds);
                buds.push_back(newBud);
            }
        }
    }
    cout << "n. of buds " << buds.size() << endl;
    cout << "n. of ormons " << ormons.size() << endl;
    bGo = true;
}
