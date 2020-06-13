1. To achieve logarithmic time for all fundamental map operations.
2. Maintain a logarithmic height for the tree
3. Any binary search tree satisfies the height-balance property is AVL Tree.
4. The height is the length of the longest path from given node v to an external node
5. Height-Balance Property: For each node v, its children's heights differ at most 1.
6. ![AVL Tree]()
7. The subtree of an AVL tree is itself an AVL Tree.
8. Height-Balance Property keeps the height as small as possible after insertion or removal
9. If the absolute value of difference between the heights of the children of node v is at most 1, the node v is balanced; otherwise it's unbalanced.
10. Thus, the height-balance property actually means that each internal node is balanced.
11. balance factor of v = (height of the left child of v) - (height of the right child of v)
12. Thus, the balance factor of v is always equal to -1,0,1 when v is balanced. otherwise -2 or +2, when unbalanced
