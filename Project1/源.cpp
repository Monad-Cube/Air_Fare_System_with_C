#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
/*****************************************************
*��������������ͻ���Ϣ
*���������name,id,line_num,time1,time2,seat_num
*���������client
			txt�ļ�
******************************************************/
typedef struct client
{
	char name[20];//�˿���
	char id[10];//�˿�֤����
	char line_num[10];//�����
	char time1[10];//���ʱ��
	char time2[10];//����ʱ��
	int seat_num;//��λ��
	int bookcount;//��Ʊ����
	struct client* next;//��һ�����
} client;
//ͷ���
typedef struct clienthead
{
	int count;
	client* next;
} clienthead;

/*****************************************************
*�������������庽����Ϣ
*���������line_num,time1,time2,seat_num��start_place,end_place,total
*���������airline
			txt
******************************************************/
typedef struct airline
{
	char line_num[10];//�����
	char start_place[20];//��ɵ�
	char end_place[20];//Ŀ�ĵ�
	char time1[10];//���ʱ��
	char time2[10];//����ʱ��
	int total;//��λ����
	int left;//ʣ����λ
	clienthead* bookedclient;//�Ѷ�Ʊ�˿�
	clienthead* waitingclient;//�򲹹˿�
	struct airline* next;//��һ�����
} airline;
//ͷ���
typedef struct airlinehead
{
	int count;
	airline* next;
} airlinehead;

/*****************************************************
*����������¼�뺽�ຯ��
*���������line_num,start_place,end_place,time1,time2,total,left
*�����������i+1������¼��
******************************************************/
airlinehead* import(int n, airlinehead* pheadline)//¼�뺽�ຯ��: nΪ��Ҫ¼�뺽�������:
{
	airline* temp = new airline;
	temp->next = NULL;
	pheadline->next = temp;
	pheadline->count = n;
	for (int i = 0; i < n; i++)
	{
		cout << "�������" << i + 1 << "������ĺ���� ";
		cin >> temp->line_num;
		cout << "�������" << i + 1 << "���������ɵ� ";
		cin >> temp->start_place;
		cout << "�������" << i + 1 << "�������Ŀ�ĵ� ";
		cin >> temp->end_place;
		cout << "�������" << i + 1 << "����������ʱ�� ";
		cin >> temp->time1;
		cout << "�������" << i + 1 << "������Ľ���ʱ�� ";
		cin >> temp->time2;
		cout << "�������" << i + 1 << "���������λ���� ";
		cin >> temp->total;
		temp->bookedclient = new clienthead;
		temp->waitingclient = new clienthead;
		temp->bookedclient->next = NULL;
		temp->bookedclient->count = 0;
		temp->waitingclient->next = NULL;
		temp->waitingclient->count = 0;
		temp->left = temp->total;
		cout << "�������ʣ����λ��:" << temp->left << endl;
		cout << "��" << i + 1 << "������ɹ�¼�롣" << endl;
		if (i < n - 1)
		{
			temp->next = new airline;
			if (temp->next == NULL)
			{
				cout << "�����ڴ�ʧ��" << endl;
				exit(1);
			}
			temp->next->next = NULL;
			temp = temp->next;
		}
	}
	return pheadline;
}

/*****************************************************
*����������ת�˼��
*���������start end checkline
*�����������
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
					cout << "�ȳ��� " << temp->line_num;
					cout << ",�ٳ��� " << temp2->line_num;
					cout << " ����ת�ˡ�" << endl;
					return;
				}
				temp2 = temp2->next;
			}
		}
		if (strcmp(temp->end_place, end) == 0 && strcmp(temp->start_place, start) != 0) {
			for (int j = 0; j < checkline->count; j++) {
				if (strcmp(temp2->start_place, start) == 0 && strcmp(temp2->end_place, temp->start_place) == 0) {
					cout << "�ȳ��� " << temp2->line_num;
					cout << ",�ٳ��� " << temp->line_num;
					cout << " ����ת�ˡ�" << endl;
					return;
				}
				temp2 = temp2->next;
			}
		}
		temp = temp->next;
	}
	cout << "��Ǹ��δ�ҵ����ϸ�������ת�˺���" << endl;
}

/*****************************************************
*������������ѯ���๦��
*���������select��1,2
*�������������ţ���ɵأ��ִ�أ����ʱ�䣬����ʱ�䣬��λ����ʣ������
*����ֵ��temp-�ɹ�,NULL-ʧ��
******************************************************/
airline* query(airlinehead* phead)//��ѯ�������
{
	airline* find = NULL;
	airline* temp;
	cout << "**************************************" << endl;
	cout << "* 1,�����߲�ѯ���������             *" << endl;
	cout << "* 2,����ɵִ���в�ѯ���������     *" << endl;
	cout << "* 3,����ɵִ���в�ѯת�˺�������� *" << endl;
	cout << "**************************************" << endl;
	cout << "��ѡ��:";
	int select;
	cin >> select;
	cout << endl;
	switch (select)
	{
	case 1:
	{
		cout << "�����뺽��ţ�";
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
			cout << "û���ҵ��ú������Ϣ��" << endl;
			return NULL;
		}
		break;
	}
	case 2:
	{
		char start_place[20];//��ɵ�
		char end_place[20];//Ŀ�ĵ�
		cout << "��������ɵ�ַ��";
		cin >> start_place;
		cout << "������Ŀ�ĵأ�";
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
			cout << "û���ҵ��ú������Ϣ��" << endl;
			return NULL;
		}
		break;
	}
	case 3:
		char start[20], end[20];
		cout << "����������ص㣺";
		cin >> start;
		cout << "������Ŀ�ĵأ�";
		cin >> end;
		checkline(start, end, phead);
		break;
	default:
		cout << "�������" << endl;
		break;
	}
	return find;
}

