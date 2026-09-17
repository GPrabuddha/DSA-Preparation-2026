/*
================================================================================
                        ARRAY PATTERNS — ONE-FILE HANDBOOK
================================================================================

HOW TO USE THIS FILE
  PART A  -> pattern-by-pattern notes + solved problems (all tested in main).
  PART B  -> practice problems in a fixed format. Fill in the stubs, run the
             file, and the tracker at the end tells you which ones pass.

  Compile & run:
      g++ -std=c++17 -O2 -Wall array.cpp -o array && ./array

  Every solved problem is written the way you should think in an interview:
      signal -> brute force -> the observation that kills the brute force
      -> pattern -> complexity -> edge cases.

--------------------------------------------------------------------------------
PATTERN RECOGNITION CHEAT SHEET  (read the question, match the signal)
--------------------------------------------------------------------------------
 Signal in the problem                               | Try this pattern
 ----------------------------------------------------|---------------------------
 "sorted array", "pair/triplet with sum X"           | Two pointers (opposite ends)
 "in-place", "remove/move elements", "O(1) space"    | Two pointers (read/write)
 only 0/1/2 (3 categories) to partition              | Dutch National Flag
 order doesn't matter, need closest/adjacent pairs   | Sort first, then scan
 "sum of range" asked many times                     | Prefix sum
 "count subarrays with sum = K" (negatives allowed)  | Prefix sum + hashmap
 "many range updates, one final read"                | Difference array
 "contiguous subarray/window" + all values >= 0      | Sliding window
 "window of size K"                                  | Fixed sliding window
 "exactly K" of something in a window                | atMost(K) - atMost(K-1)
 "have I seen this before?", O(1) lookup             | Hashing (set / map)
 "maximum subarray sum/product"                      | Kadane (DP on "ending here")
 "element appearing > n/2 or > n/3 times"            | Boyer-Moore voting
 values in range [1..n] or [0..n]                    | Index-as-hash / cyclic sort / XOR
 "find duplicate" in [1..n] without modifying        | Floyd cycle (linked-list recall!)
 sorted + "find position/first/last"                 | Binary search (lower/upper bound)
 "minimum X such that ..." / "maximize the minimum"  | Binary search on answer
 sorted but rotated                                  | Modified binary search
 list of [start, end]                                | Sort intervals, then sweep
 "next greater/smaller", "span", "window max"        | Monotonic stack / deque
 grid / 2D matrix traversal or transform             | Matrix boundaries & index tricks
 "next lexicographic arrangement"                    | Next permutation (suffix trick)
 "best from the right/left so far"                   | Running max/min (prefix state)

GENERAL CHECKLIST BEFORE CODING
  1. Constraints: n <= 1e5 means O(n log n) or better. Sums may need long long.
  2. Are there negatives? (kills sliding window on sums, kills some greedy ideas)
  3. Is it sorted? Can I sort? (does the answer depend on original indices?)
  4. Edge cases: empty, size 1, all equal, all negative, duplicates, INT_MIN/MAX.
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// TEST HELPERS  (no need to touch)
// ============================================================================
string to_str(int x) { return to_string(x); }
string to_str(long long x) { return to_string(x); }
string to_str(bool x) { return x ? "true" : "false"; }
string to_str(const string& s) { return "\"" + s + "\""; }
template <class T>
string to_str(const vector<T>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) s += (i ? "," : "") + to_str(v[i]);
    return s + "]";
}

int total_pass = 0, total_fail = 0;
bool quiet = false;  // practice section keeps output short

template <class T>
void check(const string& name, const T& got, const typename common_type<T>::type& expected) {
    if (got == expected) {
        total_pass++;
    } else {
        total_fail++;
        if (!quiet)
            cout << "  FAIL " << name << "\n    got:      " << to_str(got)
                 << "\n    expected: " << to_str(expected) << "\n";
    }
}

/*
################################################################################
#                                                                              #
#                    PART A — PATTERNS + SOLVED PROBLEMS                       #
#                                                                              #
################################################################################
*/

// ============================================================================
// PATTERN 1: SINGLE PASS + RUNNING STATE  (traversal basics)
// ----------------------------------------------------------------------------
// WHEN : Answer depends on "best so far" from one side (max, min, leader).
// HOW  : Walk once, keep 1-2 variables summarizing everything seen.
//        Ask: "what is the minimum info I must remember about the prefix?"
// TRAP : Initialising with 0 instead of INT_MIN / a[0] breaks on negatives.
// ============================================================================

// Second largest DISTINCT element, -1 if none.
// Brute: sort, scan from back -> O(n log n). Better: track top two in one pass.
// Time O(n), Space O(1).
int second_largest(const vector<int>& a) {
    int largest = INT_MIN, second = INT_MIN;
    for (int x : a) {
        if (x > largest) {
            second = largest;
            largest = x;
        } else if (x < largest && x > second) {
            second = x;
        }
    }
    return second == INT_MIN ? -1 : second;
}

// Best Time to Buy and Sell Stock (LC 121). One transaction.
// Brute: every (buy, sell) pair O(n^2).
// Observation: for a sell day, the best buy is the MINIMUM price before it.
// Time O(n), Space O(1).
int max_profit_one_transaction(const vector<int>& prices) {
    int min_price = INT_MAX, profit = 0;
    for (int p : prices) {
        min_price = min(min_price, p);
        profit = max(profit, p - min_price);
    }
    return profit;
}

// Leaders in an array: element strictly greater than everything to its right.
// Same idea mirrored: walk from the RIGHT keeping the running max.
// Time O(n), Space O(1) extra (excluding output).
vector<int> leaders(const vector<int>& a) {
    vector<int> res;
    int right_max = INT_MIN;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        if (a[i] > right_max) {
            res.push_back(a[i]);
            right_max = a[i];
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

// Rotate left by k — REVERSAL TRICK.
// Brute: rotate by 1, k times -> O(n*k). Or copy into temp array -> O(n) space.
// Trick: reverse [0,k), reverse [k,n), reverse all.
//   [1 2 | 3 4 5] -> [2 1 | 5 4 3] -> [3 4 5 1 2]
// Time O(n), Space O(1). Edge: k > n  => k %= n.  (Right rotate: k = n - k.)
void rotate_left(vector<int>& a, int k) {
    int n = a.size();
    if (n == 0) return;
    k %= n;
    reverse(a.begin(), a.begin() + k);
    reverse(a.begin() + k, a.end());
    reverse(a.begin(), a.end());
}

// ============================================================================
// PATTERN 2: TWO POINTERS
// ----------------------------------------------------------------------------
// 2a. OPPOSITE ENDS  (l = 0, r = n-1, move towards each other)
//   WHEN : sorted array + pair condition, palindromes, "container/water".
//   WHY IT WORKS: each move provably discards candidates that can't be better.
//        In a sorted array, if a[l]+a[r] < target, a[l] paired with ANY
//        element <= a[r] is also too small -> l can never be useful -> l++.
//
// 2b. SAME DIRECTION / READ-WRITE  (slow = write index, fast = read index)
//   WHEN : in-place remove / compact / partition while keeping order.
//   INVARIANT: a[0..slow-1] is the "good" part built so far.
//
// 2c. THREE POINTERS — DUTCH NATIONAL FLAG
//   WHEN : partition into 3 groups in one pass.
//   INVARIANT: [0,low) = 0s, [low,mid) = 1s, (high,n-1] = 2s, [mid,high] unknown.
//
// TRAP : 3Sum/4Sum -> skip duplicates AFTER a valid match, on both pointers.
// ============================================================================

// Two Sum II — sorted input (LC 167). Returns 0-based indices or {-1,-1}.
// Brute O(n^2). Hashing O(n) space. Two pointers O(n) time, O(1) space.
vector<int> two_sum_sorted(const vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        long long s = (long long)a[l] + a[r];
        if (s == target) return {l, r};
        if (s < target) l++;
        else r--;
    }
    return {-1, -1};
}

// 3Sum (LC 15): unique triplets summing to 0.
// Brute O(n^3). Sort + fix one element + two-pointer on the rest -> O(n^2).
vector<vector<int>> three_sum(vector<int> a) {
    sort(a.begin(), a.end());
    int n = a.size();
    vector<vector<int>> res;
    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i] == a[i - 1]) continue;  // skip duplicate first element
        int l = i + 1, r = n - 1;
        while (l < r) {
            int s = a[i] + a[l] + a[r];
            if (s < 0) l++;
            else if (s > 0) r--;
            else {
                res.push_back({a[i], a[l], a[r]});
                l++, r--;
                while (l < r && a[l] == a[l - 1]) l++;
                while (l < r && a[r] == a[r + 1]) r--;
            }
        }
    }
    return res;
}

