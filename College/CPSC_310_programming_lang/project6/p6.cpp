#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

map<string, vector<string>> createGraphWithTaskList(vector<string>& taskList)
{ //map shows association
    map<string, vector<string>> ans; // value is the nodes the key is dependent on for popping
    
    for(int i{0}; i < taskList.size(); i += 2) // initializes value
    {
        ans[taskList[i]].push_back(taskList[i + 1]);
        ans[taskList[i+1]]; 
    }
        //ans[stringNodes[i]] = vector<string>();
    return ans;   
}

vector<string>  getTaskList()
{
    string input;
    vector<string> ans;
    cout << "Enter your node relationship input (every 1st line of pair denotes depender, 2nd line denotes dependent):";
    while ((getline(cin, input) && !input.empty() )) 
        ans.push_back(input);
    return ans;
}

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

void printGraphTraversal(map<string, vector<string>>& nodes)
{
    //Goal: Go up and down map, pop if empty array, then update all other map values that contained that popped key
    map<string, vector<string>>::iterator it; 
    for(int i{0}, startNodesCount = nodes.size(); i < startNodesCount; i++)
    {
        for(it = nodes.begin(); it != nodes.end(); it++)
        {
            if(it->second.size() == 0)
            {
                cout << it -> first + '\n';
                removeAllReferencesToNode(it -> first, nodes);
                nodes.erase(it -> first);
                break;
            }
            // MAKE SURE TO BREAK AFTER REMOVING NODE
        }
    }
    if(nodes.size() > 0) 
        cout << "cycle";

}

int main()
{
    vector<string> taskList = getTaskList();
    map<string, vector<string>> graph = createGraphWithTaskList(taskList);
    printGraphTraversal(graph);
}


// Do we need to account for throwing error for > 60 char long
// "You will not be tested on invalid inputs" So does this mean we dont need to do input checking/validation?
