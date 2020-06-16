#include "headers/tree.h"

void print_post_order(node *node);

int main() {
	tree tr = {0};
	
	int a = 0;
	for (int i = 0; i < 7; i++)
	{
		scanf("%d", &a);
		insert(&tr, a);
	}
	print_post_order(tr.root);

	return 0;
}

void print_post_order(node *node)
{
	if (!node) return;
  	print_post_order(node->left);
  	print_post_order(node->right);
  	printf("%d ", node->data);
}
