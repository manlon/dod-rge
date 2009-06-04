#ifndef __DOD_GX_TYPES_H__
#define __DOD_GX_TYPES_H__

#include <psptypes.h>
#include <pspgu.h>

#include "dod_types.h"

namespace Dod
{

//===================
//	¸¨Öúºê£º×Ö½Ú¶ÔÆë
//===================
#define DOD_ALIGN_N(n, bits)	(((n) + (bits) - 1) & ~((bits) - 1))
#define	DOD_ALIGN_32(n)			DOD_ALIGN_N(n, 32)
#define DOD_ALIGN_16(n)			DOD_ALIGN_N(n, 16)

/*
 * Vertex order:
 * [for vertices(1-8)]
 * [weights (0-8)]
 * [texture uv]
 * [color]
 * [normal]
 * [vertex]
 * [/for]
 */
struct dod_vertex_tp
{
	f32				u, v;
	f32				x, y, z;
};
#define dod_vertex_tp_fvf	(GU_TEXTURE_32BITF | GU_VERTEX_32BITF)

struct dod_vertex_np
{
	f32				nx, ny, nz;
	f32				x, y, z;
};
#define dod_vertex_np_fvf	(GU_NORMAL_32BITF | GU_VERTEX_32BITF)

struct dod_vertex_tcp
{
	f32				u, v;
	u32 			color;
	f32				x, y, z;
};
#define dod_vertex_tcp_fvf	(GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF)

struct dod_vertex_tcnp
{
	f32				u, v;
	u32 			color;
	f32				nx, ny, nz;
	f32				x, y, z;
};
#define dod_vertex_tcnp_fvf	(GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_NORMAL_32BITF | GU_VERTEX_32BITF)

enum DOD_VERTEX_TYPE
{
	DOD_VT_TP = 0,
	DOD_VT_NP,
	DOD_VT_TCP,
	DOD_VT_NTCP
};

/*
struct dod_texture
{
	s32	format;
	s32	mipmap;
	s32	width, height, stride;
	void*	data;
};
*/
}	//	namespace Dod

#endif	//	__DOD_GX_TYPES_H__
