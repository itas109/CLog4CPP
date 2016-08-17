#include "stdafx.h"
#include "CLog4CPP.h"

CLog4CPP::CLog4CPP()
{
	m_bEnable = FALSE;
	m_bPrintTime = TRUE;//默认加入时间戳
	m_csFileName = "";

	//初始化临界区
	InitializeCriticalSection(&m_crit);
}

CLog4CPP::~CLog4CPP()
{
	//释放临界区
	DeleteCriticalSection(&m_crit);
}

void CLog4CPP::Init()
{
	m_bEnable = TRUE;

	CTime t = CTime::GetCurrentTime();	

	std::string pOutputFilename;
	//用时间命名文件名称
	pOutputFilename = int2string(t.GetYear()) + "-" + int2string(t.GetMonth()) + "-" + int2string(t.GetDay()) + ".log";
	
	//获取程序路径和名称
	TCHAR m_ctsFileName[MAX_PATH] = {0};

	DWORD res = GetModuleFileName(AfxGetInstanceHandle(), m_ctsFileName, MAX_PATH);

	std::string path;

#ifdef UNICODE
	int iLen = WideCharToMultiByte(CP_ACP, 0,m_ctsFileName, -1, NULL, 0, NULL, NULL);
	char* chRtn =new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, m_ctsFileName, -1, chRtn, iLen, NULL, NULL);
	path = std::string(chRtn);
	delete chRtn;
	chRtn = NULL;
#else
	path = std::string(m_ctsFileName);
#endif
	std::string appDir = GetBaseDir(path);

	_mkdir("Log");//创建Log文件夹
	
	m_csFileName = appDir + "\\Log\\" + pOutputFilename;
}

void CLog4CPP::Init(std::string pOutputFilename)
{
	m_bEnable = TRUE;

	if(GetFileExtensions(pOutputFilename) == "")
	{
		pOutputFilename += ".log";
	}

	//获取程序路径和名称
	TCHAR m_ctsFileName[MAX_PATH] = {0};

	DWORD res = GetModuleFileName(AfxGetInstanceHandle(), m_ctsFileName, MAX_PATH);

	std::string path;

#ifdef UNICODE
	int iLen = WideCharToMultiByte(CP_ACP, 0,m_ctsFileName, -1, NULL, 0, NULL, NULL);
	char* chRtn =new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, m_ctsFileName, -1, chRtn, iLen, NULL, NULL);
	path = std::string(chRtn);
	delete chRtn;
	chRtn = NULL;
#else
	path = std::string(m_ctsFileName);
#endif
	std::string appDir = GetBaseDir(path);

	_mkdir("Log1");//创建Log文件夹

	m_csFileName = appDir + "\\Log\\" + pOutputFilename;
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
	FILE *fp = NULL;
	TCHAR wc[MAX_PATH] = {0};
#ifdef UNICODE
	_stprintf_s(wc, MAX_PATH, _T("%S"), m_csFileName.c_str());//%S宽字符
#else
	_stprintf_s(wc, MAX_PATH, _T("%s"), m_csFileName.c_str());//%s单字符
#endif
	_tfopen_s(&fp, wc, _T("a"));
	if (fp)
	{
		if (m_bPrintTime)
		{
			CTime ct ; 
			ct = CTime::GetCurrentTime();
			_ftprintf_s(fp,_T("%s : "),ct.Format("%Y-%m-%d %H:%M:%S"));
		}
#ifdef UNICODE
		_ftprintf_s(fp, _T("%S\n"), text.c_str());
#else
		_ftprintf_s(fp, _T("%s\n"), text.c_str());
#endif

		fclose(fp);

		fp = NULL;

		bOK = TRUE;
	}

	LeaveCriticalSection(&m_crit);

	return bOK;
}

std::string	CLog4CPP::GetFileExtensions(std::string &fileName)
{
	std::string out = fileName;

	int iSlashPos = fileName.find_last_of('\\');
	if (iSlashPos !=-1)
	{
		out = out.substr(iSlashPos+1);
	}
	else
	{
		iSlashPos = fileName.find_last_of('/');
		if (iSlashPos !=-1) 
		{
			out = out.substr(iSlashPos+1);
		}
	}

	int iDotPos = out.find_last_of('.');
	if (iDotPos>0)
	{
		out = out.substr(iDotPos);
	}
	else
	{
		out = "";
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

//int转string
std::string CLog4CPP::int2string(int in)
{
	stringstream ss;
	std::string str;
	ss << in;
	ss >> str;
	return str;
}
