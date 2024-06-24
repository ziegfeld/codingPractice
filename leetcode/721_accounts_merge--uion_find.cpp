// https://leetcode.com/problems/accounts-merge/
/*
721. Accounts Merge
Solved
Medium


Hint
Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.
*/
// union find - BingChaJi.
// with naive appoach below, only faster than 8%.
// my solution: https://leetcode.com/problems/accounts-merge/solutions/5359741/c-43ms-33-3mb-union-find-id-to-id-map-merge-then-sort-move-with-comments-and-naive-solution

#include<map>
using namespace std;
class Solution {
    // approach 2: union find
    vector<int> idMap;
    
    int getRoot(int i) {
        if (idMap[i] != i) {
            // update union-find -> point to root directly in this query
            idMap[i] = getRoot(idMap[i]);
        }
        return idMap[i];
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // first find all ids mapping to the same root.
        int n = accounts.size();
        idMap.reserve(n);
        // init idMap i->i each element its own root, and its own set.
        for (int i = 0; i < n; i++) {
            idMap.emplace_back(i);
        }
        unordered_map<string, int> acct2idMp; // map email accounts to id number
        for (int i = 0; i < n; i++) {
            const auto& v = accounts[i];
            for (int j = 1; j < v.size(); ++j) {
                auto it = acct2idMp.find(v[j]);
                if (it != acct2idMp.end()) {
                    // email acct already exists, so union-find owner ids
                    idMap[getRoot(i)] = getRoot(it->second);
                    // can also update acct2idMp here
                    it->second = idMap[getRoot(i)]; // = getRoot(it->second);
                }
                else {
                    acct2idMp[v[j]] = i;
                }
            }
        }

        // build root id -> all owning acct map
        unordered_map<int, vector<string>> id2accts;
        for (const auto& el : acct2idMp) {
            int root = getRoot(el.second);
            id2accts[root].push_back(el.first);
        }

        // then build the ans

        vector<vector<string>> ans {};
        for (auto& el : id2accts) {
            auto& accts = el.second;
            sort(accts.begin(),accts.end());
            accts.insert(accts.begin(), accounts[el.first][0]);
            // ans.push_back(accts);
            ans.push_back(move(accts)); // using move instead of copy constructor here as id2accts not needed.
        }
        return ans;
    }
};
/*
// approach 1: naive merge, without union-find BingChaJi.
    using mp_t = std::multimap<string,set<string>>;
public:
   vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        mp_t mp; // name -> accouts in set
        for (const auto& v: accounts) {
            const auto& name = v[0];
            const int numacct = v.size()-1;
            // a, 0  1 2
            // a 3 4 5
            // a 1 3 9
            if (int n = mp.count(name) != 0) {
                // alredy exists, find if any email acct match
                auto itl = mp.lower_bound(name), itr = mp.upper_bound(name);
                int ndup = 0;
                vector<mp_t::iterator> dups; //dups.reserve(n);
                for (;itl != itr; ++itl) {
                    for (int i = 1; i <= numacct; ++i) {
                        if (itl->second.contains(v[i])) {
                            ndup++;
                            dups.push_back(itl);
                            break;
                        }
                    }
                    // if (dup !=0) {
                    //     // merge all accts to existing user:
                    //     for (int i = 1; i <= numacct; ++i) {
                    //         itl->second.insert(v[i]);
                    //     }
                    //     break;
                    // }
                }
                if (ndup != 0) {
                    auto itkeep = dups[0];
                    // assert(dups[0]->first == v[0]);
                    // merge new accts to existing user:
                    for (int i = 1; i <= numacct; ++i) {
                        itkeep->second.insert(v[i]);
                    }
                    if (ndup > 1) {
                        // merge other dups found in mp to itkeep:
                        for (int i = 1; i < ndup; ++i) {
                            // assert(dups[i]->first == v[0]);
                            const auto& accts = dups[i]->second;
                            for (auto acct : accts) {
                                itkeep->second.insert(acct);
                            }
                            // delete from map
                            mp.erase(dups[i]); // safe? added assert above
                        }
                    }
                    continue; // no new insertion
                }
            }
            // insert new name
            set<string> accts {};
            for (int i = 1; i <= numacct; ++i) {
                accts.insert(v[i]);
            }
            mp.insert({v[0], accts});
        }

        // turn set -> sorted vector
        vector<vector<string>> ans {};
        for (const auto& el : mp) {
            vector<string> accts(el.second.begin(), el.second.end());
            sort(accts.begin(),accts.end());
            accts.insert(accts.begin(), el.first);
            ans.push_back(accts);
        }
        return ans;
    }
};
*/
