#ifndef BSTNODE_H
#define BSTNODE_H

#include <vector>

class BSTNode {
private:
   virtual BSTNode* Search(int searchKey) {
      BSTNode* currentNode = this;
      while (currentNode) {
         // Return currentNode if the key matches
         if (currentNode->key == searchKey) {
            return currentNode;
         }
         
         // Branch left or right
         else if (searchKey < currentNode->key) {
            currentNode = currentNode->left;
         }
         else {
            currentNode = currentNode->right;
         }
      }
      
      // Key not found
      return nullptr;
   }

public:
   int key;
   BSTNode* left;
   BSTNode* right;
   
   BSTNode(int nodeKey, BSTNode* leftChild = nullptr, BSTNode*
      rightChild = nullptr) {
      
      key = nodeKey;
      left = leftChild;
      right = rightChild;
   }
   
   virtual ~BSTNode() {
   }
   
   virtual bool Contains(int key) {
      return Search(key) != nullptr;
   }
   
   static void DeleteTree(BSTNode* node) {
      if (node) {
         DeleteTree(node->left);
         DeleteTree(node->right);
         delete node;
      }
   }
   
   // Inserts a new key into the subtree rooted at this node, provided the key
   // doesn't already exist
   virtual bool InsertKey(int key) {
      // Duplicate keys not allowed
      if (Contains(key)) {
         return false;
      }
      
      // Allocate the new node
      InsertNode(new BSTNode(key));
      return true;
   }
   
   virtual void InsertKeys(const std::vector<int>& keys) {
      for (int key : keys) {
         InsertKey(key);
      }
   }
   
   virtual void InsertNode(BSTNode* newNode) {
      BSTNode* currentNode = this;
      while (currentNode) {
         if (newNode->key < currentNode->key) {
            if (currentNode->left) {
               currentNode = currentNode->left;
            }
            else {
               // Insert new node as currentNode's left child
               currentNode->left = newNode;
               currentNode = nullptr;
            }
         }
         else {
            if (currentNode->right) {
               currentNode = currentNode->right;
            }
            else {
               // Insert new node as currentNode's right child
               currentNode->right = newNode;
               currentNode = nullptr;
            }
         }
      }
   }
};

#endif
