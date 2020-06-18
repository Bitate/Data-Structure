/* A binary tree is an ordered tree in which each node has at most two children.
	1. Each node has at most two children
	2. Each child node is either a left child or a right child
	3. A left child precedes a right child in the ordering of children of a parent node
	
   A proper/full binary tree: Each node has either 0 or 2 children.
	
   External/Leave node: the node doesn't have children

   Check Diagram Here: https://app.diagrams.net/?lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=YcINIXsXgCQ3Grmj7Nq5&title=network.drawio#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1OAnaecU1AIIQYbnNDw52GiGPs6m5Z_tC%26export%3Ddownload
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
		Node* v;	// pointer to this node
	public:
		Position(Node* _v = NULL) :v(_v) {}	// constructor
		ELem& operator*()					// get element of a node
		{
			return v->elmt;
		}
		Position left() const				// get left child
		{
			return Position(v->left);
		}
		Position right() const				// get right child
		{
			return Position(v->right);
		}
		Position parnt() const				// get parent child
		{
			return Position(v->par);
		}
		bool isRoot() const					// root of the tree?
		{
			return v->par == NULL;
		}
		bool isExternal() const				// leave(the node doesn't have children) of the tree?
		{
			return v->left == NULL && v->right == NULL;
		}
		friend class LinkedBinaryTree;		// give binary tree access to nodes' position
	};
	typedef std::list<Position> PositionList;	// list of positions
public:
	LinkedBinaryTree();									// constructor
	int size() const;									// number of nodes
	bool empty() const;									// is tree empty?
	Position root() const;								// get the root
	PositionList positions() const;						// list of nodes
	void addRoot();										// add root to an empty tree
	void expandExternal(const Position& p);				// expand external/leave node
	Position removeAboveExternal(const Position& p);	// remove p and parent
	// housekeeping functions omitted
protected:												// local utility
	void preorder(Node* v, Position& pl) const;			// preorder traversal
private:
	Node* _root;										// pointer to the root
	int n;												// number of nodes in the tree
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

// Expand external node(the node without children)
// Transform an external node in the position p into an internal node 
// by creating 2 new external nodes and making them the left and right chidren of p, respectively;
void LinkedBinaryTree::expandExternal(const Position& p)
{
	Node* v = p.v;					// p's node 
	v->left = new Node;				// add a new left child
	v->left->par = v;				// v is its parent
	v->right = new Node;			// add a new right child
	v->right->par = v;				// v is its parent
	n += 2;							// count 2 more nodes
}

// remove p and parent
// Remove the external node in the position p together with its parent q,
// replacing q with the sibling of p.
LinkedBinaryTree::Position
LinkedBinaryTree::removeAboveExternal(const Position& p)
{
	Node* w = p.v; Node* v = w->par;					// get p's node and parent
	Node* sib = (w == v->left ? v->right : v->left) ;	// sib is a sibling of w
	if (v == _root)										// child of root?
	{
		_root = sib;									// make sibling root
		sib->par = NULL;
	}
	else
	{
		Node* gpar = v->par;		// w's grandparent
		if (v == gpar->left) gpar->left = sib;		// replace parent by sib
		else gpar->right = sib;
		sib->par = gpar;
	}
	delete w; delete v;		// delete removed nodes
	n -= 2;					// count 2 fewer nodes
	return Position(sib);
}


// list of all nodes 
LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const
{
	PositionList pl;
	preorder(_root, pl);			// preorder traversal
	return PositionList(pl);		// return resulting list
}

// preorder traversal 
void LinkedBinaryTree::preorder(Node* v, Position& pl) const
{
	pl.push_back(Position(v));	// add this node
	// traverse left subtree
	if (v->left != NULL)
		preorder(v->left, pl);
	// traverse right subtree
	if (v->right != NULL)
		preorder(v->right, pl);
}