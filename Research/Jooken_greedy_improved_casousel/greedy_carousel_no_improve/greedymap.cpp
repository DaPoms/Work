#include <iostream>
#include <fstream>
#include <filesystem> // I'm only using the scope operator for this one (not using namespace) as this is a new library I'm getting used to
#include <vector>
#include <string> //Need gap, best objective, time for excel
#include <algorithm>
#include <unordered_map>
using namespace std;
//Warning: This algorithm only works for > 1 objects, but it's normal to assume that there'd be no need to solve a knapsack with 1 element (it's already solved at that point!)
void greedyKnapsack(long long& capacity, long long& currentWeight, vector<long long>& weights, unordered_map<int, pair<int, bool> >& candidates, vector<int>& answerElems)
{
    int i{0};
    while(i < int(candidates.size()) && currentWeight < capacity) //first phase of greedy
            {
                if(candidates[i].second == 1 && weights[candidates[i].first] + currentWeight <= capacity) //had to do this to make sure it checks past objects it cannot fit
                {
                    answerElems.push_back(candidates[i].first);
                    currentWeight += weights[candidates[i].first]; 
                    candidates[i].second = 0; //removes object from being a candidate, it is now in the bag
                    i--;
                }
                i++;
            }
}

void addOneGreedy( vector<int>& answerElems, unordered_map<int, pair<int, bool> >& candidates, int& count, long long& capacity, long long& currentWeight, vector<long long>& weights)
{

    int i{0};
    while(i < count) //first phase of greedy
            {
                if(candidates[i].second == 1 && weights[candidates[i].first] + currentWeight <= capacity) //had to do this to make sure it checks past objects it cannot fit
                {
                    answerElems.push_back(candidates[i].first); // element added to the back
                    currentWeight += weights[candidates[i].first]; 
                    candidates[i].second = 0; //removes element from candidate pool
                    return;
                }
                i++;
            }
}

// NOTE: REMOVE FROM FRONT FOR A REMOVAL, ADD ELEMENT TO BACK, but RESORT, Can element back in after removal
void carouselGreedy(vector<int>& answerElems, vector<long long>& values, vector<long long>& weights, unordered_map<int, pair<int, bool> >& candidates, long long& capacity, long long& currentWeight, int a, double b)
{
    vector<int> removedUsingB; //we add answerElems we remove back to the candidate pool (bestRatioIndexesRemaining) after carousel is done
    //Note: removed items are NOT reconsidered, or else there'd be no change
    int carouselCounter{0};
    int startingSize{int(answerElems.size())};
    int numToRemove = startingSize * b; //amount of elements we are removing from the back
    if(numToRemove == 0 && a == 0) return;
    for(int i{int(answerElems.size()) - 1}; i >= startingSize - numToRemove; i--)
    {
        currentWeight -= weights[answerElems[i]];
        removedUsingB.push_back(answerElems[i]); //elements in unordered_map that we "remove"
        answerElems.pop_back(); // we do NOT add these removed elements back
       //candidates[i].second = 1;
    }
    int count = int(candidates.size()); 
    //Note: a elements removed are removed from the FRONT not the BACK like we did for b
    while(carouselCounter < (a * startingSize) ) //we assume the user inputs an "a" less than the elements left after "b" (the % of answers removed from the bag)
    {
        currentWeight -= weights[answerElems[0]]; //takes weight from front of answerElems out of our knapsack
        int addABack = answerElems[0]; // Adds element from answer pool to candidate pool after addOneGreedy finds a new candidate
        answerElems.erase(answerElems.begin()); // once again inefficient, all elements have to be shifted left one
        
        addOneGreedy(answerElems, candidates, count, capacity, currentWeight, weights); 
        carouselCounter++;

        for(int i{0}; i < candidates.size(); i++)
        {
            if(candidates[i].first == addABack)
            {
                candidates[i].second = 1;
                break;
            }
            
        }
    }

    for(int removed : removedUsingB)
    {
        for(int i{0}; i < candidates.size(); i++)
        {
            if(candidates[i].first == removed) //every unordered_map has a unique .first int stored, so we can do this!
                candidates[i].second = 1;
        }
    }
    
    greedyKnapsack(capacity, currentWeight, weights, candidates, answerElems); //We do greedy one last time to fill any freed up weight from the b or a removal
}
    
 //Do note, the way that I made this, answerElems will not be sorted by bestRatio anymore (as the addOneGreedy() pushes back, but we remove from right to left)
  //I primarily did this because we do not do anything relating to sortedness with the result of carousel

