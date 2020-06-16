// Source Code from : Data Structures and Algorithms in C++, 2nd Edition
// Implement an ordered dictionary of n internal nodes


template <typename E>
class AVLEntry : public E {		// an AVL entry to store the getHeight information; E stands for Entry class?
private:
    int nodeHeight;						
protected:						// protected, so that a user can't access them, but AVLTree can
    using Key = typedef typename E::Key;
    using Value = typedef typename E::Value;

    int getHeight() const { return nodeHeight; }			// get getHeight
    void setHeight(int h) { nodeHeight = h; }			    // set getHeight
public:						
    AVLEntry(const Key& k = Key(), const Value& v = Value())	// constructor
        : E(k, v), nodeHeight(0) { }
    friend class AVLTree<E>;				// allow AVLTree access
};


template <typename E>					// an AVL tree derived from the class SearchTree
class AVLTree : public SearchTree< AVLEntry<E> > {
public:						
    using AVLEntry = AVLEntry<E>;
    using Iterator = typename SearchTree<AVLEntry>::Iterator;
protected:						
    using Key = typename AVLEntry::Key;     
    using Value = typename AVLEntry::Value;
    using SearchTree = searchTree<AVLEntry>;    // a search tree
    using TreePosition = typename ST::TreePosition;     // a tree position

public:						
    AVLTree();						
    Iterator insert(const Key& k, const Value& x);		    // insert (k,x)
    bool erase(const Key& k) throw(NonexistentElement);	    // remove key k entry
    bool erase(const Iterator& p);			                // remove entry at p
protected:						                // utility functions to maintain the AVL tree balance properties.
    int getHeight(const TreePosition& v) const;			// node getHeight utility
    void setHeight(TreePosition v);				        // set getHeight utility
    bool isBalanced(const TreePosition& v) const;		// is v balanced?
    TreePosition getTallerGrandchild(const TreePosition& v) const;	// get tallest grandchild
    void rebalance(const TreePosition& v);			    // rebalance utility
};



template <typename E>					// constructor, create a tree having no nodes
AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node getHeight utility
int AVLTree<E>::getHeight(const TreePosition& v) const
{
    return (v.isExternal() ? 0 : v->getHeight());
}


template <typename E>					
void AVLTree<E>::setHeight(TreePosition v) 
{
    int leftChildHeight = getHeight(v.left());
    int rightChildHeight = getHeight(v.right());
    v->setHeight(1 + std::max(leftChildHeight, rightChildHeight));
}

template <typename E>
bool AVLTree<E>::isBalanced(const TreePosition& v) const 
{
    int balanceFactor = getHeight(v.left()) - getHeight(v.right());
    return ((-1 <= balanceFactor) && (balanceFactor <= 1));
}

template <typename E>					// get tallest grandchild
typename AVLTree<E>::TreePosition 
AVLTree<E>::getTallerGrandchild(const TreePosition& nodePosition) const 
{
    TreePosition leftChildPosition = nodePosition.left();
    TreePosition rightChildPosition = nodePosition.right();

    // left child taller
    if (getHeight(leftChildPosition) >= getHeight(rightChildPosition))
    {
        if (getHeight(leftChildPosition.left()) >= getHeight(leftChildPosition.right()))
            return leftChildPosition.left();
        else
            return leftChildPosition.right();
    }    
    // right child taller
    else 
    {
        if (getHeight(rightChildPosition.right()) >= getHeight(rightChildPosition.left()))
            return rightChildPosition.right();
        else
            return rightChildPosition.left();
    }
}

template <typename E>
void AVLTree<E>::rebalance(const TreePosition& v) {
    TreePosition nodePosition = v;

    // rebalance up to root
    while (!(nodePosition == ST::root())) 
    {			
        parentNodePosition = nodePosition.parent();
        setHeight(parentNodePosition);					    
        if (!isBalanced(parentNodePosition))
        {				
            TreePosition x = getTallerGrandchild(parentNodePosition);
            
            nodePosition = restructure(x);				// trinode restructure

            setHeight(nodePosition.left());			    // update heights
            setHeight(nodePosition.right());
            setHeight(nodePosition);
        }
    }
}


template <typename E>					// insert (k,x)
typename AVLTree<E>::Iterator AVLTree<E>::insert(const Key& k, const Value& x) {
    TreePosition v = inserter(k, x);				// insert in base tree
    setHeight(v);					// compute its getHeight
    rebalance(v);					// rebalance if needed
    return Iterator(v);
}


template <typename E>					
bool AVLTree<E>::erase(const Key& k) 
{
    TreePosition v = finder(k, ST::root());			// find in base tree
    if (Iterator(v) == ST::end())			        // not found?
        return false;
    TreePosition w = eraser(v);					    // remove it
    rebalance(w);					                // rebalance if needed
    return true;
}


