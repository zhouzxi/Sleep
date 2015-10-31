/**********************************************************************
* 版权所有 (C)2015, Zhou Zhaoxiong。
*
* 文件名称：Sleep.c
* 文件标识：无
* 内容摘要：演示休眠程序的编写及调用
* 其它说明：无
* 当前版本：V1.0
* 作    者：Zhou Zhaoxiong
* 完成日期：20150430
*
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


// 重定义数据类型
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
typedef unsigned int        UINT32;
typedef signed   int        INT32;
typedef long     int        LONG;

// 结构体定义
typedef struct
{
	UINT8   second;     /* 0-59 */
	UINT8   minute;     /* 0-59 */
	UINT8   hour;       /* 0-23 */
	UINT8   day;        /* 1-31 */
	UINT8   month;      /* 1-12 */
	UINT16  year;       /* 1994-2099 */
	UINT8   week;       /* 1-7 */
	UINT8   Count10ms;  /* 0-99 */
} ClockStruc;


// 函数声明
void GetCurrentTime(ClockStruc *ptClock);
void Sleep(UINT32 iCountMs);


/**********************************************************************
* 功能描述：主函数
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期        版本号        修改人           修改内容
* ---------------------------------------------------------------
* 20150430        V1.0     Zhou Zhaoxiong          创建
***********************************************************************/
INT32 main()
{
    UINT8 szCurrentTime[50] = {0};
	
    ClockStruc tClock = {0};
	
  	// 开始日期
    GetCurrentTime(&tClock);
    // 打印开始时间(YYYY.MM.DD HH:MIN:SS)
    snprintf(szCurrentTime, sizeof(szCurrentTime) - 1, "%04d.%02d.%02d %02d:%02d:%02d", tClock.year, tClock.month, tClock.day,
                tClock.hour, tClock.minute, tClock.second);
    printf("Begin time: %s\n", szCurrentTime);
	
	  // 休眠10s
    Sleep(10 * 1000);
	
  	// 结束日期
    GetCurrentTime(&tClock);
    // 打印结束时间(YYYY.MM.DD HH:MIN:SS)
    snprintf(szCurrentTime, sizeof(szCurrentTime) - 1, "%04d.%02d.%02d %02d:%02d:%02d", tClock.year, tClock.month, tClock.day,
                tClock.hour, tClock.minute, tClock.second);
    printf("End time: %s\n", szCurrentTime);
    
    return 0;                     // main函数返回0
}


/**********************************************************************
* 功能描述： 获取当前时间
* 输入参数： ptClock-时间结构体
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期      版本号       修改人        修改内容
* ------------------------------------------------------------------
* 20150430       V1.0     Zhou Zhaoxiong     创建
********************************************************************/  
void GetCurrentTime(ClockStruc *ptClock)
{
    LONG            iDate     = 0;
	  struct tm      *ptTime    = NULL;
	  struct timeval  t_timeval = {0};

	  gettimeofday(&t_timeval, NULL);
	  iDate  = t_timeval.tv_sec;
	  ptTime = localtime(&iDate);
	  ptClock->Count10ms = t_timeval.tv_usec / 10000;
  	ptClock->year      = (UINT16)(ptTime->tm_year + 1900);
	  ptClock->month     = (UINT8)ptTime->tm_mon + 1;
	  ptClock->day       = (UINT8)ptTime->tm_mday;
	  ptClock->hour      = (UINT8)ptTime->tm_hour;
  	ptClock->minute    = (UINT8)ptTime->tm_min;
	  ptClock->second    = (UINT8)ptTime->tm_sec;
	  ptClock->week      = (UINT8)ptTime->tm_wday;
  	if (ptClock->week == 0)
	  {
	      ptClock->week = 7;
	  }
}


/**********************************************************************
* 功能描述： 程序休眠
* 输入参数： iCountMs-休眠时间(单位:ms)
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期      版本号       修改人        修改内容
* ------------------------------------------------------------------
* 20150430       V1.0     Zhou Zhaoxiong     创建
********************************************************************/ 
void Sleep(UINT32 iCountMs)
{
	  struct timeval t_timeout = {0};

  	if (iCountMs < 1000)
  	{
	      t_timeout.tv_sec  = 0;
	      t_timeout.tv_usec = iCountMs * 1000;
  	}
  	else
  	{
	      t_timeout.tv_sec  = iCountMs / 1000;
	      t_timeout.tv_usec = (iCountMs % 1000) * 1000;
	  }
  	select(0, NULL, NULL, NULL, &t_timeout);    // 调用select函数阻塞程序
}
