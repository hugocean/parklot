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
	name:car
	date:2018-8-12
	breif:this struct is input every car information 
	1.che pai hao 
	2.ru ku shi jian
	3.ting fang shi jian
*/
struct car
{
	char num[20];
	char intime[30];
	char outtime[30];
};
typedef struct car Car;

/*
	name:a stack(zhan) to store parking car information
	date:2018-8-12
	breif:this struct is input pointer to store car information 
*/
struct parklot
{
	int top;
	struct car *info;
};
typedef struct parklot Park;


struct waitqueue
{
	struct car *date;
	int front;
	int rear;
};
typedef struct waitqueue Wait;







int menu()
{
	system("clear");
	int choise;
	printf("***********welcome******************\n");
	printf("*1.in car              	**********  \n");
	printf("*2.show parklot       	**********  \n");
	printf("*3.out car       		**********  \n");
	printf("*4.show car waiting 	**********  \n");
	printf("*5.locate car 			**********  \n");
	printf("*6.....				 	**********  \n");
	printf("*7.exit       	 		**********  \n");
	printf("***********welcome******************\n");
	printf("please input you choise \n");
	scanf("%d",&choise); 
	return choise;
}
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


int ParkPush(Park *p,Car car1)  //车辆进入停车场
{
	if(p == NULL)
	{
		return FALSE;
	}
	if(p->top == (SIZE - 1))
	{
		return FAILURE;
	}
	
//	time_t in_time,out_time;
//	in_time = time(NULL);
//	out_time = time(NULL);

	strcpy(p->info[p->top + 1].num ,car1.num);
	strcpy(p->info[p->top + 1].intime ,car1.intime);
	strcpy(p->info[p->top + 1].outtime ,car1.outtime);

	p->top++;
	return SUCCESS;

}

int EnterWait(Wait *w, Car car1) //停车场停满 进入等待区域
{
	if(w == NULL)
	{
		return FAILURE;
	}
	if((w->rear +1) % SIZE == w->front)
	{
		return FAILURE;
	}
//	time_t in_time,out_time;
//	in_time = time(NULL);
//	out_time = time(NULL);
	
	strcpy(w->date[w->rear].num, car1.num);
	strcpy(w->date[w->rear].intime, car1.intime);
	strcpy(w->date[w->rear].outtime, car1.outtime);

	w->rear = (w->rear + 1) % SIZE;

	return SUCCESS;
}


Car OutWait(Wait *w)  //停车场有车出 等待区域出
{
/*	if(w == NULL)
	{
		return FAILURE;
	}
	if(w->rear == w->front)
	{
		return FAILURE;
	}
*/
	Car cartemp = w->date[w->front];
	w->front = (w->front + 1) % SIZE;

	return cartemp;

}

int WaitReverse(Wait *w) //等待区域 遍历
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

int StackReverse(Park *p) //停车场车辆遍历
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

int ParkPop(Park *p)  //停车场出车
{
	if(p->top == -1)
	{
		return FAILURE;
	}
	p->top--;

	return SUCCESS;
}
int WaitEmpty(Wait *w)  //等待区域是否为空
{
	if(w == NULL)
	{
		return FAILURE;
	}
	
	return (w->rear == w->front) ? TRUE : FALSE;
}

int ParkEmpty(Park *p) //停车场是否为空
{
	if(p == NULL)
	{
		return FAILURE;
	}
	
	return (p->top == -1) ? TRUE : FALSE;
}

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



/*char *GetCarnum(Park *p)
{
	if(p == NULL)
	{
		return FAILURE;
	}
	
	return p->info[p->top].num;
}*/

Car ParkGettop(Park *p) //停车场获取栈顶
{
/*	if(p == NULL)
	{
		return FAILURE;
	}
*/
	return p->info[p->top];
}


