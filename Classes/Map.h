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
	bool NextStage(Vec2 tVec);
	TMXTiledMap* GetTMX();
	int CheckAttribute(Vec2 tVec);

	Vec2 HeroSpawn();
	Vec2 PacManSpawn();

	Vec2 SavePointPos(int ObjectNum);
	Vec2 PlatformPos(int ObjectNum);
	Vec2 JumpPointPos(int ObjectNum);
	//오브젝트 초기 배치 좌표

	CSavePoint* GetSavePtr(int index);
	CPlatform* GetPlatformPtr(int index);
	CJumpPoint* GetJumpPtr(int Index);
	//오브젝트 객체 포인터 

	int GetSavePointNum();
	int GetPlatformNum();
	int GetJumpPointNum();
	//각 오브젝트의 개수 체크
	
	
	

	


};

