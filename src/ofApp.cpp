#include "ofApp.h"
#include "graphics-utils.h"

void ofApp::setup() {
  ofSetWindowTitle("DEX UI");
  ofBackground(COLOR_15);

  ofSetFrameRate(60);

  layout = Layout();
  
  // Position components, set delays for animation
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

  // Other
  // isDrawing controls components, essentially play/pause
  isDrawing = true;

  // recording variables to handle saving animation frame by frame
  isRecording = false;
  recordFrameCounter = 0;
  recordMaxFrames = 1; //60*5;

}

void ofApp::update() {
  if (isRecording) {
    ofSaveFrame();
    recordFrameCounter++;

    if (recordFrameCounter >= recordMaxFrames) {
      isRecording = false;
      recordFrameCounter = 0;
    }
  }
}

void ofApp::draw() {
  ofPushMatrix();
  {
    // translate for osx development (smaller windows)
    // use translate to keep all other coordinates accurate when untranslated
    // note: some elements don't work with translate because they are positioned
    // with ofEasyCamera to deal with perspective differences
    ofTranslate(X_OFFSET, Y_OFFSET);

    layout.drawBG();
    layout.drawGrid(30);

    // Draw and update components
    if (isDrawing) {
      left.draw();
      right.draw();
      term.draw();
      keyboard.draw();
    }
  }
  ofPopMatrix();

  // Framerate
  ofSetColor(255);
  ofDrawBitmapString(ofToString(ofGetFrameRate()), 10,10);
}

void ofApp::keyPressed(int key) {
  if (key == '.') {
    isRecording = !isRecording;
    cout << "recording: " << isRecording << endl;
  }
  
  if (key == '=')
    isDrawing = !isDrawing;
}

void ofApp::keyReleased(int key) { }
void ofApp::mouseMoved(int x, int y ) { }
void ofApp::mouseDragged(int x, int y, int button) { }
void ofApp::mousePressed(int x, int y, int button) { }
void ofApp::mouseReleased(int x, int y, int button) { }
void ofApp::windowResized(int w, int h) { }
void ofApp::gotMessage(ofMessage msg) { }
void ofApp::dragEvent(ofDragInfo dragInfo) { }
