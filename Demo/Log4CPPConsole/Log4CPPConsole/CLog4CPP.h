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
**************************************************************************************
**  author: itas109  date:2016-08-17
**  Blog：blog.csdn.net/itas109
**  改进
**  1） Init方法重载，用时间命名文件名
**  2） 日志文件默认放到Log文件夹下
**  3） 增加int2string方法，用于数字与字符的转换
**************************************************************************************
**  author: itas109  date:2016-08-18
**  Blog：blog.csdn.net/itas109
**  改进
**  1） 去除对MFC的依赖
**  2） 采用C++通用数据类型
**************************************************************************************
**  author: itas109  date:2016-08-26
**  Blog：blog.csdn.net/itas109
**  改进
**  1） 采用通用性的#ifndef替换#pragma once
**  2） 替换一些宏定义
**************************************************************************************
**  author: itas109  date:2016-09-12
**  Blog：blog.csdn.net/itas109
**  改进
**  1） 去除int2string函数
**  2） 时间格式统一为xxxx-xx-xx xx:xx:xx，不足位补0，如2016-09-12 16:28:01
**************************************************************************************
**  author: itas109  date:2016-10-13
**  Blog：blog.csdn.net/itas109
**  改进
**  _mkdir创建文件夹时，参数采用绝对路径，防止自启动时无法创建文件夹
**************************************************************************************
**  author: itas109  date:2017-03-29
**  Blog：blog.csdn.net/itas109
**  改进
**  1) 修复指针释放问题
**  2) LogOut函数增加是否覆盖写入文件参数
**************************************************************************************
**  author: itas109  date:2017-06-03
**  Blog：blog.csdn.net/itas109
**  Version：2.1.1.170603
**  改进
**  1) 增加namespace
**  2) 使用_s的安全函数
**  3) 修复当程序运行超过一天后，日志内容依旧写入初始化当天文件的问题
**  4) 增加版本号函数
**************************************************************************************
**  author: itas109  date:2017-07-05
**  Blog：blog.csdn.net/itas109
**  Version：2.1.2.170705
**  改进
**  1) 增加LogOutHex函数，用于16进制输出
*/
#ifndef CLOG4CPP_H
#define CLOG4CPP_H

#include <string>
#include <sstream>
#include <direct.h>
#include "atltime.h"

namespace itas109
{
	class CLog4CPP
	{
	public:

		CLog4CPP();
		~CLog4CPP();

		std::string getVersion();

		//初始化
		void Init(std::string stringpOutputFilename);
		void Init();//按照当天日期生成日志文件

		//输出文字，类似与TRACE、printf
		//isOverlayWrite 是否覆盖写入文件
		bool LogOut(std::string text, bool isOverlayWrite = false);
		//以16进制输出文字
		//isOverlayWrite 是否覆盖写入文件
		bool LogOutHex(unsigned char* text, int length, bool isOverlayWrite = false);

		//设置使能
		void IsEnable(bool bEnable);

		//是否在每行加入时间戳
		void IsPrintTime(bool b) { m_bPrintTime = b; }

	private:
		//缓冲区
		enum { TBUF_SIZE = 3000 };
		std::string m_tBuf[TBUF_SIZE];

		std::string m_csFileName;

		//临界区
		CRITICAL_SECTION  m_crit;

		//使能
		bool m_bEnable;//是否打印
		bool m_bPrintTime;//是否加入时间戳
		bool m_bNamedByDate;//是否以日期命名

		//字符工具
		std::string GetBaseDir(std::string & path);
		std::string GetFileExtensions(std::string & fileName);

		//class version
		const std::string version = "2.1.2.170705";
	};
}
#endif CLOG4CPP_H