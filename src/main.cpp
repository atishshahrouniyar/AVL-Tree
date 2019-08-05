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
#include <ctime>
#include <string>

int W;
int H;

node *root;
SDL_Color text_color = { 0,51,102,255 };
SDL_Rect textRect = { 500, 50, 500, 100 };
//For input box
void renderInputBox(SDL_Renderer* renderer, SDL_Rect rect) {
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // the rect color (solid red) 
	SDL_RenderFillRect(renderer, &rect);
}
//For button to click
void renderButtonBox(SDL_Renderer* renderer, SDL_Rect rect) {
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // the rect color (solid red) 
	SDL_RenderFillRect(renderer, &rect);
}
//Check in which box user clicks
bool clickedBox(SDL_Point p, SDL_Rect rect) {
	return (p.x > rect.x && p.x < rect.x + rect.w && p.y > rect.y && p.y < rect.y + rect.h);
}

//To get input number
void getInput(SDL_Renderer* renderer, std::string& inputText, bool& isQuit, SDL_Rect inputBoxRect, SDL_Rect buttonRect) {
	inputText = "";
	SDL_Event evnt;
	TTF_Font* arial = TTF_OpenFont("../res/arial.ttf", 3000);
	auto start = std::clock();
	drawLine(renderer, { inputBoxRect.x + 3 + int(inputText.size()) * 25 , inputBoxRect.y + 3 }, { inputBoxRect.x + 3 + int(inputText.size()) * 25 , inputBoxRect.y + 27 });
	SDL_RenderPresent(renderer);
	SDL_Delay(100);
	drawLine(renderer, { inputBoxRect.x + 3 + int(inputText.size()) * 25 , inputBoxRect.y + 3 }, { inputBoxRect.x + 3 + int(inputText.size()) * 25 , inputBoxRect.y + 27 }, { 255,255,255 });
	while (true) {

		float duration = float(std::clock() - start);
		
		if (SDL_PollEvent(&evnt)) {
			if (evnt.type == SDL_QUIT) {
				isQuit = true;
				return;
			}
			if (evnt.type == SDL_KEYDOWN) {
				if ((evnt.key.keysym.sym == SDLK_RETURN || evnt.key.keysym.sym == SDLK_KP_ENTER) && inputText != "") {
					std::cout << "pressed enter" << std::endl;
					return;
				}
				else if (evnt.key.keysym.sym == SDLK_BACKSPACE && inputText.size() > 0)
				{
					inputText.pop_back();
				
					std::cout << inputText << std::endl;
				}
			}
			else if (evnt.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				x = evnt.button.x;
				y = evnt.button.y;
				if (clickedBox({ x,y }, buttonRect) && inputText != "")
					return;

			}

			if (evnt.type == SDL_TEXTINPUT) {
				int ascii = int(evnt.text.text[0]);
				if (ascii > 47 && ascii < 58 && inputText.size() < 3)
					inputText += evnt.text.text;
				std::cout << inputText << std::endl;
			}
		}
		SDL_Color black = { 0,0,0 };
		SDL_Rect textRect = { inputBoxRect.x + 3, inputBoxRect.y + 3, (int)(inputText.size()) * 25, 25 };

		renderText(renderer, inputText, black, textRect, arial);

		SDL_RenderPresent(renderer);

	}
	TTF_CloseFont(arial);
}
//To calculate height
int height(node *x)
{
	if (x == nullptr)
		return -1;
	return x->height;
}
//Rotating right the given node
node* rotate_right(node* x,SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
	SDL_RenderClear(renderer);
	set_coord(root, W, H);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	drawLines(renderer, root);
	renderNodes(renderer, root, font);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	render_particular_node(renderer, x, font, 2);
	clear(renderer, textRect);
	renderText(renderer, "Tree Unbalanced", text_color, textRect, font);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	clear(renderer, textRect);
	SDL_Color white = { 255,255,255,255 };
	renderText(renderer, "Rotating Right...", white, textRect, font);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	node* temp = x->left;
	x->left = x->left->right;
	temp->right = x;
	x->height = std::max(height(x->left), height(x->right)) + 1;
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
	return temp;
}
//To find the smallest element
node* Smallest(node* root, SDL_Renderer* renderer, TTF_Font* font)
{
	
	node* x = root;
	while (x->left != nullptr)
	{
		x = x->left;
	}
	render_particular_node(renderer, x, font, 2);
	clear(renderer, textRect);
	renderText(renderer, "Smallest on Right Found", text_color, textRect, font);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	return x;
}
//To rotate left 
node* rotate_left(node *x, SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
	SDL_RenderClear(renderer);
	set_coord(root, W, H);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	drawLines(renderer, root);
	renderNodes(renderer, root, font);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	render_particular_node(renderer, x, font, 2);
	clear(renderer, textRect);
	renderText(renderer, "Tree Unbalanced", text_color, textRect, font);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	clear(renderer, textRect);
	SDL_Color white = { 255,255,255,255 };
	renderText(renderer, "Rotating Left...", white, textRect, font);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	node* temp = x->right;
	x->right = x->right->left;
	temp->left = x;
	x->height = std::max(height(x->left), height(x->right)) + 1;
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
	return temp;
}
//To insert an element
node* Insert(int x, node *root, SDL_Renderer* renderer, TTF_Font* font)
{
	node* n = new node();
	n->key = x;
	n->height = 0;
	n->left = nullptr;
	n->right = nullptr;
	if (root == nullptr)
	{
		return n;
	}
	else if (x < root->key)
	{
		render_particular_node(renderer, root, font, 1);
		clear(renderer, textRect);
		renderText(renderer, "Searching Position...", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		root->left = Insert(x, root->left, renderer, font);
	}
	else if (x > root->key)
	{
		render_particular_node(renderer, root, font, 1);
		clear(renderer, textRect);
		renderText(renderer, "Searching Position...", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		root->right = Insert(x, root->right, renderer, font);
	}
	else
	{
		render_particular_node(renderer, root, font, 2);
		clear(renderer, textRect);
		renderText(renderer, "Already Present", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(500);
		return root;
	}
	root->height = std::max(height(root->left), height(root->right)) + 1;

	int balance = height(root->left) - height(root->right);

	if (balance > 1)
	{
		if (x < root->left->key)
			return rotate_right(root, renderer, font);
		root->left = rotate_left(root->left, renderer, font);
		return rotate_right(root, renderer, font);
	}
	else if (balance < -1)
	{
		if (x > root->right->key)
			return rotate_left(root, renderer, font);
		root->right = rotate_right(root->right, renderer, font);
		return rotate_left(root, renderer, font);
	}
	return root;
}

//To delete  an element
node* Delete(int x, node* root, SDL_Renderer* renderer, TTF_Font* font)
{
	if (root == nullptr)
	{
		clear(renderer, textRect);
		renderText(renderer, "Not Found", {255,255,255,255}, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		return root;
	}
	if (x < root->key)
	{
		render_particular_node(renderer, root, font, 1);
		clear(renderer, textRect);
		renderText(renderer, "Searching Position...", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		root->left = Delete(x, root->left, renderer, font);
	}
	else if (x > root->key)
	{
		render_particular_node(renderer, root, font, 1);
		clear(renderer, textRect);
		renderText(renderer, "Searching Position...", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		root->right = Delete(x, root->right, renderer, font);
	}
	else
	{
		render_particular_node(renderer, root, font, 0);
		clear(renderer, textRect);
		renderText(renderer, "Deleting...", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
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
			temp = Smallest(root->right, renderer, font);
			root->key = temp->key;
			render_particular_node(renderer, root, font, 0);
			SDL_Delay(1000);
			clear(renderer, textRect);
			renderText(renderer, "Deleting that Smallest Element", text_color, textRect, font);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
			root->right = Delete(temp->key, root->right, renderer, font);
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
			return rotate_right(root, renderer, font);
		root->left = rotate_left(root->left, renderer, font);
		return rotate_right(root, renderer, font);
	}
	else if (balance < -1)
	{
		int balance_right = height(root->right->left) - height(root->right->right);
		if (balance_right <= 0)
			return rotate_left(root, renderer, font);
		root->right = rotate_right(root->right, renderer, font);
		return rotate_left(root, renderer, font);
	}
	return root;
}
//For searching
void Search(int x, node* root, SDL_Renderer* renderer, TTF_Font* font)
{
	if (root == nullptr)
	{
		clear(renderer, textRect);
		renderText(renderer, "Tree is Empty", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(750);
		std::cout << "Not Found!!!" << std::endl;
		return;
	}
	else if (x == root->key)
	{
		render_particular_node(renderer, root, font, 0);
		clear(renderer, textRect);
		renderText(renderer, "Found !!!", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(750);
		std::cout << "Found!!!" << std::endl;
		return;
	}
	else if (x < root->key)
	{
		render_particular_node(renderer, root, font,1);
		clear(renderer, textRect);
		renderText(renderer, "Searching...", text_color, textRect, font);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		if(root->left!=nullptr)
			Search(x, root->left,renderer,font);
		else
		{
			render_particular_node(renderer, root, font, 2);
			clear(renderer, textRect);
			renderText(renderer, "Not Found !!!", text_color, textRect, font);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);
			return;
		}
	}
	else if (x > root->key)
	{
		render_particular_node(renderer, root, font,1);
		clear(renderer, textRect);

		renderText(renderer, "Searching...", text_color, textRect, font);

		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		if(root->right!=nullptr)
			Search(x, root->right,renderer,font);
		else
		{
			render_particular_node(renderer, root, font, 2);
			clear(renderer, textRect);

			renderText(renderer, "Not Found !!!", text_color, textRect, font);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);
			return;
		}
	}
}


int main(int argc, char *argv[]) {
	SDL_Window *window;
	SDL_Renderer* renderer;
	SDL_DisplayMode DM;

	bool quit = false;

	std::string input_str[3];

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GetCurrentDisplayMode(0, &DM);
	 W = DM.w;
	 H = DM.h;

	root = nullptr;

	TTF_Init();
	window = SDL_CreateWindow(
		"DSA",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W,                               // width, in pixels
		H - 60,                               // height, in pixels
		0                 // flags - see below
	);

	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font* arial = TTF_OpenFont("../res/aller.ttf", 500);

	if (!arial) {
		std::cout << TTF_GetError() << std::endl;
		return 1;
	}
	SDL_Rect textInputRect[3], buttonRect[3];

	textInputRect[0] = { 50, 100, 100, 32 };
	buttonRect[0] = { 200,100,150,32 };

	textInputRect[1] = { 50, 200, 100, 32 };
	buttonRect[1] = { 200,200,150,32 };

	textInputRect[2] = { 50, 300, 100, 32 };
	buttonRect[2] = { 200,300,150,32 };
	
	SDL_Event evnt;
	SDL_Color button_color = { 255,255,255,255};
	while (!quit)
	{
		SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		for (int i = 0; i < 3; i++)
		{
			renderButtonBox(renderer, buttonRect[i]);
		}
		renderText(renderer, "INSERT", button_color, buttonRect[0], arial);
		renderText(renderer, "DELETE", button_color, buttonRect[1], arial);
		renderText(renderer, "SEARCH", button_color, buttonRect[2], arial);
		
		for (int i = 0; i < 3; ++i) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			renderInputBox(renderer, textInputRect[i]);
		}
		set_coord(root, W, H);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		drawLines(renderer, root);
		renderNodes(renderer, root, arial);

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&evnt)) {

			switch (evnt.type) {
			case SDL_QUIT: {
				quit = true;
			}break;
			case SDL_MOUSEBUTTONDOWN: {
				int x = evnt.button.x;
				int y = evnt.button.y;
				for (int i = 0; i < 3; ++i) {
					if (clickedBox({ x,y }, textInputRect[i])) {
						getInput(renderer, input_str[i], quit, textInputRect[i], buttonRect[i]);
						if (input_str[i] == "")
							break;
						else if (i == 0)
							root=Insert(std::stoi(input_str[i]), root,renderer,arial);
						else if (i == 1)
							root=Delete(std::stoi(input_str[i]), root,renderer,arial);
						else if (i == 2)
							Search(std::stoi(input_str[i]), root, renderer, arial);
						break;
					}
				}
			}
			}
			set_coord(root, W, H);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

			drawLines(renderer, root);
			renderNodes(renderer, root, arial);

			SDL_RenderPresent(renderer);
		}

	}

	TTF_CloseFont(arial);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
