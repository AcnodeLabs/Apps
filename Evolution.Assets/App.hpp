// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: Terrain Model
*/

#include "../../Base/CBaseV1_2.h"

enum {
 MODEL_TERRAIN,
 MODEL_SKYDOME
} models;

class /*DemoTerrain*/ App { 
	
	
	CControls controls;
	GLfloat	xrot, yrot, zrot, xspeed, yspeed, z;
	
	float intentvec[3];

public:
    CResourceManager rm;
	PEG output;
	PEG input;
	
	void Render(float elapsed, int aX, int aY, int aZ) {
		processInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//DrawSky
		glLoadIdentity();	
		glRotatef(zrot,0.0f,1.0f,0.0f);	
		if (rm.models[MODEL_SKYDOME]->loaded) rm.models[MODEL_SKYDOME]->glDraw();
		//DrawTerrain
		glLoadIdentity();
		glTranslatef(0,-4.0f,0);
		glRotatef(90,-1.0f,0.0f,0.0f);
		glRotatef(zrot,0.0f,0.0f,1.0f);		
		if (rm.models[MODEL_TERRAIN]->loaded) rm.models[MODEL_TERRAIN]->glDraw();
		
		zrot+= intentvec[2] ;
	}

	void Init(char* path) {
		rm.Init(path); 
		alInit(STANDARD);
		glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);					// Full Brightness.  50% Alpha
		output.pushP(CMD_TITLE, $ "Terrain Demo",0);
		rm.loadAlxModel((char*) "skydome1.alx", AUTO, MODEL_SKYDOME, 0.1f);
		rm.loadAlxModel((char*) "terr2.alx", AUTO, MODEL_TERRAIN, 20.0f);	
		output.pushP(CMD_MSG, $ "This Touch Enabled Demo uses \nSkyDome and Terrain Model generated\nto ALX format using Blender3d\nand ported to this Device using\nAlge Kit R1", 0);

		z=-6.0f;
		xspeed = 1.f;
		yspeed = 1.f;
	}

	void Deinit() {
	}

void processInput() {
		
			PEG::CMD* p = input.pull();	
			
			switch (p->command) {
			
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
