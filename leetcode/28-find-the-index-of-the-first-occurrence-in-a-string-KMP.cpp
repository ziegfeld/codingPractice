#include <vector>

//  28. Find the Index of the First Occurrence in a String
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        const int nh = haystack.length();
        const int nn = needle.length();
        if (nh<nn)
            return -1;

        // longested happy prefix array - next[]
        std::vector<int> a(nn,0);

        // calc a - next[]
        for (int i = 1, j = 0; i < nn; i++) {
            while (j>0 && needle[i] != needle[j]) {
                j = a[j-1];
            }
            if (needle[i]==needle[j]) {
                j++;
            }
            a[i]=j;

        }
        // matching haystack and needle
        for (int i = 0, j = 0; i < nh; i++) {
            while (j>0 && haystack[i] != needle[j]) {
                j = a[j-1];
            }
            if (haystack[i]==needle[j]) {
                j++;
            }
            if (j==nn){
                return i-nn+1;
            }

        }
        return -1;
    }


/* 2 use c++ internal string.find();
        int pos = haystack.find(needle);
        if (pos>=0) 
            return pos;
        else
            return -1;
*/
/* // 1 naive accepted:
    int strStr(string haystack, string needle) {
        const int nh = haystack.length();
        const int nn = needle.length();
        
        for (int i = 0; i < nh-nn+1; i++) {
            bool match = true;
            int j = 0;
            while (match && j < nn) {
                match &= haystack[i+j] == needle[j];
                j++;
            }
            if (match && j == nn) {
                return i;
            }
        }
        return -1;

    }
*/


};
