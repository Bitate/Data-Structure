/* A binary tree is an ordered tree in which each node has at most two children.
	1. Each node has at most two children
	2. Each child node is either a left child or a right child
	3. A left child precedes a right child in the ordering of children of a parent node
	
   A proper/full binary tree:
	1. Each node has either 0 or 2 children.
	
*/


#include <iostream>
#include <list>

///////////////////////////////////////////////////////////////////////////////////////////
/////////                       C++ Binary Tree Interface                         ///////// 
///////////////////////////////////////////////////////////////////////////////////////////

// class Position represents a position in a tree
template<typename E>
class Position
{
public:
	E& operator*();				// get element
	Position left() const;		// get left child
	Position right() const;		// get right child
	Position parent() const;	// get parent 
	bool isRoot() const;		// root of a tree?
	bool isExternal() const;	// an external node?

	Position();
	~Postion();
};
// class BinaryTree
template <typename E>
class BinaryTree
{
public:
	class Position;
	class PositionList;
public:
	int size() const;
	bool empty() const;
	Position root() const;
	PositionList positions() const;
};





///////////////////////////////////////////////////////////////////////////////////////////
/////////                     A Linked Structure for Binary Tree                  ///////// 
///////////////////////////////////////////////////////////////////////////////////////////

typedef int ELem;			// base element type
class LinkedBinaryTree
{
protected:
	struct Node												// a single node structure
	{
		Node* par;											// parent node
		Node* left;
		Node* right;
		int elmt;											// element value
		Node() :elmt(), par(NULL), left(NULL), right(NULL) {}	// constructor
	};
public:
	class Position	// position in the tree
	{
	private:
		Node* v;	// pointer to the root node
	public:
		Position(Node* _v = NULL) :v(_v) {}	// constructor
		ELem& operator*()
		{
			return v->elmt;
		}
		Position left() const
		{
			return Position(v->left);
		}
		Position right() const
		{
			return Position(v->right);
		}
		Position parnt() const
		{
			return Position(v->par);
		}
		bool isRoot() const
		{
			return v->par == NULL;
		}
		bool isExternal() const
		{
			return v->left == NULL && v->right == NULL;
		}
		friend class LinkedBinaryTree;
	};
	typedef std::list<Position> PositionList;	// list of positions
public:
	LinkedBinaryTree();
	int size() const;
	bool empty() const;
	Position root() const;
	PositionList positions() const;
	void addRoot();
	void expandExternal(const Position& p);
	Position removeAboveExternal(const Position& p);
	// housekeeping functions omitted
protected:
	void preorder(Node* v, Position& pl) const;
private:
	Node* _root;	// pointer to the root
	int n;	// number of nodes in the tree

};


LinkedBinaryTree::LinkedBinaryTree()	// constructor
	:_root(NULL), n(0){}
int LinkedBinaryTree::size() const		// number of nodes
{
	return n;
}
bool LinkedBinaryTree::empty() const	// is tree empty?
{
	return size() == 0;
}
LinkedBinaryTree::Position LinkedBinaryTree::root() const	// get the root
{
	return Position(_root);
}
void LinkedBinaryTree::addRoot()	// add root to empty tree
{
	_root = new Node;
	n = 1;
}



