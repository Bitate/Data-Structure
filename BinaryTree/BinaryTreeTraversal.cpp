//	preorder:
//	postorder: evaluate arithmetic expression tree
//  inorder: 1. binary search tree(find the ideal number)
//			 2. Tree Drawing
//	Euler Tour: 1. Print a fully parenthesized arithmetic expression from its expression tree


template <typename E, typename R>						// element and result types
class EulerTour											// a template for Euler Tour
{
protected:
	struct Result										// stores tour result
	{
		R leftResult;									// result from left subtree
		R rightResult;									// result from right subtree
		R finalResult;									// final combined result
	};
	typedef BinaryTree<E> BinaryTree;					// the tree
	typedef typename BinaryTree::Position Position;		// a position in the tree
protected:												// data member
	const BinaryTree* tree;								// pointer to the tree
public:
	void initialize(const BinaryTree& T)				// initialize
	{
		tree = &T; 
	}
protected:												// local utilities
	int eulerTour(const Position& p) const;				// perform the Euler Tour functions
														// given by subclasses
	virtual void visitExternal(const Position& p, Result& r) const {};
	virtual void visitLeft(const Position& p, Result& r) const {};
	virtual void visitBelow(const Position& p, Result& r) const {};
	virtual void visitRight(const Position& p, Result& r) const {};
	Result initResult() const { return Result(); }
	int result(const Result& r) const { return r.finalResult; }
};


template <typename E, typename R>						// do the tour
int EulerTour<E, R>::eulerTour(const Position& p) const
{
	Result r = initResult();
	if (p.isExternal())									// external node
	{
		visitExternal(p, r);
	}	
	else                                                // internal node
	{
		visitLeft(p, r);
		r.leftResult = eulerTour(p.left());				// recurse on left
		visitBelow(p, r);
		r.rightResult = eulerTour(p.right());			// recurse on right
		visitRight(p, r);
															
	}
	return result(r);
}


template<typename E, typename R>
class EvaluateExpressionTour :public EulerTour<E, R>
{
protected:												// shortcut type names
	typedef typename EulerTour<E, R>::BinaryTree BinaryTree;
	typedef typename EulerTour<E, R>::Position Position;
	typedef typename EulerTour<E, R>::Result Result;
public:
	void execute(const BinaryTree& T)					// execute the tour
	{
		initialize(T);
		std::cout << "The value is : " << eulerTour(T.root()) << "\n";
	}
protected:
	// leaf: return value
	virtual void visitExternal(const Position& p, Result& r) const
	{
		r.finalResult = (*p).value();
	}
	// internal: do operation
	virtual void visitRight(const Position& p, Result& r) const
	{
		r.finalResult = (*p).operation(r.leftResult, r.rightResult);
	}
};


template<typename E, typename R>
class PrintExpressionTour : public EulerTour<E, R>
{
protected:												// same type name shortcuts as in EvaluateExpressionTour
public:
	void execute(const BinaryTree& T)					// execute the tour
	{
		initialize(T);
		std::cout << "Expression: " << eulerTour(T.root()) << cout << endl;
	}
protected:
	virtual void visitExternal(const Position& p, Result& r) const		// leaf: print value
	{
		(*p).print();
	}
	virtual void visitLeft(const Position& p, Result& r) const			// leaf: open new expression
	{
		std::cout << "(";
	}
	virtual void visitBelow(const Position& p, Resutl& r) const			// below: print operator
	{
		(*p).print();
	}
	virtual void visitRight(const Position& p, Result& r) const			// right: close expression
	{
		std::cout << ")";
	}


};