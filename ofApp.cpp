#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
  
    
    image.load("tokyo1.JPG");
    image.resize(ofGetWidth() * 3/4, ofGetHeight() *3/4);
    
    
    image2.load("tokyo2.JPG");
    image2.resize(ofGetWidth() * 3/4, ofGetHeight() *3/4);
   // image2.rotate90(45);
    
    image3.load("tokyo3.JPG");
    image3.resize(ofGetWidth() * 3/4, ofGetHeight() *3/4);
   // image3.rotate90(45);
    
    image4.load("tokyo4.JPG");
    image4.resize(ofGetWidth() * 3/4, ofGetHeight() *3/4);
    
    image5.load("tokyo5.JPG");
    image5.resize(ofGetWidth() * 3/4, ofGetHeight() *3/4);
    
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofHideCursor();
    
    gui.setup();
    gui.add(ampX.setup("ampX", 0, 0, 1000));
    gui.add(ampY.setup("ampY", 0, 0, 1000));
    gui.add(ampZ.setup("ampZ", 0, 0, 1000));
    gui.add(spx.setup("speedX", 0.003, 0.0, 0.1));
    gui.add(spy.setup("speedY", 0.003, 0.0, 0.1));
    gui.add(spz.setup("speedZ", 0.003 , 0.0, 0.1));
    
    gui.add(pointSize.setup("point size", 0.6, 0, 25));
    gui.add(frecSize.setup("frequency size", 0.22, 0.001, 3));
    gui.add(slipSize.setup("slip size", PI, 0, PI * 2));
    gui.add(points.setup("points", true));
    gui.add(lines.setup("lines", false));
   
    light.setup();
    //light.setSpotlight();
    //light.setDirectional();
    light.setPosition(400, 0, 500);
    light.setAmbientColor(ofFloatColor(0.2, 0.2, 0.70));
    light.setDiffuseColor(ofFloatColor(0.5, 0.3, 1.0));
    light.setSpecularColor(ofFloatColor(0.0, 0.5, 1.0));
    light.setAreaLight(3000, 3000);
    light.setPointLight();
    
    material.setShininess(10);
    //material.setEmissiveColor(ofFloatColor(1.0, 0.0, 1.0));
    //material.setAmbientColor(ofFloatColor(1.0, 0.5 , 0.5));
    //material.setDiffuseColor(ofFloatColor(0.1, 0.5, 0.3));
   
    
    //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    //ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
}

