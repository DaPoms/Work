#include <iostream>
#include <fstream>
#include <filesystem> // I'm only using the scope operator for this one (not using namespace) as this is a new library I'm getting used to
#include <vector>
#include <string> //Need gap, best objective, time for excel
#include <algorithm>
using namespace std;
//namespace fs = std::filesystem;

        
void contestCandidate(vector<int>& answerElems, int targetI, vector<long long>& values, vector<long long>& weights, vector<int>& bestRatioIndexes)
{
    vector<int> replacement;
    int startingSize{int(answerElems.size())};
    //currentWeight -= weights[bestRatioIndexes[targetI]]; //"takes out" the object we want to substitute 
    int count = bestRatioIndexes.size();
    long long weightDeficit{weights[bestRatioIndexes[targetI]]};
    long long currentWeight{0};

    //for candidate searching, we only check past the bestRatioIndex    
    int i{targetI};
    while(i < count && currentWeight < weightDeficit) //first phase of greedy
            {
                if(weights[bestRatioIndexes[i]] + currentWeight <= weightDeficit) //had to do this to make sure it checks past objects it cannot fit
                {
                    replacement.push_back(bestRatioIndexes[i]);
                    currentWeight += weights[bestRatioIndexes[i]]; 
                }
                i++;
            }
            if(answerElems.size() == startingSize) return; //case of no candidates being able to fit (optimziation), and allows us to test the next for loop without a seg fault
            long long sum{0};
            for(int i{targetI + 1}; i < answerElems.size(); i++)
            {
                sum += values[answerElems[i]];
            }
            if(sum > values[answerElems[targetI]])
                answerElems.erase(answerElems.begin() + targetI);
            else
                while(answerElems.size() != startingSize) //remove elements we tried to substitute 
                    answerElems.pop_back();
}
void readFile(ifstream& problemFile, vector<long long>& weights, vector<long long>& values, int& count, long long& capacity)
{
    //First val is number of elems/count, last val is capacity of knapsack
    long long element;
    problemFile >> count;
    for(int i{0}; i < count; i++) //for every element
    {
        problemFile >> element; //ID (we skip as theres no use in knowing the id)
        problemFile >> element; //Value
        values.push_back(element);
        problemFile >> element; // Weight
        weights.push_back(element);
    }
    
    //Last value in the problem file will be the knapsack capacity
    problemFile >> capacity;
}

int main()
{ //note, presolve on by default
    //formatting and creating a csv file following an excel format
    ofstream excel("results.csv"); //creates file for data to be put in, ios::app allows appending so .open doesn't overwrite
    excel << "Name:" << "," << "Obj Fn" << "," << "Runtime" << "," << "MIPGAP" << '\n';
    std::filesystem::path problems{"C:/Users/Pomer/projects/Job/Jooken_greedy_casousel/mySample"}; //Problem instances are provided by JorikJooken github: https://github.com/JorikJooken/knapsackProblemInstances 
    ifstream testFile;  
    vector<long long> values = {};
    vector<long long> weights = {};
    int count;
    long long capacity{-1};
        for (const auto& entry : std::filesystem::recursive_directory_iterator(problems)) //traverses every "entity" in the given folder
        { 
            if(entry.path().filename() == "test.in") //Specifies what file we want to use that we find in any folder
            {
                //File reading + writing section
                excel.open("results.csv", ios::app); //opens file again (allows adding results 1 by 1 rather than by bulk)
                testFile.open(entry.path()); //MAKE SURE TO USE .CLEAR BEFORE NEXT FILE
                //testFile.open("test.in");
                readFile(testFile, weights, values, count, capacity); //we assume the testFile is formatted properly (starts with count, then all the elements in the problem, and ends with the capacity of the knapsack)
                
                //greedy algorithm
                //pair<vector<long long>, vector<long long>> objects = {weights, values};
                vector<int> bestRatioIndexes; //index 0 has the highest ratio, last is the worst
                for(int i{0}; i < count; i++)
                    bestRatioIndexes.push_back(i);
                sort(bestRatioIndexes.begin(), bestRatioIndexes.end(), [&values, &weights](int i, int j) 
                {
                    return (double(values[i]) / weights[i]) > (double(values[j]) / weights[j]);
                } 
                );
            //NEW THING LEARNED! Lambda functions, they're inline functions! negative: lambda are not very readable
            vector<int> answerElems;
            int currentWeight{0};
            int i{0};
            //long long profits{0}; //calculate at the end

           while(i < count && currentWeight < capacity) //first phase of greedy
            {
                if(weights[bestRatioIndexes[i]] + currentWeight <= capacity) //had to do this to make sure it checks past objects it cannot fit
                {
                    answerElems.push_back(bestRatioIndexes[i]);
                    currentWeight += weights[bestRatioIndexes[i]]; 
                }
                i++;
            }
           
            int backIndex{int(answerElems.size()) - 1};
            //improvement phase of greedy
            for(int targetI{backIndex}; targetI >= 0; targetI--) //by starting from the end of our bag, we get rid of our worst candidates first
            {
                contestCandidate(answerElems, targetI, values, weights, bestRatioIndexes);
                cout << "TEST!";
            }

                
                //Puts results in CSV file
                //excel << entry.path().parent_path().filename() << "," << model.get(GRB_DoubleAttr_ObjVal) << "," << model.get(GRB_DoubleAttr_Runtime) << "," << model.get(GRB_DoubleAttr_MIPGap) << "\n";
                //excel.close(); //Close here if samples size is too large
                //Resetting values before the next model   
                testFile.close(); // to move onto the next model file
                values.clear();
                weights.clear();
            }
            excel.close(); //updates the csv file at the end of every model
        }
}



