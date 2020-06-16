#ifndef LIST

#define LIST
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct list_node {
	int value;          // значение, которое хранит узел 
	struct list_node *next;  // ссылка на следующий элемент списка
	struct list_node *prev;  // ссылка на предыдущий элемент списка
} list_node;

typedef struct list {
	struct list_node *head;  // начало списка
	struct list_node *tail;  // конец списка
	int length;
} list;


// инициализация пустого списка
void list_init(list *l);

// проверка на пустоту списка
bool list_is_empty(list *l);

// удалить все элементы из списка
void list_clean(list *l);

// поиск элемента по значению. вернуть NULL если элемент не найден
list_node *list_find(list *l, int value, bool revert);

// вставка значения в конец списка, вернуть 0 если успешно
int list_push_back(list *l, int value);

// вставка значения в начало списка, вернуть 0 если успешно
int list_push_front(list *l, int value);

//Возвращает первый элемен списка и удаляет его
list_node list_pop_front(list *l);

// Возвращает адрес элемента по индексу
list_node *list_go_to_index(list *l, int i);

// вставка значения после указанного узла, вернуть 0 если успешно
int list_insert_after(list *l, int index, int value);

// вставка значения перед указанным узлом, вернуть 0 если успешно
int list_insert_before(list *l, int index, int value);

void __list_remove_node(list *l, list_node *nodeptr);

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int list_remove_first(list *l, int value);

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int list_remove_last(list *l, int value);

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void list_print(list *l);

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void list_print_invers(list *l);

#endif // !LIST