#include "park.h"

/*
	name:menu 菜单，选择系统需要进行的操作
	date:2018-8-14
	breif:	1.停车场进车
			2.停车场出车
			3.显示停车场内的车辆信息
			4.显示等待进入停车场的车辆信息
			5.查找车辆信息
			6.退出
*/
int menu()
{
	system("clear");
	int choise;
	printf("***********welcome******************\n");
	printf("*1.in car              	**********  \n");
	printf("*2.out car       	**********  \n");
	printf("*3.show parklot       		**********  \n");
	printf("*4.show car waiting 	**********  \n");
	printf("*5.locate car 			**********  \n");
	printf("*6.....				 	**********  \n");
	printf("*7.exit       	 		**********  \n");
	printf("***********welcome******************\n");
	printf("please input you choise \n");
	scanf("%d",&choise); 
	return choise;
}

/*
	name:ParkInit
	date:2018-8-14
	breif:初始化停车场的顺序栈
	1.给结构体分配空间
	2.给结构体里面的数据指针分配空间
	3.空栈，栈顶指向-1
	parameter： Park **p停车场栈的结构体
*/

int ParkInit(Park **p)
{
	(*p) = (Park *)malloc(sizeof(Park));
	
	if((*p) == NULL || p == NULL)
	{
		return FAILURE;
	}

	(*p) -> top = -1;
	(*p) -> info = (struct car *)malloc(sizeof(struct car) * SIZE);

	if(NULL == (*p) -> info)
	{
		return FAILURE;
	}

	return SUCCESS;
}


/*
	name:WaitInit
	date:2018-8-14
	breif:初始化等待队列
	1.给结构体分配空间
	2.给结构体里面的数据指针分配空间
	3.空队列队头队尾指向0
	parameter： Wait **w等待队列的结构体
*/
int WaitInit(Wait **w)
{
	(*w) = (Wait *)malloc(sizeof(Wait));
	if((*w) == NULL || w == NULL)
	{
		return FAILURE;
	}

	(*w) -> rear = (*w) -> front = 0;
	(*w) -> date = (struct car *)malloc(sizeof(struct car) * SIZE);

	if(NULL == (*w) -> date)
	{
		return FAILURE;
	}

	return SUCCESS;
}

/*
	name:ParkPush
	date:2018-8-14
	breif:车辆进入停车场，将车辆信息存放到停车场这个栈里面
	parameter： 1.Park *p   栈的结构体
				2.Car car1	车辆结构体

*/
int ParkPush(Park *p,Car car1)  
{
	if(p == NULL)
	{
		return FALSE;
	}
	if(p->top == (SIZE - 1))
	{
		return FAILURE;
	}

	strcpy(p->info[p->top + 1].num ,car1.num);
	strcpy(p->info[p->top + 1].intime ,car1.intime);
	strcpy(p->info[p->top + 1].outtime ,car1.outtime);

	p->top++;
	return SUCCESS;

}

/*
	name:EnterWait
	date:2018-8-14
	breif:当停车场停满 车辆进入等待区域
	parameter： 1.Wait *w   等待队列的结构体
				2.Car car1	车辆结构体

*/
int EnterWait(Wait *w, Car car1) 
{
	if(w == NULL)
	{
		return FAILURE;
	}
	if((w->rear +1) % SIZE == w->front)
	{
		return FAILURE;
	}
	
	strcpy(w->date[w->rear].num, car1.num);
	strcpy(w->date[w->rear].intime, car1.intime);
	strcpy(w->date[w->rear].outtime, car1.outtime);

	w->rear = (w->rear + 1) % SIZE;

	return SUCCESS;
}


/*
	name:EnterWait
	date:2018-8-14
	breif:当停车场有车出 车辆从等待区域进停车场
	parameter： 1.Wait *w   等待队列的结构体
				2.Car car1	车辆结构体

*/
Car OutWait(Wait *w)  
{
	Car cartemp = w->date[w->front];
	w->front = (w->front + 1) % SIZE;

	return cartemp;

}

