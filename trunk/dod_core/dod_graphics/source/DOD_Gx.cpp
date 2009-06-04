#include "DOD_Gx.h"

#include "dod_debug.h"

#include "DOD_SceneManager.h"
#include "DOD_ObjManager.h"
#include "DOD_ResManager.h"

#include <pspge.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>

namespace Dod
{
namespace
{
	static bool					s_bGxInited = 0;
	
	static DOD_SceneManager*	s_pSceneMgr = NULL;
	static DOD_ObjManager*		s_pObjMgr 	= NULL;
	
	static u32 					s_lVramOffset = 0;
	
	static u32 dod_get_memory_size(u32 width, u32 height, u32 psm)
	{
		switch (psm)
		{
			case GU_PSM_T4:
				return (width * height) >> 1;

			case GU_PSM_T8:
				return width * height;

			case GU_PSM_5650:
			case GU_PSM_5551:
			case GU_PSM_4444:
			case GU_PSM_T16:
				return 2 * width * height;

			case GU_PSM_8888:
			case GU_PSM_T32:
				return 4 * width * height;

			default:
				return 0;
		}
	}

	static void* dod_get_static_vram_buffer(u32 width, u32 height, u32 psm)
	{
		u32 mem_size = dod_get_memory_size(width, height, psm);
		void* result = (void*)s_lVramOffset;
		s_lVramOffset += mem_size;
		return result;
	}

	static void* dod_get_static_vram_texture(u32 width, u32 height, u32 psm)
	{
		void* result = dod_get_static_vram_buffer(width, height, psm);
		return (void*)(((u32)result) + ((u32)sceGeEdramGetAddr()));
	}

	static u32 __attribute__((aligned(16)))	s_list[262144];
	
