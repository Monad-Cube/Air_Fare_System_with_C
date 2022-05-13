#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
/*****************************************************
*功能描述：定义客户信息
*输入参数：name,id,line_num,time1,time2,seat_num
*输出参数：client
			txt文件
******************************************************/
typedef struct client
{
	char name[20];//顾客名
	char id[10];//顾客证件号
	char line_num[10];//航班号
	char time1[10];//起飞时间
	char time2[10];//降落时间
	int seat_num;//座位号
	int bookcount;//订票数量
	struct client* next;//下一个结点
} client;
//头结点
typedef struct clienthead
{
	int count;
	client* next;
} clienthead;

/*****************************************************
*功能描述：定义航班信息
*输入参数：line_num,time1,time2,seat_num，start_place,end_place,total
*输出参数：airline
			txt
******************************************************/
typedef struct airline
{
	char line_num[10];//航班号
	char start_place[20];//起飞地
	char end_place[20];//目的地
	char time1[10];//起飞时间
	char time2[10];//降落时间
	int total;//座位总数
	int left;//剩余座位
	clienthead* bookedclient;//已订票顾客
	clienthead* waitingclient;//候补顾客
	struct airline* next;//下一个结点
} airline;
//头结点
typedef struct airlinehead
{
	int count;
	airline* next;
} airlinehead;

/*****************************************************
*功能描述：录入航班函数
*输入参数：line_num,start_place,end_place,time1,time2,total,left
*输出参数：第i+1个航班录入
******************************************************/
airlinehead* import(int n, airlinehead* pheadline)//录入航班函数: n为所要录入航班的数量:
{
	airline* temp = new airline;
	temp->next = NULL;
	pheadline->next = temp;
	pheadline->count = n;
	for (int i = 0; i < n; i++)
	{
		cout << "请输入第" << i + 1 << "个航班的航班号 ";
		cin >> temp->line_num;
		cout << "请输入第" << i + 1 << "个航班的起飞地 ";
		cin >> temp->start_place;
		cout << "请输入第" << i + 1 << "个航班的目的地 ";
		cin >> temp->end_place;
		cout << "请输入第" << i + 1 << "个航班的起飞时间 ";
		cin >> temp->time1;
		cout << "请输入第" << i + 1 << "个航班的降落时间 ";
		cin >> temp->time2;
		cout << "请输入第" << i + 1 << "个航班的座位总数 ";
		cin >> temp->total;
		temp->bookedclient = new clienthead;
		temp->waitingclient = new clienthead;
		temp->bookedclient->next = NULL;
		temp->bookedclient->count = 0;
		temp->waitingclient->next = NULL;
		temp->waitingclient->count = 0;
		temp->left = temp->total;
		cout << "本航班的剩余座位数:" << temp->left << endl;
		cout << "第" << i + 1 << "个航班成功录入。" << endl;
		if (i < n - 1)
		{
			temp->next = new airline;
			if (temp->next == NULL)
			{
				cout << "分配内存失败" << endl;
				exit(1);
			}
			temp->next->next = NULL;
			temp = temp->next;
		}
	}
	return pheadline;
}

/*****************************************************
*功能描述：转乘检查
*输入参数：start end checkline
*输出参数：无
******************************************************/
void checkline(char* start, char* end, airlinehead* checkline) {
	airline* temp = new airline;
	airline* temp2 =new airline;
	temp = checkline->next;
	temp2 = checkline->next;
	char mid[20];
	for (int i = 0; i < checkline->count; i++) {
		if (strcmp(temp->start_place, start) == 0 && strcmp(temp->end_place, end) != 0) {
			for (int j = 0; j < checkline->count; j++) {
				if (strcmp(temp2->end_place, end) == 0 && strcmp(temp2->start_place, temp->end_place) == 0) {
					cout << "先乘坐 " << temp->line_num;
					cout << ",再乘坐 " << temp2->line_num;
					cout << " 即可转乘。" << endl;
					return;
				}
				temp2 = temp2->next;
			}
		}
		if (strcmp(temp->end_place, end) == 0 && strcmp(temp->start_place, start) != 0) {
			for (int j = 0; j < checkline->count; j++) {
				if (strcmp(temp2->start_place, start) == 0 && strcmp(temp2->end_place, temp->start_place) == 0) {
					cout << "先乘坐 " << temp2->line_num;
					cout << ",再乘坐 " << temp->line_num;
					cout << " 即可转乘。" << endl;
					return;
				}
				temp2 = temp2->next;
			}
		}
		temp = temp->next;
	}
	cout << "抱歉，未找到符合该条件的转乘航班" << endl;
}

