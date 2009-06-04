#ifndef __DOD_GX_H__
#define __DOD_GX_H__

#include <psptypes.h>

#include "dod_macros.h"
#include "DOD_Gxtypes.h"

namespace Dod
{
#define	DOD_BUFFER_WIDTH	(512)
#define DOD_SCREEN_WIDTH	(480)
#define	DOD_SCREEN_HEIGHT	(272)

class DOD_SceneManager;
class DOD_ObjManager;

#ifdef __cplusplus
extern "C" {
#endif

void						Dod_GxInit();
void						Dod_GxExit();
void 						Dod_GxBeginScene();
void						Dod_GxEndScene();
DOD_SceneManager*			Dod_GxGetSceneMgr();
DOD_ObjManager*				Dod_GxGetObjMgr();

#ifdef __cplusplus
}
#endif
}

#endif
