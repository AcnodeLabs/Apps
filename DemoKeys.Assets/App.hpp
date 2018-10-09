// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: Keys
*/

#include "../../Base/CBaseV1_2.h"

class App { 

public:
	PEG output;
	PEG input;
	char msg[64];
	
	void processInput() {
		PEG::CMD* p = input.pull();
		switch (p->command) {
			case CMD_KEYDOWN:
				sprintf(msg, "KeyCode=%d char='%c'", p->i1, AlKeyChar(p->i1));
				output.pushP(CMD_TOAST, $ msg, 0);
				break;
		}
	}
	
	void Render(float sec, int aX, int aY, int aZ) {		
		processInput();
	}

	void Init(char* path) {
		output.pushP(CMD_TOAST, $ "Press Any Key to Test",0);
	}

	void Deinit() {
	}


};
