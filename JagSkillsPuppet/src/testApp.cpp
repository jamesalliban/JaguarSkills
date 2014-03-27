#include "testApp.h"

// TODO:
// - Smooth skeleton data.
// - - Fix gimbal lock on left arm/hand by flipping the mesh by 180 degrees.
// - - Fix head - Only use x rotation from skel data. Add some ambient y rotations.
// - - Fix hands - rotate them to face down when over the decks.
// - - Rotate torso when shoulders rotate. 
// - - Rotate legs when hips rotate. 
// - Add constraints to make sure limbs\head don't bend unnaturally.
// - Ensure hand rotation looks good (hands down over decks).
// - Add animated facial expressions - - cz, how are you getting on with these?
// - Add configurable camera angles.
// - Change background to green and remove the anti-aliasing - ready for greenscreen keying.


void testApp::setup()
{
    kinectManager.setup();
	jagSkillsApp.setup();
}

void testApp::update()
{
	// ofxKinectNui bollocks workaround
	kinectManager.jointPosOffset = jagSkillsApp.jointPosOffset;
	kinectManager.jointScale = jagSkillsApp.jointScale;
	kinectManager.skeletonRotDegrees = jagSkillsApp.skeletonRotDegrees;
	kinectManager.skeletonZReductionScale = jagSkillsApp.skeletonZReductionScale;
	kinectManager.skeletonSmoothing = jagSkillsApp.skeletonSmoothing;


	//if (ofGetFrameNum() == 10)
 //       kinectManager.kinectRecorder.startPlayback("images/rec/back_and_forth_4p_4k.png");

    if (!jagSkillsApp.isPaused) kinectManager.update();
    
    if (kinectManager.skeletons.size() > 0)
		jagSkillsApp.scene.update(kinectManager.smoothSkeletons[0]); //kinectManager.getActiveSkeleton());
}

void testApp::draw()
{
    ofBackground(40);
    kinectManager.draw();
    
    if (kinectManager.skeletons.size() > 0)
        jagSkillsApp.draw(kinectManager.smoothSkeletons[0]);
}

void testApp::keyPressed(int key)
{
    if (key == 'p')
    {
        jagSkillsApp.isPaused = !jagSkillsApp.isPaused;
    }
    else if (key == 'l')
    {
        kinectManager.kinectRecorder.startPlayback("images/rec/back_and_forth_4p_4k.png");
//        kinectRecorder.startPlayback("images/rec/back_and_for_2p_3k.png");
    }
    else if (key == 'f')
    {
        jagSkillsApp.isFullscreen = !jagSkillsApp.isFullscreen;
        ofSetFullscreen(jagSkillsApp.isFullscreen);
    }
    else if (key == 'r')
    {
        jagSkillsApp.scene.loadShader();
    }
}

void testApp::keyReleased(int key){

}

void testApp::mouseMoved(int x, int y){

}

void testApp::mouseDragged(int x, int y, int button){

}

void testApp::mousePressed(int x, int y, int button){

}

void testApp::mouseReleased(int x, int y, int button){
}

void testApp::windowResized(int w, int h){
}

void testApp::gotMessage(ofMessage msg){

}

void testApp::dragEvent(ofDragInfo dragInfo){

}


void testApp::exit()
{
	kinectManager.exit();
}