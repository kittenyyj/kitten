#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

typedef struct EN
{
	char name[30];
    char buf[100];
	struct EN *next;
}en;

en *CreateList();
void InsertList(en *head,char *name,char *buf);
void deleteList(en *head,char *name);
void displayList(en *head);
void clearList(en *head);
void destroyList(en *head);
void chaxunList(en *head,char *name);
void xiugaiList(en *head,char *name,char *buf);
void readFile(en *head);
int jiemian();
void writeList(en *head);
void chaxuList1(en *head,char *buf);
void writeList1(char *name,char *buf);
void displayList1();
void InsertList1(en *head,char *name,char *buf);
void qingkong();
int main()
{
	int num;
	char name[30];
	char buf[100];
	en *head=CreateList();
	readFile(head);
	while(1)
	{
		num = jiemian();
		switch(num)
		{
		case 1:
			printf("请输入添加的英语单词:\n");
			scanf("%s",name);
            printf("请输入该单词的翻译:\n");
            scanf("%s",buf);
            InsertList1(head,name,buf);
			writeList(head);
			break;
		case 2:
			printf("请输入单词:\n");
			scanf("%s",name);
            chaxunList(head,name);
			break;
		case 3:
			printf("请输入中文:\n");
			scanf("%s",buf);
			chaxuList1(head,buf);
			break;
		case 4:
			printf("历史记录为:\n");
			displayList1();
			break;
		case 5:
			qingkong();
			printf("已清空历史记录:\n");
			break;
		case 6:
			return 0;
		}
	}
	return 0;
}

en *CreateList()
{
	en *head = (en *)malloc(sizeof(en));
	assert(head != NULL);
	strcpy(head->name,"-555");
    strcpy(head->buf,"英语");
	head->next=NULL;
	return head;
}

void InsertList(en *head,char *name,char *buf)
{
	en *pnew=(en *)malloc(sizeof(en));
	assert(pnew != NULL);
	strcpy(pnew->name,name+1);
    strcpy(pnew->buf,buf+6);
	pnew->next = head->next;
	head->next=pnew;
}

void deleteList(en *head,char *name)
{
	en *p=head->next;
	en *q=head;
	while(p != NULL)
	{
		if(strcmp(p->name,name) == 0)
		{
			q->next=p->next;
			free(p);
			break;
		}
		else
		{
			p=p->next;
			q=q->next;
		}
	};

};

void displayList(en *head)
{
	char ch[100];
	int n;
	int i;
	en *p=head->next;
	while(p !=NULL)
	{
		printf("%s\n",p->name);
		strcpy(ch,p->buf);
		n=sizeof(p->buf)-1;
		for(i=1;i<=n;i++)
		{
			if(ch[i]=='@')
			{
				ch[i]='\n';
			}
		}
		printf("%s\n",ch);
		p=p->next;
	}
}

void clearList(en *head)
{
  en *p=head->next;
   while(p != NULL)
	{
	   head->next = p->next;
	   free(p);
	   p = head->next;
	}
}

void destroyList(en *head)
{
	en *p=head->next;
	while(p != NULL)
	{
		en *q;
		q=p;
		p=p->next;
		free(q);
	}
	free(p);
}

void chaxunList(en *head,char *name)
{
	char ch[100];
	int n;
	int i;
	en *p=head->next;
    while(p != NULL)
	{
		if(strcmp(p->name,name)==0)
		{
			break;
		}
		p=p->next;
	}
    if(p == NULL)
	{
        printf("未找到该单词\n");
		return;
	}
	else
	{
		strcpy(ch,p->buf);
		n=sizeof(p->buf)-1;
		for(i=1;i<=n;i++)
		{
			if(ch[i]=='@')
			{
				ch[i]='\n';
			}
		}
		printf("翻译为:\n%s\n",ch);
	}
	writeList1(p->name,p->buf);
}

void chaxuList1(en *head,char *buf)
{
	en *p=head->next;
    while(p != NULL)
	{
		if(strcmp(p->buf+3,buf)==0)
		{
			break;
		}
		p=p->next;
	}
    if(p == NULL)
	{
        printf("未找到该单词\n");
		return;
	}
	else
	{
		printf("%s\n%s\n",p->name,p->buf);
	}
	writeList1(p->name,p->buf);
}

void xiugaiList(en *head,char *name,char *buf)
{
    en *p=head->next;
    while(p != NULL)
	{
		if(strcmp(p->name,name)==0)
		{
			strcpy(p->buf,buf);
			break;
		}
		p=p->next;
	}
    if(p == NULL)
	{
        printf("未找到该单词\n");
	}
}

void readFile(en *head)
{
	char name[20];
	char buf[100];
	FILE *fp =fopen("dict.txt","r");
	if(fp == NULL)
	{
		printf("打开文件失败\n");
	}
	while(fgets(name,20,fp) != NULL)
	{
		strtok(name,"\n");
		fgets(buf,100,fp);
        strtok(buf,"\n");
        InsertList(head,name,buf);
	}
	fclose(fp);
};

int jiemian()
{
	int b;
	int n;
	printf("*****************\n");
	printf("选择功能:\n");
    printf("1 添加英语单词:\n");
    printf("2 查看中文翻译:\n");
	printf("3 查看英文:\n");
    printf("4 查看历史记录:\n");
	printf("5 清空历史记录:\n");
	printf("6 退出:\n");
	printf("*****************\n");
	fflush(stdin);
	n=scanf("%d",&b);
	return b;
}

void writeList(en *head)
{
	en *p=head->next;
	FILE *fp=fopen("a.txt","w");
	while(p != NULL)
	{
		fputs(p->name,fp);
		putc('\n',fp);
		fputs(p->buf,fp);
		putc('\n',fp);
		p=p->next;
	}
	fclose(fp);
}
void writeList1(char *name,char *buf)
{
	FILE *fp=fopen("b.txt","a");
	fputs(name,fp);
	putc('\n',fp);
	fputs(buf,fp);
	putc('\n',fp);
	fclose(fp);
}
void displayList1()
{
	char ch[100];
	int n;
	int i;
    FILE *fp=fopen("b.txt","r");
	if(fp == NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	while(fgets(ch,100,fp) != NULL)
	{
		printf("%s",ch);
        fgets(ch,100,fp);
		n=sizeof(ch)-1;
		for(i=1;i<=n;i++)
		{
			if(ch[i]=='@')
			{
				ch[i]='\n';
			}
		}
		printf("%s",ch);
	}
	fclose(fp);
}
void InsertList1(en *head,char *name,char *buf)
{
	en *pnew=(en *)malloc(sizeof(en));
	assert(pnew != NULL);
	strcpy(pnew->name,name);
    strcpy(pnew->buf,buf);
	pnew->next = head->next;
	head->next=pnew;
}
void qingkong()
{
	FILE *fp=fopen("b.txt","w");
	fclose(fp);
}
