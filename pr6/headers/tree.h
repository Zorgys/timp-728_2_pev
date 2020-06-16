#ifndef TREE

#define TREE

#include "list.h"
#include <string.h>

#define POW_2(i) !(i&(i-1))
#define FILL "_ "
#define LEFT ((char)0)
#define RIGHT ((char)1)

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
} node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
	int count;
	node *root;
} tree;

typedef list queue;

typedef struct find_return {
	bool exist;
	node * n;
} find_return;

// Инициализация дерева
void init(tree* t);

// Удалить все элементы из дерева
void clean(tree* t);

find_return __find_node(node *n, int value);

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value);

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value);

void __remove(tree *t, node *n);

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value);

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(tree *t, node* n);

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(tree *t, node* n);

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(tree *t, node* n);

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n);

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t);

#endif // !LIST