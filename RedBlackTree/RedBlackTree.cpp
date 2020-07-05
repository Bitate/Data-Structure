/**
 *	1. A red-black tree is a binary search tree with nodes colored red and black
 *	2. Root is black;
 *	3. Every external node is black;
 *	4. The children of a red node are black;
 *	5. All the external nodes have the same black depth;
 */

#include <iostream>

using namespace std::cout;
using namespace std::endl;

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

void left_rotate(struct Node* current_node);
void right_rotate(struct Node* current_node);
void insert_value(int value);
void delete_node(struct Node* current_node);



int main()
{

}