/*****************************************************
*������������ѯ���๦��
*���������select��1,2
*�������������ţ���ɵأ��ִ�أ����ʱ�䣬����ʱ�䣬��λ����ʣ������
******************************************************/
void display_line(airline* node)//���һ���������������Ϣ����Ļ
{
	if (node == NULL)
	{
		cout << "����Ϊ��!���ʧ��." << endl;
		return;
	}
	cout << endl;
	cout << "�����:" << node->line_num << endl;
	cout << "��ɵ�:" << node->start_place << "\tĿ�ĵ�:" << node->end_place << endl;
	cout << "���ʱ��:" << node->time1 << "\t����ʱ��" << node->time2 << endl;
	cout << "��λ����:" << node->total << "\tʣ����λ:" << node->left << endl;

}

/******************************************************
*����������������еĺ�����Ϣ����Ļ
*�����������
*���������headline
*******************************************************/
void display_all_line(airlinehead* headline)
{
	cout << endl;
	airline* node;
	node = headline->next;
	if (!node)
	{
		cout << "��ǰû�к�����Ϣ" << endl;
		return;
	}
	cout << "������Ŀ: " << headline->count << endl;
	while (node)
	{
		display_line(node);
		node = node->next;
	}
}

/******************************************************
*��������:�޸ĺ�����Ϣ
*���������select
*�����������
*����ֵ��0-��ȷ��1-���� 
*******************************************************/
int change_line(airlinehead* headline)//�޸ĺ�����Ϣ��
{
	cout << "��ǰ���к������ϢΪ:" << endl;
	airline* temp;
	temp = headline->next;
	while (temp)
	{
		display_line(temp);
		temp = temp->next;
	}
	cout << endl;
	cout << "��ѡ����Ҫ���еĲ���:" << endl;
	cout << "1,���Ӻ��ࡣ" << endl;
	cout << "2,ɾ�����ࡣ" << endl;
	cout << "3,�޸ĵ�ǰ�������Ϣ��" << endl;
	int select;
	cin >> select;
	cout << endl;
	if (select > 3 || select < 1)
	{
		cout << "�������" << endl;
		return 0;
	}
	switch (select)
	{
	case 1:
	{
		// temp->next = (airline*)malloc(sizeof(airline));
		temp->next = new airline;
		temp = temp->next;
		cout << "������Ҫ���ӵĺ����: ";
		cin >> temp->line_num;
		cout << "�����뺽�����ɵ�: ";
		cin >> temp->start_place;
		cout << "�����뺽���Ŀ�ĵ�: ";
		cin >> temp->end_place;
		cout << "�����뺽������ʱ��:";
		cin >> temp->time1;
		cout << "�����뺽��Ľ���ʱ��:";
		cin >> temp->time2;
		cout << "�����뺽�����λ����: ";
		cin >> temp->total;
		temp->bookedclient = new clienthead;
		temp->waitingclient = new clienthead;
		temp->bookedclient = NULL;
		temp->waitingclient = NULL;
		temp->left = temp->total;
		temp->next = NULL;
		headline->count++;
		cout << "���ӳɹ���" << endl;
		break;
	}
	case 2:
	{
		cout << "��������Ҫɾ���ĺ���ĺ����: ";
		char line_num[10];
		cin >> line_num;
		airline* delline;
		delline = headline->next;
		while (delline)
		{
			if (strcmp(delline->line_num, line_num) == 0)//���ɾ�����ǵ�һ������
			{
				delete delline;
				headline->next = NULL;
				headline->count--;
				break;
			}
			if (strcmp(delline->next->line_num, line_num) == 0)//ɾ���Ĳ��ǵ�һ������
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
			cout << "û���ҵ�����ĺ���š�" << endl;
			return 0;
		}
		break;
	}
	case 3:
	{
		cout << "��������Ҫ�޸ĵĺ���ĺ����:";
		char line_num3[10];
		cin >> line_num3;
		temp = headline->next;
		while (temp)
		{
			if (strcmp(temp->next->line_num, line_num3) == 0)
			{
				cout << "��ѡ��Ҫ�޸ĵ�����" << endl;
				cout << "--1,��λ������--" << endl;
				cout << "--2,��ʼ��ַ��--" << endl;
				cout << "--3,Ŀ�ĵ�ַ��--" << endl;
			}
			temp = temp->next;
		}
		if (temp == 0)
		{
			cout << "û���ҵ�����ĺ���š�" << endl;
			return 0;
		}
		break;
	}
	}
	return 1;
}

