//������
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
typedef struct LNODE{  //��������
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
		printf("    ��ѡ����Ĳ���[0~13]:");
		scanf("%d", &choice);
		switch (choice){
		case 1://���ձ�
			if (IntiaList(L) == OK)
				printf("���������ɹ���\n");
			else {
				printf("���������ʧ�ܣ�\n");
				exit(ERROR);
			}
			getchar(); getchar();
			break;
		case 2://��������
			DestroyList(L);
			printf("�������٣�\n");
			getchar(); getchar();
			break;
		case 3://�������
			ClearList(L);
			printf("������գ�\n");
			getchar(); getchar();
			break;
		case 4://�ж������Ƿ�Ϊ��
			if (ListEmpty(L) == true)
				printf("����Ϊ�գ�\n");
			else
				printf("����Ϊ�գ�\n");
			getchar(); getchar();
			break;
		case 5://��������
			printf("���Ա���Ϊ%d\n", ListLength(L));
			getchar(); getchar();
			break;
		case 6://����ĳ��λ�õ�Ԫ��
			int e, i;
			printf("������ҵ�λ�ã�");
			scanf("%d", &i);
			while (i<1 || i>ListLength(L)){
				printf("����λ�ô����������룡\n");
				scanf("%d", &i);
			}
			if (GetElem(L, i, e))
				printf("\n��%d��Ԫ��ֵΪ��%d\n", i, e);
			getchar(); getchar();
			break;
		case 7://����ĳ��Ԫ�ص�λ��
			int e1;
			printf("������ҵ�Ԫ�أ�");
			scanf("%d", &e1);
			if (!LocateElem(L, e1, *compare))
				printf("��������û��%d���Ԫ�ء�\n", e1);
			else
				printf("%d���������ǵ�%d��Ԫ��\n", e1, LocateElem(L, e1, *compare));
			getchar(); getchar();
			break;
		case 8://��ĳԪ�ص�ǰ��
			int current, pre;
			printf("�����뵱ǰԪ�أ�");
			scanf("%d", &current);
			PriorElem(L, current, pre);
			getchar(); getchar();
			break;
		case 9://��ĳԪ�صĺ��
			int current_1, next;
			printf("�����뵱ǰԪ�أ�");
			scanf("%d", &current_1);
			NextElem(L, current_1, next);
			getchar(); getchar();
			break;
		case 10://������Ԫ��
			int location, element;
			printf("�������λ�ã�\n");
			scanf("%d", &location);
			while (location<1 || location>ListLength(L)+1){
				printf("����λ�ô����������룡\n");
				scanf("%d", &location);
			}
			printf("���������Ԫ�أ�\n");
			scanf("%d", &element);
			ListInsert(L, location, element);
			print_list(L);
			getchar(); getchar();
			break;
		case 11://ɾ��ĳԪ��
			int location_1;
			ElemType ele;
			printf("����ɾ��Ԫ��λ�ã�\n");
			scanf("%d", &location_1);
			while (location_1<1 || location_1>ListLength(L)){
				printf("����λ�ô����������룡\n");
				scanf("%d", &location_1);
			}
			ListDelete(L, location_1, ele);
			printf("��ɾ����Ԫ��Ϊ��%d\n", ele);
			print_list(L);
			getchar(); getchar();
			break;
		case 12://����
			printf("������");
			ListTrabverse(L, visit);
			printf("\n");
			getchar(); getchar();
			break;
		case 13://�ϲ�
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
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	system("pause");
	return 0;
}//end of main()

void print_list(Linklist L){
	Linklist p;
	printf("�����ĵ�����Ϊ��\n");
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
	//������������Ԫ��
	/*Linklist p;
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	printf("��������������Ԫ��Ctrl+Z�������������б�ͷ��������\n");
	p = (LNode*)malloc(sizeof(LNode));
	while ((scanf("%d", &(p->data))) != EOF){
		p->next = L->next;
		L->next = p;
		p = (LNode*)malloc(sizeof(LNode));
	}*/

	//˳����������Ԫ��
	int n;
	Linklist nail,q;
	L = (LNode*)malloc(sizeof(LNode));
    nail = L;
	printf("������n��n������Ԫ��:\n");
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
		printf("û���������\n");
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
		printf("%d���������Ϊ��һ��Ԫ��", cur);
	else{
		GetElem(L, i - 1, e);
		f = e;
		pre_e = f;
		printf("%d��ǰ��Ϊ��%d\n", cur, pre_e);
	}
	return OK;
}

ElemType NextElem(Linklist L, ElemType cur, ElemType &next_e){
	ElemType e, f;
	int i = LocateElem(L, cur, *compare);
	if (!i || i == ListLength(L))
		printf("%d���������Ϊ���һ��Ԫ��", cur);
	else{
		GetElem(L, i + 1, e);
		f = e;
		next_e = f;
		printf("%d�ĺ��Ϊ��%d\n", cur, next_e);
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