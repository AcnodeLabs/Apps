// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: iPadPad
*/

extern void(*callBackIn)(string);
void myCallBackIn(string data);


class /*iPadDesktop*/ App : public AlgeApp { 
	
	GameObject tp;
	
public:
	
	void processCapturedInput(int cmd, int i1, int i2) {
		static LinearTweeningVariable mX;
		static LinearTweeningVariable mY;
		
		if (cmd == CMD_TOUCH_START) {

			output.pushI(CMD_MOUSE_REPOSITION, i1, i2);
		}

		if (cmd == CMD_SCREENSIZE) {

		}
	}

	void processInput(PEG::CMD* p, float deltaT) {
		
	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
	
		if (gob->modelId == tp.modelId) {
			
		}
		
	}
	virtual i2 getBackgroundSize() {return i2(100, 50);}

	virtual void Init(char* path) {
		alInit(STANDARD);
		glClearColor(1, 1, 1, 0);
		
		output.pushP(CMD_TITLE, $ "iPadPad  (nats-out: xal.iPadPad nats-in:xal.iPadPad.in)",0);
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		tp.JuiceType = JuiceTypes::JUICE_PULSATE;
		AddResource(&tp, "desk", 1.);
		int c = netmsg.SubscribeConnect("iPadPad",false);//connect as a subscriber 
		callBackIn = &myCallBackIn;
	}

};

extern App game;

void myCallBackIn(string data) {
	int cmd;
	int i1, i2;
	sscanf_s(data.c_str(), "%d,%d,%d", &cmd, &i1, &i2);
	game.processCapturedInput(cmd, i1, i2);
}