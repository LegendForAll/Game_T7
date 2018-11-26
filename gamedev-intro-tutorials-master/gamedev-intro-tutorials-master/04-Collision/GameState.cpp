#include "GameState.h"

CGameState::CGameState()
{

}

CGameState::~CGameState()
{

}

void CGameState::InitState(LPDIRECT3DDEVICE9 dv, LPDIRECT3DSURFACE9 bb)
{

}

void CGameState::LoadState()
{
	CTextures * textures = CTextures::GetInstance();
	textures->loadResources();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
}

void CGameState::UpdateState(DWORD dt)
{
	//Update collision event
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coObjectsStatic;
	vector<LPGAMEOBJECT> coObjectsEnemy;

	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objecttsStatic.size();i++)
	{
		coObjectsStatic.push_back(objecttsStatic[i]);
	}

	for (int i = 0; i < objectsEnemy.size(); i++)
	{
		coObjectsEnemy.push_back(objectsEnemy[i]);
	}

	//Object Update
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects, &coObjectsStatic,&coObjectsEnemy);
	}

	//Enemy Update
	for (int i = 0; i < objectsEnemy.size(); i++)
	{
		objectsEnemy[i]->Update(dt, &coObjects, &coObjectsStatic, &coObjectsEnemy);
	}


	//keep simon center view port
	if (simon->x > SCREEN_WIDTH / 2 && !marioInView)
	{
		tilemap->SetViewportX(simon->x - SCREEN_WIDTH / 2);
		marioInView = true;
	}
	if (marioInView)
	{
		tilemap->SetViewportX(simon->x - SCREEN_WIDTH / 2);
	}

	//Check status keyboard vs SIMON update
	PollKeyboard();
	simon->KeyEventHandler();
}

void CGameState::RenderState(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 bb, LPD3DXSPRITE spriteHandler)
{
	//render
	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//map
		tilemap->Render(spriteHandler);

		//Render object normal
		for (int i = 1; i < objects.size(); i++)
		{
			objects[i]->Render(tilemap->GetViewportX(), tilemap->GetViewPortY());
		}

		//Render object static
		for (int i = 0; i < objecttsStatic.size(); i++)
		{
			objecttsStatic[i]->Render(tilemap->GetViewportX(), tilemap->GetViewPortY());
		}

		//Render object enemy
		for (int i = 0; i < objectsEnemy.size(); i++)
		{
			objectsEnemy[i]->Render(tilemap->GetViewportX(), tilemap->GetViewPortY());
		}

		//Render simon
		objects[0]->Render(tilemap->GetViewportX(), tilemap->GetViewPortY());

		spriteHandler->End();
		d3ddv->EndScene();

		d3ddv->Present(NULL, NULL, NULL, NULL);
	}
}
