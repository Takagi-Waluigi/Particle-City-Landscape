#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofImage image;
    ofImage image2;
    ofImage image3;
    ofImage image4;
    ofImage image5;
    
    ofEasyCam cam;
    ofMesh mesh;
    ofMesh mesh2;
    ofxPanel gui;    
    
    ofFbo fbo;
    
   
    
    int begintime = 0;
    
    ofxIntSlider ampX;
    ofxIntSlider ampY;
    ofxIntSlider ampZ;
    ofxFloatSlider frecSize;
    ofxFloatSlider slipSize;
    ofxFloatSlider pointSize;
    
    ofxFloatSlider spx;
    ofxFloatSlider spy;
    ofxFloatSlider spz;
    
    ofxToggle points;
    ofxToggle lines;
    ofLight light;
    ofMaterial material;
    
    
    bool panel;   

    bool mode1 = true;
    bool mode2;
    bool mode3;
    bool mode4;
    bool mode5;
    
    bool meshMode1  = true;
    bool meshMode2;
    
    bool autoChanger = true;
    
    
    //std::vector<ofImage> img(3);
		
};
