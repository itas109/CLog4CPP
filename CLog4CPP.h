/*
**************************************************************************************
**
**	FILENAME			CLog4CPP.h
**
**	PURPOSE				这是一个C++的日志工具类
**
**	CREATION DATE		2016-08-12
**
**	AUTHOR				itas109
**
**  Blog                http://blog.csdn.net/itas109
**
**  Git                 https://github.com/itas109
**
**************************************************************************************
*/
#ifndef CLOG4CPP_H
#define CLOG4CPP_H

#include<string>

class CLog4CPP
{
public:

	CLog4CPP();
	~CLog4CPP();

	//初始化
	void Init(std::string stringpOutputFilename);

	//输出文字，类似与TRACE、printf
	BOOL LogOut(std::string text);

	//设置使能
	void IsEnable(BOOL bEnable);

	//是否在每行加入时间戳
	void IsPrintTime(BOOL b) {m_bPrintTime = b;}

	//是否在每行加入程序名称
	void IsPrintAppName(BOOL b) {m_bPrintAppName = b;}

	//设置程序名称 
	void SetAppName(const char *pName) {m_csAppName = pName;}

protected:
	//缓冲区
	enum {TBUF_SIZE = 3000};
	std::string m_tBuf[TBUF_SIZE];

	std::string m_csAppName;
	std::string m_csFileName;
	

	//临界区
	CRITICAL_SECTION  m_crit;

	//使能
	BOOL m_bEnable;
	BOOL m_bPrintTime;
	BOOL m_bPrintAppName;

	//字符工具
	std::string GetBaseDir(std::string & path);
	std::string GetBaseName(std::string & path);

};

#endif CLOG4CPP_H