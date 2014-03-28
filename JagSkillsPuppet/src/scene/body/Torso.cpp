//
//  Torso.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Torso.h"

void Torso::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
    
   // model.loadModel(modelPath, true);
    
	//model.setPosition(-200, 0, 0);

	isUseOfMesh = true;
	
    // 3 connections for torso - L and R upper arms and abdomen
    for (int i = 0; i < 3; i++)
    {
        connectingPoints.push_back(ofVec3f(0,0,0));
        connectingPointsAbsolute.push_back(ofVec3f(0, 0, 0));
    }
}



void Torso::calculateShoulderRotation(ofVec3f shoulder1, ofVec3f shoulder2)
{
	shoulderRotation = sin(ofGetElapsedTimef()) * 20;
}


void Torso::update(ofVec3f _skelJointPos, ofVec3f _skelJointTarget)
{
	// If individual vertices need to be tranfomed, the mesh data is taken from the model and used in an ofMesh object.
	if (isUseOfMesh)
	{
		meshes.clear();
		for (int i = 0; i < model.getNumMeshes(); i++)
		{
			ofMesh mesh = model.getMesh(i);
			for (int j = 0; j < mesh.getVertices().size(); j++)
			{
				ofVec3f *vert = &mesh.getVertex(j);
				vert->x -= meshVertsOffset.x;
				vert->y -= meshVertsOffset.y;
				vert->z -= meshVertsOffset.z;
				vert->rotate(meshVertsRot.x, ofVec3f(1, 0, 0));
				vert->rotate(meshVertsRot.y, ofVec3f(0, 1, 0));
				vert->rotate(meshVertsRot.z, ofVec3f(0, 0, 1));
				mesh.setVertex(j, *vert);
				//
				ofVec3f *norm = &mesh.getNormal(j);
				norm->rotate(meshVertsRot.x, ofVec3f(1, 0, 0));
				norm->rotate(meshVertsRot.y, ofVec3f(0, 1, 0));
				norm->rotate(meshVertsRot.z, ofVec3f(0, 0, 1));
				mesh.setNormal(j, *norm);
			}
			meshes.push_back(mesh);
		}
	}
	else
	{
		// some initial transforms to mesh before the body part is directed toward target
		model.setScale(scaleW, scaleH, scaleD);
		model.setRotation(0, rotX, 1, 0, 0);
		model.setRotation(1, rotY, 0, 1, 0);
		model.setRotation(2, rotZ, 0, 0, 1);
	}

    skelJointPos = _skelJointPos;
    skelJointTarget = _skelJointTarget;
    direction = skelJointTarget - skelJointPos;
	
	//direction.x += shoulderRotation;
	//direction.y += shoulderRotation;
	//direction.z -= shoulderRotation;
    
    // get quaternion to rotate model
    qt.makeRotate(ofVec3f(1, 0, 0), direction);
    qt.getRotate(qangle, qaxis);
}



void Torso::drawFaces()
{
    ofPushMatrix();
    ofTranslate(*originPoint);
    // rotate in direction of target
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    
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

    if (isUseOfMesh)
	{
		ofPushMatrix();
		ofScale(scaleW, scaleH, scaleD);
		ofRotate(rotX, 1, 0, 0);
		ofRotate(rotY, 0, 1, 0);
		ofRotate(rotZ, 0, 0, 1);

		if (isVisible)
		{
			for (int i = 0; i < meshes.size(); i++)
				meshes[i].drawFaces();
		}

		ofPopMatrix();
	}
	else
	{
		if (isVisible)
		    model.drawFaces();
	}
    
    if (isShadingActive) shader->end();

    ofPopMatrix();

	formatConnections();
}



//void Torso::drawFaces()
//{
//    BodyPart::drawFaces();
//    formatConnections();
//}



void Torso::drawWireframe()
{
    BodyPart::drawWireframe();
    formatConnections();
}


void Torso::formatConnections()
{
    // set connection points. These are used to position the axes of the child body parts
    for (int i = 0; i < connectingPointsAbsolute.size(); i++)
    {
        // rotate and position the absolute connection ponts
        connectingPointsAbsolute[i] = connectingPoints[i];
        connectingPointsAbsolute[i].rotate(qangle, ofVec3f(qaxis.x, qaxis.y, qaxis.z));
        connectingPointsAbsolute[i] += *originPoint; //skelJointPos;
    }

	if (isDrawDebug)
	{
		ofPushStyle();
		ofSetColor(0, 0, 255, 255);

#ifdef TARGET_OSX
		ofDrawSphere(connectingPointsAbsolute[0], 5);
#else
		ofSphere(connectingPointsAbsolute[0], 5);
#endif

		ofPopStyle();
	}
}