#ifndef __DOD_CLR_HOST_H__
#define __DOD_CLR_HOST_H__

#include <atlcomcli.h>
#include <windows.h>
#include <mscoree.h>
#import "mscorlib.tlb" rename("ReportEvent", "ReportEvent_")
#pragma comment(lib, "mscoree.lib")

class DodClrHost
{
public:
	DodClrHost() : m_pCorHost(NULL), m_pAppDomain(NULL), m_pDispatch(NULL), m_started(false)
	{}

	~DodClrHost()
	{ Stop(); }

public:
	bool							Start();
	void							Stop();
	void							AddSearchPath(_bstr_t Path);
	CComPtr<IDispatch>&				CreateInstance(_bstr_t AssemblyName, _bstr_t typeName);

private:
	CComPtr<ICorRuntimeHost>		m_pCorHost;
	CComPtr<mscorlib::_AppDomain>	m_pAppDomain;
	CComPtr<IDispatch>				m_pDispatch;

	bool							m_started;
};

#endif	//	__DOD_CLR_HOST_H__