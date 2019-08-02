#pragma once
#include <iostream>
#include <algorithm>
#include <math.h>
#include <node.h>

int height(node *x);
node* rotate_right(node* x);
node* rotate_left(node *x);
node* Insert(int x, node *root);
node* Smallest(node* root);
node* Delete(int x, node* root);
void preOrder(node *root);
void Search(int x, node* root);