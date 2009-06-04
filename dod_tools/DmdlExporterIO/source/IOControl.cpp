#include "IIOControl.h"

HRESULT STDMETHODCALLTYPE IOControl::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject)
{
 	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown*)this;
	}
 	else if (riid == IID_IDispatch)
	{
		*ppvObject = (IDispatch*)this;
	}
	else if (riid == __uuidof(IIOControl))
	{
		*ppvObject = (IIOControl*)this;
	}
	else
	{
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

ULONG STDMETHODCALLTYPE IOControl::AddRef(void)
{
	return ++m_dwRef;
}

ULONG STDMETHODCALLTYPE IOControl::Release(void)
{
	if (m_dwRef == 0)
		return 0;
	if (--m_dwRef == 0)
	{
		delete this;
		return 0;
	}
	return m_dwRef;
}