// Container With Most Water (LC 11).
// Observation: area limited by the SHORTER line. Moving the taller one inward
// can only shrink width without raising the limit -> always move the shorter.
// Time O(n), Space O(1).
int max_area(const vector<int>& h) {
    int l = 0, r = (int)h.size() - 1, best = 0;
    while (l < r) {
        best = max(best, min(h[l], h[r]) * (r - l));
        if (h[l] < h[r]) l++;
        else r--;
    }
    return best;
}

// Trapping Rain Water (LC 42).
// Brute: for each i, water = min(maxLeft, maxRight) - h[i] -> O(n^2).
// Better: prefix max + suffix max arrays -> O(n) time, O(n) space.
// Best: two pointers. If h[l] < h[r], the right side has a wall >= h[l], so the
//       water at l is decided by left_max alone.  O(n) time, O(1) space.
long long trap_rain_water(const vector<int>& h) {
    int l = 0, r = (int)h.size() - 1, left_max = 0, right_max = 0;
    long long water = 0;
    while (l < r) {
        if (h[l] < h[r]) {
            left_max = max(left_max, h[l]);
            water += left_max - h[l];
            l++;
        } else {
            right_max = max(right_max, h[r]);
            water += right_max - h[r];
            r--;
        }
    }
    return water;
}

// Remove Duplicates from Sorted Array (LC 26). Returns new length k.
// READ-WRITE pointers: write only when a new value appears.
int remove_duplicates_sorted(vector<int>& a) {
    if (a.empty()) return 0;
    int write = 1;
    for (int read = 1; read < (int)a.size(); read++)
        if (a[read] != a[write - 1]) a[write++] = a[read];
    return write;
}

// Move Zeroes (LC 283): keep order of non-zeros, zeros to the end.
void move_zeroes(vector<int>& a) {
    int write = 0;
    for (int read = 0; read < (int)a.size(); read++)
        if (a[read] != 0) swap(a[write++], a[read]);
}

// Merge Sorted Array (LC 88): nums1 has m elements + n empty slots at the end.
// Trick: fill from the BACK so we never overwrite unread elements.
void merge_sorted(vector<int>& nums1, int m, const vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
}

// Sort Colors / Sort 0-1-2 (LC 75) — Dutch National Flag.
// Brute: counting sort (2 passes). DNF: 1 pass, O(1) space.
// NOTE: after swapping with high, DON'T mid++ (the swapped-in value is unseen).
void sort_012(vector<int>& a) {
    int low = 0, mid = 0, high = (int)a.size() - 1;
    while (mid <= high) {
        if (a[mid] == 0) swap(a[low++], a[mid++]);
        else if (a[mid] == 1) mid++;
        else swap(a[mid], a[high--]);
    }
}

// ============================================================================
// PATTERN 3: SORTING-BASED TECHNIQUES
// ----------------------------------------------------------------------------
// WHEN : Original order doesn't matter, and the answer involves closeness,
//        grouping, pairing, or greedy "take smallest/largest first".
// HOW  : Sort (maybe with a custom comparator), then a linear scan.
//        After sorting, "closest pair" candidates are always ADJACENT.
// COST : O(n log n). If indices matter, sort pairs (value, index).
// TRAP : Comparator must be a strict weak ordering: use <, never <=.
// ============================================================================

// Minimum Absolute Difference (LC 1200): all pairs with the minimum difference.
vector<vector<int>> min_abs_diff_pairs(vector<int> a) {
    sort(a.begin(), a.end());
    int best = INT_MAX;
    for (int i = 1; i < (int)a.size(); i++) best = min(best, a[i] - a[i - 1]);
    vector<vector<int>> res;
    for (int i = 1; i < (int)a.size(); i++)
        if (a[i] - a[i - 1] == best) res.push_back({a[i - 1], a[i]});
    return res;
}

// Sort Array by Increasing Frequency (LC 1636); ties -> decreasing value.
// Shows: hashing + custom comparator.
vector<int> frequency_sort(vector<int> a) {
    unordered_map<int, int> freq;
    for (int x : a) freq[x]++;
    sort(a.begin(), a.end(), [&](int x, int y) {
        if (freq[x] != freq[y]) return freq[x] < freq[y];
        return x > y;
    });
    return a;
}

// ============================================================================
// PATTERN 4: PREFIX SUM  (+ hashmap, + difference array)
// ----------------------------------------------------------------------------
// CORE : pre[i] = a[0] + ... + a[i-1]  (size n+1, pre[0] = 0)
//        sum(l..r) = pre[r+1] - pre[l]                       -> O(1) per query
//
// PREFIX + HASHMAP (the most important trick in this section):
//   subarray (j+1..i) has sum K  <=>  pre_i - pre_j = K  <=>  pre_j = pre_i - K
//   So while walking, ask the map: "how many times have I seen pre_i - K?"
//   Works WITH NEGATIVES (sliding window does not).
//   Store COUNT for "count subarrays", FIRST INDEX for "longest subarray".
//   Seed the map with {0 -> 1} (count) or {0 -> -1} (first index).
//
// VARIANTS: prefix XOR, prefix count (e.g. #odd), replace 0 by -1 for
//           "equal 0s and 1s", sum % k for "divisible by k".
//
// DIFFERENCE ARRAY (reverse of prefix sum):
//   add v to range [l,r]:  diff[l] += v, diff[r+1] -= v; final = prefix(diff)
//
// 2D: pre[i+1][j+1] = a[i][j] + pre[i][j+1] + pre[i+1][j] - pre[i][j]
// ============================================================================

struct RangeSum {
    vector<long long> pre;
    RangeSum(const vector<int>& a) : pre(a.size() + 1, 0) {
        for (size_t i = 0; i < a.size(); i++) pre[i + 1] = pre[i] + a[i];
    }
    long long query(int l, int r) { return pre[r + 1] - pre[l]; }  // inclusive
};

// Subarray Sum Equals K (LC 560) — count.
// Brute O(n^2) over all (l, r). Prefix + hashmap O(n).
int subarray_sum_equals_k(const vector<int>& a, int k) {
    unordered_map<long long, int> seen;
    seen[0] = 1;  // empty prefix: lets a subarray starting at index 0 count
    long long sum = 0;
    int count = 0;
    for (int x : a) {
        sum += x;
        if (seen.count(sum - k)) count += seen[sum - k];
        seen[sum]++;
    }
    return count;
}

// Longest subarray with sum K (negatives allowed).
// Store FIRST occurrence of each prefix sum (earliest start = longest).
int longest_subarray_sum_k(const vector<int>& a, long long k) {
    unordered_map<long long, int> first;
    first[0] = -1;
    long long sum = 0;
    int best = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i];
        if (first.count(sum - k)) best = max(best, i - first[sum - k]);
        if (!first.count(sum)) first[sum] = i;  // never overwrite
    }
    return best;
}

// Product of Array Except Self (LC 238) — prefix product x suffix product.
// No division (handles zeros). Time O(n), Space O(1) extra besides output.
vector<int> product_except_self(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, 1);
    int left = 1;
    for (int i = 0; i < n; i++) res[i] = left, left *= a[i];
    int right = 1;
    for (int i = n - 1; i >= 0; i--) res[i] *= right, right *= a[i];
    return res;
}

