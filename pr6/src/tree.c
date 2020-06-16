#include "../headers/tree.h"

int rotate_left(tree *t, node* n)
{
	if (!n->right) return 1;
	if (t->root == n) t->root = n->right;

	node *rotated = n->right;
	n->right = rotated->left;
	rotated->left = n;

	n = rotated;

	return 0;
}

int rotate_right(tree *t, node* n)
{
	if (!n->left) return 1;
	if (t->root == n) t->root = n->left;

	node *rotated = n->left;
	n->left = rotated->right;
	rotated->right = n;

	n = rotated;

	return 0;
}

find_return __find_node(node *n, int value)
{
	if (n->data == value)
	{
		find_return ret = {true, n};
		return ret;
	}
	if (n->data > value)
	{
		if (!n->left)
		{
			find_return ret = {false, n};
			return ret;
		}
		return __find_node(n->left, value);
	}
	else 
	{
		if (!n->right)
		{
			find_return ret = {false, n};
			return ret;
		}
		return __find_node(n->right, value);
	}
}

int insert(tree *t, int value)
{
	if (!t->root) 
	{
		node *nodeptr = (node *)calloc(1,sizeof(node));
		if(!nodeptr) return 2;

		t->root = nodeptr;
		nodeptr->data = value;
		return 1;
	}

	find_return ret = __find_node(t->root, value);
	if (ret.exist) return 1;

	node *nodeptr = calloc(1,sizeof(node));
	if(!nodeptr) return 2;

	if (value > ret.n->data) ret.n->right = nodeptr;
	else ret.n->left = nodeptr;

	nodeptr->parent = ret.n;
	nodeptr->data = value;
	t->count++;

	return 0;
}

node* find(tree* t, int value)
{
	if (!t->root) return NULL;

	find_return ret =  __find_node(t->root, value);
	
	if (ret.exist) return ret.n;

	return NULL;
}

void print_tree(tree *t)
{
	if (!t->root)
	{
		puts("-");
		return;
	}
	
	queue q = {0};
	list_push_back(&q, (long int)t->root);
	long int iter = 1, null_iter = 0;

	char *out = (char *)calloc(1, sizeof(char));
	int out_strlen = strlen(out);

	while (!POW_2(iter) || iter == 1 || (POW_2(iter) && (null_iter < (iter >> 1))))
	{
		if (POW_2(iter) && iter != 1)
		{
			printf("%s\n", out);
			memset(out, 0, strlen(out)*sizeof(char));
			out = realloc(out,sizeof(char));
			null_iter = 0;
		}

		node *nd = (node *)list_pop_front(&q).value;
		if(!nd)
		{
			out_strlen = strlen(out);
			out = (char *)realloc(out,(out_strlen+strlen(FILL) + 1)*sizeof(char));
			strcpy(out+out_strlen, FILL);

			list_push_back(&q, (long int)NULL);
			list_push_back(&q, (long int)NULL);
			iter++;
			null_iter++;
			continue;
		}

		out_strlen = strlen(out);
		int needed_mem = snprintf(NULL, 0, "%d  ", nd->data);
  		out = (char *)realloc(out,(out_strlen+needed_mem)*sizeof(char));
  		snprintf(out + out_strlen, needed_mem, "%d  ", nd->data);

		list_push_back(&q, (long int)nd->left);
		list_push_back(&q, (long int)nd->right);
		iter++;
	}
	list_clean(&q);
	free(out);
}

void __remove(tree *t, node *n)
{
	char parentDir;
	bool isRoot = false;
	if (n->parent) parentDir = n->parent->left == n ? LEFT : RIGHT;
	else isRoot = true;

	if(n->left == NULL)
	{
		if(n->right == NULL)
		{
			if (isRoot) t->root = NULL;
			else
			{
				if (parentDir == LEFT) n->parent->left = NULL;
				else n->parent->right = NULL;
			}
			
			free(n);
			t->count--;
			return;
		} 
		else 
		{
			if (isRoot) t->root = n->right;
			else
			{
				if (parentDir == LEFT) n->parent->left = n->right;
				else n->parent->right = n->right;
			}
			free(n);
			t->count--;
			return;
		}
	}
	else
	{
		if(n->right == NULL){
			if (isRoot) t->root = n->left;
			else
			{
				if (parentDir == LEFT) n->parent->left = n->left;
				else n->parent->right = n->left;
			}
			free(n);
			t->count--;
			return;
		}
		else 
		{
			n->data = remove_min(t,n->right);
			return;
		}
	}
}

int remove_node(tree* t, int value)
{
	node *n = find(t, value);
	if (!n) return 1;

	__remove(t,n);
	return 0;
}

int remove_min(tree *t, node* n)
{
	while (n->left) n = n->left;

	int value = n->data;
	__remove(t,n);
	return value;
}

void clean(tree *t)
{
	queue st = {0};
	list_push_back(&st, (long int)t->root);
	while (st.length > 0)
	{
		node *nd = (node *)list_pop_front(&st).value;

		if(!nd) continue;

		list_push_back(&st, (long int)nd->left);
		list_push_back(&st, (long int)nd->right);
		free(nd);
		t->count--;
	}
	t->root = NULL;
	list_clean(&st);
}