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
#include <dos.h>

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

node* Smallest(node* root)
{
	node* x = root;
	while (x->left != nullptr)
		x = x->left;
	return x;
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

node* Delete(int x, node* root)
{
	if (root == nullptr)
		return root;
	if (x < root->key)
		root->left = Delete(x, root->left);
	else if (x > root->key)
		root->right = Delete(x, root->right);
	else
	{
		node* temp = root;
		if (root->left == nullptr && root->right == nullptr)
		{
			temp = root;
			root = nullptr;
			delete root;
		}
		else if (root->left == nullptr)
		{
			temp = root;
			root = root->right;
			delete temp;

		}
		else if (root->right == nullptr)
		{
			temp = root;
			root = root->left;
			delete temp;
		}
		else
		{
			temp = Smallest(root->right);
			root->key = temp->key;
			root->right = Delete(temp->key, root->right);
		}
	}
	if (root == nullptr)
		return root;

	root->height = std::max(height(root->left), height(root->right)) + 1;

	int balance = height(root->left) - height(root->right);

	if (balance > 1)
	{
		int balance_left = height(root->left->left) - height(root->left->right);
		if (balance_left >= 0)
			return rotate_right(root);
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}
	else if (balance < -1)
	{
		int balance_right = height(root->right->left) - height(root->right->right);
		if (balance_right <= 0)
			return rotate_left(root);
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}

void Search(int x, node* root, SDL_Renderer* renderer, TTF_Font* font)
{
	if (root == nullptr)
	{
		std::cout << "Not Found!!!" << std::endl;
		return;
	}
	else if (x == root->key)
	{
		render_particular_node(renderer, root, font, 0);
		std::cout << "Found!!!" << std::endl;
		return;
	}
	else if (x < root->key)
	{
		render_particular_node(renderer, root, font,1);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		if(root->left!=nullptr)
			Search(x, root->left,renderer,font);
		else
		{
			render_particular_node(renderer, root, font, 2);
			return;
		}
	}
	else if (x > root->key)
	{
		render_particular_node(renderer, root, font,1);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		if(root->right!=nullptr)
			Search(x, root->right,renderer,font);
		else
		{
			render_particular_node(renderer, root, font, 2);
			return;
		}
	}
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
	root = Insert(0, root);
	root = Insert(1, root);
	root = Insert(2, root);
	root = Insert(3, root);
	root = Insert(4, root);
	root = Insert(5, root);
	root = Insert(6, root);
	root = Insert(7, root);
	root = Insert(8, root);
	root = Insert(9, root);
	root = Insert(10, root);
	root = Insert(11, root);
	root = Insert(12, root);
	root = Insert(13, root);
	root = Insert(14, root);
	root = Insert(15, root);
	root = Insert(16, root);
	root = Insert(17, root);
	root = Insert(18, root);
	root = Insert(19, root);
	root = Insert(20, root);
	root = Insert(21, root);
	root = Insert(22, root);
	root = Insert(23, root);
	root = Insert(24, root);
	root = Insert(25, root);
	root = Insert(26, root);
	root = Insert(27, root);
	root = Insert(28, root);
	root = Insert(29, root);
	root = Insert(30, root);
	root = Insert(31, root);
	root = Insert(32, root);
	root = Insert(33, root);
	root = Insert(34, root);
	root = Insert(35, root);
	root = Insert(36, root);
	root = Insert(37, root);
	root = Insert(38, root);
	root = Insert(39, root);
	root = Insert(40, root);
	root = Insert(41, root);
	root = Insert(42, root);
	root = Insert(43, root);
	root = Insert(44, root);
	root = Insert(45, root);
	root = Insert(46, root);
	root = Insert(47, root);
	root = Insert(48, root);
	root = Insert(49, root);
	root = Insert(50, root);
	root = Insert(51, root);
	root = Insert(52, root);
	root = Insert(53, root);
	root = Insert(54, root);
	root = Insert(55, root);
	root = Insert(56, root);
	root = Insert(57, root);
	root = Insert(58, root);
	root = Insert(59, root);
	root = Insert(60, root);
	root = Insert(61, root);
	root = Insert(62, root);
	root = Delete(30, root);
	root = Delete(39, root);
	root = Delete(0, root);
	root = Delete(2, root);
	root = Delete(4, root);

	//std::cout << 7odes.size() << std::endl;
	
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
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		set_coord(root, W, H);
		drawLines(renderer, root);
		renderNodes(renderer, root, arial);
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&evnt)) {
			
			switch (evnt.type) {
			case SDL_QUIT:
				quit = true;
			case SDL_KEYDOWN:
				if (evnt.key.keysym.sym == SDLK_SPACE)
					Search(17, root, renderer, arial);

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
