// Source Code from : Data Structures and Algorithms in C++, 2nd Edition
// Implement an ordered dictionary of n internal nodes


/////////////////////////////////////////////////////////////////////////
//////////////      Code Fragment: AVLEntry        //////////////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>
class AVLEntry : public E {		// an AVL entry to store the height information; E stands for Entry class?
private:
    int ht;						// node height
protected:						// protected, so that a user can't access them, but AVLTree can
    typedef typename E::Key K;				// key type
    typedef typename E::Value V;			// value type
    int height() const { return ht; }			// get height
    void setHeight(int h) { ht = h; }			// set height
public:						// public functions
    AVLEntry(const K& k = K(), const V& v = V())	// constructor
        : E(k, v), ht(0) { }
    friend class AVLTree<E>;				// allow AVLTree access
};


/////////////////////////////////////////////////////////////////////////
//////////////       Code Fragment: Class           /////////////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>					// an AVL tree derived from the class SearchTree
class AVLTree : public SearchTree< AVLEntry<E> > {
public:						// public types
    typedef AVLEntry<E> AVLEntry;			// an entry
    typedef typename SearchTree<AVLEntry>::Iterator Iterator; // an iterator
protected:						// local types
    typedef typename AVLEntry::Key K;			// a key
    typedef typename AVLEntry::Value V;			// a value
    typedef SearchTree<AVLEntry> ST;			// a search tree
    typedef typename ST::TPos TPos;			// a tree position
public:						// public functions
    AVLTree();						// constructor
    Iterator insert(const K& k, const V& x);		// insert (k,x)
    void erase(const K& k) throw(NonexistentElement);	// remove key k entry
    void erase(const Iterator& p);			// remove entry at p
protected:						// utility functions to maintain the AVL tree balance properties.
    int height(const TPos& v) const;			// node height utility
    void setHeight(TPos v);				// set height utility
    bool isBalanced(const TPos& v) const;		// is v balanced?
    TPos tallGrandchild(const TPos& v) const;		// get tallest grandchild
    void rebalance(const TPos& v);			// rebalance utility
};


/////////////////////////////////////////////////////////////////////////
//////////////       Code Fragment: Balance         /////////////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>					// constructor, create a tree having no nodes
AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
int AVLTree<E>::height(const TPos& v) const
{
    return (v.isExternal() ? 0 : v->height());
}


/////////////////////////////////////////////////////////////////////////
//////////////       Code Fragment: TallGrandchild        ///////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>					// set height utility
void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    v->setHeight(1 + std::max(hl, hr));			// max of left & right
}

template <typename E>					// is v balanced?
bool AVLTree<E>::isBalanced(const TPos& v) const {
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
}

template <typename E>					// get tallest grandchild
typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
        if (height(zl.left()) >= height(zl.right()))
            return zl.left();
        else
            return zl.right();
    else 						// right child taller
        if (height(zr.right()) >= height(zr.left()))
            return zr.right();
        else
            return zr.left();
}


/////////////////////////////////////////////////////////////////////////
//////////////       Code Fragment: Rebalance         ///////////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>	// set height as 1 more than the maximum of the heights of its 2 children
void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    v->setHeight(1 + std::max(hl, hr));			// max of left & right
}

template <typename E>  // is node v balanced? By checking whether the height difference between its children is at most 1
bool AVLTree<E>::isBalanced(const TPos& v) const {
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
}

template <typename E>  // get tallest grandchild of a node to which the restructuring operation will be applied
typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
        if (height(zl.left()) >= height(zl.right()))
            return zl.left();
        else
            return zl.right();
    else 						// right child taller
        if (height(zr.right()) >= height(zr.left()))
            return zr.right();
        else
            return zr.left();
}


/////////////////////////////////////////////////////////////////////////
//////////////       Code Fragment: Rebalance         ///////////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>	// core function to rebalance the AVL tree after an insertion or removal
void AVLTree<E>::rebalance(const TPos& v) {
    TPos z = v;
    while (!(z == ST::root())) {			// rebalance up to root
        z = z.parent();
        setHeight(z);					    // compute new height
        if (!isBalanced(z)) {				// restructuring needed
            TPos x = tallGrandchild(z);
            z = restructure(x);				// trinode restructure
            setHeight(z.left());			// update heights
            setHeight(z.right());
            setHeight(z);
        }
    }
}


/////////////////////////////////////////////////////////////////////////
//////////////       Code Fragment: Insert          /////////////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>					// insert (k,x)
typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    TPos v = inserter(k, x);				// insert in base tree
    setHeight(v);					// compute its height
    rebalance(v);					// rebalance if needed
    return Iterator(v);
}


/////////////////////////////////////////////////////////////////////////
//////////////       Code Fragment: Erase           /////////////////////
/////////////////////////////////////////////////////////////////////////
template <typename E>					// remove key k entry
void AVLTree<E>::erase(const K& k) throw(NonexistentElement) {
    TPos v = finder(k, ST::root());			// find in base tree
    if (Iterator(v) == ST::end())			// not found?
        throw NonexistentElement("Erase of nonexistent");
    TPos w = eraser(v);					// remove it
    rebalance(w);					// rebalance if needed
}


