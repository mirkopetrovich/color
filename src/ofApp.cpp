#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    kinect.setRegistration(true);
    kinect.init(false,false,true);
    kinect.open();
    if (kinect.isConnected()) {
        ofLogNotice() << "kinect: " << kinect.getWidth() << "x" << kinect.getHeight();
    }
    kinect.setCameraTiltAngle(-10); //25
    
    gui1.setup();
    gui1.add(minimo.set("min",45, 0, 255));
    gui1.add(maximo.set("max",180, 0, 255));
    gui1.add(cerca.set("umbral cerca",240, 50, 255)); //UMBRAL SALA
    gui1.add(lejos.set("umbral lejos",120, 0, 255));   //UMBRAL SALA
    gui1.add(mapx.set("paramX",0,0,55));
    gui1.add(mapy.set("paramY",0,0,55));
    gui1.add(saturation.set("saturation",0.4,0,2));
    gui1.add(value.set("value",1,0,2));
    gui1.add(grad.set("grad",0.001,0,0.1));
    
}

//--------------------------------------------------------------
void ofApp::update(){
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
}

//--------------------------------------------------------------
void ofApp::draw(){
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
    ofSetColor(255);
    gui1.draw();
    
    float hue ;
    int tam_matrix = 560;
    int step = tam_matrix/56;
    
    ofPushMatrix();
    
    ofTranslate(800,20);
    // step through horizontally
    
    for ( int i=0; i<tam_matrix; i+=step )
    {
        // step through vertically
        for ( int j=0; j<tam_matrix; j+=step )
        {
           
            int radio = 560/2;
            float p = i-radio;
            int q = j-radio;
            float r = sqrt(p*p+q*q);
            float rad = atan2(q,p);
            hue = ((rad + PI)/(1*PI))*180;
            float chroma = value*saturation*r*0.0125;
            float hue1 = hue/60;
           // float x = chroma*(1-abs((fmod(hue1,2))-1));
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
    ofNoFill();
    ofSetColor(255);
    
    ofDrawRectangle( floor((centroid1.x/640)*56)*10,floor((centroid1.y/480)*56)*10,10,10 );
    //ofDrawRectangle((centroid1.x/640)*10,(centroid1.y/480)*10,9,9);
    ofPopMatrix();
    ofDrawRectangle( centroid1,10,10 );
    
    //ofDrawRectangle(60,20,640,480);

    // now we will draw a larger rectangle taking the color under the mouse

    // calculate the color under the mouse, using the same calculations as when drawing the grid,
    // using mouseX and mouseY in place of i and j; draw a rectangle with this color. here we use
    // ofColor::fromHsb which allows us to set the HSB color in a single line of code.
   // ofColor color = ofColor::fromHsb(hue,
                            //         ofMap( mouseX, 0,ofGetWidth(), 0,255 ),
                             //        ofMap( mouseY, ofGetHeight(),0, 0,255 ) );
    //ofSetColor( color );
    //ofFill();
   // ofDrawRectangle( mouseX, mouseY, 100, 100 );
    

    // now draw a white border around the rectangle
    //ofNoFill();
   // ofSetHexColor(0xFFFFFF);
   // ofDrawRectangle( mouseX, mouseY, 100, 100 );
    ofFill();

    // finally we draw text over the rectangle giving the resulting HSB and RGB values
    // under the mouse
    ofSetHexColor(0xFFFFFF);
  /*  ofDrawBitmapString("HSB: "+ofToString(int(hue))+
                       " "+ofToString(int(color.getSaturation()))+
                       " "+ofToString(int(color.getBrightness())),
                       10, ofGetHeight()-13 );
    ofDrawBitmapString("RGB: "+ofToString(int(color.r))+
                       " "+ofToString(int(color.g))+
                       " "+ofToString(int(color.b)),
                       200, ofGetHeight()-13 );*/
    
    ofDrawBitmapString(ofToString(int(mouseX))+
                       " "+ofToString(int(mouseY)),133,ofGetHeight()-8
                       );
    ofDrawBitmapString(ofToString(int(centroid1.x))+
                       " "+ofToString(int(centroid1.y)),133,ofGetHeight()-20
                       );



    
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
