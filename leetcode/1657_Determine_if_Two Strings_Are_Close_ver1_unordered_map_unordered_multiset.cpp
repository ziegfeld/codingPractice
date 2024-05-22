////1657. Determine if Two Strings Are Close
//time beats 16.77% 125ms
//mem 23.36MB beats 22.67%

#include <unordered_map>
#include <unordered_set>
using namespace std;
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        const int n1 = word1.length(), n2 = word2.length();
        if (n1 != n2) {
            // cout << "ret1 false\n";
            return false;
        }
        unordered_map<char, int> alphabet1, alphabet2;
        for (auto c : word1) {
            if (alphabet1.find(c) == alphabet1.end()) {
                alphabet1[c] = 1;
            } else {
                alphabet1[c]++;
            }
        }
        for (char c : word2) {
            if (alphabet1.find(c) == alphabet1.end()) {
                // cout << "ret2 false\n";
                return false;
            }
            if (alphabet2.find(c) == alphabet2.end()) {
                alphabet2[c] = 1;
            } else {
                alphabet2[c]++;
            }
        }
        // now reverse check if all char in alphabet2 is in alphabet1
        for (auto c : alphabet2) {
            if (alphabet1.find(c.first) == alphabet1.end()) {
                // cout << "ret3 false\n";
                return false;
            }
        }
        // now all alphabets are correct; we check occurences
        unordered_multiset<int> o1, o2;
        for (auto c : alphabet2) {
            o1.insert(alphabet1.at(c.first));
            o2.insert(c.second);
            // cout << alphabet1.at(c.first) << " ->o1, " << c.second << "
            // ->o2\n";
        }
        for (auto num : o2) {
            const auto it = o1.find(num);
            if (it != o1.end()) {
                o1.erase(it);
                // cout << "num in o2: " << num << " erased count in o1: " <<
                // count << endl;
            } else {
                // cout << "ret4 false\n";
                return false;
            }
        }
        return true;
    }
};

// swap means order does not matter. we can use unordered containers.
//  so only need to check alpha bets match first
//  operation 2 means number of occurence just needs to match like 2 a's and 3
//  b's  === 2 b's and 3 a's so get all the 2 3's and sort and make them match.
//  can use set;


///below version 2:
// 67ms beats 69.13%
// 22MB beats 69.65%
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
        array<int, 26> a1{};
        array<int, 26> a2{};

        for (int i = 0; i < n1; i++) {
            const auto c1 = word1[i], c2 = word2[i];
            a1[c1 - 'a']++;
            a2[c2 - 'a']++;
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
