/*
* Author:         Daniel Tripoli                             
* Major:          Computer Science                           
* Creation Date:  May 2, 2026                             
* Due Date:       May 8, 2026                             
* Course: CPSC    310 010                                    
* Professor Name: Dr. Dylan Schwesinger                      
* Project:        #6                                         
* Filename:       p6.cpp                                    
* Purpose:        Implements the solution to a graph traversal problem in c++                        
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

/*
* Function name:  createGraphWithTaskList
* Description:    Uses a given structure of dependents (node thats dependent)
*                 to prequisites (the node it's dependent on) to make a 
*                 map of each node's prequisite nodes before it can  
*                 be 'popped'
* Parameters:     vector<string>& taskList - The list of dependent -> prequisite 
*                 relationships
* Return Value:   map<string, vector<string>> The associations of nodes and
*                 The nodes that must be traversed before the node can be 
*                 accessed
*/
map<string, vector<string>> createGraphWithTaskList(vector<string>& taskList)
{ 
    map<string, vector<string>> ans; 
    
    for(int i{0}; i < taskList.size(); i += 2) 
    {
        ans[taskList[i]].push_back(taskList[i + 1]);
        ans[taskList[i+1]]; 
    }
    return ans;   
}

/*
* Function name:  getInputTaskList
* Description:    Collects user input (infering proper formatting) for the 
*                 creation of a task list from the input
* Parameters:     None
* Return Value:   vector<string> - The task list. Every 2 are their own pair, with
*                 The first being the dependent, and the 2nd being the 
*                 prequisite node (must be evaluated first)
*/
vector<string>  getInputTaskList()
{
    string input;
    vector<string> ans;
    while ((getline(cin, input))) 
        ans.push_back(input);
    return ans;
}

/*
* Function name:  removeAllReferencesToNode
* Description:    Removes the target node and it's references from a graph
* Parameters:     string node - The node that is removed
*                 map<string, vector<string>>& nodes The graph that gets the  
*                 target node removed
* Return Value:   none
*/
void removeAllReferencesToNode(string node, map<string, vector<string>>& nodes)
{
    map<string, vector<string>>::iterator it; 
    for(it = nodes.begin(); it != nodes.end(); it++)
    {
        vector<string>& valuesAtKey = it -> second;
        auto targetIt = find(valuesAtKey.begin(), valuesAtKey.end(), node); 
        if(targetIt != valuesAtKey.end())
            valuesAtKey.erase(targetIt);
    }
}

/*
* Function name:  printGraphTraversal
* Description:    Traverses a graph and prints out the name of the nodes it 
*                 traverses
* Parameters:     map<string, vector<string>>& nodes The graph that gets 
*                 traversed
* Return Value:   none
*/
void printGraphTraversal(map<string, vector<string>>& nodes)
{
    map<string, vector<string>>::iterator it; 
    for(int i{0}, startNodesCount = nodes.size(); i < startNodesCount; i++)
        for(it = nodes.begin(); it != nodes.end(); it++)
            if(it->second.size() == 0)
            {
                cout << it -> first + '\n';
                removeAllReferencesToNode(it -> first, nodes);
                nodes.erase(it -> first);
                break;
            }
    if(nodes.size() > 0) 
        cout << "Cycle";

}

int main()
{
    vector<string> taskList = getInputTaskList();
    map<string, vector<string>> graph = createGraphWithTaskList(taskList);
    printGraphTraversal(graph);
}


// Do we need to account for throwing error for > 60 char long
// "You will not be tested on invalid inputs" So does this mean we dont need to do input checking/validation?
