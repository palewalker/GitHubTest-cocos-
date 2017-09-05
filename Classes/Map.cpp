#include "Map.h"
#include "CSavePoint.h"
#include "CPlatform.h"
#include "CJumpPoint.h"

CMap::CMap()
{

}

CMap::~CMap()
{

}

void CMap::Create(Layer *tpLayer, int StageNum)
{
	
	char tszTemp[512];
	memset(tszTemp, 0, 512);
	sprintf(tszTemp, "Stage%d.tmx", StageNum);
	string tString = tszTemp;

	tMap = TMXTiledMap::create(tString);
	tMap->setAnchorPoint(Vec2(0.0f, 0.0f));

	tpLayer->addChild(tMap, 1);

	memset(tszTemp, 0, 512);
	sprintf(tszTemp, "BackGround%d.png", StageNum);
	tString = tszTemp;

	mpBg = Sprite::create(tString);
	mpBg->setAnchorPoint(Vec2(0.0f, 0.0f));

	tpLayer->addChild(mpBg, 0);
	Vec2 tVec;
	NextStage(tVec);

	//맵에서의 오브젝트 생성
	
	TMXObjectGroup *tSaveObject = tMap->getObjectGroup("SavePoint");
	SaveNum = tSaveObject->getObjects().size();
	tpSavepoint = new CSavePoint*[SaveNum];
	for (int i = 0; i < SaveNum; i++)
	{
		tpSavepoint[i] = new CSavePoint();
		tpSavepoint[i]->Create(this, tpLayer, i);
	}

	TMXObjectGroup *tPlatFormObject = tMap->getObjectGroup("Float");
	PlatformNum = tPlatFormObject->getObjects().size();
	tpPlatform = new CPlatform*[PlatformNum];

	for (int i = 0; i < PlatformNum; i++)
	{
		tpPlatform[i] = new CPlatform();
		tpPlatform[i]->Create(this, tpLayer, i);
	}


	TMXObjectGroup *tJumpPointObject = tMap->getObjectGroup("Jump");
	MultiJumpNum = tJumpPointObject->getObjects().size();
	tpJumppoint = new CJumpPoint*[MultiJumpNum];

	for (int i = 0; i < MultiJumpNum; i++)
	{
		tpJumppoint[i] = new CJumpPoint();
		tpJumppoint[i]->Create(this, tpLayer, i);
	}
	

}


int CMap::GetAttribute(int tRow, int tCol)
{
	int tResult = 0;

	//tCol = 0;
	//tRow = 0;

	int tGID = tMap->getLayer("TileLayer")->
		getTileGIDAt(Vec2(tCol, tRow));
	Value tValue = tMap->getPropertiesForGID(tGID);
	

	if (false == tValue.isNull())
	{
		tResult = tValue.asValueMap()["Attrib"].asInt();
	

	}

	return tResult;
}
Vec2 CMap::HeroSpawn()
{
	TMXObjectGroup *tObj = tMap->getObjectGroup("SpawnPos");


	ValueMap tSpawnPositionActor = tObj->getObject("Hero_Spawn");
	


	int tX = tSpawnPositionActor["x"].asInt();
	int tY = tSpawnPositionActor["y"].asInt();


	Vec2 tVec;
	tVec.x = tX;
	tVec.y = tY;

	return tVec;

}

