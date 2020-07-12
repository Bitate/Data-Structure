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

void rotate_left(struct Node* x, struct Node* root_node);
void rotate_right(struct Node* x, struct Node* root_node);
void rebalance(struct Node* x, struct Node* root_node);
void rebalance_for_erase(struct Node* x, struct Node* root_node);

int main()
{

}

void rotate_left(struct Node* x, struct Node* root_node)
{
	struct Node* right_child_of_x = x->right_node;

	// step 1: let left child of right_child_of_x be the right child of x
	x->right_node = right_child_of_x->left_node;
	if(right_child_of_x->left_node != nullptr)
		right_child_of_x->left_node->parent_node = x;
	
	// step 2: let right_child_of_x be the child(right or left) of x's parent.
	right_child_of_x->parent_node = x->parent_node;
	if(x == root_node)
		root_node == right_child_of_x;
	else if(x == x->parent_node->left_node)
		x->parent_node->left_node = right_child_of_x;
	else
		x->parent_node->right_node = right_child_of_x;

	// step 3: let x be the left child of right_child_of_x
	right_child_of_x->left_node = x;
	x->parent_node = right_child_of_x;
}

void rotate_right(struct Node* x, struct Node* root_node)
{
	struct Node* left_child_of_x = x->left_node;

	// step 1: let right child of left_child_of_x be 
	x->left_node = left_child_of_x->right_node;
	if(left_child_of_x->right_node != nullptr)
		left_child_of_x->right_node->parent_node = x;

	// step 2: let left_child_of_x be the child(left or right) of x's parent.
	left_child_of_x->parent_node = x->parent_node;
	if(x == root_node)
		root_node = left_child_of_x;
	else if(x == x->parent_node->left_node)
		x->parent_node->left_node = left_child_of_x;
	else
		x->parent_node->right_node = left_child_of_x;
	
	// step 3: let x be the right node of left_child_of_x.
	left_child_of_x->right_node = x;
	x->parent_node = left_child_of_x;
}

void rebalance(struct Node* x, struct Node* root_node)
{
	x->color = Color::Red;
	while (x != root_node && x->parent_node->color == Color::Red)
	{
		// if x's parent is left node of x's grandparent
		if( x->parent_node == x->parent_node->parent_node->left_node )
		{
			struct Node* uncle_of_x = x->parent_node->parent_node->right_node;
			// if x's uncle is red, we just change color
			if( uncle_of_x && uncle_of_x->color == Color::Red )
			{	
				x->parent_node->color = Color::Black;
				uncle_of_x->color = Color::Black;
				x->parent_node->parent_node->color = Color::Red;
				x = x->parent_node->parent_node;
			}
			else	// else x's uncle's color is black, we perform rotation(s).
			{
				if( x == x->parent_node->right_node) // left-right, we first left rotate
				{
					x = x->parent_node;
					rotate_left(x, root_node);
				}

				// left-left, we perform right rotation
				x->parent_node->color = Color::Black;
				x->parent_node->parent_node->color = Color::Red;
				rotate_right(x->parent_node->parent_node, root_node);
			}
		}
		else	// x's parent is right child of x's grandparent
		{
			struct Node* uncle_of_x = x->parent_node->parent_node->left_node;
			// parent and uncle are all red, we only need to change colors
			if(uncle_of_x && uncle_of_x->color == Color::Red)
			{
				uncle_of_x->color = Color::Black;
				x->parent_node->color = Color::Black;
				x->parent_node->parent_node->color = Color::Red;
				x->parent_node->parent_node;
			}
			else	// uncle is black, we need to perform rotation(s)
			{
				if( x == x->parent_node->left_node )
				{
					x = x->parent_node;
					rotate_right(x, root_node);
				}

				x->parent_node->color = Color::Black;
				x->parent_node->parent_node->color = Color::Red;
				rotate_left(x->parent_node->parent_node, root_node);
			}
		}
	}
	root_node->color = Color::Black;
}