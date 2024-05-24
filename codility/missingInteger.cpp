#include <algorithm>
using namespace std;
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A) {
    // Implement your solution here
    sort(A.begin(), A.end());
    const int n = A.size();
    if (n<=1) {
        return (A[0] == 1) ? 2 : 1;
    }
    //sort;
    // find smallest positive integer
    if (A[n-1] <= 0) return 1;
    int left = 0;
    while (A[left] <= 0) {
        left = (left + n) / 2;
        if (left == n - 1) {
            break;
        }
    }
    // pay attention to corner cases
    if (left == n - 1) {
        return (A[left] == 1) ? 2 : 1;
    }
    int min_pos = 1;
    for (int i = left; i < n; i++) {
        if (A[i] > min_pos + 1) {
            break;
        } else if (A[i] != min_pos) {
            min_pos = A[i]; // or ++
        }
    }
    return min_pos+1;

    
    // start from there, if an integter+1 is not present, print;
    // otherwise print lastest number + 1
}


// above my solution
////
//below from online source
int solution(vector<int> &A) {
    vector<bool> hashTable(A.size()); // holds information about if an integer has been found in the given vector
    

    /*
    * If there's only one element, then there are 2 cases:        
    *
    * Case 1: the element is 1 -> return 2 since that's the next positive integer after one
    * Case 2: the element is not 1 -> return 1 since that's the smallest positive integer
    */
    if(A.size() == 1){
        if(A[0] == 1)
            return 2;
        else
            return 1;
    }
    

    // Loop through the given array and set the corresponding index in the hashTable to true
    for(int i = 0; i < A.size(); i++){
        long long val = A[i]; // use long long int since array elements are large (long long is the same as long long int)
        
        if(val > 0 && val <= A.size())
            hashTable[val - 1] = true;
    }
    
    // Loop through the hashTable and try to find false values, and if there's a false value return its corresponding integer value
    for(int i = 0; i < hashTable.size(); i++){
        bool found = hashTable[i];
        if(!found){
            return i + 1;
        }
    }
    
    return A.size() + 1; // If the method has reached this point that means the missing integer is the integer after the size of the given array
}