Vec2 CMap::PacManSpawn()
{
	TMXObjectGroup *tObj = tMap->getObjectGroup("SpawnPos");


	ValueMap tSpawnPositionActor = tObj->getObject("PacMan_Spawn");

	int tX = tSpawnPositionActor["x"].asInt();
	int tY = tSpawnPositionActor["y"].asInt();


	Vec2 tVec;
	tVec.x = tX;
	tVec.y = tY;

	return tVec;
}
bool CMap::NextStage(Vec2 tVec)
{
	bool tResult = false;

	TMXObjectGroup *tObj = tMap->getObjectGroup("Map_Replace");


	ValueMap tSpawnPositionActor = tObj->getObject("NextStage");

	

	int tX = tSpawnPositionActor["x"].asInt();
	int tY = tSpawnPositionActor["y"].asInt();


	float tWidth = tSpawnPositionActor["width"].asFloat();
	float tHeight = tSpawnPositionActor["height"].asFloat();


	//bug_stageskip

	if (((tX + tWidth / 2 >= tVec.x )&& (tVec.x >= tX - tWidth / 2)) &&
		((tY + tHeight / 2 >= tVec.y )&& (tVec.y >= tY - tHeight / 2)))
	{
		//return true;
		tResult = true;
	}

	return tResult;
}

TMXTiledMap* CMap::GetTMX()
{
	return tMap;
}

//타일의 attrib
int CMap::CheckAttribute(Vec2 tVec)
{
	auto tPosInNode = tVec;

	float tTileW = tMap->getTileSize().width;
	float tTileH = tMap->getTileSize().height;

	float tTotalRowCount = tMap->getMapSize().height;

	int tCol = tPosInNode.x / tTileW;
	int tRow = tTotalRowCount - tPosInNode.y / tTileH;



	tCol = tVec.x;
	tRow = tVec.y;

	int tAttribute = GetAttribute(tRow, tCol);
	

	return tAttribute;

	
}

//오브젝트 레이어의 좌표값
Vec2 CMap::SavePointPos(int ObjectNum)
{
	char tszTemp[512];
	memset(tszTemp, 0, 512);
	sprintf(tszTemp, "Save%d", ObjectNum);
	string tString = tszTemp;

	TMXObjectGroup *tObj = tMap->getObjectGroup("SavePoint");


	ValueMap tSpawnPositionActor = tObj->getObject(tString);

	int tX = tSpawnPositionActor["x"].asInt();
	int tY = tSpawnPositionActor["y"].asInt();


	Vec2 tVec;
	tVec.x = tX;
	tVec.y = tY;

	return tVec;
}

Vec2 CMap::PlatformPos(int ObjectNum)
{
	char tszTemp[512];
	memset(tszTemp, 0, 512);
	sprintf(tszTemp, "float%d", ObjectNum);
	string tString = tszTemp;

	TMXObjectGroup *tObj = tMap->getObjectGroup("Float");


	ValueMap tSpawnPositionActor = tObj->getObject(tString);

	int tX = tSpawnPositionActor["x"].asInt();
	int tY = tSpawnPositionActor["y"].asInt();


	Vec2 tVec;
	tVec.x = tX;
	tVec.y = tY;

	return tVec;
}

Vec2 CMap::JumpPointPos(int ObjectNum)
{
	char tszTemp[512];
	memset(tszTemp, 0, 512);
	sprintf(tszTemp, "jump%d", ObjectNum);
	string tString = tszTemp;

	TMXObjectGroup *tObj = tMap->getObjectGroup("Jump");


	ValueMap tSpawnPositionActor = tObj->getObject(tString);

	int tX = tSpawnPositionActor["x"].asInt();
	int tY = tSpawnPositionActor["y"].asInt();


	Vec2 tVec;
	tVec.x = tX;
	tVec.y = tY;

	return tVec;
}

//배열로 이루어진 오브젝트의 객체를 각각 받아오기 위한 함수
CSavePoint* CMap::GetSavePtr(int Index)
{
	return tpSavepoint[Index];
}

CPlatform* CMap::GetPlatformPtr(int index)
{
	return tpPlatform[index];
}

CJumpPoint* CMap::GetJumpPtr(int Index)
{
	return tpJumppoint[Index];
}

//오브젝트 객체 배열의 인덱스 
int CMap::GetSavePointNum()
{
	return SaveNum;
}

int CMap::GetPlatformNum()
{
	return PlatformNum;
}

int CMap::GetJumpPointNum()
{
	return MultiJumpNum;
}

