/***************************************************************************
  * @file     console_queue.c
  * @author  Hhjian
  * @version v1.0
  * @date    2018.0525 
  * @brief   ���д���
  *******************************************************************************/
#include "console_queue.h"

/******************************************************************
 * ������  ��void csolQueueInit(QueueStruct *Q,int8_t *data,uint16_t Len)
 * ����    ����ʼ��һ���ṹ��
 * ����    ��
    Q      
		data
		Len
 * ����ֵ  ��NULl
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
 * ������  ��void csolQueueClr(QueueStruct *Q)
 * ����    �����һ�����е�����
 * ����    ��
    Q      
 * ����ֵ  ��NULl
 **
******************************************************************/
void csolQueueClr(QueueStruct *Q)
{
	Q->Front = 0;
	Q->Rear =0;
	Q->FullFlag =QUEUE_BOOL_FALSE;
}


/******************************************************************
 * ������  ��uint16_t csolQueueIn(QueueStruct *Q,int8_t *data,uint16_t Len)
 * ����    ����������ջ
 * ����    ��
    Q      
    data
    len
 * ����ֵ  ��ʵ����ջ�����ݸ���
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
 * ������  ��uint16_t csolQueueOut(QueueStruct *Q,int8_t *data,uint16_t Len)
 * ����    �������ݳ�ջ
 * ����    ��
    Q      
    data
    len
 * ����ֵ  ��ʵ�ʳ�ջ�����ݸ���
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
 * ������  ��uint16_t csolQueueGetLen(QueueStruct *Q)
 * ����    ����ȡ���������ݵĸ���
 * ����    ��
    Q      
 * ����ֵ  �����������ݵĸ���
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
 * ������  ��uint16_t csolQueueGetRemainLen(QueueStruct *Q)
 * ����    ����ȡ������ʣ��Ŀռ�
 * ����    ��
    Q      
 * ����ֵ  ��������ʣ��Ŀռ�
 **
******************************************************************/
uint16_t csolQueueGetRemainLen(QueueStruct *Q)
{
	return (Q->Qsize -csolQueueGetLen(Q));
}


