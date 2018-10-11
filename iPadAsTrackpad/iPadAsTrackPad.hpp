// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: iPadPad
*/

extern void(*callBackIn)(string);

void myCallBackIn(string data) {
	//MessageBeep(1);
}

class /*iPadAsTrackPad*/ App : public AlgeApp { 
	
	GameObject tp;
	
public:
	
	void processInput(PEG::CMD* p, float deltaT) {
		static char inp[256];
		sprintf_s(inp, 256, "%d,%d,%d", p->command, p->i1, p->i2);
		if (p->command>0) netmsg.Post(inp);
	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
	
		if (gob->modelId == tp.modelId) {
		}
		
	}
	virtual i2 getBackgroundSize() {return i2(800, 800);}

	virtual void Init(char* path) {
		alInit(STANDARD);
		glClearColor(1, 1, 1, 0);
		
		output.pushP(CMD_TITLE, $ "iPadPad  (nats-out: xal.iPadPad nats-in:xal.iPadPad.in)",0);
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		
		AddResource(&tp, "trackpad", 1.);
		int c = netmsg.Connect("iPadPad",false);
		callBackIn = &myCallBackIn;
	}

};
