// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: Terrain Model
*/

enum {
 MODEL_TERRAIN,
 MODEL_SKYDOME,
 MODEL_BOY
} models;

class /*DemoTerrain*/ App : public AlgeApp { 

	GameObject SkyDome;
	GameObject Terrain;
	GameObject AstroBoy;
	ResourceInf rSkyDome;
	ResourceInf rTerrain;
	ResourceInf rAstroBoy;

public:

	void UpdateCustom(GameObject* gob, PEG::CMD* p) {
		edit = true;
		if (gob->custom_type==MODEL_TERRAIN) glRotatef(90, -1.0f, 0.0f, 0.0f);
		processInput(p);
	}


	virtual void Init(char* path) {
		alInit(STANDARD);
		
		output.pushP(CMD_TITLE, $ "Evolution",0);

		//To Save Position Info
		aCamera.SetSerializeTag("ACAMERA.GOB");
		aCamera.mode = Camera::CAM_MODE_FPS;
		AddObject(&aCamera);

		SkyDome.SetSerializeTag("SKYDOME.GOB");
		rSkyDome.Set("SkyDome", "skydome.alx", "skydome.tga", 0.1f);
		LoadModel(&SkyDome, &rSkyDome, MODEL_SKYDOME);
		AddObject(&SkyDome);

		Terrain.SetSerializeTag("TERR2.GOB");
		rTerrain.Set("Terr2", "terr2.alx", "terr2.tga", 20.f);
		LoadModel(&Terrain, &rTerrain, MODEL_TERRAIN);
		AddObject(&Terrain);
		selectedObject = &Terrain;
		
		AstroBoy.SetSerializeTag("BOY.GOB");
		rAstroBoy.Set("AstroBoy_Walk", "AstroBoy_Walk/astroBoy_walk_Max.dae", "", 1.f);
	//	LoadModel(&AstroBoy, &rAstroBoy, MODEL_BOY);
	//	AddObject(&AstroBoy);

	}

};
