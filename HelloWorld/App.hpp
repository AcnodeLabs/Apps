// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: HelloWorld
*/

#include "../../SDKSRC/Base/CBaseV1_2.h"

class App { 

public:
	PEG output;
	PEG input;
	CResourceManager rm;
	
    void Render(float sec, int aX, int aY, int aZ) {}

	void Init(char* path) {
		output.pushP(CMD_TOAST, $ "Hello World !!", 0);
	}

	void Deinit() {}
};