/*****************************************************
*�������������һ���ͻ���Ϣ����Ļ
*�����������
*���������������֤�����룬���ţ�����ţ����ʱ�䣬����ʱ�䣬
******************************************************/
void display_client(client* node = NULL)//���һ���ͻ��ڵ����Ϣ����Ļ��
{
	if (node == NULL)
	{
		cout << "����Ϊ��!���ʧ�ܡ�" << endl;
		return;
	}
	cout << endl;
	cout << "����\t\t" << "֤������\t" << "����\t" << "���ʱ��\t" << "����ʱ��\t" << "����\t\t" << endl << endl;
	cout << node->name << "\t\t"
		<< node->id << "\t\t"
		<< node->seat_num << "\t\t"
		<< node->time1 << "\t"
		<< node->time2 << "\t"
		<< node->line_num << "\t\t"
		<< endl;
}

/*****************************************************
*�������������ȫ���ͻ���Ϣ����Ļ
*�����������
*���������������֤�����룬���ţ�����ţ����ʱ�䣬����ʱ�䣬
******************************************************/
void display_all_client(clienthead* headclient)//��ӡ���пͻ���Ϣ����Ļ����
{
	client* node = headclient->next;
	if (!node)
	{
		cout << "��ǰû�пͻ���Ϣ��" << endl;
		return;
	}
	while (node)
	{
		display_client(node);
		node = node->next;
	}
}

/*****************************************************
*�����������򲹼��
*���������airline
*�����������
******************************************************/
void check(airline* checkairline) {
	client* temp = new client;
	client* temp2 = new client;
	temp = checkairline->waitingclient->next;
	temp2 = checkairline->bookedclient ->next;
	while (temp != NULL)//���ƥ�亽���еĺ�
	{
		if (temp->bookcount <= checkairline->left) 
		{
			checkairline->left -= temp->bookcount;
			checkairline->bookedclient->next = temp;
			delete temp;
			cout << "�򲹳ɹ���" << endl;
			return;
		}else if(temp->next != NULL)
			{	
				if (temp->next->bookcount<=checkairline->left) {
					client* temp3 = new client;
					temp3 = temp->next;

					checkairline->left -= temp->next->bookcount;//�޸ĺ����е�Ԥ������
					checkairline->bookedclient->next = temp3;
					temp3->next = temp2;

					temp->next = temp2;	//�޸ĺ����еĺ�����		
					temp->next = temp->next->next;
					delete temp3;
					cout << "�򲹳ɹ���" << endl;
					return;
				}
			}
		cout << "test1" << endl;
		temp = temp->next;
	}
	cout << "��ʧ�ܣ�" << endl;
}

