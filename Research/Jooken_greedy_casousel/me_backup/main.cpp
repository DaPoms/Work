#include <iostream>
#include <fstream>
#include <filesystem> // I'm only using the scope operator for this one (not using namespace) as this is a new library I'm getting used to
#include <vector>
#include <string> //Need gap, best objective, time for excel
#include <algorithm>
using namespace std;
//namespace fs = std::filesystem;
//Warning: This algorithm only works for < 1 objects, but it's normal to assume that there'd be no need to solve a knapsack with 1 element (it's already solved at that point!)
void greedyKnapsack(long long& capacity, long long& currentWeight, vector<long long>& weights, vector<int>& bestRatioIndexesRemaining, vector<int>& answerElems)
{
    int i{0};
    while(i < int(bestRatioIndexesRemaining.size()) && currentWeight < capacity) //first phase of greedy
            {
                if(weights[bestRatioIndexesRemaining[i]] + currentWeight <= capacity) //had to do this to make sure it checks past objects it cannot fit
                {
                    answerElems.push_back(bestRatioIndexesRemaining[i]);
                    currentWeight += weights[bestRatioIndexesRemaining[i]]; 
                    bestRatioIndexesRemaining.erase(bestRatioIndexesRemaining.begin() + i); //removes object from being a candidate, it is now in the bag
                    i--;
                }
                i++;
            }
}

void improvement(vector<int>& answerElems, vector<long long>& values, vector<long long>& weights, vector<int>& bestRatioIndexesRemaining, long long capacity, long long& currentWeight)
{
    vector<int> candidates;
    long long weightDeficit{0};
    long long candidatesWeight{0};
    int count = int( bestRatioIndexesRemaining.size() );
    //for candidate searching, we check the pool of unused objects
    //implimenting ability to test ALL/most plausible substitutions?
    int i{0}; //traverses candidates
    for(int targetI{int(answerElems.size()) - 1}; targetI >= 0; targetI--) //by starting from the end of our bag, we try to swap our worst candidates first (using greedy alg)
    {
        candidatesWeight = 0;
         //The current amount of weight in our substitution, allowed to be <= the deficit
        count = int( bestRatioIndexesRemaining.size() ); // bestRatioIndexesRemaining could change size if we swap any previous elems
        weightDeficit = weights[answerElems[targetI]]; //how much weight we can replace in the substitution, includes the weight of the object and any leftover space we didn't use
        
        while(i < count && candidatesWeight + (currentWeight - weightDeficit) < capacity) //using capacity allows us to use spare space!
        {
            int possibleCandidate = bestRatioIndexesRemaining[i];
            if((weights[bestRatioIndexesRemaining[i]] + candidatesWeight + (currentWeight - weightDeficit) <= capacity)) //&& NOT ALREADY IN ANSWER //had to do this to make sure it checks past objects it cannot fit
            {
                candidates.push_back(possibleCandidate); 
                candidatesWeight += weights[possibleCandidate]; 
            }
            i++;
        }
        
        if(candidates.size() == 0) break; //case of no candidates being able to fit (optimziation)
        long long candidateValSum{0};

        for(int candidateI : candidates)
            candidateValSum += values[candidateI];
        //Adds elements to knapsack if they are a better set of candidates
        if(candidateValSum > values[answerElems[targetI]]) //reminder: TargetI is the element we are trying to substitute with a better set of objects
        {
            bestRatioIndexesRemaining.push_back(answerElems[targetI]); //puts element outside of the knapsack 
            //We have to re-sort our elements as we do not keep track of removed bestRatioIndexes, which is a slight inefficiency, it'd be more efficient to make my own single element sorter, for the case that we know everything else is already sorted and move the new element left till it's where it belongs
            sort(bestRatioIndexesRemaining.begin(), bestRatioIndexesRemaining.end(), [&values, &weights](int i, int j) 
            {
                return (double(values[i]) / weights[i]) > (double(values[j]) / weights[j]);
            });
            currentWeight -= weights[answerElems[targetI]];
            answerElems.erase(answerElems.begin() + targetI); //removes swapped val from knapsack
            
            for(int candidateI : candidates)
            {
                currentWeight += weights[candidateI];
                answerElems.push_back(candidateI); //adds new candidates to knapsack
            }
            //removes candidates from bestRatioIndex
            for(int elem : candidates) //erases from right to left of bestRatio to prevent improper deletion
                bestRatioIndexesRemaining.erase(find(bestRatioIndexesRemaining.begin(), bestRatioIndexesRemaining.end(), elem)); //significantly inefficient
        }
        candidates.clear(); //try another set of candidates, more optimal for some cases
        i = 0; //sets up for retraversing candidates
    }
/* 
    //One last greedy to fill any space freed up
    i = 0;
    while(i < int(bestRatioIndexesRemaining.size()) && currentWeight < capacity) //difference here is spare space, which is any space left before all the swaps 
        {
            int possibleCandidate = bestRatioIndexesRemaining[i];
            if((weights[bestRatioIndexesRemaining[i]] + currentWeight) <= capacity) //&& NOT ALREADY IN ANSWER //had to do this to make sure it checks past objects it cannot fit
            {
                answerElems.push_back(possibleCandidate);
                currentWeight += weights[possibleCandidate]; 
                bestRatioIndexesRemaining.erase(bestRatioIndexesRemaining.begin() + i);
                i--;
            }
            i++;
        } */
}

