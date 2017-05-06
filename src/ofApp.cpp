#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // initial setting
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // gui setting
    gui.setup();
    gui.add(scale.setup("scale", 80, 0, 200));
    gui.add(normalMode.setup("NormalMode", 0, 0, 1));
    gui.add(Draw.setup("draw()", true));
    gui.add(Wireframe.setup("drawWireframe()", false));
    gui.add(Faces.setup("drawFaces()", false));
    gui.add(Vertices.setup("drawVertices()", false));
    gui.add(vColor.setup("vColor", ofFloatColor(1.0, 1.0, 1.0, 0.3), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    
    // shader setting
    shader.setGeometryInputType(GL_TRIANGLES);
    shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    shader.setGeometryOutputCount(6);
    shader.load("shaders/shader.vert", "shaders/shader.frag", "shaders/shader.geom");
    
    vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    // load image
    img.load("texture0.png");
    
    // camera setting
    cam.setNearClip(0);
    cam.setFarClip(1500);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor(12, 15, 85), ofColor(0));
    cam.begin();
    
    // model Matrix
    ofMatrix4x4 modelMatrix;
    modelMatrix.translate(0, 0, 0);
    modelMatrix.rotate(time*10, 1.0, 0.5, 0.0);
    sphere.setPosition(ofVec3f(0, 0, 0));
    sphere.set(256, 32);
    sphere.mapTexCoordsFromTexture(img.getTexture());
    
    // view Matrix
    ofMatrix4x4 viewMatrix;
    viewMatrix = ofGetCurrentViewMatrix();
    
    // projection Matrix
    ofMatrix4x4 projectionMatrix;
    projectionMatrix = cam.getProjectionMatrix();
    
    // mvp Matrix
    ofMatrix4x4 mvpMatrix;
    mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
    
    shader.begin();
    shader.setUniformMatrix4f("model", modelMatrix);
    shader.setUniformMatrix4f("view", viewMatrix);
    shader.setUniformMatrix4f("projection", projectionMatrix);
    shader.setUniformMatrix4f("mvp", mvpMatrix);
    shader.setUniform1i("scale", scale);
    shader.setUniform1i("NormalMode", normalMode);
    shader.setUniformTexture("tex0", img.getTexture(), 0);
    
    vboMesh = sphere.getMesh();
    for(int i=0; i<vboMesh.getVertices().size(); i++){
        vboMesh.addColor(vColor);
    }
    if(Draw){
        vboMesh.draw();
    } else if(Wireframe){
        vboMesh.drawWireframe();
    } else if(Faces){
        vboMesh.drawFaces();
    } else if(Vertices){
        vboMesh.drawVertices();
    }
    
    shader.end();
    
    cam.end();
    
    ofDisableDepthTest();
    gui.draw();
    ofEnableDepthTest();
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