	static void dod_init_gu()
	{
		void* pDrawBuffer	= dod_get_static_vram_buffer(DOD_BUFFER_WIDTH, DOD_SCREEN_HEIGHT, GU_PSM_8888);
		void* pDispBuffer	= dod_get_static_vram_buffer(DOD_BUFFER_WIDTH, DOD_SCREEN_HEIGHT, GU_PSM_8888);
		void* pZBuffer		= dod_get_static_vram_buffer(DOD_BUFFER_WIDTH, DOD_SCREEN_HEIGHT, GU_PSM_4444);
		
		sceGuInit();
		sceGuStart(GU_DIRECT, s_list);
		
		sceGuDrawBuffer(GU_PSM_8888, pDrawBuffer, DOD_BUFFER_WIDTH);
		sceGuDispBuffer(DOD_SCREEN_WIDTH, DOD_SCREEN_HEIGHT, pDispBuffer, DOD_BUFFER_WIDTH);
		sceGuDepthBuffer(pZBuffer, DOD_BUFFER_WIDTH);
		
		sceGuOffset(2048 - (DOD_SCREEN_WIDTH / 2), 2048 - (DOD_SCREEN_HEIGHT / 2));
		sceGuViewport(2048, 2048, DOD_SCREEN_WIDTH, DOD_SCREEN_HEIGHT);
		sceGuDepthRange(65535, 0);
		
		sceGuScissor(0, 0, DOD_SCREEN_WIDTH, DOD_SCREEN_HEIGHT);
		sceGuEnable(GU_SCISSOR_TEST);
		
		sceGuEnable(GU_CULL_FACE);
	 	sceGuFrontFace(GU_CCW);
		
		sceGuShadeModel(GU_SMOOTH);

		//sceGuDepthFunc(GU_GEQUAL);
		//sceGuDepthMask(GU_TRUE);		// disable z-writes
		//sceGuEnable(GU_DEPTH_TEST);
		
		sceGuEnable(GU_TEXTURE_2D);
		//sceGuEnable(GU_CLIP_PLANES);
				
		sceGuDisable(GU_COLOR_TEST);
		sceGuDisable(GU_ALPHA_TEST);
		sceGuDisable(GU_CLIP_PLANES);
		

		// Lighting
		sceGuDisable(GU_LIGHTING);
		sceGuDisable(GU_LIGHT0);
		sceGuDisable(GU_LIGHT1);
		sceGuDisable(GU_LIGHT2);
		sceGuDisable(GU_LIGHT3);
		
		// Texturing
		sceGuTexWrap(GU_CLAMP, GU_CLAMP);
		sceGuTexFilter(GU_LINEAR, GU_LINEAR);
		sceGuTexOffset(0.f, 0.f);
		sceGuTexScale(1.f, 1.f);
		//sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
		//sceGuTexEnvColor(0xffffffff);
		
		//sceGuColor(0xffffffff);
		//sceGuAmbientColor(0xffffffff);

		// Blending
		//sceGuEnable(GU_BLEND);
		//sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
		//sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
		//sceGuTexFilter(GU_LINEAR, GU_LINEAR);
		sceGuDisable(GU_DITHER);

		sceGuFinish();
		sceGuSync(0,0);
		
		sceDisplayWaitVblankStart();
		sceGuDisplay(GU_TRUE);
	}
}

/**
 *	初始化DOD Graphics库
 */
void Dod_GxInit()
{
	if (s_bGxInited) return;
	{
		dod_init_gu();
		
		s_pSceneMgr = new DOD_SceneManager();
		s_pObjMgr = new DOD_ObjManager();
		
		Dod_CreateResManager();
	}
	s_bGxInited = true;
}

void Dod_GxBeginScene()
{
	sceGuStart(GU_DIRECT, s_list);	
	
	// clear screen

	//	test - -b

//	static struct tmp_vertex	lVertexs[] =
//	{		
//		{0,1.f,	-1.f,  1.f, 1.f},
//		{0,1.f,	1.f,   1.f, 1.f},
//		{0,1.f,	1.f,  -1.f, 1.f},
//		{0,1.f,	-1.f, -1.f, 1.f},
//		
//		{0,1.f,	-1.f,  1.f, -1.f},
//		{0,1.f,	1.f,  1.f, -1.f},
//		{0,1.f,	1.f, -1.f, -1.f},
//		{0,1.f,	-1.f, -1.f, -1.f},
//	};
//	static u16	lIndices[] =
//	{
//		0, 2, 1, 0, 3, 2,
//		4, 5, 7, 5, 6, 7,
//		0, 1, 4, 1, 5, 4,
//		3, 7, 2, 2, 7, 6,
//		0, 4, 7, 0, 7, 3,
//		1, 2, 6, 1, 6, 5
//	};
	
//	ScePspFVector3 pos = {-2.0f, 1.0f, 0.0f};
//	sceGuLight(0, GU_POINTLIGHT, GU_DIFFUSE_AND_SPECULAR, &pos);
//	sceGuLightColor(0, GU_DIFFUSE, 0xffff0000);
//	sceGuLightColor(0, GU_SPECULAR, 0xffffffff);
//	sceGuLightAtt(0, 0.0f, 1.0f, 0.0f);
	
/*	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

	sceGumMatrixMode(GU_VIEW);
	{
		//ScePspFVector3 pos = {3.0f,3.0f,3.0f};
		ScePspFVector3 pos = {0.0f,0.0f,1.5f};
		
		ScePspFVector3 up = {0.0f,1.0f,0.0f};
		ScePspFVector3 at = {0.0f,0.0f,0.0};
		
		sceGumLoadIdentity();
		sceGumLookAt(&pos, &at, &up);
	}
	
	sceGumMatrixMode(GU_MODEL);
	{
		static int val = 0;
	 //	ScePspFVector3 rot = {val * 0.3f * (GU_PI/180.0f), val * 0.7f * (GU_PI/180.0f), val * 1.3f * (GU_PI/180.0f)};
		sceGumLoadIdentity();
 	//	sceGumRotateXYZ(&rot);
 		++val;
	}*/
	
	//sceGumDrawArray(GU_TRIANGLES,GU_VERTEX_32BITF|GU_TRANSFORM_3D,3,0,vtxs); 
	//sceGumDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,36,lIndices,lVertexs); 
	//sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|pTex->m_display_mode|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,36,lIndices,lVertexs); 
//	sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|pTex->m_tf_mode|GU_VERTEX_32BITF|GU_TRANSFORM_3D,6,0,sVtx2); 

}

void Dod_GxEndScene()
{
 	sceGuFinish();
 	sceGuSync(0,0);

 	sceDisplayWaitVblankStart();
 	sceGuSwapBuffers();
}

/**
 *	退出DOD Graphics库
 */
void Dod_GxExit()
{
	sceGuTerm();
	
	SAFE_DELETE(s_pSceneMgr);
	SAFE_DELETE(s_pObjMgr);
	
	Dod_DestroyResManager();
}

/**
 *	获取DOD_SceneManager指针
 */
DOD_SceneManager* Dod_GxGetSceneMgr()
{
	return s_pSceneMgr;
}

/**
 *	获取DOD_ObjManager指针
 */
DOD_ObjManager* Dod_GxGetObjMgr()
{
	return s_pObjMgr;	
}

}
