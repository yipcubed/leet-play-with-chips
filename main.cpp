#include <algorithm>
#include <cstring>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "../utils/VectorUtils.hpp"
#include "../utils/PrintUtils.hpp"
// #include "../utils/HeapUtils.hpp"
// #include "../utils/BinarySearch.hpp"
// #include "../utils/TreeUtils.hpp"

using namespace std;

#pragma GCC diagnostic ignored "-Wunknown-pragmas"

// https://leetcode.com/problems/play-with-chips/

// Live coding problems, watch at
// https://www.twitch.tv/yipcubed
// https://www.youtube.com/channel/UCTV_UOPu7EWXvYWsBFxMsSA/videos
//

// makes code faster, but larger. Just for LeetCode fun!
#pragma GCC optimise ("Ofast")

// makes stdin not synced so it is faster. Just for LeetCode fun!
static auto __ __attribute__((unused)) = []() {              // NOLINT
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  return nullptr;
}();



class Solution {
public:

  // all indexes have same number
  int minCostToMoveChips(vector<int> &chips) {
    int evencost = 0;
    int oddcost = 0;
    for (int i = 0; i < chips.size(); ++i) {
      if (chips[i] % 2 == 0)
        ++oddcost;
      else
        ++evencost;
    }
    return min(oddcost, evencost);
  }

  using ivec = tuple<int, int, vector<int>>;
  int minCostToMoveChips2(vector<int> &chips) {
    int full = 0;
    int csize = chips.size();
    // no moves needed
    for (int i = 0; i < csize; ++i)
      if (chips[i] > 0)
        ++full;
    if (full == 1)
      return 0;
    priority_queue<ivec, vector<ivec>, greater<ivec> > pq;
    int cost = 0;
    pq.push(make_tuple(cost, full, chips));
    int mycost, myfull;
    vector<int> myc2;
    while (!pq.empty()) {
      ivec data = pq.top();
      pq.pop();
      tie(mycost, myfull, myc2) = data;
      PV4("Start:", mycost, myfull, myc2);
      if (myfull == 1)
        return mycost;
      for (int i = 0; i < csize; ++i) {
        if (myc2[i] == 0)
          continue;
        PV2(i, chips[i]);
        if ((i - 1) >= 0 && myc2[i - 1] > 0) {
          // move left
          vector<int> c2(myc2);
          c2[i - 1] += c2[i];
          c2[i] = 0;
          PV4("Addleft:", mycost + 1, myfull - 1, c2);
          pq.push(make_tuple(mycost + 1, myfull - 1, c2));
        }
        if ((i + 1) < csize && myc2[i + 1] > 0) {
          // move right
          vector<int> c2(myc2);
          c2[i + 1] += c2[i];
          c2[i] = 0;
          PV4("Addright:", mycost + 1, myfull - 1, c2);
          pq.push(make_tuple(mycost + 1, myfull - 1, c2));
        }
        if ((i - 2) >= 0 && myc2[i - 2] > 0) {
          // move 2 left
          vector<int> c2(myc2);
          c2[i - 2] += c2[i];
          c2[i] = 0;
          PV4("Addleft2:", mycost, myfull - 1, c2);
          pq.push(make_tuple(mycost, myfull - 1, c2));
        }
        if ((i + 2) < csize && myc2[i + 2] > 0) {
          // move 2 right
          vector<int> c2(myc2);
          c2[i + 2] += c2[i];
          c2[i] = 0;
          PV4("Addright2:", mycost, myfull - 1, c2);
          pq.push(make_tuple(mycost, myfull - 1, c2));
        }
      }
    }
    return 0;
  }
};

void test1() {
  vector<int> v1{1, 2, 3};

  cout << "1 ? " << Solution().minCostToMoveChips(v1) << endl;

  vector<int> v2{2, 2, 2, 3, 3};
  cout << "2 ? " << Solution().minCostToMoveChips(v2) << endl;

  vector<int> v3{1, 2, 2, 2, 2};
  cout << "1 ? " << Solution().minCostToMoveChips(v3) << endl;
}

void test2() {

}

void test3() {

}