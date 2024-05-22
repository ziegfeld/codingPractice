/*
same idea, but using vector for sort is much faster than using std::array
runtime 64ms or so beats 74%~92.67% runtime
memory 21.8MB beats 69%~84%
*/

// #include <unordered_map>
// #include <unordered_set>
#include <algorithm>

// swap means order does not matter. we can use unordered containers.
//  so only need to check alpha bets match first
//  operation 2 means number of occurence just needs to match like 2 a's and 3
//  b's  === 2 b's and 3 a's so get all the 2 3's and sort and make them match.
//  can use set;
using namespace std;
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        const int n1 = word1.length(), n2 = word2.length();
        if (n1 != n2) {
            // cout << "ret1 false\n";
            return false;
        }
        // unordered_map<char, int> alphabet1, alphabet2;
        vector<int> a1(26);
        vector<int> a2(26);

        for (int i = 0; i < n1; i++) {
            a1[word1[i] - 'a']++;
            a2[word2[i] - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            // check alphabet same
            if ((a1[i] == 0 && a2[i] != 0) || (a2[i] == 0 && a1[i] != 0)) {
                // cout << "ret2 false\n";
                return false;
            }
            // save occurences
        }
        sort(a1.begin(), a1.end());
        sort(a2.begin(), a2.end());
        for (int i = 0; i < 26; i++) {
            if (a1[i] != a2[i]) {
                // cout << "ret3 false\n";
                return false;
            }
        }
        return true;
    }
};
