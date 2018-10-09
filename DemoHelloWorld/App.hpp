// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: HelloWorld
*/

class App : public AlgeApp { 

public:
	void Render(float sec, int aX, int aY, int aZ) {}

	void Init(char* path) {
		output.pushP(CMD_TOAST, $ "Hello World !!", 0);
	}

	void Deinit() {}
};
