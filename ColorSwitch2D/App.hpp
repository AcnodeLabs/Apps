// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: ColorSwitch2D
*/

class GameObjectSnd {
public:
	GameObject obj;
	string tag;// filenames derived from tag
	
	void AddResourceWithSound(AlgeApp* app, string tag, float scale) {
		app->AddResource(&obj, tag, scale);
	//	app->PlaySnd(tag+".wav");
	}
};

class /*Arkanoid2D*/ App : public AlgeApp { 
	
	GameObjectSnd  screen0cs;
	GameObject star;
	GameObject ring4color;

public:

	virtual void Init(char* path) {
		alInit(STANDARD);
		SetTitle("ColorSwitch2D");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		screen0cs.AddResourceWithSound(this, "Screen0cs", 0.5);
		AddResource(&star, "star", 10);
		star.pos.x = originX;
		star.pos.y = originY;
		star.applyTopLeftCorrectionWRTorigin = false;
		
		PosRotScale starPrs;
		starPrs.JuiceType = JUICE_ROTZ_PULSATE;
		starPrs.JuiceSpeed = 10;
		for (int i = 0; i < 10; i++) {
			starPrs.pos.x = randm()* rightSide;
			starPrs.pos.y = randm()* bottomSide;
			star.scale = 1;
			star.AddInstance(starPrs);
			printf("Star(%.1f,%.1f)", starPrs.pos.x, starPrs.pos.y);
		}

		AddResource(&ring4color, "ring4color", 1);
		ring4color.applyTopLeftCorrectionWRTorigin = true;
		PosRotScale ringPrs;
		ringPrs.JuiceType = JuiceTypes::JUICE_ROTZ;
	
		ringPrs.pos = f3(originX,originY,0);
		ringPrs.scale = 0.995;
		ringPrs.JuiceSpeed = -75;
		ring4color.AddInstance(ringPrs);
		
		ringPrs.scale = 0.886;
		ringPrs.JuiceSpeed = 70;
		ring4color.AddInstance(ringPrs);

		ringPrs.scale = 0.786;
		ringPrs.JuiceSpeed = -85;
		ring4color.AddInstance(ringPrs);

	}
	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_KEYDOWN) {
			if (p->i1 == AL_KEY_RIGHT) {
				editX += 1;
			}
			if (p->i1 == AL_KEY_LEFT) {
				editX -= 1;
			}
			if (p->i1 == AL_KEY_UP) {
				editY += 1;
			}
			if (p->i1 == AL_KEY_DOWN) {
				editY -= 1;
			}
		}
		if (p->command == CMD_TOUCH_START) {
		}
		if (p->command == CMD_TOUCH_END) {
		}
	}

	
	float editX = originX;
	float editY = originY;





	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
	
		if (gob->modelId == star.modelId) {
			gob->rotatefirst = false;
		//	gob->getInstancePtr(instanceNo)->rot.z += 1;
		}

		if (gob->modelId == ring4color.modelId) {
			gob->rotatefirst = false;
			return;
			PosRotScale* i = gob->getInstancePtr(instanceNo);

			switch (instanceNo) {
			case 1:
				i->rot.z -= (deltaT * 75); 
				break;
			case 2:
				i->rot.z += (deltaT * 70);
				break;
			case 3:
				i->rot.z -= (deltaT * 85);
				break;
			case 4:
				i->rot.z -= (deltaT * 85);
				break;
			case 5:
				i->rot.z -= (deltaT * 85);
				break;
			}
		}
	}

	virtual i2 getBackgroundSize() {
		return i2(935, 1110).half();
		//return i2(512, 512);
	}
		


};
