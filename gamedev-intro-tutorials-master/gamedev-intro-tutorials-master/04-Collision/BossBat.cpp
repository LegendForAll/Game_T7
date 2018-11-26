#include "BossBat.h"
bool a = false;
void BossBat::LoadResource()
{
	//load resource zombie
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BOSSBAT, L"Resource\\sprites\\Bosses\\VAMPIRE_BAT.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DEAD, L"Resource\\sprites\\Effect\\DEAD.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texBoss = textures->Get(ID_TEX_BOSSBAT);


	sprites->Add(301, 0, 0, 100, 46, texBoss);		//boss static


	sprites->Add(302, 100, 0, 200, 46, texBoss);		//boss fly
	sprites->Add(303, 200, 0, 300, 46, texBoss);


	LPDIRECT3DTEXTURE9 texdead = textures->Get(ID_TEX_DEAD);
	//dead object
	sprites->Add(6000, 0, 0, 42, 44, texdead);
	sprites->Add(6001, 42, 0, 84, 44, texdead);
	sprites->Add(6002, 84, 0, 128, 44, texdead);

	LPANIMATION ani;
	CAnimations * animations = CAnimations::GetInstance();

	ani = new CAnimation(100);		//boss static
	ani->Add(301);
	animations->Add(BOSSBAT_STATIC, ani);


	ani = new CAnimation(100);		//boss fly
	ani->Add(302);
	ani->Add(303);
	animations->Add(BOSSBAT_FLY, ani);

	ani = new CAnimation(100);		//Dead
	ani->Add(6000);
	ani->Add(6001);
	ani->Add(6002);
	animations->Add(BOSSBAT_DIE, ani);

	this->AddAnimation(BOSSBAT_STATIC);
	this->AddAnimation(BOSSBAT_FLY);
	this->AddAnimation(BOSSBAT_DIE);
}

void BossBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coObjectStatic, vector<LPGAMEOBJECT>* coObjectEnemy)
{
	CGameObject::Update(dt);

	//Time deplay
	//if (isAction)
	//{
	//	deplayAttack -= 50.0f;
	//}

	deplayAttack -= 25.0f;

	//if (isAction)
	//{
	//	if (!a)
	//	{
	//		this->AttackSimon();
	//		a = true;
	//	}


	//	//tempX += dirA * vx * dt;
	//	//tempY += dirB * vy * dt;

	//	x += dirA * vx * dt;
	//	y += (dirB * vy * dt)/2;

	//	//this->x = tempX;
	//	//this->y = tempY/2;

	//	float testA = std::sqrt(std::pow(randomX - x, 2) + std::pow(randomY - y, 2));

	//	if (testA >= distance)
	//	{
	//		this->vx = 0;
	//		this->vy = 0;
	//	}
	//}

	this->RandomFly();


}

void BossBat::Render(float xViewport, float yViewport)
{
	//Update action
	this->Action(xViewport, yViewport);

	//Update state
	//this->SetState(this->state);

	//Update limit
	this->UpdateLimit(xViewport, yViewport);

	int alpha = 255;
	this->isLeft = this->nx == 1 ? true : false;

	this->X_view = x - xViewport;
	this->Y_view = y - yViewport;

	if (!(isDead && isvisible))
	{
		animations[ani]->Render(x - xViewport, y - yViewport, alpha, this->isLeft);
		RenderBoundingBox();
	}
}

void BossBat::SetState(int state)
{
	CGameObject::SetState(state);

	switch (this->state)
	{
		case BOSSBAT_STATIC:
		{
			ani = BOSSBAT_STATIC;
			//if (isAction)
			{
				this->state = BOSSBAT_FLY;
				ani = BOSSBAT_FLY;
				break;
			}
			break;
		}
		case BOSSBAT_FLY:
		{
			//vx = 0;
			//vy = 0;

			if (deplayAttack < 0 && !isAttack)
			{
				this->isAttack = true;
				this->state = BOSSBAT_ATTACK;
				break;
			}
			break;
		}

		case BOSSBAT_ATTACK:
		{
			this->AttackSimon();
			if (isHIT)
			{
				deplayAttack = 5000.0f;
				this->state = BOSSBAT_FLY;
				ani = BOSSBAT_FLY;
				isAttack = false;
				isHIT = false;
				break;
			}
			
			break;
		}
	}
}

void BossBat::UpdateLimit(float xViewport, float yViewport)
{
	r.left = xViewport;
	r.top = yViewport + 200.0f;
	r.right = r.left + SCREEN_WIDTH;
	r.bottom = r.top + SCREEN_HEIGHT;

	if (this->x <= r.left || this->x >= r.right)
	{
		this->vx = 0;
		this->isRandomFly = false;
		//this->deplayAttack = 5000.0f;
	}
	if (this->y <= r.top || this->y >= r.bottom)
	{
		this->vy = 0;
		this->isRandomFly = false;
		//this->deplayAttack = 5000.0f;
	}
}

void BossBat::RandomPos()
{
	if (deplayAttack <= 0.0f)
	{
		//this->randomX = std::rand() % (r.right - r.left) + r.left;
		//this->randomY = std::rand() % (r.bottom - r.top) + r.top + 200 ;
		//this->isRandomFly = true;
		deplayAttack = 5000.0f;
	}
	//this->isRandomFly = true;
	//this->randomX = 300;
	//this->randomY = 300;
	
}

void BossBat::RandomFly()
{
	//this->RandomPos();
	//if (isRandomFly)
	{
		this->distance = std::sqrt(std::pow(randomX - this->x, 2) + std::pow(randomY - this->y, 2));
		this->dirA = (randomX - x) / distance;
		this->dirB = (randomY - y) / distance;

		x += dirA * vx * dt;
		y += (dirB * vy * dt);

		float testA = std::sqrt(std::pow(randomX - x, 2) + std::pow(randomY - y, 2));
		if (testA >= distance)
		{
			this->vx = 0;
			this->vy = 0;
			this->isRandomFly = false;
		}
	}
}

void BossBat::Action(float xViewport, float yViewport)
{
	if ((this->x - (xViewport + SCREEN_WIDTH / 2)) <= DIS_BOSSBAT_ATTACK)
	{
		this->isAction = true;
	}
}

void BossBat::UpdatePosSimon(float _simonX, float _simonY)
{
	if (this->isAction && !isDead)
	{
		this->simonX = _simonX;
		this->simonY = _simonY;

	}
}

void BossBat::AttackSimon()
{
	if (!isAttack)
	{

		distance = std::sqrt(
			std::pow(randomX - this->x, 2) +
			std::pow(randomY - this->y, 2));
		//this->nx = x - simonX < 0 ? 1 : -1;
		//this->ny = y - simonY < 0 ? 1 : -1;
		//this->vx = nx * BOSSBAT_SPEED_X;
		//this->vy = ny * BOSSBAT_SPEED_Y;

		this->dirA = (randomX - x) / distance;
		this->dirB = (randomY - y) / distance;

		//this->dirA = (randomX - x);
		//this->dirB = (randomY - y);
		
		//if (x >= simonX && y >= simonY)
		//{
		//	isHIT = true;
		//}
		isAttack = true;
	}

}

void BossBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDead)
	{
		left = x;
		top = y;
		right = left + BOSSBAT_BBOX_WIDTH;
		bottom = top + BOSSBAT_BBOX_HEIGHT;
	}
}
