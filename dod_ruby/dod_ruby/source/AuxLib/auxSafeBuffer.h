#ifndef __AUX_SAFE_BUFFER_H__
#define __AUX_SAFE_BUFFER_H__

#include <assert.h>
#include <malloc.h>

struct auxSafeBuffer
{
private:
	enum MEM_TYPE
	{
		MEM_TYPE_MALLOC = 0, 
		MEM_TYPE_NEW, 
		MEM_TYPE_NEW_ARRAY,
		MEM_TYPE_NEW_NONE
	};

private:
	void SafeFree()
	{
		if (m_ptr)
		{
			switch (m_ptr_type)
			{
				case MEM_TYPE_MALLOC:		free(m_ptr);		break;
				case MEM_TYPE_NEW:			delete m_ptr;		break;
				case MEM_TYPE_NEW_ARRAY:	delete [] m_ptr;	break;
			}
			m_ptr = 0;
			m_ptr_type = MEM_TYPE_NEW_NONE;
			m_size = 0;
		} 
	}

public:
	auxSafeBuffer() :
		m_ptr(0),
		m_ptr_type(MEM_TYPE_NEW_NONE),
		m_size(0)
	{
	}

	~auxSafeBuffer()
	{
		SafeFree();
	}

	unsigned char* GetPtr() const
	{
		return m_ptr;
	}

	unsigned long GetSize() const
	{
		return m_size;
	}

	bool Alloc(unsigned long size)
	{
		assert(size > 0);

		SafeFree();

		m_ptr = (unsigned char*)malloc(size);

		if (m_ptr)
		{
			m_ptr_type = MEM_TYPE_MALLOC;
			m_size = 0;
			return true;
		}
		else return false;
	}

	bool New(unsigned long size)
	{
		assert(size > 0);

		SafeFree();

		m_ptr = new unsigned char[size];

		if (m_ptr)
		{
			m_ptr_type = MEM_TYPE_NEW_ARRAY;
			m_size = size;
			return true;
		}
		else return false;
	}

private:
	unsigned char	*m_ptr;
	MEM_TYPE		m_ptr_type;
	unsigned long	m_size;
};

#endif

