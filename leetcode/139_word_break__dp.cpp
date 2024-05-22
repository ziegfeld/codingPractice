class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //wordBreakable(s[n]) = wordBreak(s[n-m])+word(of length m); for m.. for n..
        // create map key as legnth of word;
        std::unordered_map<int, std::unordered_set<string>> wordMap{};
        int wordLenMin = 1, wordLenMax = 20;
        for (auto word : wordDict) {
            int len = word.length();
            if (len > wordLenMax) {
                wordLenMax = len;
            } else if (len < wordLenMin) {
                wordLenMin = len;
            }
            if (wordMap[len].contains(word) == false) {
                wordMap[len].insert(word);
                std::cout << len << " length string: " << word << " inserted. \n";
            }
        }
        if (s.length() < wordLenMin) {
            return false;
        }

        //DP
        std::vector<bool> breakable(s.length() + 1, false);
        breakable[0] = true;
        for (int i = wordLenMin; i <= s.length(); ++i) {
            //breakable[1] = true && any substr(0,1) in wordMap[1]
            // brealbe [N] = true && any substr(0,N) in wordMap[N+1]
            // breakble[N] &= breakable[1] && any substr(1,N-1) in wordMap[N-1]
            // then 2 .. N -2
            // 3...
            for (int len = wordLenMin; len <= std::min(i, wordLenMax); ++len) {
                const int start_pos = i - len; //aka prev matched string length
                if (start_pos == 0) {
                    if (wordMap[len].contains(s.substr(start_pos, len))) {
                        breakable[i] = true;
                        std::cout << "breakable[" << len << "] true as word of this exact length found. \n";                        
                        break;
                    }
                } else if (start_pos >=0 && breakable[start_pos]) {
                   if (wordMap[len].contains(s.substr(start_pos, len))) {
                        breakable[i] = true;
                        std::cout << "breakable[" << i << "] true as breakable[" << start_pos << "] true and word of length " << len << " found. \n";             
                        break;
                    }
                }
            }
        }
        return breakable[s.length()];
    }
};
// future improvement: unroll for loop for the part of start_pos==0 and >0 -- each to a loop so total 2 loops.
