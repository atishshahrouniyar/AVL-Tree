#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "draw_line.h"

//Render the text
void renderText(SDL_Renderer* renderer, std::string text, SDL_Color _color, SDL_Rect Message_rect,TTF_Font* font){

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), _color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); //now you can convert it into a texture
	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(renderer, textTexture, NULL, &Message_rect);
	SDL_DestroyTexture(textTexture);
}
//To clear the text box
void clear(SDL_Renderer* renderer, SDL_Rect rect)
{
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // the rect color (solid red) 
	SDL_RenderFillRect(renderer, &rect);
}
//To render single node
void render_particular_node(SDL_Renderer* renderer, node* node, TTF_Font* font,int x)
{
	SDL_Surface *nodeSurface;
	SDL_Texture * nodeTexture;
	if(x==0)
		nodeSurface = SDL_LoadBMP("../res/green.bmp");
	else if(x==1)
		nodeSurface = SDL_LoadBMP("../res/purple.bmp");
	else
		nodeSurface = SDL_LoadBMP("../res/red.bmp");
	if (!nodeSurface) {
		std::cout << SDL_GetError();
		return;
	}
	nodeTexture = SDL_CreateTextureFromSurface(renderer, nodeSurface);
	SDL_FreeSurface(nodeSurface);

	SDL_Rect rect = { node->nodeCoord.x - 25, node->nodeCoord.y - 25 , 50, 50 };
	SDL_RenderCopy(renderer, nodeTexture, NULL, &rect);
	SDL_DestroyTexture(nodeTexture);


	std::string val = std::to_string(node->key);
	SDL_Color white = { 255,255,255 }, black = { 0,0,0 };
	SDL_Rect textRect = { node->nodeCoord.x - 18, node->nodeCoord.y - 20, 30, 30 };
	renderText(renderer, val, white, textRect, font);
}
//To render all the nodes of  tree
void renderNodes(SDL_Renderer* renderer, node* Nodes, TTF_Font* font) {
	if (Nodes == nullptr)
		return;
		SDL_Surface *nodeSurface;
		SDL_Texture * nodeTexture;
		nodeSurface = SDL_LoadBMP("../res/black.bmp");
		if (!nodeSurface) {
			std::cout << SDL_GetError();
			return;
		}
		nodeTexture = SDL_CreateTextureFromSurface(renderer, nodeSurface);
		SDL_FreeSurface(nodeSurface);

	SDL_Rect rect = { Nodes->nodeCoord.x-25, Nodes->nodeCoord.y-25 , 50, 50 };
	SDL_RenderCopy(renderer, nodeTexture, NULL, &rect);
	SDL_DestroyTexture(nodeTexture);
	
	
	std::string val = std::to_string(Nodes->key);
	SDL_Color white = { 255,255,255 }, black = {0,0,0};
	SDL_Rect textRect = { Nodes->nodeCoord.x - 18, Nodes->nodeCoord.y - 20, 30, 30 };
	renderText(renderer, val, white, textRect, font);
	renderNodes(renderer, Nodes->left, font);
	renderNodes(renderer, Nodes->right, font);

}

