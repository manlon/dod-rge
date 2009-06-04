/*
 *	@file 		DOD_FileFormat.h
 *
 *	@desc		DODһЩ�ļ���ʽ�Ķ����ļ�
 *
 *	@author		syalon
 *
 *	@history	2009/05/12	����
 */
 
#ifndef __DOD_FILE_FORMAT_H__
#define __DOD_FILE_FORMAT_H__

#include "dod_types.h"

namespace Dod
{
//********************************************************************************
//	DOD��̬ģ�͸�ʽ�ļ�(DMDL)
//
//	�ļ��洢��ʽ:
//		|---dod_dmdl_header---|---node1---|---node2---| ���� |---nodeN---|---nodedata---| ���� material & texture ���� |---dod_dmdl_tailer---|
//********************************************************************************

//	DMDL�ļ�ħ������
#define	DOD_DMDL_MAGIC_NUM			(('L' << 24) | ('D' << 16) | ('M' << 8) | 'D')

//	DMDL�ļ���ǰ�汾��Ϣ
#define	DOD_DMDL_VERSION_H			1
#define	DOD_DMDL_VERSION_L			0

#define DOD_DMDL_MAKE_VERSION(h, l)	(((h) << 16) | (l))

#define DOD_DMDL_VERSION			DOD_DMDL_MAKE_VERSION(DOD_DMDL_VERSION_H, DOD_DMDL_VERSION_L)

#define	DOD_DMDL_GET_VERSION_H(v)	(((v) & 0xFFFF0000) >> 16)
#define	DOD_DMDL_GET_VERSION_L(v)	((v) & 0x0000FFFF)

#define DOD_DMDL_CHECK_VERSION(ver)	((DOD_DMDL_GET_VERSION_H((ver)) < DOD_DMDL_VERSION_H) ||		\
										(DOD_DMDL_GET_VERSION_H((ver)) == DOD_DMDL_VERSION_H &&		\
											DOD_DMDL_GET_VERSION_L((ver)) <= DOD_DMDL_VERSION_L))

//	DMDL���õ���һЩ�����ַ����ĳ���
#define DOD_DMDL_NAME_LENGTH		(16)

/*
 *	DMDL2ά�����ṹ��
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
 *	DMDL3ά�����ṹ��
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
 *	DMDL4ά�����ṹ��
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
 *	DMDL4x4����ṹ��
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
 *	DMDL��������ṹ��
 */
struct dod_tex_coord
{
	f32	u, v;
};

/*
 *	DMDL������Ϣ�ṹ��
 */
struct dod_dmdl_material
{
	dod_vector4	ambient;
	dod_vector4	diffuse;
	dod_vector4	specular;
	dod_vector4	emissive;
};

/*
 *	DMDL������Ϣ�ṹ��
 */
struct dod_dmdl_texture
{
	u8	tex_name[DOD_DMDL_NAME_LENGTH];
};

/*
 *	DMDL������Ϣ�ṹ��
 */
struct dod_dmdl_vertex
{
	dod_tex_coord	texcoord;
	dod_vector3		normal;
	dod_vector3		position;
};

/*
 *	DMDL���������νṹ��
 */
struct dod_dmdl_vertex_triangle
{
	dod_dmdl_vertex	vertexs[3];
};

/*
 *	DMDL���������νṹ��
 */
struct dod_dmdl_index_triangle
{
	u32	indices[3];
};

/*
 *	DMDL�ļ�ͷ�ṹ��
 */
struct dod_dmdl_header
{
	u32								magic_number;							//	ħ������
	u32								version;								//	�汾��Ϣ
	u32								file_size;								//	�ļ�ʵ���ֽ���

	u8								model_name[DOD_DMDL_NAME_LENGTH];		//	ģ������

	u32								node_count;								//	ģ�ͽ����Ŀ
	union
	{
		s32							root_node_id;							//	ģ�͸����ID
		struct dod_dmdl_node*		p_root_node;							//	���ڵ�ָ��
	};

	u32								material_count;							//	ģ�Ͳ�����Ŀ
	union
	{
		u32							material_offset;						//	�������ļ��е�ƫ�Ƶ�ַ
		dod_dmdl_material*			p_material_list;						//	�����б�ָ��
	};

	u32								texture_count;							//	ģ��������Ŀ
	union
	{
		u32							texture_offset;							//	�������ļ��е�ƫ�Ƶ�ַ
		dod_dmdl_texture*			p_texture_list;							//	�����б�ָ��
	};
};

/*
 *	DMDL������ݽṹ��
 */
struct dod_dmdl_node
{
	union
	{
		s32							parent_node_id;							//	�����ID
		struct dod_dmdl_node*		p_parent_node;							//	�����ָ��
	};

	s32								node_id;								//	���ID
	u8								node_name[DOD_DMDL_NAME_LENGTH];		//	�������
		
	u32								vertex_count;							//	������Ŀ
	union
	{
		u32							vertex_offset;							//	�������ļ��е�ƫ�Ƶ�ַ
		dod_dmdl_vertex*			p_vertex_list;							//	�����б�����
	};
	
	u32								triangle_count;							//	��������Ŀ
	union
	{
		u32							triangle_offset;						//	���������ļ��е�ƫ�Ƶ�ַ
		dod_dmdl_index_triangle*	p_triangle_list;						//	�������б�����
	};
	
	dod_matrix4x4					transformation_matrix;					//	����ڸ����ı任����
	u32								material_index;							//	�ý���õ��ò�������
	u32								texture_index;							//	�ý���õ�����������

	u32								child_node_count;						//	�ӽ����Ŀ
	union
	{
		u32							child_node_id_offset;					//	�ӽ��ID���ļ��е�ƫ�Ƶ�ַ
		struct dod_dmdl_node** 		p_child_node_list;						//	�ӽ���б�ָ��
	};
};

/*
 *	DMDL�ļ�β�ṹ��
 */
struct dod_dmdl_tailer
{
	u32	reserved[4];														//	�����ֶ�
};

}	//	namespace Dod

#endif	//	__DOD_FILE_FORMAT_H__
