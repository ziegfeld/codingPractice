
/// https://leetcode.com/problems/block-placement-queries/

// still wrong answer.. for the record, worked 1.5 hr..

#include <map>
using namespace std;
class Solution {
private:
    void updateMaxSizeBefore(int pos, int prev_pos) {
        // 0, 7, 9, 20 to 0, 2, 7, 9, 20: prev_pos = 2, pos = 7.
        if (pos == max_pos_barrier) {
            // last pos to udpate
            max_size_before[pos] =
                max(max_size_before[prev_pos], pos - prev_pos);
            cout << "last pos - updating max_sz_b4[" << pos << "] to "
                 << max_size_before[pos] << endl;
        } else
            while (pos < max_pos_barrier) {
                int new_max_before_next_barrier =
                    max(max_size_before[pos], d[pos] - pos);
                if (d[pos] - pos == max_size_before[d[pos]]) {
                    break; // no update since d[pos] now.
                }
                max_size_before[d[pos]] = max_size_before[pos];
                cout << "updating max_sz_b4[" << d[pos] << "] to "
                     << max_size_before[d[pos]] << endl;
                pos = d[pos];
                // if pos now == max_pos_barrier, that was last barrier
            }
        assert(pos == max_pos_barrier);
    }
    int max_pos_barrier{0};
    vector<bool> ret;
    map<int, int> d;
    unordered_map<int, int> max_size_before;

public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        // intuition:
        // function max_block_size_possible_before x: f(x,x) = max {f(i) + f(i,
        // x-i) for i < x and if no barrier placed in i} when a barrier placed
        // (query type 1) what is changed?
        // -- recalc
        // d[0] = 15 * 3 * 10000;
        for (auto& query : queries) {
            if (query[0] == 1) {
                // place a block at query[1] aka. x pos.
                int pos = query[1];
                while (pos > 0 && !d.contains(pos)) {
                    --pos;
                }
                auto itl = d.find(pos);

                if (itl != d.end()) {
                    // old barrier just after til.first is itl.second. compare
                    // with new x { 2,7, 7,9} now adding 8 -> {2.7, 7,8 8,9}

                    cout << "placing barrier in " << query[1]
                         << " found lower_bound: " << itl->first
                         << " previous next bar: " << itl->second << endl;
                    if (itl->second < query[1]) { // new last piece
                        assert(max_pos_barrier == itl->second);
                        max_pos_barrier = query[1];
                        d.insert({itl->second, query[1]});
                        max_size_before[query[1]] =
                            max(query[1] - itl->second,
                                max_size_before[itl->second]);
                        cout << "new last piece, updating max_sz_b4["
                             << query[1] << "] to " << max_size_before[query[1]]
                             << endl;
                    } else { // break previous 7,9 to 2 elements 7,8 8,9
                        // itl->first = 7, query[1] = 8, itl->second = 9
                        d.insert({query[1], itl->second});
                        max_size_before[query[1]] = max(
                            max_size_before[itl->first], query[1] - itl->first);
                        const int new_max_before_pos = max(
                            max_size_before[query[1]], itl->second - query[1]);
                        if (max_size_before[query[1]] !=
                            itl->second - query[1]) {
                            max_size_before[query[1]] = new_max_before_pos;
                            cout << "updating max_sz_b4[" << query[1] << "] to "
                                 << max_size_before[query[1]] << endl;
                            updateMaxSizeBefore(itl->second, query[1]);
                        } // else no other max_size_before[] needs to update.
                        itl->second = query[1];
                    }
                } else {
                    cout << "placing barrier in " << query[1]
                         << " not found barrier lower_bound" << endl;
                    if (d.empty()) {
                        d[0] = query[1];
                        max_size_before[query[1]] = query[1];
                        cout << "d[0] to new barrier, so is max_pos_barrier. "
                                "updating max_sz_b4["
                             << query[1] << "] to " << max_size_before[query[1]]
                             << endl;
                        max_pos_barrier = query[1];
                    } else {
                        // 0,7 change to 0,2 2,7
                        d[query[1]] = d[0];
                        d[0] = query[1];
                        // update max_size_before array
                        max_size_before[query[1]] = query[1];
                        cout << "d[0] -> " << d[0] << ", d[" << query[1]
                             << "] -> " << d[query[1]]
                             << "; updating max_sz_b4[" << query[1] << "] to "
                             << max_size_before[query[1]] << endl;
                        // int prev_pos = query[1];
                        int pos = d[query[1]];
                        updateMaxSizeBefore(pos, query[1]);
                    }
                }
            } else { // 2nd type, check block sz
                if (query[1] < query[2]) {
                    cout << "impossible as start_pos " << query[1]
                         << " < size_block" << query[2] << endl;
                    ret.push_back(false);
                } else {
                    int pos = query[1];
                    while (pos > 0 && !d.contains(pos)) {
                        --pos;
                    }

                    if (d[pos] == query[1]) {
                        ret.push_back(max_size_before[query[1]] >= query[2]);
                        cout << "max_size " << max_size_before[query[1]]
                             << ", as this was calc'd for pos " << pos << endl;
                    } else if (!d.contains(pos)) {
                        // no barrier before query[1]
                        if (pos == query[1]) {
                            cout << "lower_bound barrier found is at "
                                 << query[1] << endl;
                        }
                        cout << "no barrier before " << query[1] << endl;
                        ret.push_back(true);
                        // max_size_before[query[1]] = query[1];
                    } else if (pos == 0 && !d.contains(pos)) {
                        ret.push_back(true); // no barrier at all.
                    } else {
                        int max_sz =
                            max(max_size_before[d[pos]], query[1] - d[pos]);
                        cout << "max_size " << max_sz
                             << ", rightest valid pos of d is " << pos << endl;
                        ret.push_back((max_sz >= query[2]));
                    }
                }
            }
        }
        return ret;
    }
};
