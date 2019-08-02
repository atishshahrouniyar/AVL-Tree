//#include "AVL.h"
//
//int height(node *x)
//{
//	if (x == nullptr)
//		return -1;
//	return x->height;
//}
//
//node* rotate_right(node* x)
//{
//	node* temp = x->left;
//	x->left = x->left->right;
//	temp->right = x;
//	x->height = std::max(height(x->left), height(x->right)) + 1;
//	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
//	return temp;
//}
//
//node* rotate_left(node *x)
//{
//	node* temp = x->right;
//	x->right = x->right->left;
//	temp->left = x;
//	x->height = std::max(height(x->left), height(x->right)) + 1;
//	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
//	return temp;
//}
//
//node* Insert(int x, node *root)
//{
//	node* n = new node();
//	n->key = x;
//	n->height = 0;
//	n->left = nullptr;
//	n->right = nullptr;
//	if (root == nullptr)
//		return n;
//	else if (x < root->key)
//		root->left = Insert(x, root->left);
//	else if (x > root->key)
//		root->right = Insert(x, root->right);
//	else
//		return root;
//
//	root->height = std::max(height(root->left), height(root->right)) + 1;
//
//	int balance = height(root->left) - height(root->right);
//
//	if (balance > 1)
//	{
//		if (x < root->left->key)
//			return rotate_right(root);
//		root->left = rotate_left(root->left);
//		return rotate_right(root);
//	}
//	else if (balance < -1)
//	{
//		if (x > root->right->key)
//			return rotate_left(root);
//		root->right = rotate_right(root->right);
//		return rotate_left(root);
//	}
//	return root;
//}
//
//node* Smallest(node* root)
//{
//	node* x = root;
//	while (x->left != nullptr)
//		x = x->left;
//	return x;
//}
//
//node* Delete(int x, node* root)
//{
//	if (root == nullptr)
//		return root;
//	if (x < root->key)
//		root->left = Delete(x, root->left);
//	else if (x > root->key)
//		root->right = Delete(x, root->right);
//	else
//	{
//		node* temp = root;
//		if (root->left == nullptr && root->right == nullptr)
//		{
//			temp = root;
//			root = nullptr;
//			delete root;
//		}
//		else if (root->left == nullptr)
//		{
//			temp = root;
//			root = root->right;
//			delete temp;
//
//		}
//		else if (root->right == nullptr)
//		{
//			temp = root;
//			root = root->left;
//			delete temp;
//		}
//		else
//		{
//			temp = Smallest(root->right);
//			root->key = temp->key;
//			root->right = Delete(temp->key, root->right);
//		}
//	}
//	if (root == nullptr)
//		return root;
//
//	root->height = std::max(height(root->left), height(root->right)) + 1;
//
//	int balance = height(root->left) - height(root->right);
//
//	if (balance > 1)
//	{
//		int balance_left = height(root->left->left) - height(root->left->right);
//		if (balance_left >= 0)
//			return rotate_right(root);
//		root->left = rotate_left(root->left);
//		return rotate_right(root);
//	}
//	else if (balance < -1)
//	{
//		int balance_right = height(root->right->left) - height(root->right->right);
//		if (balance_right <= 0)
//			return rotate_left(root);
//		root->right = rotate_right(root->right);
//		return rotate_left(root);
//	}
//	return root;
//}
//
//void preOrder(node *root)
//{
//	if (root != NULL)
//	{
//		std::cout << root->key << " ";
//		preOrder(root->left);
//		preOrder(root->right);
//	}
//}
//
//void Search(int x, node* root)
//{
//	if (root == nullptr)
//	{
//		std::cout << "Not Found!!!" << std::endl;
//		return;
//	}
//	else if (x == root->key)
//	{
//	std::cout << "Found!!!" << std::endl;
//		return;
//	}
//	else if (x < root->key)
//	{
//		Search(x, root->left);
//	}
//	else if (x > root->key)
//	{
//		Search(x, root->right);
//	}
//}
//
