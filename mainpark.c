#include "park.c"

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
	
	//首先初始化两个停车场栈，一个存放进如停车场的车辆信息，一个用来出停车场时使用
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

	//初始化等待队列信息
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
				//1.停车场进车
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
				//2.停车场出车
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

				getchar();		
				getchar();					
				break;			
			case 3:
				//3.显示停车场内的车辆信息
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
			
			case 4:
				//4.显示等待进入停车场的车辆信息
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
				//	5.查找车辆信息		
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













