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

void set_other_coord(node* root)
{
	if (root->left == nullptr)
		return;
	root->left->nodeCoord.x = root->nodeCoord.x / 2;
	root->left->nodeCoord.y = root->nodeCoord.y + 75;
	set_other_coord(root->left);
	if (root->right == nullptr)
		return;
	root->right->nodeCoord.x = root->nodeCoord.x*1.5;
	root->right->nodeCoord.y= root->nodeCoord.y + 75;
	set_other_coord(root->right);
}

void set_coord(node* root, int W, int H) {
	root->nodeCoord.x = W / 2;
	root->nodeCoord.y = 350;
	set_other_coord(root);
}