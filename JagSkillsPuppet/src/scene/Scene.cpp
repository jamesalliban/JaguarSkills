//
//  Scene.cpp
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#include "Scene.h"

void Scene::setup()
{
    easyCam.setNearClip(0);
    easyCam.setFarClip(2000);
    easyCam.setDistance(250);
    easyCam.setPosition(0, 40, 200);

	for (int i = 0; i < 5; i++)
	{
		camPositions.push_back(ofVec3f(0,0,0));
		camTartetsPositions.push_back(ofVec3f(0,0,0));
	}
    light.setPosition(-200, 200, 200);
    
    loadShader();
    
    chestImg.loadImage("models/texturesv1/chest_blackmask_diff.tif");
    headarmsImg.loadImage("models/texturesv1/headarms_blackmask2_diff.tif");
    pantsImg.loadImage("models/texturesv1/pants_diff_black.tif");
    
    chestBumpImg.loadImage("models/texturesv1/chest_norm_combined_contrast.tif");
    headarmsBumpImg.loadImage("models/texturesv1/headarms_norm.tif");
    pantsBumpImg.loadImage("models/texturesv1/pants_norm.tif");

	
    legs.setup("models/pants_separate.obj", &pantsImg.getTextureReference(), &pantsBumpImg.getTextureReference(), &shader);
	abdomen.setup("models/belly_separate.obj", &pantsImg.getTextureReference(), &pantsBumpImg.getTextureReference(), &shader);

    torso.setup("models/chest_separate.obj", &chestImg.getTextureReference(), &chestBumpImg.getTextureReference(), &shader);
    //head.setup("models/head.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);
    //head.setup("models/headweyes.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);
    head.setup("models/headweyes_longcape.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);

    //head.setup("models/animheadtest.dae", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);

    upperArmL.setup("models/Rupperarm.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);
    upperArmR.setup("models/Lupperarm.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);
    forearmL.setup("models/Rlowerarm.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);
    forearmR.setup("models/Llowerarm.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);
    handL.setup("models/Rhand.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);
    handR.setup("models/Lhand.obj", &headarmsImg.getTextureReference(), &headarmsBumpImg.getTextureReference(), &shader);


    decks.loadModel("models/DJ_Deck.obj", true);
	decksImg.loadImage("models/texturesv1/DJ_Deck_d.tga");
	
    mixer.loadModel("models/DJ MIxer.obj", true);
}



void Scene::update(vector<SkeletonDataObject> skeletons)
{
	setCameraProps();
	
	decks.setScale(decksScale.x, decksScale.y, decksScale.z);
    decks.setRotation(0, decksRot.x, 1, 0, 0);
	decks.setRotation(1, decksRot.y, 0, 1, 0);
	decks.setRotation(2, decksRot.z, 0, 0, 1);
	
 	mixer.setScale(mixerScale.x, mixerScale.y, mixerScale.z);
    mixer.setRotation(0, mixerRot.x, 1, 0, 0);
	mixer.setRotation(1, mixerRot.y, 0, 1, 0);
	mixer.setRotation(2, mixerRot.z, 0, 0, 1);


    viewport = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
	light.setPosition(lightPosition.x, lightPosition.y, lightPosition.z);
	
	if (skeletons.size() > 0)
	{
		// calculate the target positions for abdomen and legs as they are special cases
		ofVec3f legTarget = ofVec3f(skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE].x,
									skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE].y - 100,
									skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE].z);

		legs.update(skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE], legTarget);
		abdomen.update(skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE], skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_CENTRE].getInterpolated(skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE], 0.5));
    
		torso.calculateShoulderRotation(skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_LEFT], skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_RIGHT]);
		torso.update(skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE], skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_CENTRE]);

		ofVec3f headTarget = ofVec3f(skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_CENTRE].x,
			skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_CENTRE].y + 20,
			skeletons[0].skeletonPositions[KINECT_SDK_HEAD].z);
		head.update(skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_CENTRE], skeletons[0].skeletonPositions[KINECT_SDK_HEAD]);

    
		upperArmL.update(skeletons[0].skeletonPositions[KINECT_SDK_ELBOW_LEFT], skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_LEFT]); // target and pos swapped for left arm/hand to fix gimbal lock issue
		upperArmR.update(skeletons[0].skeletonPositions[KINECT_SDK_SHOULDER_RIGHT], skeletons[0].skeletonPositions[KINECT_SDK_ELBOW_RIGHT]);
    
		forearmL.update(skeletons[0].skeletonPositions[KINECT_SDK_WRIST_LEFT], skeletons[0].skeletonPositions[KINECT_SDK_ELBOW_LEFT]); // target and pos swapped for left arm/hand to fix gimbal lock issue
		forearmR.update(skeletons[0].skeletonPositions[KINECT_SDK_ELBOW_RIGHT], skeletons[0].skeletonPositions[KINECT_SDK_WRIST_RIGHT]);
    
		handL.update(skeletons[0].skeletonPositions[KINECT_SDK_WRIST_LEFT], skeletons[0].skeletonPositions[KINECT_SDK_ELBOW_LEFT]); // target and pos swapped for left arm/hand to fix gimbal lock issue
		handR.update(skeletons[0].skeletonPositions[KINECT_SDK_ELBOW_RIGHT], skeletons[0].skeletonPositions[KINECT_SDK_WRIST_RIGHT]);
	}
}



