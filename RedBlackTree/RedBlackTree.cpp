/**
 *	1. A red-black tree is a binary search tree with nodes colored red and black
 *	2. Root is black;
 *	3. Every external node is black;
 *	4. The children of a red node are black;
 *	5. All the external nodes have the same black depth;
 */

#include <iostream>

using namespace std;

enum class Color
{
	Red,
	Black,
};

struct Node
{
	int value;
	Color color;
	struct Node* parent_node;
	struct Node* left_node;
	struct Node* right_node;
};

struct Node* nill_node;
struct Node* root_node;

void rotate_left(struct Node* new_node, struct Node* root_node);
void rotate_right(struct Node* new_node, struct Node* root_node);

int main()
{

}

void rotate_left(struct Node* new_node, struct Node* root_node)
{
	struct Node* right_child_of_new_node = new_node->right_node;

	// step 1: let left child of right_child_of_new_node be the right child of new_node
	new_node->right_node = right_child_of_new_node->left_node;
	if(right_child_of_new_node->left_node != nullptr)
		right_child_of_new_node->left_node->parent_node = new_node;
	
	// step 2: let right_child_of_new_node be the child(right or left) of new_node's parent.
	right_child_of_new_node->parent_node = new_node->parent_node;
	if(new_node == root_node)
		root_node == right_child_of_new_node;
	else if(new_node == new_node->parent_node->left_node)
		new_node->parent_node->left_node = right_child_of_new_node;
	else
		new_node->parent_node->right_node = right_child_of_new_node;

	// step 3: let new_node be the left child of right_child_of_new_node
	right_child_of_new_node->left_node = new_node;
	new_node->parent_node = right_child_of_new_node;
}

void rotate_right(struct Node* new_node, struct Node* root_node)
{
	struct Node* left_child_of_new_node = new_node->left_node;

	// step 1: let right child of left_child_of_new_node be 
	new_node->left_node = left_child_of_new_node->right_node;
	if(left_child_of_new_node->right_node != nullptr)
		left_child_of_new_node->right_node->parent_node = new_node;

	// step 2: let left_child_of_new_node be the child(left or right) of new_node's parent.
	left_child_of_new_node->parent_node = new_node->parent_node;
	if(new_node == root_node)
		root_node = left_child_of_new_node;
	else if(new_node == new_node->parent_node->left_node)
		new_node->parent_node->left_node = left_child_of_new_node;
	else
		new_node->parent_node->right_node = left_child_of_new_node;
	
	// step 3: let new_node be the right node of left_child_of_new_node.
	left_child_of_new_node->right_node = new_node;
	new_node->parent_node = left_child_of_new_node;
}