//Only need to re-sort when adding element back to remaining bestRatioIndexesRemaining pool
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
    excel << "Name:" << "," << "Obj Fn" << '\n';
    std::filesystem::path problems{"C:/Users/Pomer/projects/Research/Jooken_greedy_improved_casousel/greedy_carousel_no_improve"}; //Problem instances are provided by JorikJooken github: https://github.com/JorikJooken/knapsackProblemInstances 
    ifstream testFile;  
    vector<long long> values = {};
    vector<long long> weights = {};
    int count;
    long long capacity{-1};
    int a{1}; //comment out in case of NOT constant a and uncomment the for loop with the a variable in it for making variable a values
        for(const auto& entry : std::filesystem::recursive_directory_iterator(problems)) //tests removing 10% - 50% of elements
        {
            //excel.open("results.csv", ios::app);
            if(entry.path().filename() == "test.in") //Specifies what file we want to use that we find in any folder
            {
                //if(entry.path().parent_path().filename() <= "n_1000_c_100000000_g_2_f_0.2_eps_0.1_s_200") continue; // allows for continuing from file if it stopped for some reason (just put the file name it stopped on)
                //File reading + writing section
                //excel.open("results.csv", ios::app); //opens file again (allows adding results 1 by 1 rather than by bulk) app stands for append (prevents overwriting)
                testFile.open(entry.path()); //MAKE SURE TO USE .CLEAR BEFORE NEXT FILE
                readFile(testFile, weights, values, count, capacity); //we assume the testFile is formatted properly (starts with count, then all the elements in the problem, and ends with the capacity of the knapsack) 
                excel << entry.path().parent_path().filename();
            } else continue; //makes sure we skip all the for loops where the file isn't our testFile

            for(double b{0.2}; b <= 0.4; b += 0.05) 
            {
                
                //for (int a{1}; a <= 5; a++) //traverses every "entity" in the given folder
                //{  
                 
                    vector<int> bestRatioIndexesRemaining; //index 0 has the highest ratio, last is the worst. Only contains elements NOT in our knapsack
                    for(int i{0}; i < count; i++)
                        bestRatioIndexesRemaining.push_back(i);
                    sort(bestRatioIndexesRemaining.begin(), bestRatioIndexesRemaining.end(), [&values, &weights](int i, int j) 
                    {
                        return (double(values[i]) / weights[i]) > (double(values[j]) / weights[j]);
                    } 
                    );

                    ////////////////////////////
                    unordered_map<int, pair<int, bool> > candidates; //when bool = 1, element is still a candidate
                    for(int i{0}; i < bestRatioIndexesRemaining.size(); i++)
                        candidates[i] = pair(bestRatioIndexesRemaining[i], 1);
                    
                    //////////////////////////////////////////////

                    //NEW THING LEARNED! Lambda functions, they're inline functions! negative: lambda is not very readable
                    vector<int> answerElems; //what is in our knapsack
                    long long currentWeight{0};  
                    greedyKnapsack(capacity, currentWeight, weights, candidates, answerElems); //stage 1 of the algorithm
                    carouselGreedy(answerElems, values, weights, candidates, capacity, currentWeight, a, b);//Stage 3 - carousel
                    
                    long long profit{0};
                    for(int elem : answerElems)
                    {
                        profit += values[elem];
                    }
              
                    cout << profit << '\n';
                        //Puts results in CSV file
                    excel << "," << profit;
                        //excel.close(); //Closes to update results.csv (just to let me see vls)
                        //Resetting values before the next model   
                        //testFile.seekg(0); // moves back to beggining 
                            
                //}
            }
            excel << endl; //next file. LESSON LEARNED: endl FLUSHES buffer, which then writes the values into the file, allows sending in pieces rather than all at once (that could lead to buffer overflow)
            values.clear();
            weights.clear();
            testFile.close(); 
            //excel.close();
        }
    excel.close();
}

