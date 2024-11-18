#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    tam_matrix = 560;
    step = tam_matrix/56;
    
#ifdef KINECT
    kinect.setRegistration(true);
    kinect.init(false,false,true);
    kinect.open();
    if (kinect.isConnected()) {
        ofLogNotice() << "kinect: " << kinect.getWidth() << "x" << kinect.getHeight();
    }
    kinect.setCameraTiltAngle(-10); //25
#endif
    
    gui1.setup();
    gui1.add(minimo.set("min",45, 0, 255));
    gui1.add(maximo.set("max",180, 0, 255));
    gui1.add(cerca.set("umbral cerca",240, 50, 255)); //UMBRAL SALA
    gui1.add(lejos.set("umbral lejos",120, 0, 255));   //UMBRAL SALA
    gui1.add(mapx.set("paramX",0,0,55));
    gui1.add(mapy.set("paramY",0,0,55));
    gui1.add(saturation.set("saturation",0.1,0,2));
    gui1.add(value.set("value",1,0,2));
    gui1.add(grad.set("grad",0.001,0,0.1));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
#ifdef KINECT

    kinect.update();
    if (kinect.isFrameNew()) {
        grayImage.setFromPixels(kinect.getDepthPixels());
        grayImage.mirror(0,1);
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(cerca, true);
        grayThreshFar.threshold(lejos);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        grayImage.dilate();
        grayImage.dilate();
        grayImage.dilate();
        contourFinder.setMinAreaRadius(minimo);
        contourFinder.setMaxAreaRadius(maximo);
        contourFinder.setThreshold(0);
        contourFinder.findContours(grayImage);
        contourFinder.setFindHoles(false);
        contourFinder.setSimplify(false);
        
        //players = contourFinder.size();
    }
#endif
}

//--------------------------------------------------------------
void ofApp::draw(){
    
#ifdef KINECT
    int n = contourFinder.size();

if (n) {
    centroid1 = toOf(contourFinder.getCentroid(0));
    
}
    

    ofPushMatrix();
    ofTranslate(20, 20);
    grayImage.draw(0,0,640,480);
    ofSetColor(255,0,255);
    contourFinder.draw();
    ofSetColor(0,255,255);
    ofDrawCircle(centroid1,10);
    ofPopMatrix();
    
#endif
    ofSetColor(255);
    gui1.draw();
    
    
    if (true) {
        saturation_old =saturation;
        ofPushMatrix();
        ofTranslate(800,20);
        rosa();
        ofPopMatrix();
    }
    
    
    ofNoFill();
    ofSetColor(255);
    
    
#ifdef KINECT
    ofDrawRectangle( floor((centroid1.x/640)*56)*10,floor((centroid1.y/480)*56)*10,10,10 );
    //ofDrawRectangle((centroid1.x/640)*10,(centroid1.y/480)*10,9,9);
    ofPopMatrix();
    ofDrawRectangle( centroid1,10,10 );
    
#endif
    
    ofFill();
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString(ofToString(int(mouseX))+
                       " "+ofToString(int(mouseY)),133,ofGetHeight()-8
                       );
    ofDrawBitmapString(ofToString(int(centroid1.x))+
                       " "+ofToString(int(centroid1.y)),133,ofGetHeight()-20
                       );



    
}

void ofApp::rosa(){
    for ( int i=0; i<tam_matrix; i+=step )
    {
        for ( int j=0; j<tam_matrix; j+=step )
        {
           
            int radio = tam_matrix/2;
            float p = i-radio;
            int q = j-radio;
            float r = sqrt(p*p+q*q);
            float rad = atan2(q,p);
            hue = ((rad + PI)/(1*PI))*180;
            float chroma = value*saturation*(sqrt(r));
            float hue1 = hue/60;
            float x = chroma*(1-abs(fmod(hue1,2)-1));
            float m =  value-chroma;
            if (hue1>0 && hue1    <=1) ofSetColor((chroma+m)*255,(x+m)*255,m*255);
            else
                if (hue1>1 && hue1  <=2) ofSetColor((x+m)*255,(chroma+m)*255,m*255);
                else
                    if (hue1>2 && hue1  <=3) ofSetColor(m*255,(chroma+m)*255,(x+m)*255);
                    else
                        if (hue1>3 && hue1  <=4) ofSetColor(m*255,(x+m)*255,(chroma+m)*255);
                        else
                            if (hue1>4 && hue1  <=5) ofSetColor((x+m)*255,m*255,(chroma+m)*255);
                            else
                                if (hue1>5 && hue1  <=6) ofSetColor((chroma+m)*255,m*255,(x+m)*255);
            
            
            
            
            
            else ofSetColor(0,0,0);
            
            ofDrawRectangle( i, j, step-1, step-1 );
            ofSetColor(255);
            //ofDrawBitmapString(ofToString(x*255),i,j);
                               

        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}