//--------------------------------------------------------------
void ofApp::update(){
    //light.setPosition(lx, ly, lz);
    
    if (autoChanger == true) {
        switch (int(ofGetElapsedTimef()) % 10) {
            case 0:
                mode1 = true;
                mode2 = false;
                mode3 = false;
                mode4 = false;
                mode5 = false;
                break;
            
            case 2:
                mode1 = false;
                mode2 = true;
                mode3 = false;
                mode4 = false;
                mode5 = false;
                break;
            
            case 4:
                mode1 = false;
                mode2 = false;
                mode3 = true;
                mode4 = false;
                mode5 = false;
                break;
                
            case 6:
                mode1 = false;
                mode2 = false;
                mode3 = false;
                mode4 = true;
                mode5 = false;
                break;
                
            case 8:
                mode1 = false;
                mode2 = false;
                mode3 = false;
                mode4 = false;
                mode5 = true;
                break;
            
            default:
                break;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushView();
    cam.begin();
    light.enable();
    int f = ofGetFrameNum();
    
    int w = image.getWidth();
    int h = image.getHeight();
    ofRotateXDeg(f * 0.08);
    ofRotateYDeg(f * 0.085);
    glPointSize(pointSize);
    
 
 //   mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    mesh2.setMode(OF_PRIMITIVE_LINE_STRIP);
    // mesh.setMode(OF_PRIMITIVE_POINTS);
    // mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for (int x=0; x<w; x+=3) {
        for (int y=0 ; y<h; y+=3) {
            int br;
            ofColor col;
            if (mode1 == true) {
                col = image.getColor(x, y);
                br = col.getBrightness();
            }else if (mode2 == true){
                col = image2.getColor(x, y);
                br = col.getBrightness();
            }else if (mode3 == true){
                col = image3.getColor(x, y);
                br = col.getBrightness();
            }else if (mode4 == true){
                col = image4.getColor(x, y);
                br = col.getBrightness();
            }else if (mode5 == true){
                col = image5.getColor(x, y);
                br = col.getBrightness();
            }
            float calcSlip = ofMap(br, 0, 255, 0, slipSize);
            float calcFrec = ofMap(br, 0, 255, 0.001, frecSize);
            
            
            float flacX = ampX * sin(pow(cos(f * PI/100*calcFrec - calcSlip + f *spx), 5));
            float flacY = ampY * cos(2 * sin(sin(f * 0.01)) * cos(f * PI/100*calcFrec - calcSlip + f *spy));
            float z = ampZ * sin(sin(f * PI/100*calcFrec  - calcSlip + f *spz));
            mesh.addColor(col);
            mesh2.addColor(col);
           /*
            float fcolr = ofNormalize(col.r, 0, 255);
            float fcolg = ofNormalize(col.g, 0, 255);
            float fcolb = ofNormalize(col.b, 0, 255);
            ofFloatColor fcol = (fcolr, fcolg, fcolb);
            material.setDiffuseColor(col);
            material.setAmbientColor(col);
        
            
            //material.setEmissiveColor(fcol);
            material.setSpecularColor(col);
           */
            if (points == true) {
                mesh.addVertex(ofPoint(x + flacX -image.getWidth()/2, -y + flacY + image.getHeight()/2, z));
            }
            
            if (lines) {
                mesh2.addVertex(ofPoint(x + flacX -image.getWidth()/2, -y + flacY + image.getHeight()/2, z));
            }
            
            
            
        }
    }
    //material.begin();
    
    mesh.draw();
    mesh2.draw();
    mesh.clear();
    mesh2.clear();
    
    //material.end();
    
    ofPopView();
    
    light.disable();
    cam.end();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    if (panel == true) {
        ofPushView();
        ofPushMatrix();
        gui.draw();
        //ofShowCursor();
        ofDrawBitmapString( "Elapsed time: " + ofToString(ofGetElapsedTimef()) + "sec", ofGetWidth() -300, 100);
        ofDrawBitmapString( "Frame rate: " + ofToString(ofGetFrameRate()), ofGetWidth() -300, 130);
        if (mode1 == true) {
            ofDrawBitmapString( "sunset.jpg", ofGetWidth() -300, 160);
            image.draw(ofGetWidth() - 300, 180, 120, 75);
        }else if (mode2 == true){
            ofDrawBitmapString( "construction.jpg", ofGetWidth() -300, 160);
            image2.draw(ofGetWidth() - 300, 180, 120, 75);
        }else if (mode3 == true){
            ofDrawBitmapString( "rainy.jpg" , ofGetWidth() -300, 160);
            image3.draw(ofGetWidth() - 300, 180, 120, 75);
        }else if (mode4 == true){
            ofDrawBitmapString( "railway.jpg" , ofGetWidth() -300, 160);
            image4.draw(ofGetWidth() - 300, 180, 120, 75);
        }else if (mode5 == true){
            ofDrawBitmapString( "night.jpg" , ofGetWidth() -300, 160);
            image5.draw(ofGetWidth() - 300, 180, 120, 75);
        }
        ofPopMatrix();
        ofPopView();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_RETURN:
            autoChanger = !autoChanger;
            
            break;
            
        case OF_KEY_BACKSPACE:
            autoChanger = false;
            break;
        case ' ':
            panel = !panel;
            if (panel) {
                ofShowCursor();
            }else{
                ofHideCursor();
            }
            break;
        
        case '1':
            mode1 = true;
            mode2 = false;
            mode3 = false;
            mode4 = false;
            mode5 = false;
            break;
        
        case '2':
            mode1 = false;
            mode2 = true;
            mode3 = false;
            mode4 = false;
            mode5 = false;
            break;
        
        case '3':
            mode1 = false;
            mode2 = false;
            mode3 = true;
            mode4 = false;
            mode5 = false;
            break;
            
        case '4':
            mode1 = false;
            mode2 = false;
            mode3 = false;
            mode4 = true;
            mode5 = false;
            break;
            
        case '5':
            mode1 = false;
            mode2 = false;
            mode3 = false;
            mode4 = false;
            mode5 = true;
            break;
            
            
        default:
            break;
    }

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
