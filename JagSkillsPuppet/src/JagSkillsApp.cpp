
#include "JagSkillsApp.h"

void JagSkillsApp::setup()
{
	frameRate = 30;
    ofSetFrameRate(frameRate);

	ofSetLogLevel(OF_LOG_VERBOSE);

	//ofEnableArbTex();
    ofDisableArbTex();
    ofSetWindowPosition(10, 10);
    ofSetWindowShape(1600, 1000);
    
    scene.setup();
    
	jointPosOffset = ofVec3f(0, 0, 0);

	gui.app = (JagSkillsApp*)this;
    gui.setup();
    
	isPaused = false;
}

void JagSkillsApp::update()
{
    ofSetFullscreen(isFullscreen);
    
    scene.setMouseCamEnabled(gui.isMouseOver());
    ofSetFrameRate(frameRate); 
}

void JagSkillsApp::draw(SkeletonDataObject skeleton)
{
	ofBackground(40);
    
    scene.draw(skeleton);
}