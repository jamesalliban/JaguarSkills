//
//  Model.cpp
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#include "Scene.h"

ofFloatColor BodyPart::ambient;
ofFloatColor BodyPart::diffuse;
ofFloatColor BodyPart::specular;
float BodyPart::shinyness;
float BodyPart::shadowIntensity;
bool BodyPart::isBumpMapActive;
float BodyPart::bumpMapStrength;

void BodyPart::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    model.loadModel(modelPath, true);
    texture = _texture;
    bumpMap = _bumpMap;
    shader = _shader;
    scaleW = scaleH = scaleD = 1.0;
}


void BodyPart::update(ofVec3f _skelJointPos, ofVec3f _skelJointTarget)
{
    // some initial transforms
    model.setScale(scaleW, scaleH, scaleD);
    model.setRotation(0, rotX, 1, 0, 0);
    model.setRotation(1, rotY, 0, 1, 0);
    model.setRotation(2, rotZ, 0, 0, 1);
    
    skelJointPos = _skelJointPos;
    skelJointTarget = _skelJointTarget;
    direction = skelJointTarget - skelJointPos;
    
    // get quaternion to rotate model
    qt.makeRotate(ofVec3f(1, 0, 0), direction);
    qt.getRotate(qangle, qaxis);
}



void BodyPart::drawFaces()
{
    ofPushMatrix();
    ofTranslate(*originPoint);
    // rotate in direction of target
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    //ofRotate(qangle, 0, qaxis.y, qaxis.z);
    //ofRotate(qangle, 0, 0, 0);
    
//    texture->bind();
    
    float ambientArray[4];
    ambientArray[0] = ambient.r;
    ambientArray[1] = ambient.g;
    ambientArray[2] = ambient.b;
    ambientArray[3] = ambient.a;
    float diffuseArray[4];
    diffuseArray[0] = diffuse.r;
    diffuseArray[1] = diffuse.g;
    diffuseArray[2] = diffuse.b;
    diffuseArray[3] = diffuse.a;
    float specularArray[4];
    specularArray[0] = specular.r;
    specularArray[1] = specular.g;
    specularArray[2] = specular.b;
    specularArray[3] = specular.a;
    
    shader->begin();
    shader->setUniformTexture("tex0", *texture, texture->getTextureData().textureID);
    shader->setUniformTexture("texDepthMap", *bumpMap, bumpMap->getTextureData().textureID);
    shader->setUniform4fv("ambient", ambientArray);
    shader->setUniform4fv("diffuse", diffuseArray);
    shader->setUniform4fv("specular", specularArray);
    shader->setUniform1f("shinyness", shinyness);
    shader->setUniform1f("shadowIntensity", shadowIntensity);
    shader->setUniform1i("isBumpMapActive", (isBumpMapActive) ? 1 : 0);
    shader->setUniform1f("bumpMapStrength", bumpMapStrength);
    
    
    model.drawFaces();
    
    
    shader->end();
    
    
//    texture->unbind();
    
    ofPopMatrix();
}



void BodyPart::drawWireframe()
{
    ofPushMatrix();
    ofTranslate(*originPoint);
    // rotate in direction of target
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    
    texture->bind();
    model.drawWireframe();
    texture->unbind();
    
    ofPopMatrix();
}




void BodyPart::drawDebug(ofColor col)
{
    ofPushMatrix();
    ofTranslate(*originPoint);
    // rotate in direction of target
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    
    for (int i = 0; i < connectingPoints.size(); i++)
    {
        ofPushStyle();
        ofSetColor(col);

#ifdef TARGET_OSX
        ofDrawBox(connectingPoints[i], 7);
#else
		ofBox(connectingPoints[i], 7);
#endif
        ofPopStyle();
    }
    
    ofPopMatrix();
    
    
    for (int i = 0; i < connectingPoints.size(); i++)
    {
        // draw axes at connection point
        ofPushMatrix();
        ofTranslate(connectingPointsAbsolute[i]);
        ofDrawAxis(20);
        ofPopMatrix();
        
        // draw Sphere at connection point
        ofPushStyle();
        ofSetColor(0, 0, 255, 255);
		
#ifdef TARGET_OSX
        ofDrawSphere(connectingPointsAbsolute[i], 5);
#else
        ofSphere(connectingPointsAbsolute[i], 5);
#endif
        ofPopStyle();
    }
}


void BodyPart::formatConnections()
{
    connectingPointsAbsolute[0] = *originPoint + (ofVec3f(direction).getNormalized() * distToNextPoint);

    ofPushStyle();
    ofSetColor(0, 0, 255, 255);

#ifdef TARGET_OSX
    ofDrawSphere(connectingPointsAbsolute[0], 5);
#else
    ofSphere(connectingPointsAbsolute[0], 5);
#endif

	
	ofPopStyle();
}



//void BodyPart::drawBox(ofVec3f pos, ofVec3f target)
//{
//    ofVec3f shoulderToElbowVec = pos - target;
//    
//    ofBoxPrimitive box;
//    box.set(distToNextPoint, 5 * scaleH, 5 * scaleD, 2, 2, 2);
//    for (int i = 0; i < box.getMesh().getVertices().size(); i++)
//    {
//        ofVec3f *vert = &box.getMesh().getVertices()[i];
//        vert->x += box.getWidth() * 0.5;
//    }
//    
//    ofQuaternion qt;
//    qt.makeRotate(ofVec3f(1, 0, 0), target - pos);
//    
//    
//    ofPushMatrix();
//    ofTranslate(*originPoint);
//    
//    // rotate in direction of target
//    ofVec3f qaxis;
//    float qangle;
//    qt.getRotate(qangle, qaxis);
//    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
//    
//    
//    img.bind();
//    model.drawFaces();
//    img.unbind();
//    
//    
//    
//    for (int i = 0; i < connectingPoints.size(); i++)
//    {
//        ofPushStyle();
//        ofSetColor(0, 255, 0, 255);
//        ofDrawBox(connectingPoints[i], 7);
//        ofPopStyle();
//    }
//    
//    ofPopMatrix();
//    
//    
//    // set connection points. These are used to position the axes of the child body parts
//    if (bodyType == BODY_PART_TYPE_TORSO)
//    {
//        for (int i = 0; i < connectingPointsRotated.size(); i++)
//        {
//            connectingPointsRotated[i] = connectingPoints[i];
//            connectingPointsRotated[i].rotate(qangle, ofVec3f(qaxis.x, qaxis.y, qaxis.z));
//            connectingPointsRotated[i] += pos;
//            
//            ofPushStyle();
//            ofSetColor(0, 0, 255, 255);
//            ofDrawSphere(connectingPointsRotated[i], 5);
//            ofPopStyle();
//        }
//    }
//    else if (bodyType == BODY_PART_TYPE_ARM)
//    {
//        connectingPointsRotated[0] = *originPoint + (ofVec3f(target - pos).getNormalized() * distToNextPoint);
//        
//        ofPushStyle();
//        ofSetColor(0, 0, 255, 255);
//        ofDrawSphere(connectingPointsRotated[0], 5);
//        ofPopStyle();
//    }
//    else if (bodyType == BODY_PART_TYPE_HAND)
//    {
//    }
//}