#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
//reads one block of data from MDMKP .txt file (one block = either <=, >= constraints or cost coefficient vals)
/* 
Function name: readAttributeOfMDMKP
Params:
    ifstream& file: The file we want to read from, should be "pointing" to the start of the attribute we want to read 
    vector<vector<long>>& candidateCapacityAtrributes: Where we will store each candidates attribute for each constraint (reminder that there are multiple capacity constraints and demand constraints in each problem)
    bool IsConstraint: if true, will read an additional line that will be the capacity/demand max/min(s) depending on the attribute we are reading. (<= constraint is capacity / max, >= constraint is demand/min)


*/

class MDMKRawProblem // each MDMKRawProblem is actually a set of 6 problems in 1 entity, but processing must be done for that to formm thus the "raw" name
{
    private:
        vector<vector<long>> candidateCapacityAtrributes;
        vector<vector<long>> candidateDemandAtrributes;
        vector<vector<long>> candidateCostAtrributes;
        vector<long> knapsackCapacityVals;
        vector<long> knapsackDemandRequirementVals;
    public:
        vector<vector<long>>& getcandidateCapacityAtrributes() { return candidateCapacityAtrributes; } 
        vector<vector<long>>& getcandidateDemandAtrributes() { return candidateDemandAtrributes; }
        vector<vector<long>>& getcandidateCostAtrributes() { return candidateCostAtrributes; }
        vector<long>& getknapsackCapacityVals() { return knapsackCapacityVals; }
        vector<long>& getknapsackDemandRequirementVals() { return knapsackDemandRequirementVals; }
};

struct MDMKCandidate
{
    vector<long> capacityVal; // How much capacity this candidate takes up for each capacity constraint
    vector<long> demandVal; //How much demand value this candidate contributes
    long value; // "Cost": how much this item is worth (either +/- depending on the case)
};

//Formats MKMDProblem into their 6 respective cases, in accordance to the brunel paper. Here is a definition of each case:
/* 
    Note that "q" is the number of demand constraints (>=) and "m" is the number of capacity (<=) constraints
    These constraints are picked in order as they show up. EX: when q=1, it means only the first demand constraint is considered
    Positive cost/value cases
    Case 1: q = 1
    Case 2: q = m/2
    Case 3: q = m
    Mixed cost/value cases
    Case 4: q = 1
    Case 5: q = m/2
    Case 6: q = m
*/
void separateByCases(MDMKRawProblem& problem) 
{
    vector<vector<long>> MDMKCapacityAttributes = problem.getcandidateCapacityAtrributes(); 
    vector<vector<long>> MDMKDemandAttributes = problem.getcandidateDemandAtrributes();
    long capacityVarsCount = MDMKCapacityAttributes.size(); //Shortcut to finding the amount of capacity variables (dimensions) for the problem
    long candidateCount = MDMKCapacityAttributes[0].size();//This is a way to find the # of candidates we have without having to pass directly (not too efficient, but less params = simpler). Only works if problem is not empty
    int caseDemand1 = 1; //sort of pointless but slightly more readable as it describes what the value 1 is for (Case 1 of MDMKP problems)
    int caseDemand2 = capacityVarsCount / 2;
    int caseDemand3 = capacityVarsCount;
    

    for(int i{0}; i < candidateCount; i++)
    {
        MDMKCandidate candidate;
        for(int c{0}; c < capacityVarsCount; c++)
        {
            candidate.capacityVal.push_back(MDMKCapacityAttributes[c][i]);
        //Think through demand here
        }

        //NEXT GOAL: Impliment demand

    }
}

void readAttributeOfMDMKP(ifstream& file, vector<vector<long>>& candidateCoefficientAtrributes, vector<long>& knapsackGoalVals, long candidateCount, long leConstraints, bool isConstraint)
{
    long placeholder; 
    //leConstraints means <= constraints (also known as capacity constraints)
    for(int m{0}; m < leConstraints; m++) //reading for all candidate constraints
    {
        candidateCoefficientAtrributes.push_back(vector<long>());
        for(int i{0}; i < candidateCount; i++) // reading all <
        {
            file >> placeholder;
            candidateCoefficientAtrributes[m].push_back(placeholder);
        }
    }
    if(isConstraint)
        for(int m{0}; m < leConstraints; m++) //Reads capacity of knapsack for each capacity constraint
        {
            file >> placeholder;
            knapsackGoalVals.push_back(placeholder);
        }
}


