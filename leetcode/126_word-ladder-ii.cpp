// word-ladder-ii
// https://leetcode.com/problems/word-ladder-ii/description/
// hard. 
// get cost/adjacency, then DFS with heuristic. recursive but has reuse for reducing stack mem
// passed 31/36 and 32th meeting time limit exceeded.

//next step for optimization:
// sort the wordList or change the order to choose the next word to try in dfs - the one with min dist to beginWord and endWrod should be the first to try
using namespace std;
class Solution {
    int dist(string a, string b, int len) {
        int dis = 0;
        for (int i = 0; i < len; i++) {
            if (a[i] != b[i]) {
                dis++;
            }
        }
        return dis;
    }

    void dfsSeq(int begin, int end, const vector<string>& wordList,
                const vector<vector<int>>& d, vector<int>& seqnowleft, vector<int>& seqnowright,
                vector<bool>& used, vector<pair<vector<int>,vector<int>>>& retidx, int& minseq) {
        //minseq does not include start and end words! (+2 for real length of seq)
        // int minseqret = minseq;
        // find local minimum
        int seqnowlen = seqnowleft.size() + seqnowright.size();
        if (d[begin][end] == 1) { // found!
            if (minseq == seqnowlen) {
                // cout << "found another seq with same min lenth = " << minseq << " : ";
                retidx.push_back({seqnowleft, seqnowright});
                // for (auto wi : retidx.back()) {
                //     cout << wordList[wi] << " ";
                // }
                // cout << endl;
                return;
            } else if (minseq > seqnowlen) {
                // found new shortest seq!
                minseq = seqnowlen;
                // cout << "found new 1st seq with new min lenth = " << minseq << " : ";
                retidx.clear();
                retidx.push_back({seqnowleft, seqnowright});
                // for (auto wi : retidx.back()) {
                //     cout << wordList[wi] << " ";
                // }
                // cout << endl;
                // // auto tmpseqmin = seqnow; //deepcopy
                // // retidx.push_back(tmpseqmin); 
                // retidx.push_back(tmpseqmin); 
                return;
            } else {
                // cout << "found new seq but length > minseq = " << minseq << " : ";
                return;
            }
        }
        const bool leftOrRight = seqnowlen % 2 == 0;
        for (int i = 1; i < wordList.size(); i++) {
            if (used[i] == false) {
                // cout << "current seqnow length = " << seqnowlen << " tring word[" << i << "] " << wordList[i] << " - dists to begin:" << d[begin][i] << " end: " << d[end][i] << endl;
                if (leftOrRight) {
                    if (d[i][begin] == 1 &&
                        d[i][end] + 1 + seqnowlen <= minseq + 1) {
                        used[i] = true;
                        seqnowleft.push_back(i);
                        // cout << "current seqnow length = " << seqnowlen << " try adding left: " << wordList[i] << endl;
                        dfsSeq(i, end, wordList, d, seqnowleft, seqnowright, used, retidx, minseq);
                        seqnowleft.pop_back();
                        used[i] = false;
                        // cout << "current seqnow length = " << seqnowlen  << " done try adding left \n";
                    }
                } else if (d[i][end] == 1 &&
                           d[i][begin] + 1 + seqnowlen <= minseq + 1) {
                    used[i] = true;
                    // cout << "current seqnow length = " << seqnowlen << " try adding to right:" << wordList[i] << endl;
                    // seqnowright.insert(seqnowright.begin(), i);
                    seqnowright.push_back(i);
                    dfsSeq(begin, i, wordList, d, seqnowleft, seqnowright, used, retidx, minseq);
                    // cout << "current seqnow length = " << seqnowlen  << " done try adding right \n";
                    // seqnowright.erase(seqnowright.begin());
                    seqnowright.pop_back();
                    // O(n) might over time limit; use deque instead for seqnowright, or just backward vector and use rbegin() rend() iterator later.
                    used[i] = false;
                }
            }
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord,
                                       vector<string>& wordList) {
        if (beginWord == endWord) {
            const vector<vector<string>> ret = {{beginWord, endWord}};
            return ret;
        }
        unordered_set<string> setWords;
        setWords.insert(beginWord);
        // setWords.insert(endWord); // must not insert endWord
        int i = wordList.size() - 1;
        // remove duplicates;
        while (i != -1) {
            if (setWords.contains(wordList[i])) {
                // cout << "removing dup, loc @" << i << " in wordList - " << wordList[i] << endl;
                wordList.erase(wordList.begin() + i);
            } else {
                setWords.insert(wordList[i]);
            }
            --i;
        }
        if (!setWords.contains(endWord)) {
            return {};
        }
        // cout << "wordList adding begin  words\n";
        wordList.insert(wordList.begin(), beginWord);
        const int numwords = wordList.size();
        int endWI = -1;
        for (int i = 0; i < numwords; i++) {
            if (wordList[i] == endWord) {
                endWI = i;
                break;
            }
        }
        assert(endWI != -1);
        // cout << "wordList added begin  words\n";
        const int wordlen = beginWord.length();
        vector<vector<int>> dists;
        dists.resize(numwords);
        for (int i = 0; i < numwords; i++) {
            dists[i].resize(numwords);
        }
        // cout << "dists resized to " << numwords <<  "\n";
        for (int i = 0; i < numwords - 1; i++) {
            for (int j = i + 1; j < numwords; j++) {
                dists[i][j] = dist(wordList[i], wordList[j], wordlen);
                // cout << "dists[" << i << "][" << j << "] = " << dists[i][j] << endl;
                assert(dists[i][j] > 0);
                dists[j][i] = dists[i][j];
                // cout << "dists[" << j << "][" << i << "] = " << dists[j][i] << endl;
            }
        }
        // cout << "dists calc'd, numwords = " << numwords << endl;
        vector<int> seqnowleft, seqnowright;
        int minseq = numwords +1; 
        // minseq store found shortest sequence length (num words in the seq) -2
        vector<bool> used;
        used.resize(numwords);
        used[0] = true;
        used[endWI] = true;

        vector<pair<vector<int>,vector<int>>> retIdx{};

        dfsSeq(0, endWI, wordList, dists, seqnowleft, seqnowright, used, retIdx, minseq);

        vector<vector<string>> ret{};
        ret.resize(retIdx.size());
        for (int i = 0; i < retIdx.size(); i++) {
            ret[i].push_back(beginWord);
            for (auto j : retIdx[i].first) {
                ret[i].push_back(wordList[j]);
            }
            for (auto j = retIdx[i].second.rbegin(); j != retIdx[i].second.rend(); j++) {
                ret[i].push_back(wordList[*j]);
            }
            ret[i].push_back(endWord);
        }
        return ret;
    }
};

/*
beginWord has d = 0;
find d =1 words;

endWord has d = diff(beginWord,endWord);

search:
how many worlds? 500 at most
10^5 for sum of all shortest.

- opti 1: heuristic: A* use f() d_to_beginWord() + d_to_endWord()

*/
