// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: 2D
   Demonstrates Use of Orthographic Helper Functions HudBegin and HudEnd
*/

enum { 
	MDL_POSTER,
	MDL_TEXT
};

class App : public AlgeApp { 
public:
	CFTFont font;
	GameObject aPoster;
	ResourceInf rPoster;

    int screen[2];
    
	void UpdateCustom(GameObject* gob, PEG::CMD* p) {
		
		if (gob->custom_type == MDL_POSTER) {
			font.PrintText("HELLO");
		};// glRotatef(90, -1.0f, 0.0f, 0.0f);
		processInput(p);
	}

	void processInput(PEG::CMD* p) {
		switch (p->command) {
            case CMD_SCREENSIZE:
                //Store Screen Size
                screen[0] = p->i1;
                screen[1] = p->i2;				
                break;
            }
	}
	/*
	void Render(float tick, int aX, int aY, int aZ) {
		processInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		
        hudBegin(screen);
		 rm.models[MDL_POSTER]->glDraw();
        hudEnd();
	}
	*/

	void Init(char* path) {
		alInit(STANDARD_WITH_TEXTURES);	
		rm.Init(path);
		//rm.loadAlxModel((char*) "animposter.alx",(char*) "animposter.tga", MDL_POSTER, 160);
		
		aCamera.SetSerializeTag("acamera.GOB");
		aCamera.mode = Camera::CAM_MODE_2D;
		AddObject(&aCamera);

		aPoster.SetSerializeTag("animposter.GOB");
		rPoster.Set("animposter");
		LoadModel(&aPoster, &rPoster, MDL_POSTER);
		AddObject(&aPoster);

		//output.pushP(CMD_SNDSET0, $ "elephant.wav", 0); 
		//output.pushP(CMD_SNDPLAY0, $ "elephant.wav", 0);
	}

	void Deinit() {
	}


};
