// question description : https://leetcode.com/problems/longest-uploaded-prefix/description/
// answer solution written: https://leetcode.com/problems/longest-uploaded-prefix/solutions/5348756/segment-tree-binary-search-longest-o-1-time-build-upload-o-logn-time-logest-o-n-space

class LUPrefix {
    vector<int> seg{};
    int n{0};
    void upd(int i, int l, int h, int ind) {
        if (l == h) {
            // assert(i>=0 && i<=4*n + 4);
            seg[i] = 1;
            // cout << "seg[" << i << "] - " << l << " aka " << ind << " -> 1" << endl;
            return;
        }
        int m = (l + h) / 2;
        if (ind <= m) {
            upd(i * 2, l, m, ind);
        } else {
            upd(i * 2 + 1, m + 1, h, ind);
        }
        seg[i] = seg[i * 2] + seg[i * 2 + 1];
        // cout << "seg[" << i << "] - [" << l << "," << h << "] -> " << seg[i] << endl;
    }
    int qpref(int i, int l, int h) {
        if (seg[i] == h - l + 1) {
            return seg[i];
        }
        if (l == h) {
            // cout << "ans pref - seg[" << i << "] - [" << l <<  "," << h << "] = " << seg[i] << endl;
            return seg[i];
        }
        int m = (l + h) / 2;
        int ans = qpref(i * 2, l, m);
        if (ans == m - l + 1) {
            // how to know 1,2,..,n all uploaded? total is n, aka n - 1 + 1;
            ans += qpref(i * 2 + 1, m + 1, h);
        }
        // cout << "ans pref - [" << l << "," << h << "] = " << ans << endl;
        return ans;
    }
    // old native query_prefix: everytime build up from (x,x) lowest level segment leaves.
    // int qpref(int i, int l, int h) {
    //     if (l == h) {
    //         // cout << "ans pref - seg[" << i << "] - [" << l <<  "," << h << "] = " << seg[i] << endl;
    //         return seg[i];
    //     }
    //     int m = (l + h) / 2;
    //     int ans = qpref(i * 2, l, m);
    //     if (ans == m - l + 1) {
    //         // how to know 1,2,..,n all uploaded? total is n, aka n - 1 + 1;
    //         ans += qpref(i * 2 + 1, m + 1, h);
    //     }
    //     // cout << "ans pref - [" << l << "," << h << "] = " << ans << endl;
    //     return ans;
    // }
public:
    LUPrefix(int n) {
        seg.resize(4 * n, 0);
        // upd(0, 0, n-1, 0);
        this->n = n;
    }

    void upload(int video) { 
        assert(n != 0);
        upd(1, 1, n, video); }

    int longest() { 
        assert(n != 0);
        return qpref(1, 1, n); 
    }
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
