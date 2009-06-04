#include "DOD_Texture.h"
#include "DOD_Bitmap.h"

#include "DOD_ResManager.h"

#include "dod_macros.h"

namespace Dod
{
namespace
{
	const char *s_filename = "test.png";
}

void CreateTexture()
{
	DOD_Texture *pTex = DOD_Texture::Create(s_filename);

 	SAFE_DESTROY(pTex);
 	
 	DOD_Bitmap*	btm = DOD_Bitmap::Create(s_filename);
 	SAFE_DESTROY(btm);
}
}