int main()
{
	int outnumber = 0;
	int ret,n,i,ret2;
	Park *park_in;
	Park *park_out;
	Wait *wait_ing;
	char num[20] = "0";
	char *carnum;
	Car car001,car002;
	Car car_temp;
	
	ret = ParkInit(&park_in);
	if(ret = SUCCESS)
	{
		printf("parking stack parkin init success \n");
	}
	else
	{
		printf("parking stack parkin init failure \n");
	}
	
	ret = ParkInit(&park_out);
	if(ret = SUCCESS)
	{
		printf("parking stack parkout init success \n");
	}
	else
	{
		printf("parking stack parkout init failure \n");
	}

	ret = WaitInit(&wait_ing);
	if(ret = SUCCESS)
	{
		printf("Waiting queue init success \n");
	}
	else
	{
		printf("Waiting queue init failure \n");
	}

	while(1)
	{
		n = menu();
		switch(n)
		{
			case 1:
				printf("please input car information \n");
				printf("input car license plate number \n");
				scanf("%s",num);
				time_t in_time,out_time;
				in_time = time(NULL);
				out_time = time(NULL);
			

				strcpy(car001.num , num);
				strcpy(car001.intime , ctime(&in_time));
				strcpy(car001.outtime ,ctime(&out_time));

				ret = ParkPush(park_in,car001);
				if(ret == SUCCESS)
				{
					printf("the car push success \n");
				}
				else if(ret == FAILURE)
				{
					printf("push failure please wait \n");
					ret2 = EnterWait(wait_ing,car001);
					if(ret2 == SUCCESS)
					{
						printf("this car is waiting \n");
					}
					else
					{
						printf("this car wait failure \n");
					}
					
				}
				else
				{
					printf("push failure \n");
				}
				
				getchar();		
				getchar();		
				
				break;
			
			case 2:
				ret = StackReverse(park_in);
				if(ret == SUCCESS)
				{
					printf("this is cars in the parklot \n");
				}
				else
				{
					printf("show failure \n");
				}
				getchar();		
				getchar();		
				
				break;			
			case 3:
				printf("please input car license plate number you want out \n");
				scanf("%s",num);

				for(i = 0; i < SIZE && ParkEmpty(park_in) != TRUE; i++)
				{
					car001 = ParkGettop(park_in);
					if(strcmp(car001.num, num) == 0)
					{
						printf("car : %s want out \n",car001.num);
						printf("in time is : %s \n",car001.intime);
						ParkPop(park_in);
						break;
					}
					else
					{
						car_temp = ParkGettop(park_in);		
						ParkPop(park_in);
						ParkPush(park_out,car_temp);
						outnumber++;
					}
				}
				
				for(i = 0; i < outnumber; i++)
				{
					car_temp = ParkGettop(park_out);		
					ParkPop(park_out);
					ParkPush(park_in,car_temp);
				}

				outnumber = 0;
				printf("car out success \n");
				
				if(WaitEmpty(wait_ing) != TRUE)
				{
					time_t in_newtime;
					
					car002 = OutWait(wait_ing);
					strcpy(car002.intime, ctime(&in_newtime));
					strcpy(car002.outtime, ctime(&in_newtime));
					ParkPush(park_in,car002);
					printf("car %s in park \n",car002.num);
					printf("car intime is %s \n",car002.intime);


				}

	/*			ret = ParkOut(park_in,num);
				if(ret == SUCCESS)
				{
					printf("our car success \n");
				}
				else
				{
					printf("out car failure \n");
				}
	*/
				getchar();		
				getchar();		
				break;
			
			case 4:
				ret = WaitReverse(wait_ing);
				if(ret == SUCCESS)
				{
					printf("this is cars in waiting \n");
				}
				else
				{
					printf("show failure \n");
				}
				getchar();		
				getchar();		
				break;
			case 5:					
				printf("please input license plate number you want find \n");
				scanf("%s",num);
				ret = CarFindPark(park_in,num);
				if(ret == FAILURE)
				{
					printf("not this car in park \n");
				}
				else
				{
					printf("find success \n");
				}
						
				ret = CarFindWait(wait_ing,num);
				if(ret == FAILURE)
				{
					printf("not this car in wait \n");
				}
				else
				{
					printf("find success \n");
				}

				getchar();		
				getchar();		
				break;
			
			case 6:

				break;
			
			case 7:
				exit(0);
				break;
		
			default:
				printf("please input right choise \n");
	
		
		}
		
	}
	
	return 0;

}





























