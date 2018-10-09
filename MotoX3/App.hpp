// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: Arkanoid2D
*/

//#include "1_Arkanoid/p9.cpp"


constexpr float paddleWidth{ 60.f }, paddleHeight{ 20.f }, paddleVelocity{ 6.f };
constexpr float blockWidth{ 60.f }, blockHeight{ 20.f };
constexpr int countBlocksX{ 1 }, countBlocksY{ 5 };
constexpr int windowWidth{ 640*2 }, windowHeight{ 425*2 };//repeated see App.w*


class RoundGameObject : public GameObject
{
public:
	float ballRadius{ 10.f }, ballVelocity{ 250.f };

	f2 velocity{ -ballVelocity, -ballVelocity };
	
	RoundGameObject() {};

	RoundGameObject(float mX, float mY)
	{
		pos.x = mX, pos.y = mY;
	}

	bool ballwall(float deltaT)
	{
		pos.x += velocity.x * deltaT;
		pos.y += velocity.y * deltaT;
		bool hit = false;

		if (left() < 0) {
			velocity.x = ballVelocity;
			hit = true;
		}
		else if (right() > windowWidth) {
			hit = true;
			velocity.x = -ballVelocity;
		}

		if (top() < 0) {
			velocity.y = ballVelocity;
			hit = true;
		}
		else if (bottom() > windowHeight) {
			velocity.y = -ballVelocity;
			hit = true;
		}
		return hit;
	}

	float x() { return pos.x; }
	float y() { return pos.y; }
	float left() { return x() - ballRadius; }
	float right() { return x() + ballRadius; }
	float top() { return y() - ballRadius; }
	float bottom() { return y() + ballRadius; }
};
class RectGameObject : public GameObject {
public:
	float width;
};

class /*Arkanoid2D*/ App : public AlgeApp { 
	
	GameObject  bg;
	GameText bat;	
	RoundGameObject bal; ResourceInf res;
	GameObject bric;
	
	const int xMax = 500;
	const int xSpd = 10;
public:
	int windowWidth{ 640*2 }, windowHeight{ 425*2 };
	
	void processInput(PEG::CMD* p, float deltaT) {
		PosRotScale prs;
		float moveDelta = 0.1;//10%
		if (p->command == CMD_KEYDOWN) {
			if (p->i1 == AL_KEY_RIGHT) {
				f2 right{ windowWidth * 0.9f, bat.pos.y };
				bat.transitionTo(right,200);
			}
			if (p->i1 == AL_KEY_LEFT) {
				f2 left{ windowWidth * 0.1f, bat.pos.y };
				bat.transitionTo(left,200);
			}
		}
		
		if (p->command == CMD_TOUCH_START) {
			int x = p->i1;
			int y = p->i2;

		}
		if (p->command == CMD_TOUCH_END) {
		
		}
	}

#define ADJUST /1.0
	
	
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
	
		if (gob->modelId == bric.modelId) {
			RectGameObject* b = (RectGameObject*)bric.getInstancePtr(instanceNo);
			if (isCircleIntersectingRect(bal.pos.x, bal.pos.y, bal.ballRadius, b->pos.x, b->pos.y,blockWidth,blockHeight)) {
				if (bat.pos.x < bal.pos.x) bal.velocity.x = -bal.velocity.x;
				bal.velocity.y = -bal.velocity.y;
			};
		}
		if (gob->modelId == bg.modelId) {
			bg.rotatefirst = false;
			bg.rot.z = 180;
			bg.pos.x = windowWidth /2;
			bg.pos.y = windowHeight /2;		
		}

		if (gob->modelId == bat.modelId) {
			if (isCircleIntersectingRect(bal.pos.x, bal.pos.y, bal.ballRadius, bat.pos.x, bat.pos.y, bat.width, 20)) {
				if (bat.pos.x < bal.pos.x) bal.velocity.x = -bal.velocity.x;
				bal.velocity.y = -bal.velocity.y;
			};
			bat.Update(deltaT);
		} 

		static float r;
		if (gob->modelId == bal.modelId) {
			bal.rotatefirst = false;
			bal.rot.z += 1;
			if (bal.ballwall(deltaT)) { output.pushP(CMD_SNDPLAY1);  }
			
		}
	}
	//http://gamedistribution.com/games/moto-x3m-bike-race-game
	//Play FullScreen https://html5.gamedistribution.com/5b0abd4c0faa4f5eb190a9a16d5a1b4c/
	virtual void Init(char* path) {
		alInit(STANDARD);
		
		output.pushP(CMD_TITLE, $ "MotoX3M",0);
		AddDefaultCamera(Camera::CAM_MODE_2D, windowWidth, windowHeight);
		
		AddResource(&bg, "Screen0", 1.);
		AddResource(&bal, "adidas_ball", 10.);
		bal.pos.x = windowWidth / 2;
		bal.pos.y = windowHeight / 2;
		AddResource(&bat, "paddle");
		bat.pos.x = windowWidth / 2;
		bat.pos.y = windowHeight - 50;
		AddResource(&bric, "brick");
		
		output.pushP(CMD_SNDSET0, "techno.wav");
		output.pushP(CMD_SNDSET1, "blip.wav");

		output.pushP(CMD_SNDPLAY0);
	
		f2 pos(windowWidth / 2, 50);
		for (int x = 100; x < windowWidth; x += 100) {
			pos.x = x;
			pos.y = 50;
			bric.AddInstance(pos);
			pos.y += 50;
			bric.AddInstance(pos);
			pos.y += 50;
			bric.AddInstance(pos);
		}
	}

};
