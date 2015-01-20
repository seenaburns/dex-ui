#include "ofApp.h"
#include "graphics-utils.h"

void ofApp::setup() {
  ofSetWindowTitle("DEX UI");
  ofBackground(0,0,0);

  ofSetFrameRate(60);

  layout = Layout();
  left = Left();
  left.setPos(165,165);
  left.setDelay(-50);

  right = Right();
  right.setPos(101*GRID_SIZE,165);
  right.setDelay(-50);

  term = Term();
  term.setPos(29*GRID_SIZE, 11*GRID_SIZE);

  keyboard.setPos(39*GRID_SIZE, 53*GRID_SIZE);
  keyboard.setDelay(-100);

  show_ref = false;
  show_scanner = false;
  show_bg = true;

  recording = false;
  record_counter = 0;

  drawing = true;
}

void ofApp::update() {
  if (recording) {
    ofSaveFrame();
    record_counter++;

    if (record_counter >= 60*5) {
      recording = false;
      record_counter = 0;
    }
  }
}

void ofApp::draw() {
//  ofGetCurrentRenderer()->setupScreenOrtho(ofGetWidth(), ofGetHeight(),-1000,1000);
  ofPushMatrix();
  {
    // translate for osx development (smaller windows)
    // use translate to keep all other coordinates accurate when untranslated
    ofTranslate(X_OFFSET, Y_OFFSET);

    if (show_bg)
      layout.drawBG();
    if (show_ref)
      layout.drawReferenceImage(150);
    layout.drawGrid(30);

    if (drawing) {
      left.draw();
      right.draw();
      term.draw();
      keyboard.draw();
    }
  }
  ofPopMatrix();

  if (show_scanner)
    layout.drawScannerlines();

  ofSetColor(255);
  ofPoint p = ofPoint(ofGetMouseX(), ofGetMouseY());
  //ofDrawBitmapString(ofToString(ofGetFrameRate()), 10,10);
//  ofDrawBitmapString(ofToString(p),10,10);
//  ofRect(p,2,2);
}

void ofApp::keyPressed(int key) {
  /*if (key == 'r')
    show_ref = !show_ref;
  if (key == 's')
    show_scanner = !show_scanner;
  if (key == 'b')
    show_bg = !show_bg;
  if (key == '.') {
    recording = !recording;
    cout << "recording: " << recording << endl;
  }
  */
  if (key == '=')
    drawing = !drawing;
}
void ofApp::keyReleased(int key) { }
void ofApp::mouseMoved(int x, int y ) { }
void ofApp::mouseDragged(int x, int y, int button) { }
void ofApp::mousePressed(int x, int y, int button) { }
void ofApp::mouseReleased(int x, int y, int button) { }
void ofApp::windowResized(int w, int h) { }
void ofApp::gotMessage(ofMessage msg) { }
void ofApp::dragEvent(ofDragInfo dragInfo) { }
