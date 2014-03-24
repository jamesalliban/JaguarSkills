//
//  GUI.cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "GUI.h"
#include "Scene.h"
#include "testApp.h"


void GUI::setup(string _guiPath)
{
    app = (testApp*)ofGetAppPtr();
    GUIManager::setup(_guiPath);
    
    addKeyGUI();
    addAppGUI();
    addSceneGUI();
    addSkeletonGUI();
    addModelGlobalGUI();
    addModelTorsoGUI();
    addModelHeadGUI();
    addModelAbdomenAndLegsGUI();
    addModelArmsLGUI();
    addModelArmsRGUI();
    addModelHandsGUI();
    addShadingGUI();
    addBackgroundGUI();
    addGUIDesignGUI();
    
    setGUIColour();
}



void GUI::addKeyGUI()
{
    string title = "KEYS";
    ofxUICanvas* gui = getNewGUI(title);
    gui->addLabel("KEY", OFX_UI_FONT_MEDIUM);
    gui->addLabel("SPACE - SHOW/HIDE GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("'[' - PREVIOUS GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("']' - NEXT GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("'p' - PAUSE SCENE", OFX_UI_FONT_SMALL);
    gui->addLabel("'f' - TOGGLE FULLSCREEN", OFX_UI_FONT_SMALL);
    gui->addLabel("'l' - LOAD SHADER", OFX_UI_FONT_SMALL);
    gui->addSpacer(length, 1);
    gui->addLabel("DRAG TO ROTATE CAMERA", OFX_UI_FONT_SMALL);
    gui->addLabel("HOLD 'm' AND DRAG TO MOVE CAMERA", OFX_UI_FONT_SMALL);
    
    finaliseCanvas(gui);
}


void GUI::addAppGUI()
{
    string title = "APP SETTINGS";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addSlider("FRAME RATE", 1, 60, &app->frameRate, length, dim);
    gui->addToggle("FULLSCREEN", &app->isFullscreen, toggleSize, toggleSize);
    
    finaliseCanvas(gui);
}


void GUI::addSceneGUI()
{
    string title = "SCENE";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("CAMERA");
    gui->addToggle("MOUSE CONTROLS CAMERA", &app->scene.isMouseCam, toggleSize, toggleSize);
    gui->addSpacer(length, 1);
    gui->addSlider("CAMERA POS X", -300, 300, &app->scene.cameraPosition.x, length, dim);
    gui->addSlider("CAMERA POS Y", -300, 300, &app->scene.cameraPosition.y, length, dim);
    gui->addSlider("CAMERA POS Z", -500, 500, &app->scene.cameraPosition.z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("CAMERA TARGET POS X", -300, 300, &app->scene.cameraTargetPosition.x, length, dim);
    gui->addSlider("CAMERA TARGET POS Y", -300, 300, &app->scene.cameraTargetPosition.y, length, dim);
    gui->addSlider("CAMERA TARGET POS Z", -500, 500, &app->scene.cameraTargetPosition.z, length, dim);
    gui->addSpacer(length, 1);
    gui->addLabel("LIGHTING");
    gui->addSlider("LIGHT POS X", -300, 300, &app->scene.lightPosition.x, length, dim);
    gui->addSlider("LIGHT pos Y", -300, 300, &app->scene.lightPosition.y, length, dim);
    gui->addSlider("LIGHT pos Z", -500, 500, &app->scene.lightPosition.z, length, dim);
    
    
    // grid
    
    finaliseCanvas(gui);
}



void GUI::addSkeletonGUI()
{
    string title = "SKELETON";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("POSITION OFFSET", OFX_UI_FONT_MEDIUM);
    gui->addSlider("JOINT OFFSET X", -300, 300, &app->kinectManager.jointPosOffset.x, length, dim);
    gui->addSlider("JOINT OFFSET Y", -300, 300, &app->kinectManager.jointPosOffset.y, length, dim);
    gui->addSlider("JOINT OFFSET Z", -300, 300, &app->kinectManager.jointPosOffset.z, length, dim);
    gui->addLabel("ROTATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("ROT X DEGREES", -50, 50,&app->kinectManager.skeletonRotDegrees, length, dim);
    
    gui->addLabel("KINECT Z REDUCTION", OFX_UI_FONT_MEDIUM);
	gui->addSlider("Z REDUCTION SCALE", 0.001, 0.03, &app->kinectManager.skeletonZReductionScale, length, dim)->setLabelPrecision(3);
	
    
    finaliseCanvas(gui);
}



void GUI::addModelGlobalGUI()
{
    string title = "MODEL GLOBAL";
    ofxUICanvas* gui = getNewGUI(title);
    
    vector<string> drawModes;
	drawModes.push_back("FACE");
	drawModes.push_back("WIREFRAME");
    gui->addLabel("DRAW MODES", OFX_UI_FONT_MEDIUM);
	gui->addRadio("DRAW MODES", drawModes, OFX_UI_ORIENTATION_VERTICAL);
    gui->addSpacer(length, 1);
    
    // debug
    gui->addToggle("DRAW DEBUG", &app->scene.isDrawDebug, toggleSize, toggleSize);
    gui->addToggle("DRAW MODEL", &app->scene.isDrawModel, toggleSize, toggleSize);
    gui->addSlider("MODEL ALPHA", 0, 255, &app->scene.modelAlpha, length, dim);
    
    //scale
    
    // positioning
    
	ofAddListener(gui->newGUIEvent, this, &GUI::guiModelGlobalGUIEvent);
    finaliseCanvas(gui);
}



void GUI::addModelTorsoGUI()
{
    string title = "TORSO";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("TORSO", OFX_UI_FONT_MEDIUM);
    gui->addSlider("TORSO WIDTH SCALE", 0.01, 0.5, &app->scene.torso.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("TORSO HEIGHT SCALE", 0.01, 0.5, &app->scene.torso.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("TORSO DEPTH SCALE", 0.01, 0.5, &app->scene.torso.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("TORSO ROT X", -180, 180, &app->scene.torso.rotX, length, dim);
    gui->addSlider("TORSO ROT Y", -180, 180, &app->scene.torso.rotY, length, dim);
    gui->addSlider("TORSO ROT Z", -180, 180, &app->scene.torso.rotZ, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("TORSO-LEFT SHLDER CONNECT X", -100, 100, &app->scene.torso.connectingPoints[0].x, length, dim);
    gui->addSlider("TORSO-LEFT SHLDER CONNECT Y", -100, 100, &app->scene.torso.connectingPoints[0].y, length, dim);
    gui->addSlider("TORSO-LEFT SHLDER CONNECT Z", -100, 100, &app->scene.torso.connectingPoints[0].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("TORSO-RIGHT SHLDER CONNECT X", -100, 100, &app->scene.torso.connectingPoints[1].x, length, dim);
    gui->addSlider("TORSO-RIGHT SHLDER CONNECT Y", -100, 100, &app->scene.torso.connectingPoints[1].y, length, dim);
    gui->addSlider("TORSO-RIGHT SHLDER CONNECT Z", -100, 100, &app->scene.torso.connectingPoints[1].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("TORSO-ABDOMEN CONNECT X", -100, 100, &app->scene.torso.connectingPoints[2].x, length, dim);
    gui->addSlider("TORSO-ABDOMEN CONNECT Y", -100, 100, &app->scene.torso.connectingPoints[2].y, length, dim);
    gui->addSlider("TORSO-ABDOMEN CONNECT Z", -100, 100, &app->scene.torso.connectingPoints[2].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("TORSO-HEAD CONNECT X", -100, 100, &app->scene.torso.connectingPoints[3].x, length, dim);
    gui->addSlider("TORSO-HEAD CONNECT Y", -100, 100, &app->scene.torso.connectingPoints[3].y, length, dim);
    gui->addSlider("TORSO-HEAD CONNECT Z", -100, 100, &app->scene.torso.connectingPoints[3].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("TORSO CONNECT DIST", 1, 200, &app->scene.torso.distToNextPoint, length, dim);
    gui->addSpacer(length, 1);
    
    
    finaliseCanvas(gui);
}


void GUI::addModelHeadGUI()
{
    string title = "HEAD";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("HEAD", OFX_UI_FONT_MEDIUM);
    gui->addSlider("HEAD WIDTH SCALE", 0.01, 0.5, &app->scene.head.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("HEAD HEIGHT SCALE", 0.01, 0.5, &app->scene.head.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("HEAD DEPTH SCALE", 0.01, 0.5, &app->scene.head.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("HEAD ROT X", -180, 180, &app->scene.head.rotX, length, dim);
    gui->addSlider("HEAD ROT Y", -180, 180, &app->scene.head.rotY, length, dim);
    gui->addSlider("HEAD ROT Z", -180, 180, &app->scene.head.rotZ, length, dim);
    
    finaliseCanvas(gui);
}



void GUI::addModelAbdomenAndLegsGUI()
{
    string title = "ABDOMEN LEGS";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("ABDOMEN", OFX_UI_FONT_MEDIUM);
    gui->addSlider("ABDOMEN WIDTH SCALE", 0.01, 0.5, &app->scene.abdomen.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("ABDOMEN HEIGHT SCALE", 0.01, 0.5, &app->scene.abdomen.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("ABDOMEN DEPTH SCALE", 0.01, 0.5, &app->scene.abdomen.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("ABDOMEN ROT X", -180, 180, &app->scene.abdomen.rotX, length, dim);
    gui->addSlider("ABDOMEN ROT Y", -180, 180, &app->scene.abdomen.rotY, length, dim);
    gui->addSlider("ABDOMEN ROT Z", -180, 180, &app->scene.abdomen.rotZ, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("ABDOMEN-LEGS CONNECT X", -100, 100, &app->scene.abdomen.connectingPoints[0].x, length, dim);
    gui->addSlider("ABDOMEN-LEGS SHLDER CONNECT Y", -100, 100, &app->scene.abdomen.connectingPoints[0].y, length, dim);
    gui->addSlider("ABDOMEN-LEGS SHLDER CONNECT Z", -100, 100, &app->scene.abdomen.connectingPoints[0].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("ABDOMEN DIST TO NEXT PNT", 1, 200, &app->scene.abdomen.distToNextPoint, length, dim);
    
    
    gui->addLabel("LEGS", OFX_UI_FONT_MEDIUM);
    gui->addSlider("LEGS WIDTH SCALE", 0.01, 0.5, &app->scene.legs.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("LEGS HEIGHT SCALE", 0.01, 0.5, &app->scene.legs.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("LEGS DEPTH SCALE", 0.01, 0.5, &app->scene.legs.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("LEGS ROT X", -180, 180, &app->scene.legs.rotX, length, dim);
    gui->addSlider("LEGS ROT Y", -180, 180, &app->scene.legs.rotY, length, dim);
    gui->addSlider("LEGS ROT Z", -180, 180, &app->scene.legs.rotZ, length, dim);
    gui->addSpacer(length, 1);
    
//    gui->addLabel("LEGS", OFX_UI_FONT_MEDIUM);
//    gui->addSlider("LEGS WIDTH SCALE", 0.1, 10, &app->scene.head.scaleW, length, dim);
//    gui->addSlider("LEGS HEIGHT SCALE", 0.1, 10, &app->scene.head.scaleH, length, dim);
//    gui->addSlider("LEGS DEPTH SCALE", 0.1, 10, &app->scene.head.scaleD, length, dim);
//    gui->addSpacer(length, 1);
//    gui->addSlider("LEGS CONNECT DIST", 1, 200, &app->scene.head.distToNextPoint, length, dim);
    
    finaliseCanvas(gui);
}


void GUI::addModelArmsLGUI()
{
    string title = "ARMS LEFT";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("UPPER ARM", OFX_UI_FONT_MEDIUM);
    gui->addSlider("UPPER ARM WIDTH SCALE", 0.01, 0.5, &app->scene.upperArmL.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("UPPER ARM HEIGHT SCALE", 0.01, 0.5, &app->scene.upperArmL.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("UPPER ARM DEPTH SCALE", 0.01, 0.5, &app->scene.upperArmL.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("UPPER ARM ROT X", -180, 180, &app->scene.upperArmL.rotX, length, dim);
    gui->addSlider("UPPER ARM ROT Y", -180, 180, &app->scene.upperArmL.rotY, length, dim);
    gui->addSlider("UPPER ARM ROT Z", -180, 180, &app->scene.upperArmL.rotZ, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("UPPER-FOREARM CONNECT X", -100, 100, &app->scene.upperArmL.connectingPoints[0].x, length, dim);
    gui->addSlider("UPPER-FORE SHLDER CONNECT Y", -100, 100, &app->scene.upperArmL.connectingPoints[0].y, length, dim);
    gui->addSlider("UPPER-FORE SHLDER CONNECT Z", -100, 100, &app->scene.upperArmL.connectingPoints[0].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("UPPER-FOREARM CONNECT DIST", 1, 100, &app->scene.upperArmL.distToNextPoint, length, dim);
    gui->addSpacer(length, 1);
    
    gui->addLabel("FOREARM", OFX_UI_FONT_MEDIUM);
    gui->addSlider("FOREARM WIDTH SCALE", 0.01, 0.5, &app->scene.forearmL.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("FOREARM HEIGHT SCALE", 0.01, 0.5, &app->scene.forearmL.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("FOREARM DEPTH SCALE", 0.01, 0.5, &app->scene.forearmL.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("FOREARM ROT X", -180, 180, &app->scene.forearmL.rotX, length, dim);
    gui->addSlider("FOREARM ROT Y", -180, 180, &app->scene.forearmL.rotY, length, dim);
    gui->addSlider("FOREARM ROT Z", -180, 180, &app->scene.forearmL.rotZ, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("FOREARM-HAND CONNECT X", -100, 100, &app->scene.forearmL.connectingPoints[0].x, length, dim);
    gui->addSlider("FOREARM-HAND CONNECT Y", -100, 100, &app->scene.forearmL.connectingPoints[0].y, length, dim);
    gui->addSlider("FOREARM-HAND CONNECT Z", -100, 100, &app->scene.forearmL.connectingPoints[0].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("FOREARM-HAND CONNECT DIST", 1, 100, &app->scene.forearmL.distToNextPoint, length, dim);
    
    finaliseCanvas(gui);
}


void GUI::addModelArmsRGUI()
{
    string title = "ARMS RIGHT";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("UPPER ARM", OFX_UI_FONT_MEDIUM);
    gui->addSlider("UPPER ARM WIDTH SCALE", 0.01, 0.5, &app->scene.upperArmR.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("UPPER ARM HEIGHT SCALE", 0.01, 0.5, &app->scene.upperArmR.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("UPPER ARM DEPTH SCALE", 0.01, 0.5, &app->scene.upperArmR.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("UPPER ARM ROT X", -180, 180, &app->scene.upperArmR.rotX, length, dim);
    gui->addSlider("UPPER ARM ROT Y", -180, 180, &app->scene.upperArmR.rotY, length, dim);
    gui->addSlider("UPPER ARM ROT Z", -180, 180, &app->scene.upperArmR.rotZ, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("UPPER-FOREARM CONNECT X", -100, 100, &app->scene.upperArmR.connectingPoints[0].x, length, dim);
    gui->addSlider("UPPER-FORE SHLDER CONNECT Y", -100, 100, &app->scene.upperArmR.connectingPoints[0].y, length, dim);
    gui->addSlider("UPPER-FORE SHLDER CONNECT Z", -100, 100, &app->scene.upperArmR.connectingPoints[0].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("UPPER-FOREARM CONNECT DIST", 1, 100, &app->scene.upperArmR.distToNextPoint, length, dim);
    gui->addSpacer(length, 1);
    
    gui->addLabel("FOREARM", OFX_UI_FONT_MEDIUM);
    gui->addSlider("FOREARM WIDTH SCALE", 0.01, 0.5, &app->scene.forearmR.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("FOREARM HEIGHT SCALE", 0.01, 0.5, &app->scene.forearmR.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("FOREARM DEPTH SCALE", 0.01, 0.5, &app->scene.forearmR.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("FOREARM ROT X", -180, 180, &app->scene.forearmR.rotX, length, dim);
    gui->addSlider("FOREARM ROT Y", -180, 180, &app->scene.forearmR.rotY, length, dim);
    gui->addSlider("FOREARM ROT Z", -180, 180, &app->scene.forearmR.rotZ, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("FOREARM-HAND CONNECT X", -100, 100, &app->scene.forearmR.connectingPoints[0].x, length, dim);
    gui->addSlider("FOREARM-HAND CONNECT Y", -100, 100, &app->scene.forearmR.connectingPoints[0].y, length, dim);
    gui->addSlider("FOREARM-HAND CONNECT Z", -100, 100, &app->scene.forearmR.connectingPoints[0].z, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("FOREARM-HAND CONNECT DIST", 1, 100, &app->scene.forearmR.distToNextPoint, length, dim);
    
    finaliseCanvas(gui);
}



void GUI::addModelHandsGUI()
{
    string title = "HANDS";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("HAND LEFT", OFX_UI_FONT_MEDIUM);
    gui->addSlider("HAND LEFT WIDTH SCALE", 0.01, 0.5, &app->scene.handL.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("HANDS LEFT HEIGHT SCALE", 0.01, 0.5, &app->scene.handL.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("HANDS LEFT DEPTH SCALE", 0.01, 0.5, &app->scene.handL.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("HANDS LEFT ROT X", -180, 180, &app->scene.handL.rotX, length, dim);
    gui->addSlider("HANDS LEFT ROT Y", -180, 180, &app->scene.handL.rotY, length, dim);
    gui->addSlider("HANDS LEFT ROT Z", -180, 180, &app->scene.handL.rotZ, length, dim);
    
    gui->addLabel("HAND RIGHT", OFX_UI_FONT_MEDIUM);
    gui->addSlider("HAND RIGHT WIDTH SCALE", 0.01, 0.5, &app->scene.handR.scaleW, length, dim)->setLabelPrecision(4);
    gui->addSlider("HANDS RIGHT HEIGHT SCALE", 0.01, 0.5, &app->scene.handR.scaleH, length, dim)->setLabelPrecision(4);
    gui->addSlider("HANDS RIGHT DEPTH SCALE", 0.01, 0.5, &app->scene.handR.scaleD, length, dim)->setLabelPrecision(4);
    gui->addSpacer(length, 1);
    gui->addSlider("HANDS RIGHT ROT X", -180, 180, &app->scene.handR.rotX, length, dim);
    gui->addSlider("HANDS RIGHT ROT Y", -180, 180, &app->scene.handR.rotY, length, dim);
    gui->addSlider("HANDS RIGHT ROT Z", -180, 180, &app->scene.handR.rotZ, length, dim);
    
    finaliseCanvas(gui);
}



void GUI::addShadingGUI()
{
    string title = "SHADING";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addSlider("AMBIENT RED", 0, 0.5, &BodyPart::ambient.r, length, dim);
    gui->addSlider("AMBIENT GREEN", 0, 0.5, &BodyPart::ambient.g, length, dim);
    gui->addSlider("AMBIENT BLUE", 0, 0.5, &BodyPart::ambient.b, length, dim);
    gui->addSlider("AMBIENT ALPHA", 0, 1, &BodyPart::ambient.a, length, dim);
    gui->addSpacer(spacerW, spacerH);
    gui->addSlider("DIFFUSE RED", 0, 2, &BodyPart::diffuse.r, length, dim);
    gui->addSlider("DIFFUSE GREEN", 0, 2, &BodyPart::diffuse.g, length, dim);
    gui->addSlider("DIFFUSE BLUE", 0, 2, &BodyPart::diffuse.b, length, dim);
    gui->addSlider("DIFFUSE ALPHA", 0, 2, &BodyPart::diffuse.a, length, dim);
    gui->addSpacer(spacerW, spacerH);
    gui->addSlider("SPECULAR RED", 0, 2, &BodyPart::specular.r, length, dim);
    gui->addSlider("SPECULAR GREEN", 0, 2, &BodyPart::specular.g, length, dim);
    gui->addSlider("SPECULAR BLUE", 0, 2, &BodyPart::specular.b, length, dim);
    gui->addSlider("SPECULAR ALPHA", 0, 2, &BodyPart::specular.a, length, dim);
    gui->addSpacer(spacerW, spacerH);
    gui->addSlider("SHINYNESS", 0, 200, &BodyPart::shinyness, length, dim);
    gui->addSlider("SHADOW INTENSITY", 0, 1, &BodyPart::shadowIntensity, length, dim);
    gui->addSpacer(spacerW, spacerH);
    gui->addToggle("TOGGLE BUMP MAP", &BodyPart::isBumpMapActive, toggleSize, toggleSize);
    gui->addSlider("BUMP MAP STRENGTH", 0, 10, &BodyPart::bumpMapStrength, length, dim);
    
    finaliseCanvas(gui);
}


void GUI::addBackgroundGUI()
{
    string title = "BACKGROUND";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addSlider("BG RED", 0, 255, &app->scene.cameraTargetPosition.x, length, dim);
    gui->addSlider("BG GREEN", 0, 255, &app->scene.cameraTargetPosition.y, length, dim);
    gui->addSlider("BG BLUE", 0, 255, &app->scene.cameraTargetPosition.z, length, dim);
    
    finaliseCanvas(gui);
}


void GUI::addGUIDesignGUI()
{
    string title = "GUI DESIGN";
    ofxUICanvas* gui = getNewGUI(title);
    gui->addSlider("BACK RED", 0, 255, 255, length, dim);
    gui->addSlider("BACK GREEN", 0, 255, 1, length, dim);
    gui->addSlider("BACK BLUE", 0, 255, 1, length, dim);
    gui->addSlider("BACK ALPHA", 0, 255, 255, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("FILL RED", 0, 255, 255, length, dim);
    gui->addSlider("FILL GREEN", 0, 255, 1, length, dim);
    gui->addSlider("FILL BLUE", 0, 255, 1, length, dim);
    gui->addSlider("FILL ALPHA", 0, 255, 255, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("HIGHLIGHT RED", 0, 255, 255, length, dim);
    gui->addSlider("HIGHLIGHT GREEN", 0, 255, 1, length, dim);
    gui->addSlider("HIGHLIGHT BLUE", 0, 255, 1, length, dim);
    gui->addSlider("HIGHLIGHT ALPHA", 0, 255, 255, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("OUTLINE RED", 0, 255, 255, length, dim);
    gui->addSlider("OUTLINE GREEN", 0, 255, 1, length, dim);
    gui->addSlider("OUTLINE BLUE", 0, 255, 1, length, dim);
    gui->addSlider("OUTLINE ALPHA", 0, 255, 255, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("OUTLINE HIGHLIGHT RED", 0, 255, 255, length, dim);
    gui->addSlider("OUTLINE HIGHLIGHT GREEN", 0, 255, 1, length, dim);
    gui->addSlider("OUTLINE HIGHLIGHT BLUE", 0, 255, 1, length, dim);
    gui->addSlider("OUTLINE HIGHLIGHT ALPHA", 0, 255, 255, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("PADDED RED", 0, 255, 255, length, dim);
    gui->addSlider("PADDED GREEN", 0, 255, 1, length, dim);
    gui->addSlider("PADDED BLUE", 0, 255, 1, length, dim);
    gui->addSlider("PADDED ALPHA", 0, 255, 255, length, dim);
    gui->addSpacer(length, 1);
    gui->addSlider("PADDED HIGHLIGHT RED", 0, 255, 255, length, dim);
    gui->addSlider("PADDED HIGHLIGHT GREEN", 0, 255, 1, length, dim);
    gui->addSlider("PADDED HIGHLIGHT BLUE", 0, 255, 1, length, dim);
    gui->addSlider("PADDED HIGHLIGHT ALPHA", 0, 255, 255, length, dim);
    
	ofAddListener(gui->newGUIEvent, this, &GUI::guiDesignGUIEvent);
    finaliseCanvas(gui);
}



void GUI::update()
{
    
}


void GUI::draw()
{
}


void GUI::guiModelGlobalGUIEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if (name == "FACE")
    {
     	ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue()) app->scene.isDrawFaces = true;
    }
    else if (name == "WIREFRAME")
    {
     	ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        if (toggle->getValue()) app->scene.isDrawFaces = false;
    }
}

void GUI::guiDesignGUIEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if (name == "BACK RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorBack.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "BACK GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorBack.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "BACK BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorBack.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "BACK ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorBack.a = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "FILL RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorFill.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "FILL GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorFill.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "FILL BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorFill.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "FILL ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorFill.a = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "HIGHLIGHT RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorHighlight.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "HIGHLIGHT GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorHighlight.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "HIGHLIGHT BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorHighlight.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "HIGHLIGHT ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorHighlight.a = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutline.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutline.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutline.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutline.a = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE HIGHLIGHT RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutlineHighlight.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE HIGHLIGHT GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutlineHighlight.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE HIGHLIGHT BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutlineHighlight.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "OUTLINE HIGHLIGHT ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorOutlineHighlight.a = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPadded.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPadded.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPadded.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPadded.a = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED HIGHLIGHT RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPaddedHighlight.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED HIGHLIGHT GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPaddedHighlight.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED HIGHLIGHT BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPaddedHighlight.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "PADDED HIGHLIGHT ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        colorPaddedHighlight.a = slider->getScaledValue();
        setGUIColour();
    }
}
