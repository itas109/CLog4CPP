/*
**************************************************************************************
**
**	FILENAME			CLog4CPP.h
**
**	PURPOSE				这是一个C++的日志工具类,兼容ASNI和UINCODE编码
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
**  author: itas109  date:2016-08-15
**  Blog：blog.csdn.net/itas109
**  改进
**  1） Init方法增加默认初始化名称
**  2） 精简代码
**  3） 优化编码兼容性
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
	void Init(std::string stringpOutputFilename = "CLog4CPP_itas109.log");

	//输出文字，类似与TRACE、printf
	BOOL LogOut(std::string text);

	//设置使能
	void IsEnable(BOOL bEnable);

	//是否在每行加入时间戳
	void IsPrintTime(BOOL b) {m_bPrintTime = b;}

protected:
	//缓冲区
	enum {TBUF_SIZE = 3000};
	std::string m_tBuf[TBUF_SIZE];

	std::string m_csFileName;
	

	//临界区
	CRITICAL_SECTION  m_crit;

	//使能
	BOOL m_bEnable;
	BOOL m_bPrintTime;

	//字符工具
	std::string GetBaseDir(std::string & path);
	std::string GetFileExtensions(std::string & fileName);

};

#endif CLOG4CPP_H