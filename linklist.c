# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <malloc.h>
# include <stdbool.h>

typedef struct Node {
    int data;      // 存储的数据
    struct Node* next;  // 指向下一个节点的指针 递归的思想，每一个结点往后指向的又是一个结构体内的数据和指针
} Node,*Linklist;//Node等价于struct Node  Linklist等价于struct Node*

//create_list需要返回值，且返回的是一个地址，故为Linklist类型
Linklist create_list(void) {
    int len;
    printf("请输入需要生成链表结点个数");
    scanf("%d",&len);
    int val;//用来存放输入的值
    
    //分配了一个不存放有效数据的头结点
    Linklist head = (Linklist)malloc(sizeof(Node));//此处的head与主函数中的head代表的意义不一样
    if(head == NULL)
    {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    Linklist tail = head;
    tail->next = NULL;//使尾结点一直在最后
    
    for(int i = 0;i < len;i++)
    {
        printf("请输入第%d个结点的值",i+1);
        scanf("%d",&val);
        Linklist new = (Linklist)malloc(sizeof(Node));//每循环一次就造出一个新节点
        if(new == NULL)
    {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    new->data = val;
    tail->next = new;//尾插法
    new->next = NULL;
    tail = new;
    }
    return head;
}

//遍历链表
void traverse_list(Linklist head)
{
    Linklist p = head->next;
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
    return;
}

//链表判空
bool is_empty(Linklist head)
{
    if(head->next == NULL)
    {
        return true;
    }
    else return false;
}

//求链表长度
int length_list(Linklist head)
{
    
    Linklist p = head->next;
    int len = 0;
    while(p != NULL)
    {
        ++len;
        p = p->next;
    }
    return len;
}
bool insert_list(Linklist head,int pos,int val) {
    int i = 0;
    Linklist p = head;
    while(p != NULL && i < pos-1)
    {
        p = p->next;
        ++i;
    }
    if(p == NULL || i > pos - 1)
    {
        return false;
    }
    Linklist new = (Linklist)malloc(sizeof(Linklist));
    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    new->data = val;
    Linklist q = p->next;
    p->next = new;
    new->next = q;
    return true;
}
bool delete_list(Linklist head, int pos,int *val)//把删除的结点放到第三个形参中
{
    int i = 0;
    Linklist p = head;
    while(p->next != NULL && i < pos-1)
    {
        p = p->next;
        ++i;
    }
    if(p->next == NULL || i > pos - 1)
    {
        return false;
    }
    
    Linklist q = p->next;
    *val = q->data;
    p->next = p->next->next;
    free(q);
    q = NULL;
}

//排序
//冒泡排序
//    int i,j;
//    for(i = 0;i<len-1;i++)
//    {
//     for(j = i+1;j<len;j++)
//     {
//         if(a[i] > a[j])
//         {
//             int t=a[i];
//             a[i]=a[j];
//             a[j]=t;
//         }
//     }
//    }
void sort_list(Linklist head)
{
    int i,j;
    Linklist p,q;
    int len = length_list(head);
    for(i = 0,p = head->next;i<len-1;i++,p = p->next)
    {
     for(j = i+1,q = p->next;j<len;j++,q = q->next)
     {
         if(p->data > q->data)
         {
             int t = p->data;
             p->data = q->data;
             p->data = t;
         }
     }
    }
    return;
}
int main() {
    Linklist head = NULL;
    int val;
    head = create_list();//创建一个非循环单链表，并将头结点的地址赋给head
    traverse_list(head);
    
    //insert_list(head,2,33);
    if(delete_list(head,3,&val))
    {
        printf("删除成功，删除的元素是%d\n",val);
    }
    else
    {
        printf("删除失败\n");
    }
    traverse_list(head);
    
    // int len = length_list(head);
    // printf("链表长度是%d\n",len);
    
    // if( is_empty(head))
    // {
    //     printf("链表为空\n");
    // }
    // else
    // {
    //     printf("链表不空\n");
    // }
    
    
    // sort_list(head);
    // traverse_list(head);
    
    // insert_list(head,2,33);
    return 0;
}