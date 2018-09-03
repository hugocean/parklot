#ifndef __PARK_H
#define __PARK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define SUCCESS 10000
#define FAILURE 10001
#define TRUE 	10002
#define FALSE	10003
#define SIZE   	5       //tin fang che lian de shu liang(the number this park can park)

/*
	name:车辆结构体
	date:2018-8-14
	breif:结构体存放车辆 的车牌号 进入停车场时间 出停车场时间
*/
struct car
{
	char num[20];
	char intime[30];
	char outtime[30];
};
typedef struct car Car;

/*
	name:顺序栈 存放停车场的车辆
	date:2018-8-14
	breif:顺序栈结构体，指针info指向车辆数据，top指向栈顶
*/
struct parklot
{
	int top;
	struct car *info;
};
typedef struct parklot Park;

/*
	name:顺序队列 存放等待的车辆
	date:2018-8-14
	breif:顺序队列结构体，指针date指向车辆数据，front rear指向队头队尾
*/
struct waitqueue
{
	struct car *date;
	int front;
	int rear;
};
typedef struct waitqueue Wait;

int menu();
int ParkInit(Park **p);
int WaitInit(Wait **w);
int ParkPush(Park *p,Car car1) ;
int EnterWait(Wait *w, Car car1) ;
Car OutWait(Wait *w) ;
int WaitReverse(Wait *w); 
int StackReverse(Park *p) ;
int ParkPop(Park *p) ; 
int WaitEmpty(Wait *w);  
int ParkEmpty(Park *p); 
int CarFindPark(Park *p, char *name);
int CarFindWait(Wait *w, char *name);
Car ParkGettop(Park *p) ;

#endif