// Range updates with a difference array. updates = {l, r, val}.
// Brute: O(n) per update -> O(n*q). Difference array: O(n + q).
vector<int> apply_range_updates(int n, const vector<vector<int>>& updates) {
    vector<int> diff(n + 1, 0);
    for (auto& u : updates) {
        diff[u[0]] += u[2];
        diff[u[1] + 1] -= u[2];
    }
    vector<int> res(n);
    int run = 0;
    for (int i = 0; i < n; i++) run += diff[i], res[i] = run;
    return res;
}

// ============================================================================
// PATTERN 5: SLIDING WINDOW
// ----------------------------------------------------------------------------
// WHEN : contiguous subarray + a condition that is MONOTONIC as the window
//        grows (e.g. sum of NON-NEGATIVE numbers, # distinct, # zeros).
//
// FIXED SIZE k:
//   add a[r]; if (r >= k) remove a[r-k]; if (r >= k-1) record answer.
//
// VARIABLE SIZE (template):
//   for r in 0..n-1:
//       add a[r] to window
//       while (window invalid) remove a[l], l++
//       update answer with window [l..r]        // longest valid
//   For "shortest valid": while (window VALID) { update; shrink; }
//
// COUNTING: number of subarrays ending at r inside a valid window = r - l + 1.
// EXACTLY K  = atMost(K) - atMost(K - 1).
//
// TRAP : negatives in a SUM break monotonicity -> use prefix sum + hashmap.
// COST : O(n): each element enters and leaves the window at most once.
// ============================================================================

// Maximum sum of any window of size k.
long long max_sum_window_k(const vector<int>& a, int k) {
    long long sum = 0, best = LLONG_MIN;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        if (r >= k) sum -= a[r - k];
        if (r >= k - 1) best = max(best, sum);
    }
    return best;
}

// Minimum Size Subarray Sum (LC 209): shortest window with sum >= target.
// Positives only -> shrink while valid.
int min_subarray_len(int target, const vector<int>& a) {
    int l = 0, best = INT_MAX;
    long long sum = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum >= target) {
            best = min(best, r - l + 1);
            sum -= a[l++];
        }
    }
    return best == INT_MAX ? 0 : best;
}

// Longest subarray with at most k distinct values (Fruit Into Baskets, LC 904
// is k = 2). Window state lives in a frequency map.
int longest_at_most_k_distinct(const vector<int>& a, int k) {
    unordered_map<int, int> freq;
    int l = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        freq[a[r]]++;
        while ((int)freq.size() > k) {
            if (--freq[a[l]] == 0) freq.erase(a[l]);
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}

// Binary Subarrays With Sum (LC 930): count subarrays with sum EXACTLY goal.
// "Exactly" isn't monotonic, "at most" is -> exactly(g) = atMost(g) - atMost(g-1).
int count_at_most_sum(const vector<int>& a, int goal) {
    if (goal < 0) return 0;
    int l = 0, sum = 0, count = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > goal) sum -= a[l++];
        count += r - l + 1;  // all subarrays ending at r
    }
    return count;
}
int binary_subarrays_with_sum(const vector<int>& a, int goal) {
    return count_at_most_sum(a, goal) - count_at_most_sum(a, goal - 1);
}

// ============================================================================
// PATTERN 6: HASHING / FREQUENCY
// ----------------------------------------------------------------------------
// WHEN : "have I seen X?", "how many times?", complement lookups (target - x),
//        grouping, or you need O(1) membership instead of a nested loop.
// HOW  : unordered_set for existence, unordered_map for count/index.
//        If values are small (e.g. 0..1e5 or 'a'..'z') use a plain array.
// COST : O(n) average. unordered_map worst case O(n) per op (anti-hash tests)
//        -> map (O(log n)) is the safe fallback.
// TRAP : Two Sum — check the complement BEFORE inserting the current element
//        (otherwise x + x = target matches itself).
// ============================================================================

// Two Sum (LC 1) — unsorted, return indices.
vector<int> two_sum(const vector<int>& a, int target) {
    unordered_map<int, int> index_of;
    for (int i = 0; i < (int)a.size(); i++) {
        auto it = index_of.find(target - a[i]);
        if (it != index_of.end()) return {it->second, i};
        index_of[a[i]] = i;
    }
    return {-1, -1};
}

// Longest Consecutive Sequence (LC 128) in O(n).
// Brute: sort O(n log n). Hash: only START counting from x where x-1 is absent,
// so every sequence is walked exactly once.
int longest_consecutive(const vector<int>& a) {
    unordered_set<int> s(a.begin(), a.end());
    int best = 0;
    for (int x : s) {
        if (s.count(x - 1)) continue;  // not a start
        int len = 1;
        while (s.count(x + len)) len++;
        best = max(best, len);
    }
    return best;
}

// Contiguous Array (LC 525): longest subarray with equal 0s and 1s.
// Map 0 -> -1, then it is "longest subarray with sum 0" (Pattern 4 + 6).
int longest_equal_zeros_ones(const vector<int>& a) {
    unordered_map<int, int> first;
    first[0] = -1;
    int sum = 0, best = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i] == 0 ? -1 : 1;
        if (first.count(sum)) best = max(best, i - first[sum]);
        else first[sum] = i;
    }
    return best;
}

// ============================================================================
// PATTERN 7: KADANE'S ALGORITHM  (DP on "best subarray ENDING at i")
// ----------------------------------------------------------------------------
// WHEN : max/min subarray sum or product, or anything "best contiguous".
// IDEA : cur = best sum of a subarray ending at i
//        cur = max(a[i], cur + a[i])  -> a negative running sum is dead weight.
// VARIANTS:
//   - track start index when you restart, to recover the subarray
//   - product: keep BOTH max and min (a negative flips min into max)
//   - circular: max(normal kadane, total - min subarray) unless all negative
// TRAP : all-negative arrays -> initialise best with a[0], not 0.
// ============================================================================

// Maximum Subarray (LC 53). Returns {sum, start, end}.
vector<long long> max_subarray(const vector<int>& a) {
    long long best = a[0], cur = 0;
    int start = 0, best_start = 0, best_end = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (cur <= 0) cur = a[i], start = i;  // restart here
        else cur += a[i];
        if (cur > best) best = cur, best_start = start, best_end = i;
    }
    return {best, best_start, best_end};
}

// Maximum Product Subarray (LC 152).
long long max_product_subarray(const vector<int>& a) {
    long long mx = a[0], mn = a[0], best = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        long long x = a[i];
        if (x < 0) swap(mx, mn);
        mx = max(x, mx * x);
        mn = min(x, mn * x);
        best = max(best, mx);
    }
    return best;
}

// Maximum Sum Circular Subarray (LC 918).
// Wrapping subarray = total - (the middle part we skip) -> skip the MIN subarray.
int max_circular_subarray(const vector<int>& a) {
    int total = 0, cur_max = 0, cur_min = 0, best_max = a[0], best_min = a[0];
    for (int x : a) {
        total += x;
        cur_max = max(x, cur_max + x), best_max = max(best_max, cur_max);
        cur_min = min(x, cur_min + x), best_min = min(best_min, cur_min);
    }
    if (best_max < 0) return best_max;  // all negative: can't skip everything
    return max(best_max, total - best_min);
}

// ============================================================================
// PATTERN 8: BOYER-MOORE VOTING
// ----------------------------------------------------------------------------
// WHEN : element appearing more than n/2 (1 candidate) or n/3 (2 candidates).
// IDEA : pair off different elements and cancel them. A true majority can't
//        be fully cancelled, so it survives as the candidate.
// TRAP : if a majority is NOT guaranteed, do a second pass to verify counts.
// COST : O(n) time, O(1) space (hashmap solution is O(n) space).
// ============================================================================