/*****************************************************
*功能描述：查询航班功能
*输入参数：select，1,2
*输出参数：航班号，起飞地，抵达地，起飞时间，降落时间，座位数，剩余座数
*返回值：temp-成功,NULL-失败
******************************************************/
airline* query(airlinehead* phead)//查询航班情况
{
	airline* find = NULL;
	airline* temp;
	cout << "**************************************" << endl;
	cout << "* 1,按航线查询航班情况。             *" << endl;
	cout << "* 2,按起飞抵达城市查询航班情况。     *" << endl;
	cout << "* 3,按起飞抵达城市查询转乘航班情况。 *" << endl;
	cout << "**************************************" << endl;
	cout << "请选择:";
	int select;
	cin >> select;
	cout << endl;
	switch (select)
	{
	case 1:
	{
		cout << "请输入航班号：";
		char line_num[10];
		cin >> line_num;
		temp = phead->next;
		while (temp)
		{
			if (strcmp(temp->line_num, line_num) == 0)
			{
				find = temp;
				return temp;
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		if (!temp)
		{
			cout << "没有找到该航班的信息。" << endl;
			return NULL;
		}
		break;
	}
	case 2:
	{
		char start_place[20];//起飞地
		char end_place[20];//目的地
		cout << "请输入起飞地址：";
		cin >> start_place;
		cout << "请输入目的地：";
		cin >> end_place;
		temp = phead->next;
		while (temp)
		{
			if (strcmp(temp->start_place, start_place) == 0 &&
				strcmp(temp->end_place, end_place) == 0)
			{
				find = temp;
				//return temp;
				break;
			}
			temp = temp->next;
		}
		if (!temp)
		{
			cout << "没有找到该航班的信息。" << endl;
			return NULL;
		}
		break;
	}
	case 3:
		char start[20], end[20];
		cout << "请输入出发地点：";
		cin >> start;
		cout << "请输入目的地：";
		cin >> end;
		checkline(start, end, phead);
		break;
	default:
		cout << "输入错误。" << endl;
		break;
	}
	return find;
}

/*****************************************************
*功能描述：查询航班功能
*输入参数：select，1,2
*输出参数：航班号，起飞地，抵达地，起飞时间，降落时间，座位数，剩余座数
******************************************************/
void display_line(airline* node)//输出一个航班结点的所有信息到屏幕
{
	if (node == NULL)
	{
		cout << "参数为空!输出失败." << endl;
		return;
	}
	cout << endl;
	cout << "航班号:" << node->line_num << endl;
	cout << "起飞地:" << node->start_place << "\t目的地:" << node->end_place << endl;
	cout << "起飞时间:" << node->time1 << "\t降落时间" << node->time2 << endl;
	cout << "座位总数:" << node->total << "\t剩余座位:" << node->left << endl;

}

/******************************************************
*功能描述：输出所有的航班信息到屏幕
*输入参数：无
*输出参数：headline
*******************************************************/
void display_all_line(airlinehead* headline)
{
	cout << endl;
	airline* node;
	node = headline->next;
	if (!node)
	{
		cout << "当前没有航班信息" << endl;
		return;
	}
	cout << "航班数目: " << headline->count << endl;
	while (node)
	{
		display_line(node);
		node = node->next;
	}
}

/******************************************************
*功能描述:修改航班信息
*输入参数：select
*输出参数：无
*返回值：0-正确，1-错误 
*******************************************************/
int change_line(airlinehead* headline)//修改航班信息。
{
	cout << "当前所有航班的信息为:" << endl;
	airline* temp;
	temp = headline->next;
	while (temp)
	{
		display_line(temp);
		temp = temp->next;
	}
	cout << endl;
	cout << "请选择你要进行的操作:" << endl;
	cout << "1,增加航班。" << endl;
	cout << "2,删除航班。" << endl;
	cout << "3,修改当前航班的信息。" << endl;
	int select;
	cin >> select;
	cout << endl;
	if (select > 3 || select < 1)
	{
		cout << "输入错误。" << endl;
		return 0;
	}
	switch (select)
	{
	case 1:
	{
		// temp->next = (airline*)malloc(sizeof(airline));
		temp->next = new airline;
		temp = temp->next;
		cout << "请输入要增加的航班号: ";
		cin >> temp->line_num;
		cout << "请输入航班的起飞地: ";
		cin >> temp->start_place;
		cout << "请输入航班的目的地: ";
		cin >> temp->end_place;
		cout << "请输入航班的起飞时间:";
		cin >> temp->time1;
		cout << "请输入航班的降落时间:";
		cin >> temp->time2;
		cout << "请输入航班的座位总数: ";
		cin >> temp->total;
		temp->bookedclient = new clienthead;
		temp->waitingclient = new clienthead;
		temp->bookedclient = NULL;
		temp->waitingclient = NULL;
		temp->left = temp->total;
		temp->next = NULL;
		headline->count++;
		cout << "增加成功。" << endl;
		break;
	}
	case 2:
	{
		cout << "请输入您要删除的航班的航班号: ";
		char line_num[10];
		cin >> line_num;
		airline* delline;
		delline = headline->next;
		while (delline)
		{
			if (strcmp(delline->line_num, line_num) == 0)//如果删除的是第一个航班
			{
				delete delline;
				headline->next = NULL;
				headline->count--;
				break;
			}
			if (strcmp(delline->next->line_num, line_num) == 0)//删除的不是第一个航班
			{
				airline* plink;
				plink = delline->next->next;
				//free(delline->next);
				delete delline->next;
				delline->next = plink;
				headline->count--;
			}
			delline = delline->next;
		}
		if (delline == 0)
		{
			cout << "没有找到输入的航班号。" << endl;
			return 0;
		}
		break;
	}
	case 3:
	{
		cout << "请输入您要修改的航班的航班号:";
		char line_num3[10];
		cin >> line_num3;
		temp = headline->next;
		while (temp)
		{
			if (strcmp(temp->next->line_num, line_num3) == 0)
			{
				cout << "请选择要修改的内容" << endl;
				cout << "--1,座位总数。--" << endl;
				cout << "--2,起始地址。--" << endl;
				cout << "--3,目的地址。--" << endl;
			}
			temp = temp->next;
		}
		if (temp == 0)
		{
			cout << "没有找到输入的航班号。" << endl;
			return 0;
		}
		break;
	}
	}
	return 1;
}

/*****************************************************
*功能描述：输出一个客户信息到屏幕
*输入参数：无
*输出参数：姓名，证件号码，座号，航班号，起飞时间，降落时间，
******************************************************/
void display_client(client* node = NULL)//输出一个客户节点的信息到屏幕。
{
	if (node == NULL)
	{
		cout << "参数为空!输出失败。" << endl;
		return;
	}
	cout << endl;
	cout << "姓名\t\t" << "证件号码\t" << "座号\t" << "起飞时间\t" << "降落时间\t" << "航班\t\t" << endl << endl;
	cout << node->name << "\t\t"
		<< node->id << "\t\t"
		<< node->seat_num << "\t\t"
		<< node->time1 << "\t"
		<< node->time2 << "\t"
		<< node->line_num << "\t\t"
		<< endl;
}

/*****************************************************
*功能描述：输出全部客户信息到屏幕
*输入参数：无
*输出参数：姓名，证件号码，座号，航班号，起飞时间，降落时间，
******************************************************/
void display_all_client(clienthead* headclient)//打印所有客户信息到屏幕。。
{
	client* node = headclient->next;
	if (!node)
	{
		cout << "当前没有客户信息。" << endl;
		return;
	}
	while (node)
	{
		display_client(node);
		node = node->next;
	}
}

/*****************************************************
*功能描述：候补检查
*输入参数：airline
*输出参数：无
******************************************************/
void check(airline* checkairline) {
	client* temp = new client;
	client* temp2 = new client;
	temp = checkairline->waitingclient->next;
	temp2 = checkairline->bookedclient ->next;
	while (temp != NULL)//添加匹配航线中的候补
	{
		if (temp->bookcount <= checkairline->left) 
		{
			checkairline->left -= temp->bookcount;
			checkairline->bookedclient->next = temp;
			delete temp;
			cout << "候补成功！" << endl;
			return;
		}else if(temp->next != NULL)
			{	
				if (temp->next->bookcount<=checkairline->left) {
					client* temp3 = new client;
					temp3 = temp->next;

					checkairline->left -= temp->next->bookcount;//修改航线中的预定人数
					checkairline->bookedclient->next = temp3;
					temp3->next = temp2;

					temp->next = temp2;	//修改航线中的候补人数		
					temp->next = temp->next->next;
					delete temp3;
					cout << "候补成功！" << endl;
					return;
				}
			}
		cout << "test1" << endl;
		temp = temp->next;
	}
	cout << "候补失败！" << endl;
}

/*****************************************************
*功能描述：订票
*输入参数：line_num,id
*输出参数：
*返回值：1-正确，0-错误
******************************************************/
int bookticket(airlinehead* headline, clienthead* headclient)//订票
{
	//headclient->count=0;
	cout << "请输入航班号: ";
	char line_num[10];
	cin >> line_num;
	airline* temp;
	client* custom = new client;
	temp = headline->next;
	while (temp)
	{
		if (strcmp(temp->line_num, line_num) == 0)
		{
			break;
		}
		temp = temp->next;
	}
	if (!temp)
	{
		cout << "未找到该航班" << endl;
		return 0;
	}
	if (temp->left == 0)
	{
		cout << "对不起,该航班票已经售完。请选择执行以下操作" << endl;
		int sel;	
		cout << "1.选择候补."<< endl;
		cout << "2.取消订票." << endl;
		cin >> sel;
		client* temp_client = new client;
		switch (sel)
		{
			case 1:
				cout << "请输入你的证件号码: ";
				cin >> custom->id;
				cout << endl;
				cout << "请输入你的姓名:";
				cin >> custom->name;
				cout << endl;
				cout << "请输入订票数:";
				cin >> custom->bookcount;
				custom->seat_num = temp->total - temp->left + 1;
				strcpy_s(custom->line_num, line_num);
				//修改该航班候补情况
				
				temp_client = temp->waitingclient->next;
				if (temp_client == NULL) {
					custom->next = temp->waitingclient->next;
					temp->waitingclient->count++;
					temp->waitingclient->next=custom;
				}else{
					while (temp_client->next)
					{
						temp_client = temp_client->next;
					}
					temp_client->next = custom;
					custom->next = NULL;
				}
				//修改client
				headclient->count++;
				custom->next = headclient->next;
				headclient->next = custom;
				cout << "候补成功！" << endl;
				return 1;
				break;
			case 2:
				return 0;
			default:
				break;
		}
	}
	cout << "请输入你的证件号码: ";
	cin >> custom->id;
	cout << endl;
	cout << "请输入你的姓名:";
	cin >> custom->name;
	cout << endl;
	cout << "请输入订票数:";	
	cin >> custom->bookcount;
	cout << endl;
	if(temp->left < custom->bookcount)
	{
		cout << "余票不足，请执行以下操作：" << endl;
		cout << "1.选择候补" << endl;
		cout << "2.查看转乘" << endl;
		cout << "3.取消订票" << endl;
		cout << "请输入操作：";
		int sel;
		cin >> sel;
		client* temp_client = new client;
		switch (sel)
		{
			case 1:
				cout << "请输入你的证件号码: ";
				cin >> custom->id;
				cout << endl;
				cout << "请输入你的姓名:";
				cin >> custom->name;
				cout << endl;
				cout << "请输入订票数:";
				cin >> custom->bookcount;

				custom->seat_num = temp->total - temp->left + 1;
				custom->next = NULL;
				strcpy_s(custom->line_num, line_num);
				//修改该航班候补情况
				
				temp_client = temp->waitingclient->next;
				if (temp_client == NULL) {
					custom->next = temp->waitingclient->next;
					temp->waitingclient->count++;
					temp->waitingclient->next = custom;
				}
				else {
					while (temp_client->next)
					{
						temp_client = temp_client->next;
					}
					temp_client->next = custom;
					custom->next = NULL;
				}
				//修改client
				headclient->count++;
				custom->next = headclient->next;
				headclient->next = custom;
				cout << "候补成功！" << endl;
				break;
			case 2:				
				char start[20], end[20];
				cout << "请输入出发地点：";
				cin >> start;
				cout << "请输入目的地：";
				cin >> end;
				checkline(start,end,headline);
				return 1;
			case 3:
				return 0;
		default:
			break;
		}
		
	}
	custom->seat_num = temp->total - temp->left + 1;
	
	strcpy_s(custom->line_num, line_num);
	temp->left -= custom->bookcount;
	custom->next = temp->bookedclient->next;
	temp->bookedclient->next = custom;
	temp->bookedclient->count ++;
	headclient->count++;
	custom->next = headclient->next;
	headclient->next = custom;
	cout << "订票成功！" << endl;
	return 0;
}
/*****************************************************
*功能描述：退票
*输入参数：id
*输出参数：
*返回值：1-正确，0-错误
******************************************************/
int returnticket(airlinehead* headline, clienthead* headclient)//退票。
{
	cout << "请输入顾客的证件号码: ";
	char id[10];
	cin >> id;
	airline* airlinetemp = headline->next;
	client* clienttemp = headclient->next;
	if (NULL == airlinetemp)
	{
		cout << "当前没有航班信息。" << endl;
		return 0;
	}
	char line_num[10];
	client* delnext;
	client* delnext2;
	if (strcmp(clienttemp->id, id) == 0)//要删除的节点为第一个时
	{
		strcpy_s(line_num, clienttemp->line_num);
		while (airlinetemp)//修改退票客户所对应的航班的售票信息。
		{
			if (strcmp(line_num, airlinetemp->line_num) == 0)
			{
				airlinetemp->left+=clienttemp->bookcount;
				break;
			}
			airlinetemp = airlinetemp->next;
		}		
		headclient->next = clienttemp->next;
		delete clienttemp;
		cout << "退票成功!希望有机会与您继续合作。"<<endl;
		check(airlinetemp);
		return 1;
	}
	while (clienttemp->next)//要删除的节点不是第一个时
	{
		if (strcmp(clienttemp->next->id, id) == 0)
		{
			strcpy_s(line_num, clienttemp->next->line_num);

			while (airlinetemp)//修改退票客户所对应的航班的售票信息。
			{
				if (strcmp(line_num, airlinetemp->line_num) == 0)
				{
					airlinetemp->left += clienttemp->next->bookcount;
					client* temp2 = new client;
					temp2 = airlinetemp->bookedclient->next;
					break;
				}
				airlinetemp = airlinetemp->next;
			}			
			delnext = clienttemp->next->next;
			delete clienttemp->next;
			clienttemp->next = delnext;
			
			cout << "退票成功！有机会继续合作。" << endl;
			check(airlinetemp);
			return 1;
			break;
		}
		clienttemp = clienttemp->next;
	}
	cout << "未找到该客户的信息。" << endl;
	return 0;
}

//主函数
void main_menu()
{
	cout << "******************** 欢迎使用飞机售票系统************************" << endl << endl;
	cout << "***               1---- 录入航班信息。                        ***" << endl << endl;
	cout << "***               2---- 查询航线信息。                        ***" << endl << endl;
	cout << "***               3---- 客户订票。                            ***" << endl << endl;
	cout << "***               4---- 客户退票。                            ***" << endl << endl;
	cout << "***               5---- 输出所有航班信息。                    ***" << endl << endl;
	cout << "***               6---- 输出所有顾客信息。                    ***" << endl << endl;
	cout << "***               7---- 修改航线信息。                        ***" << endl << endl;
	cout << "***               0---- 退出系统。                            ***" << endl << endl;
	cout << "****************************************************************" << endl << endl;
}

int main()
{
	airlinehead* headline = new airlinehead;
	headline->count = 0;
	headline->next = NULL;
	clienthead* headclient = new clienthead;
	headclient->count = 0;
	headclient->next = NULL;
	while (1)
	{
		main_menu();
		int n;
		cout << "请选择您要进行的操作: ";
		cin >> n;
		cout << endl;
		switch (n)
		{
		case 1:
			int num;
			cout << "请选择您要录入的航班的数目： ";
			cin >> num;
			cout << endl;
			import(num, headline);
			cout << endl;
			//display_all_line(headline);
			cout << "航班信息成功录入。。";
			cout << endl << endl;
			break;
		case 2:
			airline * find;
			find = query(headline);
			if(find)
			{
				display_line(find);
			}
			break;
		case 3:
			bookticket(headline, headclient);
			//display_all_client(headclient);
			break;
		case 4:
			returnticket(headline, headclient);
			break;
		case 5:
			display_all_line(headline);
			break;
		case 6:
			display_all_client(headclient);
			break;
		case 7:
			change_line(headline);
			break;
		case 0:
			exit(1);
			break;
		}
	}
}
