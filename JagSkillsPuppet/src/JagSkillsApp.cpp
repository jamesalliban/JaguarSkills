
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

	
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		// check for mouse moved message
		if (m.getAddress() == "/camera_position/1")
			scene.setCamerangle(1);
		else if (m.getAddress() == "/camera_position/2")
			scene.setCamerangle(2);
		else if (m.getAddress() == "/camera_position/3")
			scene.setCamerangle(3);
		else if (m.getAddress() == "/camera_position/4")
			scene.setCamerangle(4);
		else if (m.getAddress() == "/camera_position/5")
			scene.setCamerangle(5);
	}
}

void JagSkillsApp::draw(vector<SkeletonDataObject> skeletons)
{
	ofBackground(backgroundR, backgroundG, backgroundB);
    
    scene.draw(skeletons);
}