int majority_element(const vector<int>& a) {
    int candidate = 0, count = 0;
    for (int x : a) {
        if (count == 0) candidate = x;
        count += (x == candidate) ? 1 : -1;
    }
    return candidate;  // guaranteed to exist in LC 169
}

// Majority Element II (LC 229): all elements appearing > n/3 times (sorted).
vector<int> majority_element_n3(const vector<int>& a) {
    int e1 = 0, e2 = 1, c1 = 0, c2 = 0;
    for (int x : a) {
        if (x == e1) c1++;
        else if (x == e2) c2++;
        else if (c1 == 0) e1 = x, c1 = 1;
        else if (c2 == 0) e2 = x, c2 = 1;
        else c1--, c2--;
    }
    vector<int> res;
    for (int e : {e1, e2})
        if (count(a.begin(), a.end(), e) > (int)a.size() / 3) res.push_back(e);
    sort(res.begin(), res.end());
    return res;
}

// ============================================================================
// PATTERN 9: VALUES IN [0..n] or [1..n]  — index as hash, cyclic sort, XOR, Floyd
// ----------------------------------------------------------------------------
// WHEN : the values themselves can be used as indices.
// TOOLS:
//   - Math / XOR  : missing number = XOR(0..n) ^ XOR(array)   (x ^ x = 0)
//   - Cyclic sort : put value v at index v-1 by swapping; then the first
//                   mismatch is the answer. O(n) — each swap fixes one slot.
//   - Floyd cycle : treat i -> a[i] as a linked list; a duplicate value means
//                   two nodes point to the same node = cycle entry.
//                   (Exactly your linked_list_middle_cycle.cpp logic!)
//   - Negation marking: a[abs(v)-1] *= -1 to mark "v was seen".
// ============================================================================

// Missing Number (LC 268): n distinct numbers from 0..n, one missing.
// Sum formula also works but can overflow; XOR can't.
int missing_number(const vector<int>& a) {
    int n = a.size(), x = n;
    for (int i = 0; i < n; i++) x ^= i ^ a[i];
    return x;
}

// First Missing Positive (LC 41) — cyclic sort. O(n) time, O(1) space.
int first_missing_positive(vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n; i++)
        while (a[i] >= 1 && a[i] <= n && a[a[i] - 1] != a[i]) swap(a[i], a[a[i] - 1]);
    for (int i = 0; i < n; i++)
        if (a[i] != i + 1) return i + 1;
    return n + 1;
}

// Find the Duplicate Number (LC 287): n+1 numbers in [1..n], don't modify array.
// Floyd: phase 1 find meeting point, phase 2 reset slow to start -> cycle entry.
int find_duplicate(const vector<int>& a) {
    int slow = a[0], fast = a[0];
    do {
        slow = a[slow];
        fast = a[a[fast]];
    } while (slow != fast);
    slow = a[0];
    while (slow != fast) {
        slow = a[slow];
        fast = a[fast];
    }
    return slow;
}

// ============================================================================
// PATTERN 10: BINARY SEARCH  (on index, and on the ANSWER)
// ----------------------------------------------------------------------------
// THINK IN TERMS OF A MONOTONIC PREDICATE:  F F F F T T T  -> find first T.
//
//   int lo = 0, hi = n;              // hi = n means "not found" is possible
//   while (lo < hi) {
//       int mid = lo + (hi - lo) / 2;
//       if (pred(mid)) hi = mid;     // mid could be the answer, keep it
//       else lo = mid + 1;
//   }
//   return lo;                       // first index where pred is true
//
// lower_bound(x): first i with a[i] >= x      upper_bound(x): first i with a[i] > x
// first occurrence = lower_bound(x), last occurrence = upper_bound(x) - 1
// count of x = upper_bound(x) - lower_bound(x)
//
// BINARY SEARCH ON ANSWER — signals:
//   "minimum capacity/speed/days such that ...", "maximize the minimum distance",
//   "minimize the largest sum". Answer lies in a range [lo, hi] and
//   feasible(ans) is monotonic. Write feasible() greedily in O(n).
//   Total: O(n log(range)).
//
// TRAPS: mid = lo + (hi-lo)/2 (overflow), infinite loops when using lo = mid
//        (use mid rounding up then), off-by-one on hi = n vs n-1.
// ============================================================================

