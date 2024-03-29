#pragma once

#include "ofMain.h"
#include <list>

#include "bud.h"
#include "ormon.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void associateBud(Ormon * o);
        void snapshot();

		int deadIterations;

//var buds;
//var hormons;
        int hormonSize;
        int hormonDeadZoneRadius;
        int budSize;
        int growthStep;
        float splitChance;

        int margin;
        int numHormons;

        int numBuds;

        ofVec2f center;
        float radius;

        list<Bud> buds;
        list<Ormon> ormons;

        bool bBackground;
        bool bRecord;
        bool bGui;
        bool bGo;

        int camWidth;
        int camHeight;
        ofVideoGrabber cam;
        ofTexture camTexture;
        unsigned char * pixels;
        unsigned char * snapPixels;

        float darkThreshold;
        float brightThreshold;

        ofTrueTypeFont ttf;

        // gui elements
        bool showGui;
        void openImageFile();
        void openVideoFile();
        bool bImageLoad;
        bool bVideoLoad;

};
