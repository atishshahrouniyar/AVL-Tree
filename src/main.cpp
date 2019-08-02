#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "render.h"
#include <vector>
#include <cmath>
#include "draw_line.h"
#include "AVL.h"
#include <algorithm>

int height(node *x)
{
	if (x == nullptr)
		return -1;
	return x->height;
}

node* rotate_right(node* x)
{
	node* temp = x->left;
	x->left = x->left->right;
	temp->right = x;
	x->height = std::max(height(x->left), height(x->right)) + 1;
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

node* rotate_left(node *x)
{
	node* temp = x->right;
	x->right = x->right->left;
	temp->left = x;
	x->height = std::max(height(x->left), height(x->right)) + 1;
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
	return temp;
}

node* Insert(int x, node *root)
{
	node* n = new node();
	n->key = x;
	n->height = 0;
	n->left = nullptr;
	n->right = nullptr;
	if (root == nullptr)
		return n;
	else if (x < root->key)
		root->left = Insert(x, root->left);
	else if (x > root->key)
		root->right = Insert(x, root->right);
	else
		return root;

	root->height = std::max(height(root->left), height(root->right)) + 1;

	int balance = height(root->left) - height(root->right);

	if (balance > 1)
	{
		if (x < root->left->key)
			return rotate_right(root);
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}
	else if (balance < -1)
	{
		if (x > root->right->key)
			return rotate_left(root);
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}


int main(int argc, char *argv[]) {
	SDL_Window *window;
	SDL_Renderer* renderer;
	SDL_DisplayMode DM;
	
	bool quit = false;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GetCurrentDisplayMode(0, &DM);
	const int W = DM.w;
	const int H = DM.h;

	node *root=nullptr;
	root = Insert(3, root);
	root = Insert(1, root);
	root = Insert(5, root);
	root = Insert(0, root);
	//std::cout << Nodes.size() << std::endl;
	
	TTF_Init();

	window = SDL_CreateWindow(
		"DSA",                 
		SDL_WINDOWPOS_UNDEFINED,           
		SDL_WINDOWPOS_UNDEFINED,          
		W,                               // width, in pixels
		H-60,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);

	SDL_RenderClear(renderer);

	TTF_Font* arial = TTF_OpenFont("../res/aller.ttf",500);

	if (!arial) {
		std::cout << TTF_GetError() << std::endl;
		return 1;
	}

	SDL_Event evnt;
	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
		set_coord(root,W,H);
		drawLines(renderer, root);
		renderNodes(renderer, root, arial);
		while (SDL_PollEvent(&evnt)) {
			
			switch (evnt.type) {
			case SDL_QUIT:
				quit = true;
			}
		}
		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(arial);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