int lower_bound_idx(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int upper_bound_idx(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// First and Last Position of Element (LC 34).
vector<int> search_range(const vector<int>& a, int target) {
    int first = lower_bound_idx(a, target);
    if (first == (int)a.size() || a[first] != target) return {-1, -1};
    return {first, upper_bound_idx(a, target) - 1};
}

// Koko Eating Bananas (LC 875) — binary search on answer (speed).
// feasible(speed): hours needed <= h. Larger speed -> fewer hours (monotonic).
int min_eating_speed(const vector<int>& piles, int h) {
    auto hours_needed = [&](int speed) {
        long long hours = 0;
        for (int p : piles) hours += (p + speed - 1) / speed;  // ceil
        return hours;
    };
    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (hours_needed(mid) <= h) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// Split Array Largest Sum (LC 410) == Book Allocation == Painter's Partition.
// Answer range: [max element, total sum]. feasible(cap): greedy parts <= k.
long long split_array_largest_sum(const vector<int>& a, int k) {
    auto parts_needed = [&](long long cap) {
        int parts = 1;
        long long cur = 0;
        for (int x : a) {
            if (cur + x > cap) parts++, cur = x;
            else cur += x;
        }
        return parts;
    };
    long long lo = *max_element(a.begin(), a.end());
    long long hi = accumulate(a.begin(), a.end(), 0LL);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (parts_needed(mid) <= k) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// ============================================================================
// PATTERN 11: ROTATED SORTED ARRAY
// ----------------------------------------------------------------------------
// KEY FACT: at any mid, AT LEAST ONE half [lo..mid] or [mid..hi] is sorted.
//   if a[lo] <= a[mid] -> left half sorted: is target inside [a[lo], a[mid])?
//   else               -> right half sorted: is target inside (a[mid], a[hi]]?
// Find minimum: compare a[mid] with a[hi]  (a[mid] > a[hi] -> min is right).
// With DUPLICATES: when a[lo] == a[mid] == a[hi] you can't decide -> lo++, hi--
//   (worst case O(n)).
// ============================================================================

// Search in Rotated Sorted Array (LC 33), distinct values.
int search_rotated(const vector<int>& a, int target) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[lo] <= a[mid]) {  // left half sorted
            if (a[lo] <= target && target < a[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {                // right half sorted
            if (a[mid] < target && target <= a[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}

// Find Minimum in Rotated Sorted Array (LC 153).
int find_min_rotated(const vector<int>& a) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > a[hi]) lo = mid + 1;  // min is strictly right of mid
        else hi = mid;                     // mid could be the min
    }
    return a[lo];
}

// ============================================================================
// PATTERN 12: INTERVALS
// ----------------------------------------------------------------------------
// WHEN : input is [start, end] pairs: meetings, merge, overlap, rooms.
// HOW  : SORT first. Which key?
//   - merge / insert       -> sort by START, compare with last merged end
//   - max non-overlapping  -> sort by END, greedily keep earliest finishing
//   - rooms / platforms    -> sort starts and ends SEPARATELY, sweep
//                             (+1 on start, -1 on end)
// OVERLAP of [a,b] and [c,d]  <=>  max(a,c) <= min(b,d)
// TRAP : decide whether touching intervals ([1,2] & [2,3]) count as overlap.
// ============================================================================

// Merge Intervals (LC 56).
vector<vector<int>> merge_intervals(vector<vector<int>> iv) {
    sort(iv.begin(), iv.end());
    vector<vector<int>> res;
    for (auto& cur : iv) {
        if (res.empty() || res.back()[1] < cur[0]) res.push_back(cur);
        else res.back()[1] = max(res.back()[1], cur[1]);
    }
    return res;
}

// Insert Interval (LC 57): input already sorted & non-overlapping. O(n).
// Three phases: before (end < new start), overlapping (absorb), after.
vector<vector<int>> insert_interval(const vector<vector<int>>& iv, vector<int> ni) {
    vector<vector<int>> res;
    int i = 0, n = iv.size();
    while (i < n && iv[i][1] < ni[0]) res.push_back(iv[i++]);
    while (i < n && iv[i][0] <= ni[1]) {
        ni[0] = min(ni[0], iv[i][0]);
        ni[1] = max(ni[1], iv[i][1]);
        i++;
    }
    res.push_back(ni);
    while (i < n) res.push_back(iv[i++]);
    return res;
}

// Non-overlapping Intervals (LC 435): min removals so the rest don't overlap.
// Greedy: keep the interval that ENDS earliest -> leaves most room for others.
int erase_overlap_intervals(vector<vector<int>> iv) {
    sort(iv.begin(), iv.end(), [](const vector<int>& x, const vector<int>& y) {
        return x[1] < y[1];
    });
    int removed = 0;
    long long last_end = LLONG_MIN;
    for (auto& cur : iv) {
        if (cur[0] >= last_end) last_end = cur[1];
        else removed++;
    }
    return removed;
}

// Minimum Platforms (GFG) / Meeting Rooms II.
// Sweep: at any time, rooms in use = starts so far - ends so far.
int min_platforms(vector<int> arr, vector<int> dep) {
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());
    int n = arr.size(), i = 0, j = 0, cur = 0, best = 0;
    while (i < n) {
        if (arr[i] <= dep[j]) cur++, i++;  // <= : same-time arrival needs a platform
        else cur--, j++;
        best = max(best, cur);
    }
    return best;
}

// ============================================================================
// PATTERN 13: MONOTONIC STACK / DEQUE
// ----------------------------------------------------------------------------
// WHEN : "next/previous greater/smaller element", stock span, histogram,
//        daily temperatures, sliding window max/min.
// IDEA : keep the stack sorted. When a new element arrives, pop everything it
//        "beats" — those popped elements can never be the answer for anyone
//        to the left again. Each element pushed & popped once -> O(n).
//
//   next greater (walk right -> left):
//       while (!st.empty() && st.top() <= a[i]) st.pop();
//       ans[i] = st.empty() ? -1 : st.top();
//       st.push(a[i]);
//
// DEQUE for sliding window max: store INDICES, front = max of current window,
//   pop front if out of window, pop back while a[back] <= a[i].
// ============================================================================

vector<int> next_greater_element(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= a[i]) st.pop();
        res[i] = st.empty() ? -1 : st.top();
        st.push(a[i]);
    }
    return res;
}

// Sliding Window Maximum (LC 239). Brute O(n*k), heap O(n log n), deque O(n).
vector<int> sliding_window_max(const vector<int>& a, int k) {
    deque<int> dq;  // indices, values decreasing from front to back
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

// ============================================================================
// PATTERN 14: MATRIX / 2D ARRAYS
// ----------------------------------------------------------------------------
// TOOLS:
//   - Boundaries (top, bottom, left, right) for spiral / layer traversal
//   - Transpose + reverse rows = rotate 90 clockwise
//     (reverse rows first + transpose = rotate 90 anticlockwise)
//   - Marker rows/cols (or first row/col as markers for O(1) space)
//   - Staircase search from top-right when rows AND cols are sorted: O(m+n)
//   - Fully sorted matrix (row-wise continuing) -> treat as 1D: idx/cols, idx%cols
//   - Directions arrays: dr = {-1,0,1,0}, dc = {0,1,0,-1} for grid neighbours
// TRAP : m (rows) vs n (cols) mix-ups on non-square matrices.
// ============================================================================

// Rotate Image (LC 48) in place.
void rotate_90_clockwise(vector<vector<int>>& mat) {
    int n = mat.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) swap(mat[i][j], mat[j][i]);
    for (auto& row : mat) reverse(row.begin(), row.end());
}

// Spiral Matrix (LC 54).
vector<int> spiral_order(const vector<vector<int>>& mat) {
    vector<int> res;
    if (mat.empty()) return res;
    int top = 0, bottom = mat.size() - 1, left = 0, right = mat[0].size() - 1;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) res.push_back(mat[top][j]);
        top++;
        for (int i = top; i <= bottom; i++) res.push_back(mat[i][right]);
        right--;
        if (top <= bottom) {  // guards: single remaining row
            for (int j = right; j >= left; j--) res.push_back(mat[bottom][j]);
            bottom--;
        }
        if (left <= right) {  // guards: single remaining column
            for (int i = bottom; i >= top; i--) res.push_back(mat[i][left]);
            left++;
        }
    }
    return res;
}

// Set Matrix Zeroes (LC 73). O(m+n) space with marker arrays.
// Follow-up (O(1) space): use row 0 / col 0 as markers + one flag for col 0.
void set_matrix_zeroes(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<bool> zero_row(m, false), zero_col(n, false);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j] == 0) zero_row[i] = zero_col[j] = true;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (zero_row[i] || zero_col[j]) mat[i][j] = 0;
}

// Search a 2D Matrix II (LC 240): rows and columns sorted. Staircase O(m+n).
// From top-right: go left if too big (column below is bigger), down if too small.
bool search_matrix_sorted(const vector<vector<int>>& mat, int target) {
    int i = 0, j = (int)mat[0].size() - 1;
    while (i < (int)mat.size() && j >= 0) {
        if (mat[i][j] == target) return true;
        if (mat[i][j] > target) j--;
        else i++;
    }
    return false;
}

// ============================================================================
// PATTERN 15: PERMUTATION / SUFFIX TRICK
// ----------------------------------------------------------------------------
// Next Permutation (LC 31):
//   1. from the right, find first i with a[i] < a[i+1]  (the "break point")
//   2. if found, swap a[i] with the smallest element > a[i] in the suffix
//      (scan from right: first a[j] > a[i])
//   3. reverse the suffix a[i+1..]  (it was decreasing -> make it smallest)
//   If no break point: array is the last permutation -> reverse whole array.
// ============================================================================

void next_permutation_manual(vector<int>& a) {
    int n = a.size(), i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--;
    if (i >= 0) {
        int j = n - 1;
        while (a[j] <= a[i]) j--;
        swap(a[i], a[j]);
    }
    reverse(a.begin() + i + 1, a.end());
}

