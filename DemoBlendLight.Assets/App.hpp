#include "../../Base/CBaseV1_2.h"

//BasicTnL
class App { 

	
	CControls controls;
	
	GLfloat	xrot;				// X Rotation
	GLfloat	yrot;				// Y Rotation
	GLfloat xspeed;				// X Rotation Speed
	GLfloat yspeed;				// Y Rotation Speed
	GLfloat	z;					// Depth Into The Screen

	short light;
	short blend;

	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightPosition[4];

public:
    CResourceManager rm;
	PEG output;
	PEG input;
	aL10 AL10;
	char szP1[128];
	short mode ;

	void processInput() {
		PEG::CMD* p = input.pull();
		switch (p->command) {
			case CMD_TOUCH_START:
				{
					if (mode==0) {light=0;blend=0;}
					if (mode==1) {light=0;blend=1;}
					if (mode==2) {light=1;blend=0;}
					if (mode==3) {light=1;blend=1;}
					
					if (light) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
					if (blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);

					mode++;
					if (mode>3) mode=0;
				}
				break;
		}
	}


	void Render(float elapsed, int aX, int aY, int aZ) {
		
		processInput();

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();	
		glTranslatef(0.0f,0.0f,-10);
		glRotatef(yrot,0,1,0); 
		float gap = 1.2;
		
		float step = 2.2;

		for (float y = 5*step; y> -5*step; y-=step) {
			glTranslatef(-gap, y, 0);
			rm.models[0]->glDraw();
			glTranslatef(gap, -y, 0);
			
			glTranslatef(gap, y, 0);
			rm.models[0]->glDraw();
			glTranslatef(-gap, -y, 0);
			
		}
		glTranslatef(0.0f,0.0f,10);
		
		xrot+=xspeed;
		yrot+=yspeed;
	}



	void Init(char* path) {			
		glShadeModel(GL_SMOOTH);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);		
		int depth;
		glGetIntegerv(GL_DEPTH_BITS, &depth);		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
		{
			LightAmbient[0] = 0.5f;
			LightAmbient[1] = 0.5f;
			LightAmbient[2] = 0.5f;
			LightAmbient[3] = 1.0f;
			LightDiffuse[0] = LightDiffuse[1]	= LightDiffuse[2] = LightDiffuse[3] = 1;
			LightPosition[0]  =	0.0f;
			LightPosition[1]  =	0.0f;
			LightPosition[2]  =	2.0f;
			LightPosition[3]  =	1.0f;
		}

		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
		glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);		// Position The Light
		glEnable(GL_LIGHT1);											// Enable Light One

		glColor4f(1.0f, 1.0f, 1.0f, 0.5);							// Full Brightness.  50% Alpha
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency

		output.pushP(CMD_TITLE, $ "Basic TnL",0);
		output.pushP(CMD_TOAST, $ "Touch to Change Mode", 0);
		xrot=0;
		yrot=0;
		z=-6.0f;
		xspeed = 0;
		yspeed = 0.3;
		light = 0;
		blend = 0;
		mode = 1;
		rm.Init(path);
		rm.loadAlxModel((char*) "colorcube.alx", AUTO ,0, 1);
	}

	void Deinit() {
	}
};
