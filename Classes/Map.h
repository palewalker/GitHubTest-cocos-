#pragma once
#include "cocos2d.h"


using namespace cocos2d;
using namespace std;

class CSavePoint;
class CJumpPoint;
class CPlatform;

class CMap
{
protected:
	
	TMXTiledMap *tMap = NULL;
	Sprite *mpBg = NULL;
	CSavePoint **tpSavepoint;
	CPlatform  **tpPlatform;
	CJumpPoint **tpJumppoint;
	
	int SaveNum;
	int PlatformNum;
	int MultiJumpNum;

public:
	CMap();
	~CMap();

	void Create(Layer *tpLayer, int StageNum);
	int GetAttribute(int tRow, int tCol);
	Vec2 HeroSpawn();
	bool NextStage(Vec2 tVec);
	TMXTiledMap* GetTMX();
	int CheckAttribute(Vec2 tVec);

	Vec2 SavePointPos(int ObjectNum);
	Vec2 PlatformPos(int ObjectNum);
	Vec2 JumpPointPos(int ObjectNum);

	CSavePoint* GetSavePtr(int index);
	CPlatform* GetPlatformPtr(int index);
	CJumpPoint* GetJumpPtr(int Index);

	int GetSavePointNum();
	int GetPlatformNum();
	int GetJumpPointNum();

	
	
	

	


};