// ============================================================================
// TESTS FOR PART A
// ============================================================================
void test_solved() {
    // Pattern 1
    check("second_largest", second_largest({12, 35, 1, 10, 34, 1}), 34);
    check("second_largest all equal", second_largest({7, 7, 7}), -1);
    check("stock", max_profit_one_transaction({7, 1, 5, 3, 6, 4}), 5);
    check("stock falling", max_profit_one_transaction({7, 6, 4, 3, 1}), 0);
    check("leaders", leaders({16, 17, 4, 3, 5, 2}), {17, 5, 2});
    {
        vector<int> a = {1, 2, 3, 4, 5};
        rotate_left(a, 7);  // 7 % 5 = 2
        check("rotate_left", a, {3, 4, 5, 1, 2});
    }

    // Pattern 2
    check("two_sum_sorted", two_sum_sorted({2, 7, 11, 15}, 9), {0, 1});
    check("three_sum", three_sum({-1, 0, 1, 2, -1, -4}), {{-1, -1, 2}, {-1, 0, 1}});
    check("three_sum zeros", three_sum({0, 0, 0, 0}), {{0, 0, 0}});
    check("max_area", max_area({1, 8, 6, 2, 5, 4, 8, 3, 7}), 49);
    check("trap", trap_rain_water({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}), 6LL);
    {
        vector<int> a = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
        int k = remove_duplicates_sorted(a);
        check("remove_duplicates k", k, 5);
        check("remove_duplicates arr", vector<int>(a.begin(), a.begin() + k), {0, 1, 2, 3, 4});
    }
    {
        vector<int> a = {0, 1, 0, 3, 12};
        move_zeroes(a);
        check("move_zeroes", a, {1, 3, 12, 0, 0});
    }
    {
        vector<int> a = {1, 2, 3, 0, 0, 0};
        merge_sorted(a, 3, {2, 5, 6}, 3);
        check("merge_sorted", a, {1, 2, 2, 3, 5, 6});
    }
    {
        vector<int> a = {2, 0, 2, 1, 1, 0};
        sort_012(a);
        check("sort_012", a, {0, 0, 1, 1, 2, 2});
    }

    // Pattern 3
    check("min_abs_diff_pairs", min_abs_diff_pairs({4, 2, 1, 3}), {{1, 2}, {2, 3}, {3, 4}});
    check("frequency_sort", frequency_sort({1, 1, 2, 2, 2, 3}), {3, 1, 1, 2, 2, 2});

    // Pattern 4
    {
        RangeSum rs({-2, 1, 3, -1, 2});
        check("range_sum [1,3]", rs.query(1, 3), 3LL);
        check("range_sum [0,4]", rs.query(0, 4), 3LL);
    }
    check("subarray_sum_k", subarray_sum_equals_k({1, 1, 1}, 2), 2);
    check("subarray_sum_k neg", subarray_sum_equals_k({1, -1, 0}, 0), 3);
    check("longest_sum_k", longest_subarray_sum_k({1, -1, 5, -2, 3}, 3), 4);
    check("product_except_self", product_except_self({1, 2, 3, 4}), {24, 12, 8, 6});
    check("diff_array", apply_range_updates(5, {{1, 3, 2}, {2, 4, 3}, {0, 2, -1}}), {-1, 1, 4, 5, 3});

    // Pattern 5
    check("max_sum_window_k", max_sum_window_k({2, 1, 5, 1, 3, 2}, 3), 9LL);
    check("min_subarray_len", min_subarray_len(7, {2, 3, 1, 2, 4, 3}), 2);
    check("min_subarray_len none", min_subarray_len(100, {1, 2, 3}), 0);
    check("at_most_k_distinct", longest_at_most_k_distinct({1, 2, 3, 2, 2}, 2), 4);
    check("binary_subarrays_sum", binary_subarrays_with_sum({1, 0, 1, 0, 1}, 2), 4);

    // Pattern 6
    check("two_sum", two_sum({3, 2, 4}, 6), {1, 2});
    check("longest_consecutive", longest_consecutive({100, 4, 200, 1, 3, 2}), 4);
    check("equal_zeros_ones", longest_equal_zeros_ones({0, 1, 1, 0, 1, 1, 1, 0}), 4);

    // Pattern 7
    check("kadane", max_subarray({-2, 1, -3, 4, -1, 2, 1, -5, 4}), {6, 3, 6});
    check("kadane all negative", max_subarray({-3, -1, -2}), {-1, 1, 1});
    check("max_product", max_product_subarray({2, 3, -2, 4}), 6LL);
    check("max_product zero", max_product_subarray({-2, 0, -1}), 0LL);
    check("circular", max_circular_subarray({5, -3, 5}), 10);
    check("circular all neg", max_circular_subarray({-3, -2, -3}), -2);

    // Pattern 8
    check("majority", majority_element({2, 2, 1, 1, 1, 2, 2}), 2);
    check("majority n/3", majority_element_n3({1, 1, 1, 3, 3, 2, 2, 2}), {1, 2});

    // Pattern 9
    check("missing_number", missing_number({9, 6, 4, 2, 3, 5, 7, 0, 1}), 8);
    check("first_missing_positive", first_missing_positive({3, 4, -1, 1}), 2);
    check("first_missing_positive 2", first_missing_positive({7, 8, 9, 11, 12}), 1);
    check("find_duplicate", find_duplicate({3, 1, 3, 4, 2}), 3);

    // Pattern 10
    check("lower_bound", lower_bound_idx({1, 2, 2, 2, 5}, 3), 4);
    check("search_range", search_range({5, 7, 7, 8, 8, 10}, 8), {3, 4});
    check("search_range missing", search_range({5, 7, 7, 8, 8, 10}, 6), {-1, -1});
    check("koko", min_eating_speed({30, 11, 23, 4, 20}, 6), 23);
    check("split_array", split_array_largest_sum({7, 2, 5, 10, 8}, 2), 18LL);

    // Pattern 11
    check("search_rotated", search_rotated({4, 5, 6, 7, 0, 1, 2}, 0), 4);
    check("search_rotated missing", search_rotated({4, 5, 6, 7, 0, 1, 2}, 3), -1);
    check("find_min_rotated", find_min_rotated({3, 4, 5, 1, 2}), 1);
    check("find_min not rotated", find_min_rotated({11, 13, 15, 17}), 11);

    // Pattern 12
    check("merge_intervals", merge_intervals({{1, 3}, {8, 10}, {2, 6}, {15, 18}}),
          {{1, 6}, {8, 10}, {15, 18}});
    check("insert_interval", insert_interval({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}),
          {{1, 2}, {3, 10}, {12, 16}});
    check("erase_overlap", erase_overlap_intervals({{1, 2}, {2, 3}, {3, 4}, {1, 3}}), 1);
    check("min_platforms",
          min_platforms({900, 940, 950, 1100, 1500, 1800}, {910, 1200, 1120, 1130, 1900, 2000}), 3);

    // Pattern 13
    check("next_greater", next_greater_element({13, 7, 6, 12}), {-1, 12, 12, -1});
    check("sliding_window_max", sliding_window_max({1, 3, -1, -3, 5, 3, 6, 7}, 3), {3, 3, 5, 5, 6, 7});

    // Pattern 14
    {
        vector<vector<int>> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        rotate_90_clockwise(m);
        check("rotate_90", m, {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}});
    }
    check("spiral", spiral_order({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}),
          {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7});
    {
        vector<vector<int>> m = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
        set_matrix_zeroes(m);
        check("set_zeroes", m, {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}});
    }
    check("staircase found", search_matrix_sorted({{1, 4, 7, 11}, {2, 5, 8, 12}, {3, 6, 9, 16}}, 5), true);
    check("staircase missing", search_matrix_sorted({{1, 4, 7, 11}, {2, 5, 8, 12}, {3, 6, 9, 16}}, 13), false);

    // Pattern 15
    {
        vector<int> a = {1, 3, 2};
        next_permutation_manual(a);
        check("next_perm", a, {2, 1, 3});
        vector<int> b = {3, 2, 1};
        next_permutation_manual(b);
        check("next_perm last", b, {1, 2, 3});
    }
}

/*
################################################################################
#                                                                              #
#                   PART B — PRACTICE PROBLEMS (FILL THESE IN)                 #
#                                                                              #
################################################################################

WORKFLOW FOR EACH PROBLEM
  1. Read the problem + examples. Do NOT look at the pattern hint yet.
  2. Fill "Pattern guess", "Brute force", "Optimization" in the comment
     BEFORE writing code.
  3. Only then read the hint line (if stuck for > 20-25 min).
  4. Implement the function, run the file, check the tracker.
  5. Fill "Mistakes" honestly. If you needed the hint -> add to REVISIT LOG.

COPY-PASTE TEMPLATE FOR A NEW PROBLEM
--------------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// PXX. <Problem name>  (<LC number / GFG / source>)   Difficulty: E/M/H
// ----------------------------------------------------------------------------
// Problem  : <one or two lines>
// Example  : <input> -> <output>
// Hint     : <pattern name, keep it vague>
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO | SOLVED | SOLVED WITH HINT | REVISIT
// ----------------------------------------------------------------------------
<return type> pxx_function_name(<params>) {
    // your code
    return {};
}
void test_pxx() {
    check("pxx ex1", pxx_function_name(<input>), <expected>);
    check("pxx ex2", pxx_function_name(<input>), <expected>);
}
// then add {"PXX name", test_pxx} to the practice list in main()
--------------------------------------------------------------------------------
*/

