//
//  Head.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Head.h"

void Head::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
}

//void Head::drawFaces()
//{
//    BodyPart::drawFaces();
//}


void Head::update(ofVec3f _skelJointPos, ofVec3f _skelJointTarget)
{
	
    skelJointPos = _skelJointPos;
    skelJointTarget = _skelJointTarget;
    direction = skelJointTarget - skelJointPos;

	//float rotXNodOffsetAngle = ofMap(direction.y, 13, 23, 16, 20, true);
	float rotXNodOffsetAngle = ofMap(direction.y, rotXNodOffsetAngleInMin, rotXNodOffsetAngleInMax, rotXNodOffsetAngleOutMin, rotXNodOffsetAngleOutMax, true);
	// some initial transforms to mesh before the body part is directed toward target
	model.setScale(scaleW, scaleH, scaleD);
	model.setRotation(0, rotX - (rotXNodOffsetAngle * -20), 1, 0, 0);
	model.setRotation(1, rotY, 0, 1, 0);
	model.setRotation(2, rotZ, 0, 0, 1);
	
    // get quaternion to rotate model
    qt.makeRotate(ofVec3f(1, 0, 0), direction);
    qt.getRotate(qangle, qaxis);	
}



void Head::drawFaces()
{
    ofPushMatrix();
    ofTranslate(*originPoint);
    // rotate in direction of target
    //ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    //ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);

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
    
	if (isShadingActive)
	{
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
	}

	if (isVisible)
	    model.drawFaces();
    
    if (isShadingActive) shader->end();

    ofPopMatrix();
}




void Head::drawWireframe()
{
	BodyPart::drawWireframe();
}

