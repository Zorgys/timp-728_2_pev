#include "headers/tree.h"

void print_width(tree *t);

int main() {
	tree tr = {0};
	
	int a = 0;
	for (int i = 0; i < 7; i++)
	{
		scanf("%d", &a);
		insert(&tr, a);
	}
	print_width(&tr);

	return 0;
}

void print_width(tree *t)
{
	if (!t->root)
	{
		puts("-");
		return;
	}
	
	queue q = {0};
	list_push_back(&q, (long int)t->root);

	while (q.length > 0)
	{

		node *nd = (node *)list_pop_front(&q).value;
		
        printf("%d ", nd->data);

        if (nd->left) list_push_back(&q, (long int)nd->left);
		if (nd->right) list_push_back(&q, (long int)nd->right);
	}
	list_clean(&q);
}