// ----------------------------------------------------------------------------
// P01. Squares of a Sorted Array  (LC 977)   Difficulty: E
// ----------------------------------------------------------------------------
// Problem  : sorted array (may contain negatives) -> sorted squares, O(n).
// Example  : [-4,-1,0,3,10] -> [0,1,9,16,100]
// Hint     : the largest square is always at one of the two ends.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
vector<int> p01_sorted_squares(const vector<int>& a) {
    // your code
    return {};
}
void test_p01() {
    check("p01 ex1", p01_sorted_squares({-4, -1, 0, 3, 10}), {0, 1, 9, 16, 100});
    check("p01 ex2", p01_sorted_squares({-7, -3, 2, 3, 11}), {4, 9, 9, 49, 121});
}

// ----------------------------------------------------------------------------
// P02. Rearrange Array Elements by Sign  (LC 2149)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : equal #positives and #negatives. Output alternates +,-,+,-...
//            starting with positive, preserving relative order of each sign.
// Example  : [3,1,-2,-5,2,-4] -> [3,-2,1,-5,2,-4]
// Hint     : two write pointers into the result (even / odd indices).
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
vector<int> p02_rearrange_by_sign(const vector<int>& a) {
    // your code
    return {};
}
void test_p02() {
    check("p02 ex1", p02_rearrange_by_sign({3, 1, -2, -5, 2, -4}), {3, -2, 1, -5, 2, -4});
    check("p02 ex2", p02_rearrange_by_sign({-1, 1}), {1, -1});
}

// ----------------------------------------------------------------------------
// P03. 4Sum  (LC 18)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : unique quadruplets with sum == target. Return them sorted
//            (each quadruplet ascending, list in lexicographic order).
// Example  : [1,0,-1,0,-2,2], target 0 -> [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
// Hint     : 3Sum with one more loop. Watch the sum overflow.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
vector<vector<int>> p03_four_sum(vector<int> a, int target) {
    // your code
    return {};
}
void test_p03() {
    check("p03 ex1", p03_four_sum({1, 0, -1, 0, -2, 2}, 0), {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}});
    check("p03 ex2", p03_four_sum({2, 2, 2, 2, 2}, 8), {{2, 2, 2, 2}});
    check("p03 overflow",
          p03_four_sum({1000000000, 1000000000, 1000000000, 1000000000}, -294967296),
          vector<vector<int>>{});
}

// ----------------------------------------------------------------------------
// P04. Find Pivot Index  (LC 724)   Difficulty: E
// ----------------------------------------------------------------------------
// Problem  : leftmost index where sum(left of i) == sum(right of i), else -1.
// Example  : [1,7,3,6,5,6] -> 3
// Hint     : right sum = total - left sum - a[i].
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p04_pivot_index(const vector<int>& a) {
    // your code
    return -2;
}
void test_p04() {
    check("p04 ex1", p04_pivot_index({1, 7, 3, 6, 5, 6}), 3);
    check("p04 ex2", p04_pivot_index({1, 2, 3}), -1);
    check("p04 ex3", p04_pivot_index({2, 1, -1}), 0);
}

// ----------------------------------------------------------------------------
// P05. Count Subarrays with XOR = K  (Striver / InterviewBit)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : number of subarrays whose XOR equals k.
// Example  : [4,2,2,6,4], k = 6 -> 4
// Hint     : same as subarray sum = k, but with XOR (x ^ k ^ k = x).
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p05_subarrays_xor_k(const vector<int>& a, int k) {
    // your code
    return -1;
}
void test_p05() {
    check("p05 ex1", p05_subarrays_xor_k({4, 2, 2, 6, 4}, 6), 4);
    check("p05 ex2", p05_subarrays_xor_k({5, 6, 7, 8, 9}, 5), 2);
}

// ----------------------------------------------------------------------------
// P06. Subarray Sums Divisible by K  (LC 974)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : count non-empty subarrays whose sum is divisible by k.
// Example  : [4,5,0,-2,-3,1], k = 5 -> 7
// Hint     : two prefixes with the same remainder. C++ % can be negative!
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p06_subarrays_div_by_k(const vector<int>& a, int k) {
    // your code
    return -1;
}
void test_p06() {
    check("p06 ex1", p06_subarrays_div_by_k({4, 5, 0, -2, -3, 1}, 5), 7);
    check("p06 ex2", p06_subarrays_div_by_k({5}, 9), 0);
}

// ----------------------------------------------------------------------------
// P07. Max Consecutive Ones III  (LC 1004)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : binary array, flip at most k zeros -> longest run of 1s.
// Example  : [1,1,1,0,0,0,1,1,1,1,0], k = 2 -> 6
// Hint     : rephrase as "longest window with at most k zeros".
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p07_longest_ones(const vector<int>& a, int k) {
    // your code
    return -1;
}
void test_p07() {
    check("p07 ex1", p07_longest_ones({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2), 6);
    check("p07 ex2", p07_longest_ones({0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 3), 10);
}

// ----------------------------------------------------------------------------
// P08. Maximum Points You Can Obtain from Cards  (LC 1423)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : take exactly k cards, each from the start or end. Max total.
// Example  : [1,2,3,4,5,6,1], k = 3 -> 12
// Hint     : what you DON'T take is a contiguous window of size n-k.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p08_max_card_score(const vector<int>& cards, int k) {
    // your code
    return -1;
}
void test_p08() {
    check("p08 ex1", p08_max_card_score({1, 2, 3, 4, 5, 6, 1}, 3), 12);
    check("p08 ex2", p08_max_card_score({9, 7, 7, 9, 7, 7, 9}, 7), 55);
    check("p08 ex3", p08_max_card_score({1, 1000, 1}, 1), 1);
}

// ----------------------------------------------------------------------------
// P09. Count Number of Nice Subarrays  (LC 1248)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : count subarrays with exactly k odd numbers.
// Example  : [1,1,2,1,1], k = 3 -> 2
// Hint     : odd -> 1, even -> 0, then you've already solved this in Part A.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p09_nice_subarrays(const vector<int>& a, int k) {
    // your code
    return -1;
}
void test_p09() {
    check("p09 ex1", p09_nice_subarrays({1, 1, 2, 1, 1}, 3), 2);
    check("p09 ex2", p09_nice_subarrays({2, 4, 6}, 1), 0);
    check("p09 ex3", p09_nice_subarrays({2, 2, 2, 1, 2, 2, 1, 2, 2, 2}, 2), 16);
}

// ----------------------------------------------------------------------------
// P10. Best Time to Buy and Sell Stock II  (LC 122)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : unlimited transactions (hold at most one share). Max profit.
// Example  : [7,1,5,3,6,4] -> 7
// Hint     : a long rise = sum of its daily rises.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p10_max_profit_unlimited(const vector<int>& prices) {
    // your code
    return -1;
}
void test_p10() {
    check("p10 ex1", p10_max_profit_unlimited({7, 1, 5, 3, 6, 4}), 7);
    check("p10 ex2", p10_max_profit_unlimited({1, 2, 3, 4, 5}), 4);
    check("p10 ex3", p10_max_profit_unlimited({7, 6, 4, 3, 1}), 0);
}

// ----------------------------------------------------------------------------
// P11. Single Element in a Sorted Array  (LC 540)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : every element appears twice except one. O(log n).
// Example  : [1,1,2,3,3,4,4,8,8] -> 2
// Hint     : before the single element, pairs start at EVEN indices.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p11_single_non_duplicate(const vector<int>& a) {
    // your code
    return -1;
}
void test_p11() {
    check("p11 ex1", p11_single_non_duplicate({1, 1, 2, 3, 3, 4, 4, 8, 8}), 2);
    check("p11 ex2", p11_single_non_duplicate({3, 3, 7, 7, 10, 11, 11}), 10);
    check("p11 ex3", p11_single_non_duplicate({5}), 5);
}

