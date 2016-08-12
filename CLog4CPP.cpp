#include "stdafx.h"
#include "CLog4CPP.h"

CLog4CPP::CLog4CPP()
{
	m_bEnable = FALSE;
	m_bPrintTime = TRUE;//默认加入时间戳
	m_bPrintAppName = FALSE;
	m_csFileName = "";

	m_csAppName = "";

	//初始化临界区
	InitializeCriticalSection(&m_crit);
}

CLog4CPP::~CLog4CPP()
{
	//释放临界区
	DeleteCriticalSection(&m_crit);
}

void CLog4CPP::Init(std::string pOutputFilename)
{
	m_bEnable = TRUE;

	//获取程序路径和名称
	TCHAR m_ctsFileName[MAX_PATH];

	DWORD res = GetModuleFileName(AfxGetInstanceHandle(), m_ctsFileName, MAX_PATH);

	std::string path;

#ifdef UNICODE
	int iLen = WideCharToMultiByte(CP_ACP, 0,m_ctsFileName, -1, NULL, 0, NULL, NULL);
	char* chRtn =new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, m_ctsFileName, -1, chRtn, iLen, NULL, NULL);
	path = std::string(chRtn);
	delete chRtn;
#else
	path = std::string(m_ctsFileName);
#endif
	std::string appDir = GetBaseDir(path);

	m_csAppName = GetBaseName(path);
	
	m_csFileName = appDir + "\\" + pOutputFilename;
	
	// overwrite the old one!
	//remove(m_csFileName.c_str());
}

void CLog4CPP::IsEnable(BOOL bEnable)
{
	m_bEnable = bEnable;
}

BOOL CLog4CPP::LogOut(std::string text)
{
	if (m_csFileName.size() == 0)
		return FALSE;

	if (!m_bEnable)
		return TRUE;

	//if (!AfxIsValidString(text, -1))
	//	return FALSE;

	EnterCriticalSection(&m_crit);

	BOOL bOK = FALSE;

	// output 
	FILE *fp;
	TCHAR wc[MAX_PATH];
	_stprintf_s(wc,_T("%S"),m_csFileName.c_str());//
	
	_tfopen_s(&fp,wc,_T("a"));
	if (fp)
	{
		if (m_bPrintAppName)
		{
			_ftprintf_s(fp,_T("%s : "), m_csAppName);
		}

		if (m_bPrintTime)
		{
			CTime ct ; 
			ct = CTime::GetCurrentTime();
			_ftprintf_s(fp,_T("%s : "),ct.Format("%Y-%m-%d %H:%M:%S"));
		}

		TCHAR txt[MAX_PATH];
		_stprintf_s(txt,_T("%S"),text.c_str());
		_ftprintf_s(fp, _T("%s\n"), txt);		

		fclose(fp);

		bOK = TRUE;
	}

	LeaveCriticalSection(&m_crit);

	return bOK;
}

std::string	CLog4CPP::GetBaseName(std::string &path)
{
	std::string out = path;

	int iSlashPos = path.find_last_of('\\');
	if (iSlashPos !=-1) 
	{
		out = out.substr(iSlashPos+1);
	}
	else
	{
		iSlashPos = path.find_last_of('/');
		if (iSlashPos !=-1) 
		{
			out = out.substr(iSlashPos+1);
		}
	}

	int iDotPos = out.find_last_of('.');
	if (iDotPos>0)
	{
		out = out.substr(0,iDotPos);
	}

	return out;
}

std::string CLog4CPP::GetBaseDir(std::string & path)
{
	std::string out = path;
	int iSlashPos = path.find_last_of('\\');
	if (iSlashPos !=-1) 
	{
		out = path.substr(0,iSlashPos);
	} 
	else
	{
		iSlashPos = path.find_last_of('/');
		if (iSlashPos !=-1) 
		{
			out = path.substr(0,iSlashPos);
		} 
	}

	return out;
}
