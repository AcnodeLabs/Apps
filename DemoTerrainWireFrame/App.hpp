// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: Terrain Model
*/

#include "../../SDKSRC/Base/CBaseV1_2.h"

enum {
 MODEL_TERRAIN,
 MODEL_SKYDOME
} models;

class /*DemoTerrain*/ App : public AlgeApp { 
	
	
	CControls controls;
	GLfloat	xrot, yrot, zrot, xspeed, yspeed, z;
	
	float intentvec[3];

public:
	
	void Render(float elapsed, int aX, int aY, int aZ) {
		processInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//DrawSky
		glLoadIdentity();	
		glTranslatef(0,z,0);
		glRotatef(zrot,0.0f,1.0f,0.0f);	
		if (rm.models[MODEL_SKYDOME]->loaded) rm.models[MODEL_SKYDOME]->glDraw(wireframe);
		//DrawTerrain
		glLoadIdentity();
		glTranslatef(0,z,0);
		glRotatef(90,-1.0f,0.0f,0.0f);
		glRotatef(zrot,0.0f,0.0f,1.0f);		
		if (rm.models[MODEL_TERRAIN]->loaded) rm.models[MODEL_TERRAIN]->glDraw(wireframe);		
		zrot+= intentvec[2] ;
	}

	void Init(char* path) {
		rm.Init(path); 
		alInit(STANDARD);
		glClearColor(0.4f, 0.8f, 0.1f, 1.0f);
		glColor4f(0.1f, 0.1f, 1.0f, 0.5f);					// Night Feel.  50% Alpha
		output.pushP(CMD_TITLE, $ "Terrain Demo",0);
		rm.loadAlxModel((char*) "skydome1.alx", AUTO, MODEL_SKYDOME, 0.01f);
		rm.loadAlxModel((char*) "terr2.alx", AUTO, MODEL_TERRAIN, 200.0f);	
		
		z=-30.0f;
		xspeed = 0.1f;
		yspeed = 0.1f;
		wireframe = true;
	}

	void Deinit() {
	}

	bool wireframe;

void processInput() {
		
			PEG::CMD* p = input.pull();	
			
			switch (p->command) {
			
			case CMD_KEYDOWN:
				{
					wireframe=!wireframe;
					break;
				}
			
			case CMD_TOUCH_START:
			{
				switch (controls.KROSS_(true, p->i1, p->i2))  {
				
					case KROSS_RIGHT:
					{
						intentvec[0] = 0; intentvec[1] = 0;	intentvec[2] = 0.2;
						break;
					}
				
					case KROSS_LEFT:
					{
						intentvec[0] = 0;intentvec[1] = 0;intentvec[2] = -0.2;
						break;
					}
				
				} 

				break;
			}
		
		}
	}
};
