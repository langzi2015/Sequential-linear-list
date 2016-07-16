//单链表
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;
typedef struct LNODE{  //单链表定义
	int data;
	struct LNODE *next;
}LNode, *Linklist;

void print_list(Linklist L);
status IntiaList(Linklist &L);
void CreatList(Linklist &L);
status DestroyList(Linklist &L);
status ClearList(Linklist &L);
bool ListEmpty(Linklist L);
int ListLength(Linklist L);
ElemType GetElem(Linklist &L, int i, ElemType &e);
status compare(ElemType e1, ElemType e2);
int LocateElem(Linklist L, ElemType e, status(*compare)(ElemType, ElemType));
ElemType PriorElem(Linklist L, ElemType cur, ElemType &pre_e);
ElemType NextElem(Linklist L, ElemType cur, ElemType &next_e);
status ListInsert(Linklist & L, int i, ElemType e);
status ListDelete(Linklist & L, int i, ElemType &e);
bool visit(ElemType e);
status ListTrabverse(Linklist L, bool(*visit)(ElemType));
void Mergelist(Linklist La, Linklist Lb, Linklist &Lc);
/*--------------------------------------------*/
int main(){
	Linklist L;
	int op = 1;
	CreatList(L);
	print_list(L);
	int choice;
	while (op){
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaList       7. LocateElem\n");
		printf("    	  2. DestroyList     8. PriorElem\n");
		printf("    	  3. ClearList       9. NextElem \n");
		printf("    	  4. ListEmpty      10. ListInsert\n");
		printf("    	  5. ListLength     11. ListDelete\n");
		printf("    	  6. GetElem        12. ListTrabverse\n");
		printf("    	 13. MergeList       0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~13]:");
		scanf("%d", &choice);
		switch (choice){
		case 1://建空表
			if (IntiaList(L) == OK)
				printf("空链表创建成功！\n");
			else {
				printf("空链表表创建失败！\n");
				exit(ERROR);
			}
			getchar(); getchar();
			break;
		case 2://销毁链表
			DestroyList(L);
			printf("链表销毁！\n");
			getchar(); getchar();
			break;
		case 3://清空链表
			ClearList(L);
			printf("链表清空！\n");
			getchar(); getchar();
			break;
		case 4://判断链表是否为空
			if (ListEmpty(L) == true)
				printf("链表为空！\n");
			else
				printf("链表不为空！\n");
			getchar(); getchar();
			break;
		case 5://求链表长度
			printf("线性表长度为%d\n", ListLength(L));
			getchar(); getchar();
			break;
		case 6://查找某个位置的元素
			int e, i;
			printf("输入查找的位置：");
			scanf("%d", &i);
			while (i<1 || i>ListLength(L)){
				printf("输入位置错误，重新输入！\n");
				scanf("%d", &i);
			}
			if (GetElem(L, i, e))
				printf("\n第%d个元素值为：%d\n", i, e);
			getchar(); getchar();
			break;
		case 7://查找某个元素的位置
			int e1;
			printf("输入查找的元素：");
			scanf("%d", &e1);
			if (!LocateElem(L, e1, *compare))
				printf("该链表中没有%d这个元素。\n", e1);
			else
				printf("%d在链表中是第%d个元素\n", e1, LocateElem(L, e1, *compare));
			getchar(); getchar();
			break;
		case 8://求某元素的前驱
			int current, pre;
			printf("请输入当前元素：");
			scanf("%d", &current);
			PriorElem(L, current, pre);
			getchar(); getchar();
			break;
		case 9://求某元素的后继
			int current_1, next;
			printf("请输入当前元素：");
			scanf("%d", &current_1);
			NextElem(L, current_1, next);
			getchar(); getchar();
			break;
		case 10://插入新元素
			int location, element;
			printf("输入插入位置：\n");
			scanf("%d", &location);
			while (location<1 || location>ListLength(L)+1){
				printf("输入位置错误，重新输入！\n");
				scanf("%d", &location);
			}
			printf("请输入插入元素：\n");
			scanf("%d", &element);
			ListInsert(L, location, element);
			print_list(L);
			getchar(); getchar();
			break;
		case 11://删除某元素
			int location_1;
			ElemType ele;
			printf("输入删除元素位置：\n");
			scanf("%d", &location_1);
			while (location_1<1 || location_1>ListLength(L)){
				printf("输入位置错误，重新输入！\n");
				scanf("%d", &location_1);
			}
			ListDelete(L, location_1, ele);
			printf("被删除的元素为：%d\n", ele);
			print_list(L);
			getchar(); getchar();
			break;
		case 12://遍历
			printf("遍历：");
			ListTrabverse(L, visit);
			printf("\n");
			getchar(); getchar();
			break;
		case 13://合并
			Linklist L1, L_last;
			CreatList(L1);
			print_list(L1);
			Mergelist(L, L1, L_last);
			print_list(L_last);
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	system("pause");
	return 0;
}//end of main()

void print_list(Linklist L){
	Linklist p;
	printf("建立的单链表为：\n");
	p = L->next;
	while (p != NULL){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

status IntiaList(Linklist &L){
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}

void CreatList(Linklist &L){
	//逆序输入链表元素
	/*Linklist p;
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	printf("请逆序输入链表元素Ctrl+Z结束，建立带有表头结点的链表：\n");
	p = (LNode*)malloc(sizeof(LNode));
	while ((scanf("%d", &(p->data))) != EOF){
		p->next = L->next;
		L->next = p;
		p = (LNode*)malloc(sizeof(LNode));
	}*/

	//顺序输入链表元素
	int n;
	Linklist nail,q;
	L = (LNode*)malloc(sizeof(LNode));
    nail = L;
	printf("请输入n和n个数据元素:\n");
	scanf("%d",&n);
	while(n--)
	{
	q = (LNode*)malloc(sizeof(LNode));
	scanf("%d",&(q->data));
	q->next=NULL;
	nail->next= q;
	nail=q;
	}
}

status DestroyList(Linklist &L){
	Linklist q;
	while (L){
		q = L->next;
		free(L);
		L = q;
	}
	return OK;
}

status ClearList(Linklist &L){
	Linklist p, q;
	p = L->next;
	while (p){
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}

bool ListEmpty(Linklist L){
	if (!L || L->next == NULL)
		return true;
	else
		return false;
}

int ListLength(Linklist L){
	int num = 0;
	Linklist p;
	p = L->next;
	while (p){
		num++;
		p = p->next;
	}
	return num;
}

status GetElem(Linklist &L, int i, ElemType &e){
	int j = 1;
	Linklist p;
	p = L->next;
	while (p&&j < i){
		p = p->next;
		++j;
	}
	if (!p || j>i){
		printf("没有这个数！\n");
		return ERROR;
	}
	e = p->data;
	return OK;
}

status compare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return true;
	return false;

}

int LocateElem(Linklist L, ElemType e, status(*compare)(ElemType, ElemType)){
	Linklist p;
	int i = 0;
	p = L->next;
	while (p){
		i++;
		if ((*compare)(p->data, e)){
			return i;
		}
		p = p->next;
	}
	return 0;
}

ElemType PriorElem(Linklist L, ElemType cur, ElemType &pre_e){
	ElemType e, f;
	int i = LocateElem(L, cur, *compare);
	if (!i || i == 1)
		printf("%d不在链表或为第一个元素", cur);
	else{
		GetElem(L, i - 1, e);
		f = e;
		pre_e = f;
		printf("%d的前驱为：%d\n", cur, pre_e);
	}
	return OK;
}

ElemType NextElem(Linklist L, ElemType cur, ElemType &next_e){
	ElemType e, f;
	int i = LocateElem(L, cur, *compare);
	if (!i || i == ListLength(L))
		printf("%d不在链表或为最后一个元素", cur);
	else{
		GetElem(L, i + 1, e);
		f = e;
		next_e = f;
		printf("%d的后继为：%d\n", cur, next_e);
	}
	return OK;
}

status ListInsert(Linklist & L, int i, ElemType e){
	int j = 0;
	Linklist s, p;
	p = L;
	while (p&&j < i - 1){
		p = p->next;
		j++;
	}
	if (!p || j>i - 1)
		return ERROR;
	s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return ERROR;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

status ListDelete(Linklist &L, int i, ElemType &e){
	Linklist p, q;
	int j = 0;
	p = L;
	while (p->next&&j < i - 1){
		p = p->next;
		j++;
	}
	if (!p->next || j>i - 1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

bool visit(ElemType e){
	printf(" %d", e);
	return true;
}

status ListTrabverse(Linklist L, bool(*visit)(ElemType)){
	int i = 1;
	Linklist p;
	p = L->next;
	while (i <= ListLength(L) && (*visit)(p->data)){
		i++;
		p = p->next;
	}
	return OK;
}

void Mergelist(Linklist La, Linklist Lb, Linklist &Lc){
	Linklist pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;
	while (pa&&pb){
		if (pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Lb);
}