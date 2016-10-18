# CLog4CPP
log utils for c++

FILENAME:CLog4CPP.h

PURPOSE:这是一个C++的日志工具类,兼容ASNI和UINCODE编码

CREATION DATE:2016-08-12

AUTHOR:itas109

Blog:http://blog.csdn.net/itas109

Git:https://github.com/itas109

----------------------------------------------------
*  author: itas109  date:2016-08-15
*  Blog：blog.csdn.net/itas109

*  Init方法增加默认初始化名称
*  精简代码
*  优化编码兼容性

----------------------------------------------------
* author: itas109  date:2016-08-17
* Blog：blog.csdn.net/itas109

* Init方法重载，用时间命名文件名
* 日志文件默认放到Log文件夹下
* 增加int2string方法，用于数字与字符的转换

----------------------------------------------------
* author: itas109  date:2016-08-18
* Blog：blog.csdn.net/itas109

* 去除对MFC的依赖
* 采用C++通用数据类型

----------------------------------------------------
* author: itas109  date:2016-08-26
* Blog：blog.csdn.net/itas109

* 采用通用性的#ifndef替换#pragma once
* 替换一些宏定义

----------------------------------------------------
* author: itas109  date:2016-09-12
* Blog：blog.csdn.net/itas109

* 去除int2string函数
* 时间格式统一为xxxx-xx-xx xx:xx:xx，不足为补0，如2016-09-12 16:28:01

----------------------------------------------------
* author: itas109  date:2016-10-13
* Blog：blog.csdn.net/itas109

* _mkdir创建文件夹时，参数采用绝对路径，防止自启动时无法创建文件夹

----------------------------------------------------
* author: itas109  date:2017-03-29
* Blog：blog.csdn.net/itas109

* 修复指针释放问题
* LogOut函数增加是否覆盖写入文件参数

