    #include <vector>
    #include <iostream>
    using namespace std;
    vector<vector<int>> generate(int numRows) 
    {
        int traverseRow{0};
        vector<int> toBeAdded = {1};
        vector<vector<int>> ans = {toBeAdded};
        toBeAdded.clear();
        for(int i{1}; i < numRows; i++)
        {
            while(traverseRow <= ans[i - 1].size() - 1) //One away from end
            {
                if(traverseRow == 0) //Case of start
                    toBeAdded.push_back(1);

                if(traverseRow != ans[i - 1].size() - 1 && ans[i - 1].size() > 1) //Case of adding of adding the 2 above touching elements to make the new below element (which is for the new row), makes sure the index is not at the end to prevent seg faults
                    toBeAdded.push_back( (ans[i - 1])[traverseRow] + (ans[i - 1])[traverseRow + 1]);
                
                if(traverseRow == (ans[i - 1].size() - 1)) //Case of end, it will always be 1
                    toBeAdded.push_back(1);

                traverseRow++;
            }

            traverseRow = 0;
            ans.push_back(toBeAdded); //We add the new row we created to the triangle
            toBeAdded.clear();
        }
        
        return ans;
    }

    //Alternate of pascals that only returns the row that is passed as a param
    vector<int> getRow(int rowIndex)
    {
        int numRows = rowIndex + 1;
        int traverseRow{0};
        vector<int> toBeAdded = {1};
        vector<vector<int>> ans = {toBeAdded};
        toBeAdded.clear();
        for(int i{1}; i < numRows; i++)
        {
            while(traverseRow <= ans[i - 1].size() - 1) //One away from end
            {
                if(traverseRow == 0) //Case of start
                    toBeAdded.push_back(1);

                if(traverseRow != ans[i - 1].size() - 1 && ans[i - 1].size() > 1) //Case of adding of adding the 2 above touching elements to make the new below element (which is for the new row), makes sure the index is not at the end to prevent seg faults
                    toBeAdded.push_back( (ans[i - 1])[traverseRow] + (ans[i - 1])[traverseRow + 1]);
                
                if(traverseRow == (ans[i - 1].size() - 1)) //Case of end, it will always be 1
                    toBeAdded.push_back(1);

                traverseRow++;
            }

            traverseRow = 0;
            ans.push_back(toBeAdded); //We add the new row we created to the triangle
            toBeAdded.clear();
        }
        
        return ans[rowIndex];
    }

    int main()
    {
        vector<vector<int>> ans = generate(5);
        for(vector<int> rows : ans) // This doesn't really print the correct shape of the triangle, but you get the idea
        {
            for(int num : rows)
            {
                cout << num << " ";
            }
            cout << '\n';
        }
    }