void Scene::draw(vector<SkeletonDataObject> skeletons)
{
	ofEnableAlphaBlending();
    glEnable(GL_DEPTH_TEST);

	if (isMouseCam)
		easyCam.begin(viewport);
	else
		cam.begin(viewport);

	if (isGridVisible)
	{
		ofSetColor(255, 100);
		ofPushMatrix();
		ofRotateZ(90);
		ofDrawGridPlane(400);
		ofPopMatrix();
	}

    ofEnableLighting();
    light.enable();
    
	//printf("skeletons.size() = %i \n", skeletons.size());
	
	if (skeletons.size() > 0)
	{
		ofSetColor(255, modelAlpha);


		ofVec3f legOrigin = ofVec3f(skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE].x, 0, skeletons[0].skeletonPositions[KINECT_SDK_HIP_CENTRE].z);
		// set origins for head and torso to shoulder centre
		legs.originPoint = &legOrigin;
		abdomen.originPoint = &legs.connectingPointsAbsolute[0];
		torso.originPoint = &abdomen.connectingPointsAbsolute[0];
		head.originPoint = &torso.connectingPointsAbsolute[2];
		upperArmL.originPoint = &torso.connectingPointsAbsolute[0];
		upperArmR.originPoint = &torso.connectingPointsAbsolute[1];
		forearmL.originPoint = &upperArmL.connectingPointsAbsolute[0];
		forearmR.originPoint = &upperArmR.connectingPointsAbsolute[0];
		handL.originPoint = &forearmL.connectingPointsAbsolute[0];
		handR.originPoint = &forearmR.connectingPointsAbsolute[0];


		if (BodyPart::isDrawModel)
		{
			if (isDrawFaces)
			{
				torso.drawFaces();
				head.drawFaces();
				abdomen.drawFaces();
				legs.drawFaces();
				upperArmL.drawFaces();
				upperArmR.drawFaces();
				forearmL.drawFaces();
				forearmR.drawFaces();
				handL.drawFaces();
				handR.drawFaces();

				//mixer.drawFaces();
			}
			else
			{
				torso.drawWireframe();
				head.drawWireframe();
				abdomen.drawWireframe();
				legs.drawWireframe();
				upperArmL.drawWireframe();
				upperArmR.drawWireframe();
				forearmL.drawWireframe();
				forearmR.drawWireframe();
				handL.drawWireframe();
				handR.drawWireframe();
			}
		}
    
		if (BodyPart::isDrawDebug)
		{
			torso.drawDebug(ofColor(255, 0, 255));
			head.drawDebug(ofColor(255, 255, 0));
			abdomen.drawDebug(ofColor(255, 255, 0));
			legs.drawDebug(ofColor(255, 255, 0));
			upperArmL.drawDebug(ofColor(255, 255, 0));
			upperArmR.drawDebug(ofColor(255, 255, 0));
			forearmL.drawDebug(ofColor(255, 255, 0));
			forearmR.drawDebug(ofColor(255, 255, 0));
			handL.drawDebug(ofColor(255, 255, 0));
			handR.drawDebug(ofColor(255, 255, 0));
		}

		
		if (isEquipmentVisible)
		{
			ofSetColor(255, 255);
			ofPushMatrix();
			ofTranslate(decks1Pos.x, decks1Pos.y, decks1Pos.z);
			decksImg.getTextureReference().bind();
			decks.drawFaces();
			decksImg.getTextureReference().unbind();
			ofPopMatrix();
			
			ofPushMatrix();
			ofTranslate(decks2Pos.x, decks2Pos.y, decks2Pos.z);
			decksImg.getTextureReference().bind();
			decks.drawFaces();
			decksImg.getTextureReference().unbind();
			ofPopMatrix();
			
			ofPushMatrix();
			ofTranslate(mixerPos.x, mixerPos.y, mixerPos.z);
			ofSetColor(100, 255);
			mixer.drawFaces();
			ofPopMatrix();
		}

		if (isDebugSkeletonVIsible)
		{
			ofPushMatrix();
			ofTranslate(80, 0);
			drawLineSkeleton(skeletons[0]);
			ofPopMatrix();
		}
	}


    light.disable();
    ofDisableLighting();
    
	if (isMouseCam)
		easyCam.end();
	else
		cam.end();
    
	glDisable(GL_DEPTH_TEST);
	
	ofDisableAlphaBlending();
}



