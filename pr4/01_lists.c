#include "headers/list.h"

// инициализация пустого списка
void list_init(list *l)
{
	l->head = NULL;
	l->tail = NULL;
}

// проверка на пустоту списка
bool list_is_empty(list *l)
{
	if(!l->head) {return true;}
	return false;
}

// удалить все элементы из списка
void list_clean(list *l)
{
	list_node *currnode = l->tail;
	list_node *prevnode = NULL;

	while(currnode)
	{
		prevnode = currnode->prev;
		memset(currnode, 0, sizeof(currnode));
		free(currnode);
		currnode = prevnode;
	}

	memset(l, 0, sizeof(l));
}

// поиск элемента по значению. вернуть NULL если элемент не найден
list_node *list_find(list *l, int value, bool revert)
{
	if(list_is_empty(l)) {return NULL;}

	if(!revert)
	{
		list_node *nextnode = l->head;

		while(nextnode)
		{
			if (nextnode->value == value)
			{
				return nextnode;
			}

			nextnode = nextnode->next;
		}
	}
	else
	{
		list_node *prevnode = l->tail;

		while(prevnode)
		{
			if (prevnode->value == value)
			{
				return prevnode;
			}

			prevnode = prevnode->prev;
		}
	}
	
	return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int list_push_back(list *l, int value)
{
	list_node *nodeptr = (list_node *)calloc(1,sizeof(list_node));
	if(!nodeptr) {return -1;}

	list_node *lastptr;
	if(list_is_empty(l))
	{
		l->tail = nodeptr;
		l->head = nodeptr;
		lastptr = NULL;
	}
	else
	{
		lastptr = l->tail;
		lastptr->next = nodeptr;
	}
	
	nodeptr->value = value;
	nodeptr->prev = lastptr;
	

	l->tail = nodeptr;
	l->length++;

	return 0;
}

// вставка значения в начало списка, вернуть 0 если успешно
int list_push_front(list *l, int value)
{
	list_node *nodeptr = (list_node *)calloc(1,sizeof(list_node));
	if(!nodeptr) {return -1;}

	list_node *nextptr;
	if(list_is_empty(l))
	{
		l->tail = nodeptr;
		l->head = nodeptr;
		nextptr = NULL;
	}
	else
	{
		nextptr = l->head;
		nextptr->prev = nodeptr;
	}
	
	nodeptr->value = value;
	nodeptr->next = nextptr;

	l->head = nodeptr;
	l->length++;
	
	return 0;
}

list_node list_pop_front(list *l)
{	
	list_node node = {0};
	if (!l->head) {return node;}
    node = *(l->head);
    __list_remove_node(l,l->head);
    return node;
}

// Возвращает адрес элемента по индексу
list_node *list_go_to_index(list *l, int i)
{
	if(list_is_empty(l)) {return NULL;}

	list_node *nodeptr;

	if(l->length/2 > i)
	{
		nodeptr = l->head;
		while(--i >= 0)
		{
			nodeptr = nodeptr->next;
		}
	}
	else if(i < l->length)
	{
		nodeptr = l->tail;
		while(++i < l->length)
		{
			nodeptr = nodeptr->prev;
		}
	}
	else {return NULL;}

	return nodeptr;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int list_insert_after(list *l, int index, int value)
{
	list_node *nodeptr = (list_node *)calloc(1,sizeof(list_node));
	if(!nodeptr) {return -1;}

	list_node *prevptr = list_go_to_index(l, index);
	if (!prevptr) {return -1;}
	list_node *nextptr = prevptr->next;
	if (!nextptr)
	{
		l->tail = nodeptr;
	}
	else
	{
		nextptr->prev = nodeptr;
	}

	prevptr->next = nodeptr;

	nodeptr->value = value;
	nodeptr->next = nextptr;
	nodeptr->prev = prevptr;

	l->length++;
	return 0;
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int list_insert_before(list *l, int index, int value)
{
	{
	list_node *nodeptr = (list_node *)calloc(1,sizeof(list_node));
	if(!nodeptr) {return -1;}

	list_node *nextptr = list_go_to_index(l, index);
	if(!nextptr) {return -1;}
	list_node *prevptr = nextptr->prev;
	if (!prevptr)
	{
		l->head = nodeptr;
	}
	else
	{
		prevptr->next = nodeptr;
	}

	nodeptr->value = value;
	nodeptr->next = nextptr;
	nodeptr->prev = prevptr;

	nextptr->prev = nodeptr;
	
	l->length++;
	return 0;
}
}

void __list_remove_node(list *l, list_node *nodeptr)
{
	list_node *prevptr = nodeptr->prev;
	if (!prevptr) 
	{
		l->head = nodeptr->next;
	}
	else
	{
		prevptr->next = nodeptr->next;
	}
	
	list_node *nextptr = nodeptr->next;
	if (!nextptr) 
	{
		l->tail = nodeptr->prev;
	}
	else
	{
		nextptr->prev = nodeptr->prev;
	}
	
	l->length--;
	memset(nodeptr, 0, sizeof(nodeptr));
	free(nodeptr);
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int list_remove_first(list *l, int value)
{
	list_node *nodeptr = list_find(l, value, false);
	if (!nodeptr) {return -1;}

	__list_remove_node(l, nodeptr);
	
	return 0;
}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int list_remove_last(list *l, int value)
{
	list_node *nodeptr = list_find(l, value, true);
	if (!nodeptr) {return -1;}

	__list_remove_node(l, nodeptr);

	return 0;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void list_print(list *l)
{
	if(list_is_empty(l)) {return;}

	list_node *nextnode = l->head;
	while(nextnode)
	{
		printf("%d ", nextnode->value);
		nextnode = nextnode->next;
	}
	puts("");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void list_print_invers(list *l)
{
	if(list_is_empty(l)) {return;}

	list_node *prevnode = l->tail;
	while(prevnode)
	{
		printf("%d ", prevnode->value);
		prevnode = prevnode->prev;
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
		list_push_back(&l, a);
	}
	list_print(&l);

	for(int i = 0; i < 3; i++)
	{
		scanf("%d", &a);
		if(list_find(&l, a, false) == NULL) {printf("0 ");}
		else {printf("1 ");}
	}
	puts("");

	scanf("%d", &a);
	list_push_back(&l, a);
	list_print_invers(&l);

	scanf("%d", &a);
	list_push_front(&l, a);
	list_print(&l);

	int i;
	scanf("%d%d", &i, &a);
	list_insert_after(&l, i-1, a);
	list_print_invers(&l);

	scanf("%d%d", &i, &a);
	list_insert_before(&l, i-1, a);
	list_print(&l);

	scanf("%d", &a);
	list_remove_first(&l, a);
	list_print_invers(&l);

	scanf("%d", &a);
	list_remove_last(&l, a);
	list_print(&l);

	list_clean(&l);

	return 0;
};
