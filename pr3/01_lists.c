#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
} list;

// инициализация пустого списка
void init(list *l)
{
	l->head = NULL;
}

// проверка на пустоту списка
bool is_empty(list *l)
{
	if(l->head == NULL) {return true;}
	return false;
}

// удалить все элементы из списка
void clean(list *l)
{
	if(is_empty(l))
	{
		memset(l, 0, sizeof(list));
		return;
	}

	node *currnode = l->head;
	node *nextnode = NULL;

	while(currnode != NULL)
	{
		nextnode = currnode->next;
		memset(currnode, 0, sizeof(node));
		free(currnode);
		currnode = nextnode;
	}

	memset(l, 0, sizeof(list));
}

node *find_last(list *l)
{
	if(is_empty(l)) {return NULL;}

	node *nptr = l->head;
	while(nptr->next != NULL)
	{
		nptr = nptr->next;
	}

	return nptr;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value, bool returnprev)
{
	if(is_empty(l))
	{
		return NULL;
	}

	node *nextnode = l->head;
	node *prev = NULL;

	while(nextnode != NULL)
	{
		if (nextnode->value == value)
		{
			if(!returnprev)
			{
				return nextnode;
			}
			return prev;
		}
		
		prev = nextnode;
		nextnode = nextnode->next;
	}

	return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value)
{
	node *nodeptr = calloc(1,sizeof(node));
	if(nodeptr == NULL) {return -1;}

	node *lastptr = find_last(l);
	if(!(lastptr))
	{
		l->head = nodeptr;
	}
	else
	{
		lastptr->next = nodeptr;
	}

	nodeptr->value = value;
	nodeptr->next = NULL;
	return 0;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value)
{
	node *nodeptr = calloc(1,sizeof(node));
	if(nodeptr == NULL) {return -1;}

	node *nextptr = NULL;
	if(is_empty(l))
	{
		l->head = nodeptr;
	}
	else
	{
		nextptr = l->head;
		l->head = nodeptr;
	}
	
	nodeptr->value = value;
	nodeptr->next = nextptr;
	return 0;
}

// Возвращает адрес элемента по индексу
node *list_go_to_index(list *l, int i)
{
	if(is_empty(l)) {return NULL;}

	node *nodeptr = l->head;
	while(--i >= 0)
	{
		nodeptr = nodeptr->next;
		if(nodeptr == NULL) {return NULL;}
	}

	return nodeptr;
}

// вставка значения после указанного узла (по индексу), вернуть 0 если успешно
int insert_after(list *l, int i, int value)
{
	node *nodeptr = calloc(1,sizeof(node));
	if(nodeptr == NULL) {return -1;}

	node *prevptr = list_go_to_index(l, i);
	if(prevptr == NULL) {return -1;}
	node *nextptr = prevptr->next;

	prevptr->next = nodeptr;
	nodeptr->value = value;
	nodeptr->next = nextptr;
	return 0;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list *l, int value)
{
	node *nodeptr;

	if(l->head->value == value)
	{
		nodeptr = l->head;
		l->head = nodeptr->next;

		memset(nodeptr, 0, sizeof(node));
		free(nodeptr);
		return 0;
	}
	else
	{
		node *prevnode = find(l, value, true);
		if (prevnode == NULL) {return -1;}
		nodeptr = prevnode->next;	
		prevnode->next = nodeptr->next;

		memset(nodeptr, 0, sizeof(node));
		free(nodeptr);
		return 0;
	}

	return -1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l)
{
	if(is_empty(l))
	{
		return;
	}

	node *nextnode = l->head;

	while(nextnode != NULL)
	{
		printf("%d ", nextnode->value);
		nextnode = nextnode->next;
	}
	puts("");
}


int main() {
	int N;

	scanf("%d", &N);
	list l = {0};

	int a;
	for(int i = 0; i < N; i++)
	{
		scanf("%d", &a);
		push_back(&l, a);
	}
	print(&l);

	for(int i = 0; i < 3; i++)
	{
		scanf("%d", &a);
		if(find(&l, a, false) == NULL) {printf("0 ");}
		else {printf("1 ");}
	}
	puts("");

	scanf("%d", &a);
	push_back(&l, a);
	print(&l);

	scanf("%d", &a);
	push_front(&l, a);
	print(&l);

	int i;
	scanf("%d%d", &i, &a);
	insert_after(&l, i-1, a);
	print(&l);

	scanf("%d", &a);
	remove_node(&l, a);
	print(&l);

	clean(&l);

	return 0;
};
