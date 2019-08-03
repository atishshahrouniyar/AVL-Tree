#pragma once
#include <SDL.h>
#include <vector>

struct node
{
	SDL_Point nodeCoord;
	int key;
	int height;
	node *left;
	node *right;
};

void set_other_coord(node* root, int x, int W)
{
	if (root->left != nullptr)
	{
	root->left->nodeCoord.x = root->nodeCoord.x - W / (int)pow(2, x);
	root->left->nodeCoord.y = root->nodeCoord.y + 75;
	set_other_coord(root->left, ++x, W);
	}
	if (root->right != nullptr)
	{
		if (root->left == nullptr)
		{
			++x;
		}
		root->right->nodeCoord.x = root->nodeCoord.x + W / (int)pow(2, --x);
		root->right->nodeCoord.y = root->nodeCoord.y + 75;
		set_other_coord(root->right, ++x, W);
	}
}

void set_coord(node* root, int W, int H) {
	if (root == nullptr)
		return;
	root->nodeCoord.x = W / 2;
	root->nodeCoord.y = 350;
	set_other_coord(root,2,W);
}