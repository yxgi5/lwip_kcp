/********************************************************
 * @author : Andreas Zhang
 * @date : 2013/05/24 10:11
 * @brief : 定义调试打印宏
 ********************************************************/
#ifndef _TRACE_ZZG_DEBUG_H_
#define _TRACE_ZZG_DEBUG_H_
#define _DEBUG_TRACE_ZZG_ 3
#if 0 != _DEBUG_TRACE_ZZG_
	#include <stdio.h>
#endif

#if 1==_DEBUG_TRACE_ZZG_ //普通打印
	#define TRACE_ZZG printf
#elif 2==_DEBUG_TRACE_ZZG_ //打印文件名、行号
	#define TRACE_ZZG(fmt,...) \
		printf("%s(%d): "fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#elif 3==_DEBUG_TRACE_ZZG_ //打印文件名、行号、函数名
	#define TRACE_ZZG(fmt,...) \
		printf("%s(%d)-<%s>: "fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else		
	#define TRACE_ZZG
#endif 

#endif //_TRACE_ZZG_DEBUG_H_