void Scene::drawLineSkeleton(SkeletonDataObject skeleton)
{
    ofSetColor(255, 255);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_HEAD], skeleton.skeletonPositions[KINECT_SDK_SHOULDER_CENTRE]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_SHOULDER_CENTRE], skeleton.skeletonPositions[KINECT_SDK_SHOULDER_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_SHOULDER_CENTRE], skeleton.skeletonPositions[KINECT_SDK_SHOULDER_RIGHT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_SHOULDER_LEFT], skeleton.skeletonPositions[KINECT_SDK_ELBOW_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_SHOULDER_RIGHT], skeleton.skeletonPositions[KINECT_SDK_ELBOW_RIGHT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_ELBOW_LEFT], skeleton.skeletonPositions[KINECT_SDK_WRIST_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_ELBOW_RIGHT], skeleton.skeletonPositions[KINECT_SDK_WRIST_RIGHT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_WRIST_LEFT], skeleton.skeletonPositions[KINECT_SDK_HAND_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_WRIST_RIGHT], skeleton.skeletonPositions[KINECT_SDK_HAND_RIGHT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_SHOULDER_CENTRE], skeleton.skeletonPositions[KINECT_SDK_HIP_CENTRE]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_HIP_CENTRE], skeleton.skeletonPositions[KINECT_SDK_HIP_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_HIP_CENTRE], skeleton.skeletonPositions[KINECT_SDK_HIP_RIGHT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_HIP_LEFT], skeleton.skeletonPositions[KINECT_SDK_KNEE_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_HIP_RIGHT], skeleton.skeletonPositions[KINECT_SDK_KNEE_RIGHT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_KNEE_LEFT], skeleton.skeletonPositions[KINECT_SDK_ANKLE_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_KNEE_RIGHT], skeleton.skeletonPositions[KINECT_SDK_ANKLE_RIGHT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_ANKLE_LEFT], skeleton.skeletonPositions[KINECT_SDK_FOOT_LEFT]);
    ofLine(skeleton.skeletonPositions[KINECT_SDK_ANKLE_RIGHT], skeleton.skeletonPositions[KINECT_SDK_FOOT_RIGHT]);
    
    for (int i = 0; i < skeleton.skeletonPositions.size(); i++)
    {
        ofVec3f skelPoint = skeleton.skeletonPositions[i];
        ofSetColor(255, 0, 0);
#ifdef TARGET_OSX
        ofDrawSphere(skelPoint.x, skelPoint.y, skelPoint.z, 1);
#else
		ofSphere(skelPoint.x, skelPoint.y, skelPoint.z, 1);
#endif
    }
}


void Scene::setMouseCamEnabled(bool isGUIMouseOver)
{
    if (isMouseCam)
    {
        if (isGUIMouseOver)
            easyCam.disableMouseInput();
        else
            easyCam.enableMouseInput();
    }
}


void Scene::loadShader()
{
    shader.load("shader/PhongShader");
}


void Scene::setCameraProps()
{
	if (isMouseCam)
        easyCam.enableMouseInput();
	else
		easyCam.disableMouseInput();

	cam.setPosition(camPositions[currentCameraIndex]);
	cam.lookAt(camTartetsPositions[currentCameraIndex]);

}


void Scene::setCamerangle(int camIndex)
{
	currentCameraIndex =camIndex;
}