//Param of fileName is the file we want to read from, must be in the same folder as this file (though I could easily change this if needed)
void readMDMKP(string fileName, vector<MDMKRawProblem>& MDMKRawProblems) // read MDMKP problem text files in accordance to the format done by https://people.brunel.ac.uk/~mastjjb/jeb/orlib/mdmkpinfo.html
{
    
    ifstream file{fileName};
    long testProblemCount, candidateCount, leConstraints; //leConstraints means <= constraints (also known as capacity constraints)
    
    file >> testProblemCount;

    for(int i{0}; i < testProblemCount; i++) //traverses all the problem sets of the file 
    {
        MDMKRawProblem problemSet; //creates a new empty problem set for every instance
        //cout << file.tellg() << '\n';
        file >> candidateCount >> leConstraints; // These are the "header" variables for the brunel samples, they apply to all cases of a single problem (6 cases)
        vector<vector<long>> candidateCapacityAtrributes; //each vector contains a separate attribute for every candidate 
        vector<long> knapsackCapacityVals;
        readAttributeOfMDMKP(file, problemSet.getcandidateCapacityAtrributes(), problemSet.getknapsackCapacityVals(), candidateCount, leConstraints, true); // reads <= constraint

        vector<vector<long>> candidateDemandAtrributes;
        vector<long> knapsackDemandRequirementVals;
        readAttributeOfMDMKP(file, problemSet.getcandidateDemandAtrributes(), problemSet.getknapsackDemandRequirementVals(), candidateCount, leConstraints, true); // reads >= constraint

        vector<vector<long>> candidateCostAtrributes; //Note that "knapsackCapacityVals" is useless here due to the boolean parameter being = false
        //I repurposed the leconstraints parameter to be the # of cases each model has, which is 6 for Brunel test cases
        readAttributeOfMDMKP(file, problemSet.getcandidateCostAtrributes(), problemSet.getknapsackCapacityVals(), candidateCount, 6, false); // reads value of each object (Though the Brunel paper calls these "Cost" coefficients). 
        
        MDMKRawProblems.push_back(problemSet);
    }
}






int main()
{
    vector<MDMKRawProblem> MDMKRawProblems;
    readMDMKP("data.txt", MDMKRawProblems);
    separateByCases(MDMKRawProblems[0]);
    return 0;
}
/* 

void readAttributeOfMDMKP(ifstream& file, vector<vector<long>>& candidateCoefficientAtrributes, vector<long>& knapsackGoalVals, long candidateCount, long leConstraints, bool isConstraint)
{
    long placeholder; //leConstraints means <= constraints (also known as capacity constraints)

    for(int m{0}; m < leConstraints; m++) //reading for all candidate constraints
    {
        candidateCoefficientAtrributes.push_back(vector<long>());
        for(int i{0}; i < candidateCount; i++) // reading all <
        {
            file >> placeholder;
            candidateCoefficientAtrributes[m].push_back(placeholder);
        }
        
    }
    if(isConstraint)
        for(int m{0}; m < leConstraints; m++) //Reads capacity of knapsack for each capacity constraint
        {
            file >> placeholder;
            knapsackGoalVals.push_back(placeholder);
        }

}


//Param of fileName is the file we want to read from, must be in the same folder as this file (though I could easily change this if needed)
void readMDMKP(string fileName) // read MDMKP problem text files in accordance to the format done by https://people.brunel.ac.uk/~mastjjb/jeb/orlib/mdmkpinfo.html
{
    ifstream file{fileName};
    long testProblemCount, candidateCount, leConstraints; //leConstraints means <= constraints (also known as capacity constraints)
    

    file >> testProblemCount >> candidateCount >> leConstraints; // These are the "header" variables for the brunel samples, they apply to all cases of a single problem (6 cases)
    vector<vector<long>> candidateCapacityAtrributes; //each vector contains a separate attribute for every candidate 
    vector<long> knapsackCapacityVals;
    readAttributeOfMDMKP(file, candidateCapacityAtrributes, knapsackCapacityVals, candidateCount, leConstraints, true); // reads <= constraint

    vector<vector<long>> candidateDemandAtrributes;
    vector<long> knapsackDemandRequirementVals;
    readAttributeOfMDMKP(file, candidateDemandAtrributes, knapsackDemandRequirementVals, candidateCount, leConstraints, true); // reads >= constraint

    vector<vector<long>> candidateCostAtrributes; //Note that "knapsackCapacityVals" is useless here due to the boolean parameter being = false
    //I repurposed the leconstraints parameter to be the # of cases each model has, which is 6 for Brunel test cases
    readAttributeOfMDMKP(file, candidateCostAtrributes, knapsackCapacityVals, candidateCount, 6, false); // reads value of each object (Though the Brunel paper calls these "Cost" coefficients). 
    
    
}

*/
