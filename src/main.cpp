#include "ofMain.h"
#include "ofApp.h"

int main( ){
  ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
  ofSetupOpenGL(1920,1200,OF_WINDOW);
  ofRunApp(new ofApp());
}
