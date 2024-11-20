#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxOsc.h"


#define HOST "localhost"
#define PORT 6666
//#define KINECT

class ofApp : public ofBaseApp{

    public:
        void setup() override;
        void update() override;
        void draw() override;
        void exit() override;

        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void mouseMoved(int x, int y ) override;
        void mouseDragged(int x, int y, int button) override;
        void mousePressed(int x, int y, int button) override;
        void mouseReleased(int x, int y, int button) override;
        void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
        void mouseEntered(int x, int y) override;
        void mouseExited(int x, int y) override;
        void windowResized(int w, int h) override;
        void dragEvent(ofDragInfo dragInfo) override;
        void gotMessage(ofMessage msg) override;
        
    void rosa();
    glm::vec3 rgb(int i, int j);
    
    ofxKinect kinect;
    ofxCvGrayscaleImage mirror;
    ofxCvGrayscaleImage grayImage;        // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear;   // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar;    // the far thresholded image

    ofxCv::ContourFinder contourFinder;
    ofVec2f centroid1,centroid2,centroid3;
    ofParameter<int> minimo,maximo,cerca, lejos;
    ofxPanel gui1;
    ofParameter<int> mapx,mapy;
    ofParameter<float> saturation, value, grad;
    float hue, hue_grilla;
    int tam_matrix, step, radio;
    float saturation_old;
        
    ofxOscSender sender;
    
    glm::vec3 col;
};

