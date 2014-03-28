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
bool BodyPart::isShadingActive;
bool BodyPart::isDrawDebug;
bool BodyPart::isDrawModel;


void BodyPart::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    model.loadModel(modelPath, true);
    texture = _texture;
    bumpMap = _bumpMap;
    shader = _shader;
    scaleW = scaleH = scaleD = 1.0;
	isUseOfMesh = false;
	meshVertsOffset = ofVec3f(0,0,0);
	meshVertsRot = ofVec3f(0,0,0);
}


void BodyPart::update(ofVec3f _skelJointPos, ofVec3f _skelJointTarget)
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
				//vert->rotate(meshVertsRot.x, ofVec3f(1, 0, 0));
				vert->rotate(meshVertsRot.y, ofVec3f(0, 1, 0));
				vert->rotate(meshVertsRot.z, ofVec3f(0, 0, 1));
				mesh.setVertex(j, *vert);
				//
				ofVec3f *norm = &mesh.getNormal(j);
				//norm->rotate(meshVertsRot.x, ofVec3f(1, 0, 0));
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
}



void BodyPart::drawWireframe()
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
			for (int i = 0; i< meshes.size(); i++)
				meshes[i].drawWireframe();
		}
		ofPopMatrix();
	}
	else
	{
		if (isVisible)
		    model.drawWireframe();
	}
    
    if (isShadingActive) shader->end();

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

	if (BodyPart::isDrawDebug)
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