void addOneGreedy( vector<int>& answerElems, vector<int>& bestRatioIndexesRemaining, int& count, long long& capacity, long long& currentWeight, vector<long long>& weights)
{

    int i{0};
    while(i < count) //first phase of greedy
            {
                if(weights[bestRatioIndexesRemaining[i]] + currentWeight <= capacity) //had to do this to make sure it checks past objects it cannot fit
                {
                    answerElems.push_back(bestRatioIndexesRemaining[i]); //we don't know where it belongs, so we put in back and sort later (with an ugly lambda function)
                    currentWeight += weights[bestRatioIndexesRemaining[i]]; 
                    bestRatioIndexesRemaining.erase(bestRatioIndexesRemaining.begin() + i);
                    
                    return;
                }
                i++;
            }
}

// NOTE: REMOVE FROM FRONT FOR A REMOVAL, ADD ELEMENT TO BACK, but RESORT, Can element back in after removal
void carouselGreedy(vector<int>& answerElems, vector<long long>& values, vector<long long>& weights, vector<int>& bestRatioIndexesRemaining, long long& capacity, long long& currentWeight, int a, double b)
{
    //Note: removed items are NOT reconsidered, or else there'd be no change
    int carouselCounter{0};
    int startingSize{int(answerElems.size())};
    int numToRemove = int(answerElems.size()) * b; //amount of elements we are removing from the back
    if(numToRemove == 0 && a == 0) return;
    for(int i{int(answerElems.size()) - 1}; i >= startingSize - numToRemove; i--)
    {
        currentWeight -= weights[answerElems[i]];
        answerElems.pop_back(); // we do NOT add these removed elements back
    }

    //Note: a elements removed are removed from the FRONT not the BACK like we did for b
    while(carouselCounter < a) //we assume the user inputs an "a" less than the elements left after "b" (the % of answers removed from the bag)
    {
        currentWeight -= weights[answerElems[0]]; //takes weight from front of answerElems out of our knapsack

        int addBack = answerElems[0]; ///COMMENT OUT!!!! Adds element from answer pool to candidate pool after addOneGreedy finds a new candidate

        answerElems.erase(answerElems.begin()); // once again inefficient, all elements have to be shifted left one
        int count = int(bestRatioIndexesRemaining.size()); //bestRatioIndexesRemaining changes IF we REMOVE the functionality of adding removed elements back to pool
        addOneGreedy(answerElems, bestRatioIndexesRemaining, count, capacity, currentWeight, weights); 
        carouselCounter++;

        bestRatioIndexesRemaining.push_back(addBack); ///COMMENT OUT!!!!
        
        ///This makes it so we consider the candidate we removed from the last while in the next while iteration, VERY INEFFICIENT, but our samples are small
        sort(bestRatioIndexesRemaining.begin(), bestRatioIndexesRemaining.end(), [&values, &weights](int i, int j) 
        {
            return (double(values[i]) / weights[i]) > (double(values[j]) / weights[j]);
        }); 
    }
    //we must re-sort afterwards as greedyKnapsack needs a sorted by value/weight bestRatioIndexesRemaining and carousel ruined the ratio at the back.
    sort(bestRatioIndexesRemaining.begin(), bestRatioIndexesRemaining.end(), [&values, &weights](int i, int j) 
    {
        return (double(values[i]) / weights[i]) > (double(values[j]) / weights[j]);
    }); 
    greedyKnapsack(capacity, currentWeight, weights, bestRatioIndexesRemaining, answerElems); //We do greedy one last time to fill any freed up weight from the b or a removal
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
    std::filesystem::path problems{"C:/Users/Pomer/projects/Research/Jooken_greedy_casousel/problemInstances"}; //Problem instances are provided by JorikJooken github: https://github.com/JorikJooken/knapsackProblemInstances 
    ifstream testFile;  
    vector<long long> values = {};
    vector<long long> weights = {};
    int count;
    long long capacity{-1};

        for(double b{0.1}; b <= 0.5; b += 0.1) //tests removing 10% - 50% of elements
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(problems)) //traverses every "entity" in the given folder
            { 
                
                //add for loop here to change a value, and store the answer in a vector instead
                if(entry.path().filename() == "test.in") //Specifies what file we want to use that we find in any folder
                {
                    //File reading + writing section
                    excel.open("results.csv", ios::app); //opens file again (allows adding results 1 by 1 rather than by bulk) app stands for append (prevents overwriting)
                    testFile.open(entry.path()); //MAKE SURE TO USE .CLEAR BEFORE NEXT FILE
                    //testFile.open("test.in");
                    readFile(testFile, weights, values, count, capacity); //we assume the testFile is formatted properly (starts with count, then all the elements in the problem, and ends with the capacity of the knapsack)    
                    vector<int> bestRatioIndexesRemaining; //index 0 has the highest ratio, last is the worst. Only contains elements NOT in our knapsack
                    for(int i{0}; i < count; i++)
                        bestRatioIndexesRemaining.push_back(i);
                    sort(bestRatioIndexesRemaining.begin(), bestRatioIndexesRemaining.end(), [&values, &weights](int i, int j) 
                    {
                        return (double(values[i]) / weights[i]) > (double(values[j]) / weights[j]);
                    } 
                    );
                //NEW THING LEARNED! Lambda functions, they're inline functions! negative: lambda is not very readable
                vector<int> answerElems; //what is in our knapsack
                long long currentWeight{0};
                int a = 0;
                double b = 0;

                //improvement phase of greedy    
                greedyKnapsack(capacity, currentWeight, weights, bestRatioIndexesRemaining, answerElems); //stage 1 of the algorithm
                improvement(answerElems, values, weights, bestRatioIndexesRemaining, capacity, currentWeight); //Stage 2 - improvement of greedy outcome
                carouselGreedy(answerElems, values, weights, bestRatioIndexesRemaining, capacity, currentWeight, a, b);//Stage 3 - carousel
                improvement(answerElems, values, weights, bestRatioIndexesRemaining, capacity, currentWeight); //stage 4 - improvement again. saw a very minor increase in some cases
                long long profit{0};
                for(int elem : answerElems)
                {
                    profit += values[elem];
                }
                ///////////////// Debugging block (DELETE WHEN DONE!!)
                //long long weightChecker{0};
                 /* for(int elem : answerElems) 
                        weightChecker += weights[elem];
                if(weightChecker != currentWeight)
                {
                    cout << "HOLY THIS IS BAD";
                    exit(0);
                } */

    
            
                //////////////////
                
                cout << profit << '\n';
                //stage 3: Carousel of outcome

                    
                    //Puts results in CSV file
                    excel << entry.path().parent_path().filename() << "," << profit << '\n';
                    excel.close(); //Close here if samples size is too large
                    //Resetting values before the next model   
                    testFile.close(); // to move onto the next model file
                    values.clear();
                    weights.clear();
                }
                excel.close(); //updates the csv file at the end of every model
            }
        }
}



//Greedy still doesn't account for removal of multiple smalls