// ----------------------------------------------------------------------------
// P12. Aggressive Cows  (SPOJ / GFG)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : place `cows` cows in stalls to MAXIMIZE the minimum distance.
// Example  : stalls [1,2,4,8,9], cows 3 -> 3
// Hint     : "maximize the minimum" -> guess the distance, check greedily.
//            (predicate is T T T F F -> find the LAST true)
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p12_aggressive_cows(vector<int> stalls, int cows) {
    // your code
    return -1;
}
void test_p12() {
    check("p12 ex1", p12_aggressive_cows({1, 2, 4, 8, 9}, 3), 3);
    check("p12 ex2", p12_aggressive_cows({10, 1, 2, 7, 5}, 3), 4);
}

// ----------------------------------------------------------------------------
// P13. Search in Rotated Sorted Array II  (LC 81)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : rotated sorted array WITH duplicates. Does target exist?
// Example  : [2,5,6,0,0,1,2], target 0 -> true
// Hint     : when a[lo] == a[mid] == a[hi] you learn nothing -> shrink both.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
bool p13_search_rotated_dup(const vector<int>& a, int target) {
    // your code
    return false;
}
void test_p13() {
    check("p13 ex1", p13_search_rotated_dup({2, 5, 6, 0, 0, 1, 2}, 0), true);
    check("p13 ex2", p13_search_rotated_dup({2, 5, 6, 0, 0, 1, 2}, 3), false);
    check("p13 ex3", p13_search_rotated_dup({1, 0, 1, 1, 1}, 0), true);
}

// ----------------------------------------------------------------------------
// P14. Kth Missing Positive Number  (LC 1539)   Difficulty: E (O(log n) is M)
// ----------------------------------------------------------------------------
// Problem  : strictly increasing positive ints; find the kth missing positive.
// Example  : [2,3,4,7,11], k = 5 -> 9
// Hint     : missing count before index i = a[i] - (i + 1). Is it monotonic?
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p14_kth_missing(const vector<int>& a, int k) {
    // your code
    return -1;
}
void test_p14() {
    check("p14 ex1", p14_kth_missing({2, 3, 4, 7, 11}, 5), 9);
    check("p14 ex2", p14_kth_missing({1, 2, 3, 4}, 2), 6);
}

// ----------------------------------------------------------------------------
// P15. Interval List Intersections  (LC 986)   Difficulty: M
// ----------------------------------------------------------------------------
// Problem  : two sorted disjoint interval lists -> all intersections.
// Example  : A=[[0,2],[5,10]], B=[[1,5],[8,12]] -> [[1,2],[5,5],[8,10]]
// Hint     : overlap formula + two pointers; advance the one that ends first.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
vector<vector<int>> p15_interval_intersection(const vector<vector<int>>& A,
                                              const vector<vector<int>>& B) {
    // your code
    return {};
}
void test_p15() {
    check("p15 ex1",
          p15_interval_intersection({{0, 2}, {5, 10}, {13, 23}, {24, 25}},
                                    {{1, 5}, {8, 12}, {15, 24}, {25, 26}}),
          {{1, 2}, {5, 5}, {8, 10}, {15, 23}, {24, 24}, {25, 25}});
    check("p15 empty", p15_interval_intersection({{1, 3}, {5, 9}}, {}), vector<vector<int>>{});
}

// ----------------------------------------------------------------------------
// P16. Pascal's Triangle  (LC 118)   Difficulty: E
// ----------------------------------------------------------------------------
// Problem  : first numRows rows of Pascal's triangle.
// Example  : 5 -> [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
// Hint     : row[i][j] = row[i-1][j-1] + row[i-1][j].
//            Follow-up: nth row directly with nCr in O(n).
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
vector<vector<int>> p16_pascal(int num_rows) {
    // your code
    return {};
}
void test_p16() {
    check("p16 ex1", p16_pascal(5), {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}});
    check("p16 ex2", p16_pascal(1), {{1}});
}

// ----------------------------------------------------------------------------
// P17. Count Inversions  (GFG / Striver)   Difficulty: H
// ----------------------------------------------------------------------------
// Problem  : count pairs i < j with a[i] > a[j].
// Example  : [2,4,1,3,5] -> 3
// Hint     : merge sort; while merging, a right element smaller than left[i]
//            is smaller than ALL remaining left elements.
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
long long p17_count_inversions(vector<int> a) {
    // your code
    return -1;
}
void test_p17() {
    check("p17 ex1", p17_count_inversions({2, 4, 1, 3, 5}), 3LL);
    check("p17 ex2", p17_count_inversions({5, 4, 3, 2, 1}), 10LL);
    check("p17 ex3", p17_count_inversions({1, 1, 1}), 0LL);
}

// ----------------------------------------------------------------------------
// P18. Largest Rectangle in Histogram  (LC 84)   Difficulty: H
// ----------------------------------------------------------------------------
// Problem  : bars of width 1, find the largest rectangle area.
// Example  : [2,1,5,6,2,3] -> 10
// Hint     : for each bar, how far can it extend left/right? (previous/next
//            SMALLER element)
//
// Pattern guess :
// Brute force   :                               Time:        Space:
// Optimization  :
// Final         :                               Time:        Space:
// Edge cases    :
// Mistakes      :
// Status        : TODO
// ----------------------------------------------------------------------------
int p18_largest_rectangle(const vector<int>& h) {
    // your code
    return -1;
}
void test_p18() {
    check("p18 ex1", p18_largest_rectangle({2, 1, 5, 6, 2, 3}), 10);
    check("p18 ex2", p18_largest_rectangle({2, 4}), 4);
    check("p18 ex3", p18_largest_rectangle({3, 3, 3}), 9);
}

/*
--------------------------------------------------------------------------------
REVISIT LOG  (add a line whenever you needed a hint or got it wrong)
--------------------------------------------------------------------------------
 Date        | Problem                 | What I missed                 | Re-solved?
 ------------|-------------------------|-------------------------------|-----------
             |                         |                               |
--------------------------------------------------------------------------------
*/

// ============================================================================
// MAIN
// ============================================================================
int main() {
    cout << "===== PART A: solved patterns =====\n";
    test_solved();
    cout << "  " << total_pass << " passed, " << total_fail << " failed\n\n";

    // Practice tracker: add new problems here.
    vector<pair<string, function<void()>>> practice = {
        {"P01 Squares of Sorted Array   [two pointers]", test_p01},
        {"P02 Rearrange by Sign         [two pointers]", test_p02},
        {"P03 4Sum                      [two pointers]", test_p03},
        {"P04 Pivot Index               [prefix sum]", test_p04},
        {"P05 Subarrays XOR K           [prefix + hash]", test_p05},
        {"P06 Subarray Sums Div by K    [prefix + hash]", test_p06},
        {"P07 Max Consecutive Ones III  [sliding window]", test_p07},
        {"P08 Max Points from Cards     [sliding window]", test_p08},
        {"P09 Nice Subarrays            [sliding window]", test_p09},
        {"P10 Stock II                  [greedy]", test_p10},
        {"P11 Single Element Sorted     [binary search]", test_p11},
        {"P12 Aggressive Cows           [BS on answer]", test_p12},
        {"P13 Rotated Search II         [rotated BS]", test_p13},
        {"P14 Kth Missing Positive      [binary search]", test_p14},
        {"P15 Interval Intersections    [intervals]", test_p15},
        {"P16 Pascal's Triangle         [matrix]", test_p16},
        {"P17 Count Inversions          [merge sort]", test_p17},
        {"P18 Largest Rectangle         [monotonic stack]", test_p18},
    };

    cout << "===== PART B: practice tracker =====\n";
    quiet = true;  // set to false to see got/expected for failing practice tests
    int solved = 0;
    for (auto& [name, test] : practice) {
        int pass_before = total_pass, fail_before = total_fail;
        test();
        int p = total_pass - pass_before, f = total_fail - fail_before;
        bool ok = f == 0;
        solved += ok;
        cout << "  [" << (ok ? "DONE" : "    ") << "] " << name << "  (" << p << "/" << p + f << ")\n";
    }
    cout << "  Solved " << solved << " / " << practice.size() << "\n";
    return 0;
}
