#pragma once
#include "GameObject.h"
#include "Items.h"

class BossBat :public CGameObject
{
	Items *item;
	bool isLeft = true;
	float simonX;
	float simonY;
	float randomX = 550.0f;
	float randomY = 300.0f;
	RECT r;
	//float tempX = 0.0f;
	//float tempY = 0.0f;
	int ny;

	int ani = BAT_RED_STATIC;

	bool isAction = false;
	bool isAttack = false;
	bool isRandomFly = false;
	bool isHIT = false;
	float deplayAttack = 5000.0f;

	float dirA, dirB;
	float distance;


public:

	virtual void LoadResource();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *coObjectStatic, vector<LPGAMEOBJECT> *coObjectEnemy);
	virtual void Render(float xViewport, float yViewport);
	void SetState(int state);
	void SetItem(Items *_item) { this->item = _item; }

	void UpdateLimit(float xViewport, float yViewport);
	void RandomPos();
	void RandomFly();
	void Action(float xViewport, float yViewport);
	void SetAction(bool _isAction) { this->isAction = _isAction; }
	bool GetAction() { return this->isAction; }
	void UpdatePosSimon(float _simonX, float _simonY);
	void AttackSimon();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};