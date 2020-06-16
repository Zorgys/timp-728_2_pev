#include "headers/tree.h"

typedef list stack;

void print_pre_order(tree *t);

int main() {
	tree tr = {0};
	
	int a = 0;
	for (int i = 0; i < 7; i++)
	{
		scanf("%d", &a);
		insert(&tr, a);
	}
	print_pre_order(&tr);

	return 0;
}

void print_pre_order(tree *t)
{
	if (!t->root)
	{
		puts("-");
		return;
	}


	stack st = {0};
	node *curr = t->root;
	list_push_back(&st, (long int)curr);

	while (st.length > 0)
	{
		
		if (!curr)
		{
			curr = ((node *)list_pop_back(&st).value)->right;
			continue;
		}

		list_push_back(&st, (long int)curr);
		
		printf("%d ", curr->data);
		curr = curr->left;
	}

	list_clean(&st);
}
