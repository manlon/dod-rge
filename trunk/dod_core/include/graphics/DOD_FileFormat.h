/*
 *	@file 		DOD_FileFormat.h
 *
 *	@desc		DOD一些文件格式的定义文件
 *
 *	@author		syalon
 *
 *	@history	2009/05/12	初版
 */
 
#ifndef __DOD_FILE_FORMAT_H__
#define __DOD_FILE_FORMAT_H__

#include "dod_types.h"

namespace Dod
{
//********************************************************************************
//	DOD静态模型格式文件(DMDL)
//
//	文件存储格式:
//		|---dod_dmdl_header---|---node1---|---node2---| …… |---nodeN---|---nodedata---| …… material & texture …… |---dod_dmdl_tailer---|
//********************************************************************************

//	DMDL文件魔法数字
#define	DOD_DMDL_MAGIC_NUM			(('L' << 24) | ('D' << 16) | ('M' << 8) | 'D')

//	DMDL文件当前版本信息
#define	DOD_DMDL_VERSION_H			1
#define	DOD_DMDL_VERSION_L			0

#define DOD_DMDL_MAKE_VERSION(h, l)	(((h) << 16) | (l))

#define DOD_DMDL_VERSION			DOD_DMDL_MAKE_VERSION(DOD_DMDL_VERSION_H, DOD_DMDL_VERSION_L)

#define	DOD_DMDL_GET_VERSION_H(v)	(((v) & 0xFFFF0000) >> 16)
#define	DOD_DMDL_GET_VERSION_L(v)	((v) & 0x0000FFFF)

#define DOD_DMDL_CHECK_VERSION(ver)	((DOD_DMDL_GET_VERSION_H((ver)) < DOD_DMDL_VERSION_H) ||		\
										(DOD_DMDL_GET_VERSION_H((ver)) == DOD_DMDL_VERSION_H &&		\
											DOD_DMDL_GET_VERSION_L((ver)) <= DOD_DMDL_VERSION_L))

//	DMDL中用到的一些文字字符串的长度
#define DOD_DMDL_NAME_LENGTH		(16)

/*
 *	DMDL2维向量结构体
 */
struct dod_vector2
{
	union
	{
		struct
		{
			f32	x, y;
		};
		f32				f[2];
	//	ScePspFVector2	vec;
	};
};

/*
 *	DMDL3维向量结构体
 */
struct dod_vector3
{
	union
	{
		struct
		{
			f32 x, y, z;
		};
		f32				f[3];
	//	ScePspFVector3	vec;
	};
};

/*
 *	DMDL4维向量结构体
 */
struct dod_vector4
{
	union
	{
		struct
		{
			f32	x, y, z, w;
		};
		f32	f[4];
	};
};

/*
 *	DMDL4x4矩阵结构体
 */
struct dod_matrix4x4
{
	union
	{
		struct
		{
			f32 _00, _01, _02, _03;
			f32 _10, _11, _12, _13;
			f32 _20, _21, _22, _23;
			f32 _30, _31, _32, _33;
		};
		f32	m2[4][4];
		f32	m1[16];
	};
};

/*
 *	DMDL纹理坐标结构体
 */
struct dod_tex_coord
{
	f32	u, v;
};

/*
 *	DMDL材质信息结构体
 */
struct dod_dmdl_material
{
	dod_vector4	ambient;
	dod_vector4	diffuse;
	dod_vector4	specular;
	dod_vector4	emissive;
};

/*
 *	DMDL纹理信息结构体
 */
struct dod_dmdl_texture
{
	u8	tex_name[DOD_DMDL_NAME_LENGTH];
};

/*
 *	DMDL顶点信息结构体
 */
struct dod_dmdl_vertex
{
	dod_tex_coord	texcoord;
	dod_vector3		normal;
	dod_vector3		position;
};

/*
 *	DMDL顶点三角形结构体
 */
struct dod_dmdl_vertex_triangle
{
	dod_dmdl_vertex	vertexs[3];
};

/*
 *	DMDL索引三角形结构体
 */
struct dod_dmdl_index_triangle
{
	u32	indices[3];
};

/*
 *	DMDL文件头结构体
 */
struct dod_dmdl_header
{
	u32								magic_number;							//	魔法数字
	u32								version;								//	版本信息
	u32								file_size;								//	文件实际字节数

	u8								model_name[DOD_DMDL_NAME_LENGTH];		//	模型名字

	u32								node_count;								//	模型结点数目
	union
	{
		s32							root_node_id;							//	模型根结点ID
		struct dod_dmdl_node*		p_root_node;							//	根节点指针
	};

	u32								material_count;							//	模型材质数目
	union
	{
		u32							material_offset;						//	材质在文件中的偏移地址
		dod_dmdl_material*			p_material_list;						//	材质列表指针
	};

	u32								texture_count;							//	模型纹理数目
	union
	{
		u32							texture_offset;							//	纹理在文件中的偏移地址
		dod_dmdl_texture*			p_texture_list;							//	纹理列表指针
	};
};

/*
 *	DMDL结点数据结构体
 */
struct dod_dmdl_node
{
	union
	{
		s32							parent_node_id;							//	父结点ID
		struct dod_dmdl_node*		p_parent_node;							//	父结点指针
	};

	s32								node_id;								//	结点ID
	u8								node_name[DOD_DMDL_NAME_LENGTH];		//	结点名字
		
	u32								vertex_count;							//	顶点数目
	union
	{
		u32							vertex_offset;							//	顶点在文件中的偏移地址
		dod_dmdl_vertex*			p_vertex_list;							//	顶点列表数据
	};
	
	u32								triangle_count;							//	三角形数目
	union
	{
		u32							triangle_offset;						//	三角形在文件中的偏移地址
		dod_dmdl_index_triangle*	p_triangle_list;						//	三角形列表数据
	};
	
	dod_matrix4x4					transformation_matrix;					//	相对于父结点的变换矩阵
	u32								material_index;							//	该结点用到得材质索引
	u32								texture_index;							//	该结点用到得纹理索引

	u32								child_node_count;						//	子结点数目
	union
	{
		u32							child_node_id_offset;					//	子结点ID在文件中的偏移地址
		struct dod_dmdl_node** 		p_child_node_list;						//	子结点列表指针
	};
};

/*
 *	DMDL文件尾结构体
 */
struct dod_dmdl_tailer
{
	u32	reserved[4];														//	保留字段
};

}	//	namespace Dod

#endif	//	__DOD_FILE_FORMAT_H__
