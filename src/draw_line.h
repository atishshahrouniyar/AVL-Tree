#pragma once
#include <iostream>
#include <SDL.h>
#include "node.h"

void drawLine(SDL_Renderer* renderer, SDL_Point A, SDL_Point B) {
	SDL_RenderDrawLine(renderer, A.x, A.y, B.x, B.y);
}

void drawLines(SDL_Renderer* renderer,node* root) {
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
