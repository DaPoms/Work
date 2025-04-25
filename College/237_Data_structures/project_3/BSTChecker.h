#ifndef BSTCHECKER_H
#define BSTCHECKER_H

// TODO: Include any needed header files
#include "BSTNode.h"
#include <iostream> //Delete  reijiogjoiwegjrwgijwerjgiwrjgiwiroegjireg
#include <vector>
using namespace std;

class BSTChecker {
public:
   // TODO: Add any desired utility functions

   static bool contains(int key, vector<int>& passedVect)
   {
        for(int i{0}; i < passedVect.size(); i++)
        {
            if(key == passedVect[i])
                return true;
        }
        return false;
   }
   static BSTNode* preOrderTraversal(BSTNode* rootNode, BSTNode* origin, char side, BSTNode* errorAns, vector<int>& explored)
    { 
                if(rootNode -> key == 25)
                    cout << "";
                
                //cout << "visiting: " << rootNode -> key << '\n';
                if(!contains(rootNode -> key, explored)) //CURRENT ISSUE: Base case is the right most node, so the duplicate of 75 is triggering first, explore how 75 works
                    explored.push_back(rootNode -> key); //NEXT TO IMPLIMENT: Child related problems
                else
                {
                
                    //errorAns = rootNode;
                    return rootNode; //This is our error case of child leading to a parent
                }

                if(rootNode == (origin -> right) ) //Case of first left w5gjuwertgiuhgiousbg
                    side = 'R';
                
                if(rootNode == (origin -> left) ) //Case of first left
                    side = 'L';

                if(rootNode != origin) //need some way to find if we are left or right of origin            TO BE DONE: Add detection for left or ride side of origin
                {
                    
                    if(side == 'R' && rootNode -> key < origin -> key) //Case of right side error (something less being on the right)
                    {
                        //return rootNode;
                        errorAns = rootNode;
                    }

                    if(side == 'L' && rootNode -> key > origin -> key) //Case of left side error (something greater than root being on the left)
                    {
                        //return rootNode;
                        errorAns = rootNode;
                    }
                }

                
            
                if(rootNode -> right)
                {
                    if(rootNode -> key > rootNode -> right -> key)
                    {
                        return rootNode -> right;
                    } 
    
                    errorAns = preOrderTraversal(rootNode -> right, origin, side, errorAns, explored); //current issue: Only visiting left most nodes    
                }
                
                if(rootNode -> left)
                {
                    if(rootNode -> key < rootNode -> left -> key)
                    {
                        //cout << rootNode -> key << "  " << rootNode -> left -> key <<  "n";
                        return rootNode -> left;
                    } 
                    /* if(rootNode == (origin -> left) ) //Case of first left
                        side = 'L'; */
                    errorAns = preOrderTraversal(rootNode -> left, origin, side, errorAns, explored);
                }

                

                
                
                return errorAns; 
           // }
        
        
    }



    static BSTNode* CheckBSTValidity(BSTNode* rootNode) //Possibly for case of element being on wrong side of the parent, try inserting. If insertion is different then the location, then we can flag error
   {
    //Preorder traversal
    vector<int> dupeChecker;
    BSTNode* answer = preOrderTraversal(rootNode, rootNode, '\0', nullptr, dupeChecker);
    //Plan: Keep value of first root, then make sure all left vals are less than root, all right greater than root
    return answer;
   }

   
};
   // CheckBSTValidty() determines if the tree is a valid BST. If so, nullptr
   // is returned. If not, the first (in preorder traversal) node in violation
   // of BST requirements is returned. Such a node will be one of the following:
   // - A node in the left subtree of an ancestor with a lesser or equal key
   // - A node in the right subtree of an ancestor with a greater or equal key
   // - A node that is encountered more than once during traversal
   /* static BSTNode* CheckBSTValidity(BSTNode* rootNode) //Possibly for case of element being on wrong side of the parent, try inserting. If insertion is different then the location, then we can flag error
   {
    //Preorder traversal

    //Plan: Keep value of first root, then make sure all left vals are less than root, all right greater than root
        cout << "visited: " << rootNode -> key << '\n'; 
        while(rootNode)
            {
            
                if(rootNode -> left)
                {
                    if(rootNode -> key < rootNode -> left -> key)
                    {
                        
                        //cout << rootNode -> key << "  " << rootNode -> left -> key <<  "n";
                        return rootNode -> left;
                    } 
                    CheckBSTValidity(rootNode -> left);
                }

                if(rootNode -> right)
                {
                    if(rootNode -> key > rootNode -> right -> key)
                    {
                        return rootNode -> right;
                    } 
                    CheckBSTValidity(rootNode -> right); //current issue: Only visiting left most nodes    
                }
                
                return nullptr;
                
            }
        
        return nullptr;
   }

}; */

#endif


/* 
        cout << rootNode -> key << '\n'; 
        while(rootNode -> left || rootNode -> right)
        {
        
            
            if(rootNode -> left)
            {
            
                if(rootNode -> key < rootNode -> left -> key)
                {
                    return rootNode -> left;
                } 

                CheckBSTValidity(rootNode -> left);
            }

            if(rootNode -> right)
            {
                if(rootNode -> key > rootNode -> right -> key)
                {
                    
                    return rootNode -> right;
                } 
                
                CheckBSTValidity(rootNode -> right);
            }

            return rootNode;
            //return nullptr; //NEED TO FIX!!!! what to do???
        
        }

 */






       /*  //Test for validity here
        while(rootNode -> left || rootNode -> right)
        {
           
            cout << rootNode -> key << '\n'; 
            if(rootNode -> left)
            {
            
                if(rootNode -> key < rootNode -> left -> key)
                {
                    
                    //cout << rootNode -> key << "  " << rootNode -> left -> key <<  "n";
                    return rootNode -> left;
                } 

                CheckBSTValidity(rootNode -> left);
            }

            if(rootNode -> right)
            {
                if(rootNode -> key > rootNode -> right -> key)
                {
                    return rootNode -> right;
                } 
                CheckBSTValidity(rootNode -> right);
            }
            return nullptr; //NEED TO FIX!!!! what to do???
        
        }
     */
