#ifndef __CONSOLE__QUEUE_H
#define __CONSOLE__QUEUE_H
#include "c_types.h"
typedef enum {
QUEUE_BOOL_FALSE=0,
QUEUE_BOOL_TRUE=!QUEUE_BOOL_FALSE,
}QUEUE_BOOL_ENUM;

typedef struct
{
	int8_t *Data;
	uint16_t Rear;
	uint16_t Front;
	uint16_t Qsize;
	QUEUE_BOOL_ENUM FullFlag;
}QueueStruct;



extern void csolQueueInit(QueueStruct *Q,int8_t *data,uint16_t Len);
extern uint16_t csolQueueIn(QueueStruct *Q,int8_t *data,uint16_t Len);
extern uint16_t csolQueueOut(QueueStruct *Q,int8_t *data,uint16_t Len);
extern uint16_t csolQueueGetLen(QueueStruct *Q);
extern uint16_t csolQueueGetRemainLen(QueueStruct *Q);
extern void csolQueueClr(QueueStruct *Q);

#endif

