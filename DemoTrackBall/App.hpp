// Copyright (c) 2012 AcnodLabs Inc

/* 
ALGE SDK Demo :: TrackBall
*/

#define MDL_PLANET 0
#define MDL_RINGS 1

class App : public AlgeApp { 
 
	CTrackBall trackball;
public:
	
	float eye[3];
	float tgt[3];
           
	void Render(float deltaT, int aX, int aY, int aZ) {	
        processInput();       
        glClearColor(trackball._color().x, trackball._color().y, trackball._color().z, 1); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();		
        aluLookAt(eye[0],eye[1],eye[2], tgt[0],tgt[1],tgt[2], 0,1,0);
        trackball.ApplyRotate();// Apply TrackBall Rotation onto Current Matrix
        rm.models[MDL_PLANET]->glDraw();
        rm.models[MDL_RINGS]->glDraw();
	}  

	void Init(char* path) {
		float size = 9900 / 12756.f;		
		rm.Init(path);

		alInit(STANDARD_WITH_TEXTURES);
		glEnable(GL_DEPTH_TEST);        

		rm.loadAlxModel((char*) "sphere.alx", (char*) "saturn.tga", MDL_PLANET, size*0.7f);
		rm.loadAlxModel((char*) "satrings.alx", AUTO, MDL_RINGS, 1*0.95);

        tgt[0] = tgt[1] = tgt[2] = 0;eye[0] = 0;eye[1] = 0;
		eye[2] = - rm.models[0]->boundz()*5; 
		output.pushP(CMD_MSG,  $ "Demo TrackBall2 :: ALGE SDK R1\nFeatures:\n- Swipe to Rotate\n- Pinch (In/Out) to Zoom\n AcnodeLabs (c) 2011", 0);		
    }

	void Deinit() {
	}
	
    
	void processInput() {			
        PEG::CMD* p = input.pull();
        trackball.processTouches(p->command, p->i1, p->i2);
        eye[2] += 0.1f * trackball.pinchDirection();
	}

};