/*****************************************************
*������������Ʊ
*���������line_num,id
*���������
*����ֵ��1-��ȷ��0-����
******************************************************/
int bookticket(airlinehead* headline, clienthead* headclient)//��Ʊ
{
	//headclient->count=0;
	cout << "�����뺽���: ";
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
		cout << "δ�ҵ��ú���" << endl;
		return 0;
	}
	if (temp->left == 0)
	{
		cout << "�Բ���,�ú���Ʊ�Ѿ����ꡣ��ѡ��ִ�����²���" << endl;
		int sel;	
		cout << "1.ѡ���."<< endl;
		cout << "2.ȡ����Ʊ." << endl;
		cin >> sel;
		client* temp_client = new client;
		switch (sel)
		{
			case 1:
				cout << "���������֤������: ";
				cin >> custom->id;
				cout << endl;
				cout << "�������������:";
				cin >> custom->name;
				cout << endl;
				cout << "�����붩Ʊ��:";
				cin >> custom->bookcount;
				custom->seat_num = temp->total - temp->left + 1;
				strcpy_s(custom->line_num, line_num);
				//�޸ĸú�������
				
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
				//�޸�client
				headclient->count++;
				custom->next = headclient->next;
				headclient->next = custom;
				cout << "�򲹳ɹ���" << endl;
				return 1;
				break;
			case 2:
				return 0;
			default:
				break;
		}
	}
	cout << "���������֤������: ";
	cin >> custom->id;
	cout << endl;
	cout << "�������������:";
	cin >> custom->name;
	cout << endl;
	cout << "�����붩Ʊ��:";	
	cin >> custom->bookcount;
	cout << endl;
	if(temp->left < custom->bookcount)
	{
		cout << "��Ʊ���㣬��ִ�����²�����" << endl;
		cout << "1.ѡ���" << endl;
		cout << "2.�鿴ת��" << endl;
		cout << "3.ȡ����Ʊ" << endl;
		cout << "�����������";
		int sel;
		cin >> sel;
		client* temp_client = new client;
		switch (sel)
		{
			case 1:
				cout << "���������֤������: ";
				cin >> custom->id;
				cout << endl;
				cout << "�������������:";
				cin >> custom->name;
				cout << endl;
				cout << "�����붩Ʊ��:";
				cin >> custom->bookcount;

				custom->seat_num = temp->total - temp->left + 1;
				custom->next = NULL;
				strcpy_s(custom->line_num, line_num);
				//�޸ĸú�������
				
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
				//�޸�client
				headclient->count++;
				custom->next = headclient->next;
				headclient->next = custom;
				cout << "�򲹳ɹ���" << endl;
				break;
			case 2:				
				char start[20], end[20];
				cout << "����������ص㣺";
				cin >> start;
				cout << "������Ŀ�ĵأ�";
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
	cout << "��Ʊ�ɹ���" << endl;
	return 0;
}
/*****************************************************
*������������Ʊ
*���������id
*���������
*����ֵ��1-��ȷ��0-����
******************************************************/
int returnticket(airlinehead* headline, clienthead* headclient)//��Ʊ��
{
	cout << "������˿͵�֤������: ";
	char id[10];
	cin >> id;
	airline* airlinetemp = headline->next;
	client* clienttemp = headclient->next;
	if (NULL == airlinetemp)
	{
		cout << "��ǰû�к�����Ϣ��" << endl;
		return 0;
	}
	char line_num[10];
	client* delnext;
	client* delnext2;
	if (strcmp(clienttemp->id, id) == 0)//Ҫɾ���Ľڵ�Ϊ��һ��ʱ
	{
		strcpy_s(line_num, clienttemp->line_num);
		while (airlinetemp)//�޸���Ʊ�ͻ�����Ӧ�ĺ������Ʊ��Ϣ��
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
		cout << "��Ʊ�ɹ�!ϣ���л�����������������"<<endl;
		check(airlinetemp);
		return 1;
	}
	while (clienttemp->next)//Ҫɾ���Ľڵ㲻�ǵ�һ��ʱ
	{
		if (strcmp(clienttemp->next->id, id) == 0)
		{
			strcpy_s(line_num, clienttemp->next->line_num);

			while (airlinetemp)//�޸���Ʊ�ͻ�����Ӧ�ĺ������Ʊ��Ϣ��
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
			
			cout << "��Ʊ�ɹ����л������������" << endl;
			check(airlinetemp);
			return 1;
			break;
		}
		clienttemp = clienttemp->next;
	}
	cout << "δ�ҵ��ÿͻ�����Ϣ��" << endl;
	return 0;
}

//������
void main_menu()
{
	cout << "******************** ��ӭʹ�÷ɻ���Ʊϵͳ************************" << endl << endl;
	cout << "***               1---- ¼�뺽����Ϣ��                        ***" << endl << endl;
	cout << "***               2---- ��ѯ������Ϣ��                        ***" << endl << endl;
	cout << "***               3---- �ͻ���Ʊ��                            ***" << endl << endl;
	cout << "***               4---- �ͻ���Ʊ��                            ***" << endl << endl;
	cout << "***               5---- ������к�����Ϣ��                    ***" << endl << endl;
	cout << "***               6---- ������й˿���Ϣ��                    ***" << endl << endl;
	cout << "***               7---- �޸ĺ�����Ϣ��                        ***" << endl << endl;
	cout << "***               0---- �˳�ϵͳ��                            ***" << endl << endl;
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
		cout << "��ѡ����Ҫ���еĲ���: ";
		cin >> n;
		cout << endl;
		switch (n)
		{
		case 1:
			int num;
			cout << "��ѡ����Ҫ¼��ĺ������Ŀ�� ";
			cin >> num;
			cout << endl;
			import(num, headline);
			cout << endl;
			//display_all_line(headline);
			cout << "������Ϣ�ɹ�¼�롣��";
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
