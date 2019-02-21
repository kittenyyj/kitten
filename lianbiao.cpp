#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
using namespace std;
//创建单链表的成员  其实就是结点
//link p;  p就是一个结点
typedef struct Link {
    int data;  //数据域
    struct Link *next;  //指针域
}link;  //link 为这个结构体的别名

//初始化链表
link *initLink() {
    link *p = (link*)malloc(sizeof(link));  //创建一个头结点
    //动态分配内存
    link *temp = p;  //声明一个指针指向头结点，用于遍历链表
    //14行中创建了一个头结点 定义一个指针  因为p是指针变量 temp也是指针变量
    //生成链表
    for (int i = 1; i < 5; i++) {
        link *a = (link*)malloc(sizeof(link));   //创建一个新的结点
        //对这个结点的成员进行赋值
        a->data = i;
        a->next = NULL;   //这个结点的指针指向NULL 表示结束标志
        temp->next = a;   //temp的作用用来遍历链表
        temp = temp->next;
    }
    return p;
}

//链表的基本操作
//对链表进行插入
link * insertElem(link *p, int elem, int add) {
    link *temp = p;   //创建临时结点用来遍历链表
    //先找到要插入的位置的上一个结点
    for (int i = 1; i < add; i++) {
        if (temp == NULL) {
            printf("插入位置无效\n");
            return p; //这里形参为这个链表的首地址 如果首地址指向为空 说明是一个空链表
            //还有一种情况就是 在i进行遍历的时候还未到达add的位置就已经结束了
        }
        temp = temp->next;   //进行遍历 temp一步的往后移
    }
    //创建插入结点c
    //链表中的所有存储方式必须是以结点的方式
    link *c = (link*)malloc(sizeof(link));   //
    c->data = elem;   //数据域
    //向链表中插入结点
    //这里是插入结点的一个方法 先通过新节点连接后面的数 然后原来的结点连接新节点
    c->next = temp->next;
    temp->next = c;
    return p;
}

link *delElem(link *p, int add) {
    link *temp = p;  //创建一个临时结点用来遍历
    //判断删除位置是否正确
    for (int i = 1; i < add; i++)
    {
        if (temp == NULL) {
            printf("删除位置异常\n");
            return p;
        }
        temp = temp->next;
    }
    link *c = temp->next;   //这里定义的这个非常巧妙
    //此时的c指向被删去的结点
    //要删除直接将其覆盖
    temp->next = c->next;    //这里就ok
    free(c);   //释放内存
    return p;
}

int selectElem(link *p, int elem)
{
    link *temp = p;
    int i = 1;
    while (temp->next) {
        temp = temp->next;
        if (temp->data == elem)
            return i;
    }

    return -1;
}
//进行更改
link *amendElem(link *p, int add, int newElem)
{
    link *temp = p;   //创建一个临时结点用来遍历
    for (int i = 1; i < add; i++)
    {
        if (temp == NULL) {
            printf("更改位置无效\n");
            return p;
        }
        temp = temp->next;
    }
    //此时的temp指向更改位置的前一个点
    link *amend = temp->next;   //创建一个临时结点指向更改的位置
    amend->data = newElem;    //更改数据成功

    return p;
}

//输出链表
void display(link *p) {
    link *temp = p;  //创建一个临时结点用来遍历
    //只要temp->next不指向NULL就输出
    while (temp->next) {
        temp = temp->next;
        printf("%d ", temp->data);
    }
    printf("\n");
}


//测试案例
int main() {
    //初始化链表
    cout<<ttt<<endl;
    printf("\n------初始化链表----------\n");
    link *p = initLink();
    display(p);

    printf("在第4的位置插入元素5：\n");
    p = insertElem(p, 5, 4);
    display(p);

    printf("删除元素3：\n");
    p = delElem(p, 3);
    display(p);

    printf("查找元素2的位置为：\n");
    int address = selectElem(p, 2);
    if (address == -1)
        printf("没有该元素\n");
    else printf("元素2的位子为：%d\n", address);

    printf("更改第3的位置的数为7：\n");
    p = amendElem(p, 3, 7);
    display(p);

    return 0;

}
