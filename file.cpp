//˳�����Ա�
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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;

status IntiaList(SqList & L);
void CreatList(SqList &L, int len);
void PrintList(SqList L);
void DestroyList(SqList & L);
void ClearList(SqList &L);
bool ListEmpty(SqList L);
int ListLength(SqList L);
ElemType GetElem(SqList &L, int i, ElemType *e);
status compare(ElemType e1, ElemType e2);
int LocateElem(SqList L, ElemType e, status(*compare)(ElemType, ElemType));
ElemType PriorElem(SqList L, ElemType cur, ElemType *pre_e);
ElemType NextElem(SqList L, ElemType cur, ElemType *next_e);
status ListInsert(SqList & L, int i, ElemType e);
ElemType ListDelete(SqList & L, int i, ElemType *e);
bool visit(ElemType e);
status ListTrabverse(SqList L, bool(*visit)(ElemType));
void Mergelist(SqList L1, SqList L2, SqList &L3);
void Mergelist1(SqList &La, SqList Lb);
void Mergelist2(SqList L1, SqList L2, SqList &L3);
/*--------------------------------------------*/
int main(){
	SqList L;
	int op = 1;
	int Sqlen;
	if (!IntiaList(L)){
		printf("���Ա��ʼ��ʧ�ܣ�\n");
		exit(ERROR);
	}
	printf("������˳���Ԫ�ظ���: ");
	scanf("%d", &Sqlen);
	CreatList(L, Sqlen);
	printf("������˳���Ϊ��\n");
	PrintList(L);
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
		scanf("%d", &op);
		switch (op){
		case 1://���ձ�
			if (IntiaList(L) == OK) printf("���Ա����ɹ���\n");
			else {
				printf("���Ա���ʧ�ܣ�\n");
				exit(ERROR);
			}
			getchar(); getchar();
			break;
		case 2://�������Ա�
			DestroyList(L);
			printf("���Ա����٣�\n");
			getchar(); getchar();
			break;
		case 3://������Ա�
			ClearList(L);
			printf("���Ա���գ�\n");
			getchar(); getchar();
			break;
		case 4://�ж����Ա��Ƿ�Ϊ��
			if (ListEmpty(L) == true)
				printf("���Ա�Ϊ�գ�\n");
			else
				printf("���Ա�Ϊ�գ�\n");
			getchar(); getchar();
			break;
		case 5://�����Ա���
			printf("���Ա���Ϊ%d\n", ListLength(L));
			getchar(); getchar();
			break;
		case 6://��ĳ��λ�õ�Ԫ��
			int location, e;
			printf("������ҵ�λ�ã�");
			scanf("%d", &location);
			while (location > L.length || location < 1){
				printf("����λ�ô����������룡\n");
				scanf("%d", &location);
			}
			printf("��%d��Ԫ��Ϊ��%d\n", location, GetElem(L, location, &e));
			getchar(); getchar();
			break;
		case 7://��ĳ��Ԫ�ص�λ��
			int element;
			printf("������ҵ�Ԫ�أ�");
			scanf("%d", &element);
			if (!LocateElem(L, element, *compare))
				printf("��˳�����û��%d���Ԫ�ء�\n", element);
			else
				printf("%d��˳������ǵ�%d��Ԫ��\n", element, LocateElem(L, element, *compare));
			getchar(); getchar();
			break;
		case 8://��ĳ��Ԫ�ص�ǰ��
			int current, pre;
			printf("�����뵱ǰԪ�أ�");
			scanf("%d", &current);
			PriorElem(L, current, &pre);
			getchar(); getchar();
			break;
		case 9://��ĳ��Ԫ�صĺ��
			int current_1, next;
			printf("�����뵱ǰԪ�أ�");
			scanf("%d", &current_1);
			NextElem(L, current_1, &next);
			getchar(); getchar();
			break;
		case 10://������Ԫ��
			int location_1, element_1;
			printf("�������λ�ã�");
			scanf("%d", &location_1);
			while (location_1>L.length + 1 || location_1<1)
			{
				printf("����λ�ô����������룡\n");
				scanf("%", &location_1);
			}
			printf("���������Ԫ�أ�");
			scanf("%d", &element_1);
			if (!ListInsert(L, location_1, element_1)){
				printf("���Ա����ʧ�ܣ�\n");
				exit(ERROR);
			}
			printf("������˳���Ϊ: \n");
			PrintList(L);
			getchar(); getchar();
			break;
		case 11://ɾ��ĳԪ��
			int location_2, element_2;
			printf("����ɾ��λ�ã�");
			scanf("%d", &location_2);
			while (location_2>L.length || location_2<1)
			{
				printf("����λ�ô����������룡\n");
				scanf("%", &location_2);
			}
			if (!ListDelete(L, location_2, &element_2)){
				printf("ɾ������\n");
				exit(ERROR);
			}
			printf("��ɾ����Ԫ��Ϊ��%d\n", element_2);
			printf("��ɾ�����˳���Ϊ�� \n");
			PrintList(L);
			getchar(); getchar();
			break;
		case 12://����
			printf("������");
			ListTrabverse(L, visit);
			printf("\n");
			getchar(); getchar();
			break;
		case 13://�ϲ�
			//�ϲ��㷨1ʱ�临�Ӷ�ΪO��La.length+Lb.length��
			/*SqList La,L_last;
			int Sqlen1;
			if (!IntiaList(La)){
				printf("���Ա��ʼ��ʧ�ܣ�\n");
				exit(ERROR);
			}
			printf("������˳���Ԫ�ظ���: ");
			scanf("%d", &Sqlen1);
			CreatList(La, Sqlen1);
			Mergelist(L, La, L_last);
			printf("�ϲ����˳���Ϊ�� \n");
			PrintList(L_last);*/

			//�ϲ��㷨2ʱ�临�Ӷ�ΪO��La.lengthxLb.length��
			/*SqList L1;
			int Sqlen1;
			if (!IntiaList(L1)){
				printf("���Ա��ʼ��ʧ�ܣ�\n");
				exit(ERROR);
			}
			printf("������˳���Ԫ�ظ���: ");
			scanf("%d", &Sqlen1);
			CreatList(L1, Sqlen1);
			Mergelist1(L, L1);
			printf("�ϲ����˳���Ϊ�� \n");
			PrintList(L);*/

			//�ϲ��㷨3ʱ�临�Ӷ�ΪO��La.length+Lb.length��
			SqList La, L_last;
			int Sqlen1;
			if (!IntiaList(La)){
				printf("���Ա��ʼ��ʧ�ܣ�\n");
				exit(ERROR);
			}
			printf("������˳���Ԫ�ظ���: ");
			scanf("%d", &Sqlen1);
			CreatList(La, Sqlen1);
			Mergelist2(L, La, L_last);
			printf("�ϲ����˳���Ϊ�� \n");
			PrintList(L_last);
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	system("pause");
	return 0;
}

status IntiaList(SqList & L){
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof (ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

void CreatList(SqList &L, int len){
	if (len > LIST_INIT_SIZE){
		L.elem = (ElemType *)malloc(len * sizeof (ElemType));
		L.length = len;
	}
	printf("������˳���Ԫ�أ�\n");
	for (int i = 0; i <= len - 1; i++){
		scanf("%d", &L.elem[i]);
	}
	printf("\n");
	L.length = len;
}

void PrintList(SqList L){
	int n=L.length;
	for (int i = 0; i <= n - 1; i++){
		printf("%d ", L.elem[i]);
	}
	printf("\n");
	printf("˳���%d��Ԫ�ء� \n", L.length);
}

void DestroyList(SqList & L){
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
}

void ClearList(SqList &L){
	L.length = 0;
}

bool ListEmpty(SqList L){
	if (L.length == 0)
		return true;
	else
		return false;
}

int ListLength(SqList L){
	return L.length;
}

ElemType GetElem(SqList &L, int i, ElemType *e){
	if (i<1 || i>L.length || !L.elem)
		exit(ERROR);
	e = L.elem + (i - 1);
	return *e;
}

status compare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return true;
	return false;
}

int LocateElem(SqList L, ElemType e, status(*compare)(ElemType, ElemType)){
	int i = 1;
	ElemType *p = L.elem;
	while (i <= L.length &&!(*compare)(*p++, e))
	{
		++i;
	}
	if (i <= L.length)
	{
		return i;
	}
	else
	{
		return 0;
	}
}

ElemType PriorElem(SqList L, ElemType cur, ElemType *pre_e){
	ElemType e, f;
	int i = LocateElem(L, cur, *compare);
	if (!i || i == 1)
		printf("%d����˳����Ϊ��һ��Ԫ��", cur);
	else{
		f = GetElem(L, i - 1, &e);
		pre_e = &f;
		printf("%d��ǰ��Ϊ��%d\n", cur, *pre_e);
	}
	return OK;
}

ElemType NextElem(SqList L, ElemType cur, ElemType *next_e){
	ElemType e, f;
	int i = LocateElem(L, cur, *compare);
	if (!i || i == L.length)
		printf("%d����˳����Ϊ���һ��Ԫ��", cur);
	else{
		f = GetElem(L, i + 1, &e);
		next_e = &f;
		printf("%d�ĺ��Ϊ��%d\n", cur, *next_e);
	}
	return OK;
}

status ListInsert(SqList &L, int i, ElemType e){
	ElemType *newbase;
	int *q, *p;
	if (i<1 || i>L.length + 1) {
		printf("����λ�ô���\n");
		return ERROR;
	}
	if (L.length >= L.listsize){
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	if (i == L.length + 1)
		L.elem[i - 1] = e;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; p--)
		*(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}

ElemType ListDelete(SqList &L, int i, ElemType *e){
	int *q, *p;
	if ((i<1) || (i>L.length))return ERROR;
	p = &(L.elem[i - 1]);
	*e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return *e;
}

bool visit(ElemType e){
	printf(" %d", e);
	return true;
}

status ListTrabverse(SqList L, bool(*visit)(ElemType)){
	int i = 1;
	ElemType *p = L.elem;
	while (i <= L.length && (*visit)(*p++)) ++i;
	return OK;
}

void Mergelist(SqList L1, SqList L2, SqList &L3){
	ElemType *p1, *p2, *p3,*p1_last,*p2_last;
	p1 = L1.elem;
	p2 = L2.elem;
	L3.length = L1.length + L2.length;
	L3.listsize = L3.length;
	L3.elem= (ElemType*)malloc(L3.listsize*sizeof(ElemType));
	p3 = L3.elem;
	if (!L3.elem)
		exit(OVERFLOW);
	p1_last = L1.elem + L1.length - 1;
	p2_last = L2.elem + L2.length - 1;
	while (p1 <= p1_last&&p2 < p2_last){
		if (*p1 <= *p2)
			*p3++ = *p1++;
		else
			*p3++ = *p2++;
	}
	while (p1 <=p1_last)
		*p3++ = *p1++;
	while (p2 <= p2_last)
		*p3++ = *p2++;
}

void Mergelist1(SqList &La, SqList Lb){
	int e;
	int la_len = La.length;
	for (int i = 1 ; i <=Lb.length ; i++){
		if (!LocateElem(La, GetElem(Lb, i, &e), *compare))
			ListInsert(La, ++la_len, GetElem(Lb, i, &e));
	}
}

void Mergelist2(SqList L1, SqList L2, SqList &L3){
	IntiaList(L3);
	int i = 1;
	int j = 1;
	int k = 0;
	int e1, e2;
	while (i <= L1.length&&j <= L2.length){
		int a1 = GetElem(L1, i, &e1);
		int b1 = GetElem(L2, j, &e2);
		if (a1 <= b1){
			ListInsert(L3, ++k, a1);
			++i;
		}
		else{
			ListInsert(L3, ++k, b1);
			++j;
		}
	}
	while (i <= L1.length){
		int a_1 = GetElem(L1, i++, &e1);
		ListInsert(L3, ++k, a_1);
	}
	while (j <= L2.length){
		int b_1 = GetElem(L2, j++, &e2);
		ListInsert(L3, ++k, b_1);
	}
}