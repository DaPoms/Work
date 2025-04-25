/*	File(s):		tree.cpp
	By:				Dr. Hussain
	Last Modified:	9-Apr-2025
	Purpose:		To demonstrate creation of a binary tree using the LinkedBinaryTree class
	Source:			zyBook Code Fragment 8.3.1 simplified (erase, attach, clone member 
					functions as well as copy constructor, copy assignment, and 
					move assignment are deleted).
*/	
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename E>
class LinkedBinaryTree {
  protected:
    // Nested Node class
    class Node {
      public:					// members public for convenience, as Node class is protected
        E element;
        Node* parent;
        Node* left{nullptr};
        Node* right{nullptr};

        Node(E e, Node* p = nullptr) : element{e}, parent{p} {}
    };						  // end of Node class

    //------ data members of LinkedBinaryTree ------
    Node* rt{nullptr};
    int sz{0};

  public:
    // Nested Position class
    class Position {
      private:
        Node* node;
        friend class LinkedBinaryTree;    // allow outer class access to node pointer

      public:
        Position(Node* nd = nullptr) : node{nd} {}
                 
        bool operator==(Position other) const { return node == other.node; }
        bool operator!=(Position other) const { return node != other.node; }

        bool is_null() const { return node == nullptr; }
        bool is_root() const { return node->parent == nullptr; }
        bool is_external() const { return node->left == nullptr && node->right == nullptr; }
        
        E& element() { return node->element; }        // will allow element to be edited
        const E& element() const { return node->element; }
        Position parent() const { return Position(node->parent); }
        Position left() const { return Position(node->left); }
        Position right() const { return Position(node->right); }
        
        vector<Position> children() const {
            vector<Position> result;
            if (node->left != nullptr) result.push_back(Position(node->left));
            if (node->right != nullptr) result.push_back(Position(node->right));
            return result;
        }
    };				// end of Position class

    // Member functions of LinkedBinaryTree
	LinkedBinaryTree() {}                           // Constructs a tree with zero nodes

    int size() const { return sz; }                 // Returns the number of elements in the tree
    bool empty() const { return sz == 0; }          // True if the tree has size 0

    Position root() const { return Position(rt); }  // Returns a Position for the root (possibly null)

    vector<Position> positions() const {            // Returns an inorder sequence of positions
        vector<Position> gather;
        if (rt) inorder(Position(rt), gather);      // (the inorder function is defined in later section)
        return gather;
    }

    void add_root(const E& e = E()) {               // add root to (presumed) empty tree
        rt = new Node(e);
        sz = 1;
    }

    void add_left(Position p, const E& e) {         // Creates a new left child of p storing e
        p.node->left = new Node{e, p.node};         // parent of new node is p's node
        sz++;
    }
    
    void add_right(Position p, const E& e) {        // Creates a new left child of p storing e
        p.node->right = new Node{e, p.node};        // parent of new node is p's node
        sz++;
    }

  public:
    ~LinkedBinaryTree() { tear_down(rt); }    // Destructor

  private:
    // Recursive helper function to delete nodes
    void tear_down(Node* nd) {
        if (nd != nullptr) {
            tear_down(nd->left);
            tear_down(nd->right);
            delete nd;
        }
    }
};

/*	Write the following function to display the tree
	You may think of using recursion (see the tear_down function)
    You may need to write a helper function in the LinkedBinaryTree class
*/
template <typename E>
void display_tree(const typename LinkedBinaryTree<E>::Position& pos, int depth = 0)
{
    
    if(!pos.is_null())
    {
        for(int i{depth}; i > -1; i--)
            cout << "   ";
        cout << pos.element() << '\n';
        depth++;
        display_tree<E>(pos.left(), depth);
        display_tree<E>(pos.right(), depth);
    }
    
}

int main() {
//	Create a binary tree with the data shown in Fig. 8.3.1 (b) of the text
    LinkedBinaryTree<string> myTree;
    
   /*  myTree.add_root("LAX");
    myTree.add_left(myTree.root(), "BWI");
    myTree.add_left(myTree.root().left(), "ATL");
    myTree.add_right(myTree.root().left(), "JFK");
    myTree.add_right(myTree.root(), "PVD");
 */

    myTree.add_root("LAX");
    myTree.add_left(myTree.root(), "ATL");
    myTree.add_left(myTree.root().left(), "BOS");
    myTree.add_right(myTree.root().left(), "PAR");
    myTree.add_right(myTree.root(), "JFK");
    myTree.add_left(myTree.root().right(), "DTW");
    myTree.add_right(myTree.root().right(), "LHR");

    cout << "Tree elements are: " << endl ;
//  Display the tree (elements only)
    display_tree<string>(myTree.root());

    return 0;
}