/*
	name:WaitReverse
	date:2018-8-14
	breif:遍历等待区域
	parameter： 1.Wait *w   等待队列的结构体
*/
int WaitReverse(Wait *w) 
{
	if(w == NULL)
	{
		return FAILURE;
	}

	int i = w->front;
	int a=1;
	while(i % SIZE != w->rear)
	{
		printf("NO.%d car lisence is %s \n", a ,w->date[i].num);
		printf("this car wait-time is %s \n",w->date[i].intime);
		i++;
		a++;
	}

	return SUCCESS;
}

/*
	name:WaitReverse
	date:2018-8-14
	breif:遍历停车场车辆
	parameter： 1.Park *p  停车场栈的结构体
*/
int StackReverse(Park *p) 
{
	if(p == NULL)
	{
		return FAILURE;
	}
	if(p->top >= SIZE )
	{
		return FAILURE;
	}	

	int temp = p->top;
	int i;

	for(i = 0; i <= temp; i++)
	{
		printf("NO.%d car lisence is %s \n",i + 1,p->info[i].num);
		printf("this car in-time is %s \n",p->info[i].intime);
	}
	return SUCCESS;

}

/*
	name:ParkPop
	date:2018-8-14
	breif:停车场出车 出栈操作
	parameter： 1.Park *p  停车场栈的结构体
*/
int ParkPop(Park *p)  
{
	if(p->top == -1)
	{
		return FAILURE;
	}
	p->top--;

	return SUCCESS;
}

/*
	name:WaitEmpty
	date:2018-8-14
	breif:判断等待区域是否为空
	parameter： 1.Wait *w 等待队列的结构体
*/
int WaitEmpty(Wait *w)  
{
	if(w == NULL)
	{
		return FAILURE;
	}
	
	return (w->rear == w->front) ? TRUE : FALSE;
}


/*
	name:ParkEmpty
	date:2018-8-14
	breif:判断停车场是否为空
	parameter： 1.Park *p停车场栈的结构体
*/
int ParkEmpty(Park *p) //停车场是否为空
{
	if(p == NULL)
	{
		return FAILURE;
	}
	
	return (p->top == -1) ? TRUE : FALSE;
}

/*
	name:CarFindPark
	date:2018-8-14
	breif:查找车辆信息，在停车场中查找
	parameter： 1.Park *p停车场栈的结构体
				2.char *name需要查找的车辆车牌号
*/
int CarFindPark(Park *p, char *name)
{
	if(p == NULL)
	{
		return FAILURE;
	}
	printf("finding park \n");
	int temp = p->top;
	int i;

	for(i = 0; i <= temp; i++)
	{
		if(strcmp(p->info[i].num, name) == 0)
		{
			printf("NO.%d car lisence is %s \n",i + 1,p->info[i].num);
			printf("this car in-time is %s \n",p->info[i].intime);		
			return SUCCESS;
		}
	}

	return FAILURE;
}

/*
	name:CarFindWait
	date:2018-8-14
	breif:查找车辆信息，在等待队列中查找
	parameter： 1.Wait *w等待队列的结构体
				2.char *name需要查找的车辆车牌号
*/
int CarFindWait(Wait *w, char *name)
{
	if(w == NULL)
	{
		return FAILURE;
	}
	printf("finding wait \n");

	int temp = ((w->rear) - (w->front) + SIZE) % SIZE;
	int i;

	for(i = 0; i <= temp; i++)
	{
		if(strcmp(w->date[i].num, name) == 0)
		{
			printf("NO.%d car lisence is %s \n",i + 1,w->date[i].num);
			printf("this car in-time is %s \n",w->date[i].intime);		
			return SUCCESS;
		}
	}

	return FAILURE;

}

/*
	name:CarFindWait
	date:2018-8-14
	breif:获取停车场栈顶的车辆信息
	parameter： 1.Park *p 停车场结构体
*/
Car ParkGettop(Park *p) 
{
	return p->info[p->top];
}







