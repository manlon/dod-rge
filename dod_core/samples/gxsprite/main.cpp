/**
 *	@file		main.cpp
 *
 *	@desc		DOD 2Dæ´¡È≤‚ ‘π§≥Ã
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11
 */
#include <DOD_Gx.h>

//	define the sample title
#define DOD_SAMPLE_TITLE "DOD_Sprite Test"

//	include common cpp
#include "../common.cpp"

#include <DOD_SceneManager.h>
#include <DOD_Sprite.h>

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();

	Dod::Dod_GxInit();

	Dod::DOD_Sprite*		pSpr = new Dod::DOD_Sprite();
	Dod::DOD_Bitmap*		pTex = Dod::DOD_Bitmap::Create("logo.png");

	pSpr->SetBitmap(pTex);

	pSpr->SetColor(0x00ff0000, 0);
	pSpr->SetColor(0x00ff00ff, 1);
	pSpr->SetColor(0x000000ff, 2);
	pSpr->SetColor(0x0000ff00, 3);

	while(!g_done)
	{
		Dod::Dod_GxBeginScene();
		Dod::Dod_GxGetSceneMgr()->Render();
		Dod::Dod_GxEndScene();
	}

	delete pSpr;
	SAFE_DESTROY(pTex);

	Dod::Dod_GxExit();

	sceKernelExitGame();

	return 0;
}
