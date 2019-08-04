#pragma once
#include <iostream>
#include <SDL.h>
#include "node.h"
//To draw a line
void drawLine(SDL_Renderer* renderer, SDL_Point A, SDL_Point B, SDL_Color color = {0,0,0}) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(renderer, A.x, A.y, B.x, B.y);
}
//To draw all lines of the tree
void drawLines(SDL_Renderer* renderer,node* root) {
	if (root == nullptr)
		return;
	if (root->left != nullptr)
	{
		drawLine(renderer, root->nodeCoord, root->left->nodeCoord);
		drawLines(renderer, root->left);
	}
	if (root->right != nullptr)
	{
		drawLine(renderer, root->nodeCoord, root->right->nodeCoord);
		drawLines(renderer, root->right);
	}
}
