/*
 *	singleton utils
 *
 *	by syalon
 */

#ifndef __AUX_SINGLETON_H__
#define __AUX_SINGLETON_H__

template <class T>

class AuxSingleton
{
protected:
	static T	*sInstance;

protected:

	AuxSingleton()
	{
		sInstance = (T*)(this);
	}

	~AuxSingleton()
	{
		sInstance = 0;
	}

public:
	static T* Instance()
	{
		if (sInstance)
			return sInstance;

		return new T();
	}

	static void Release()
	{
		if (sInstance)
		{
			delete sInstance;
			sInstance = 0;
		}
	}
};

template <class T>	T* AuxSingleton<T>::sInstance = 0;

#endif
