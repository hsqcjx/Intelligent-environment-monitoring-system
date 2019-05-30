/***************************************************************************
  * @file     console_queue.c
  * @author  Hhjian
  * @version v1.0
  * @date    2018.0525 
  * @brief   队列处理
  *******************************************************************************/
#include "console_queue.h"

/******************************************************************
 * 函数名  ：void csolQueueInit(QueueStruct *Q,int8_t *data,uint16_t Len)
 * 功能    ：初始化一个结构体
 * 参数    ：
    Q      
		data
		Len
 * 返回值  ：NULl
 **
******************************************************************/
void csolQueueInit(QueueStruct *Q,int8_t *data,uint16_t Len)
{
	Q->Data = data;
	Q->Front = 0;
	Q->Rear =0;
	Q->Qsize = Len;
	Q->FullFlag =QUEUE_BOOL_FALSE;
}


/******************************************************************
 * 函数名  ：void csolQueueClr(QueueStruct *Q)
 * 功能    ：清除一个队列的数据
 * 参数    ：
    Q      
 * 返回值  ：NULl
 **
******************************************************************/
void csolQueueClr(QueueStruct *Q)
{
	Q->Front = 0;
	Q->Rear =0;
	Q->FullFlag =QUEUE_BOOL_FALSE;
}


/******************************************************************
 * 函数名  ：uint16_t csolQueueIn(QueueStruct *Q,int8_t *data,uint16_t Len)
 * 功能    ：将数据入栈
 * 参数    ：
    Q      
    data
    len
 * 返回值  ：实际入栈的数据个数
 **
******************************************************************/
uint16_t csolQueueIn(QueueStruct *Q,int8_t *data,uint16_t Len)
{
	uint16_t i = 0;
	uint16_t Front = Q->Front;
	uint16_t Rear =  Q->Rear;
	
	while(1)
	{
		if(Q->FullFlag )break;
		Q->Data[Front++] = data[i];
		if(Front >= Q->Qsize)
			Front = 0;
		i++;
		if(Front == Rear)
		{
			Q->FullFlag = QUEUE_BOOL_TRUE;
		}
		if(i>=Len)
			break;
	}
	Q->Front = Front;
	return i;
}


/******************************************************************
 * 函数名  ：uint16_t csolQueueOut(QueueStruct *Q,int8_t *data,uint16_t Len)
 * 功能    ：将数据出栈
 * 参数    ：
    Q      
    data
    len
 * 返回值  ：实际出栈的数据个数
 **
******************************************************************/
uint16_t csolQueueOut(QueueStruct *Q,int8_t *data,uint16_t Len)
{
	uint16_t i = 0;
	uint16_t Front = Q->Front;
	uint16_t Rear = Q->Rear;
	while((Rear != Front)||(Q->FullFlag ==QUEUE_BOOL_TRUE))
	{
		Q->FullFlag =QUEUE_BOOL_FALSE;
		data[i] = Q->Data[Rear++];
		if(Rear>= Q->Qsize)
			Rear = 0;
		i++;
		if(i == Len)break;
		
	}
	Q->Rear = Rear;
	return i;
}


/******************************************************************
 * 函数名  ：uint16_t csolQueueGetLen(QueueStruct *Q)
 * 功能    ：获取队列里数据的个数
 * 参数    ：
    Q      
 * 返回值  ：队列里数据的个数
 **
******************************************************************/
uint16_t csolQueueGetLen(QueueStruct *Q)
{
	uint16_t Len;
	if(Q->FullFlag)
		return Q->Qsize;
	if(Q->Front >= Q->Rear)
		Len=Q->Front - Q->Rear;
	else
		Len=Q->Qsize - Q->Rear + Q->Front;
	return Len;
}


/******************************************************************
 * 函数名  ：uint16_t csolQueueGetRemainLen(QueueStruct *Q)
 * 功能    ：获取队列里剩余的空间
 * 参数    ：
    Q      
 * 返回值  ：队列里剩余的空间
 **
******************************************************************/
uint16_t csolQueueGetRemainLen(QueueStruct *Q)
{
	return (Q->Qsize -csolQueueGetLen(Q));
}


