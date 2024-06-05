// https://leetcode.com/problems/maximum-building-height/
// 1840. Maximum Building Height 
// hard; 2 loop passes ---  1-n front and n->1 back greedy. 

struct Point {
    int x, y;
    Point() {x = y = 0;}
    Point(const int & _x, const int & _y) {
        x = _x, y = _y;
    }

    bool operator<(const Point & p) {
        return x == p.x?y <= p.y:x<p.x;
    }
};
class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        vector<Point> pts;
        for (auto & r: restrictions) {
            pts.push_back({r[0], r[1]});
        }
        pts.push_back({1, 0});
        ::sort(begin(pts), end(pts));
        if (pts.back().x != n) {
            pts.push_back({n, n-1});
        }

        int sz = pts.size(), hmax = 0;
        for (int i = 0; i < sz-1; ++i) {
            int h = pts[i].y + pts[i+1].x - pts[i].x;
            if (pts[i+1].y > h) {
                pts[i+1].y = h;
            }
        }
        for (int i = sz-2; i>= 0; --i) {
            int h = pts[i+1].y + pts[i+1].x - pts[i].x;
            if (pts[i].y < h) {
                h = (pts[i].y + h)/2;
            }
            hmax = max(h, hmax);
            pts[i].y = min(pts[i].y, h);
        }
        return hmax;
    }
};
/*
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        vector<Point> pts;
        for (auto & r: restrictions) {
            pts.push_back({r[0], r[1]});
        }
        pts.push_back({1, 0});
        ::sort(begin(pts), end(pts));
        if (pts.back().x != n) {
            pts.push_back({n, 1000000000});
        }
        
        int sz = pts.size();
        for (int i = 0; i < sz-1; ++i) {
            int xdiff = pts[i+1].x - pts[i].x;
            if (pts[i+1].y > pts[i].y + xdiff) {
                pts[i+1].y = pts[i].y + xdiff;
            }
        }
        for (int i = sz-2; i>= 0; --i) {
            int xdiff = pts[i+1].x - pts[i].x;
            if (pts[i].y > pts[i+1].y + xdiff) {
                pts[i].y = pts[i+1].y + xdiff;
            }
        }
        int h = 0;
        for (int i = 0; i < sz-1; ++i) {
            h = max(h, max(pts[i].y, pts[i+1].y));
            int x1 = pts[i].x, x2 = pts[i+1].x;
            int y1 = pts[i].y, y2 = pts[i+1].y;
            int twox = x1+x2+y2-y1;
            if (twox >= 2*x1 && twox <= 2*x2) {
                int mid = twox/2;
                int newy = y1 + mid - x1;
                h = max(newy, h);
            }
        }
        return h;
    }
};
*/
/*
public:
    int maxBuilding(int n, vector<vector<int>>& res) {
        // height >=0; hiehg diff = -1, 0 or 1 for adjacent buildings.
        // a sparse indexed restricution for {{id,max_h},...}
        // sort the restricutions, elemate those that's automatically fuflliled ( can be culled)
        //
        sort(res.begin(), res.end());
        int left = 1; 
        long left_h = 0;
        int mh_idx = 1;
        long mh = 0;
        int last_seg_open = true;
        // starting from 0, each next ones are left_h +1, left_h+2.. aka. max of an index i  = (i-left) + left_h;
        for (auto pair : res) {
            if (pair[0] - left + left_h <= pair[1]) {
                cout << "left " << left << " h:" << left_h << "; res.idx " << pair[0] << " res.h:" << pair[1] << " - skip " << endl;
                // this restriction pair doesn't do anything.
                last_seg_open = true;
            } else {
                last_seg_open = false;
                // update prev mh if needed
                if ((pair[1] < mh) && (pair[0] - mh_idx < mh - pair[1])) {
                    // mh = 10 @ 10, but res hi = 5 @ 12; dist.= 2; height_diff = 5.
                    // res -> hi = 5+dis_diff2 = 7 @ (same pos))
                    cout << "mh " << mh << " @" << mh_idx << "; res.idx " << pair[0] << " res.h:" << pair[1] << " - update mh -> " << pair[1] + pair[0] - mh_idx << " @ " << mh_idx << " (same pos)" << endl;
                    mh = pair[1] + (pair[0] - mh_idx);
                }
                //close last seg by calculating max possible and compare with previous mh
                int len = pair[0] - left + abs(left_h - pair[1]);
                long boundary = std::min(left_h, static_cast<long>(pair[1]));
                long max_h_seg = (len /2 ) + boundary;
                if (max_h_seg > mh) {
                    int max_h_pos = pair[0] - (max_h_seg - pair[1]);
                    cout << "left " << left << " h:" << left_h << "; res.idx " << pair[0] << " res.h:" << pair[1] << " - max_this_seg " << max_h_seg << " @ " << max_h_pos << " > old mh " << mh << " @ " << mh_idx << endl;
                    mh = max_h_seg;
                    mh_idx = max_h_pos;
                }
                left = pair[0];
                left_h = pair[1];
            }
        }
        if (last_seg_open) {
            long max_h_seg = n - left + left_h;
            if (max_h_seg > mh) {
                mh = max_h_seg;
            }
        }
        return mh;
// left, lefth; right, righth -- calc the formula for max hight:
// if lefth = righth, then just (right-left)/2 + lefth;
// if lefth > righth, think as lefth expanded left by the diff (lefth-righth); then (right-left-lefth+righth)/2 + righth.
        
    }
};
*/
// 1 2 3 4 5 6 7 8 9
// 0 1 2 
// 0 1 1 0
// 0 1 1 0 1 2 3 4
// 0 1 1 0 1 2 3 4 0
// 0 1 1 0 1 2 2 1 0
