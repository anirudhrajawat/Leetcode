class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> left, right;
        long long sum1 = 0, sum2 = 0;

        vector<long long> cost;

        auto balance = [&]() {
            while (left.size() > right.size() + 1) {
                int v = *left.rbegin();
                left.erase(prev(left.end()));
                sum1 -= v;
                right.insert(v);
                sum2 += v;
            }

            while (left.size() < right.size()) {
                int v = *right.begin();
                right.erase(right.begin());
                sum2 -= v;
                left.insert(v);
                sum1 += v;
            }
        };

        auto add = [&](int v) {
            if (left.empty() || v <= *left.rbegin()) {
                left.insert(v);
                sum1 += v;
            } else {
                right.insert(v);
                sum2 += v;
            }
            balance();
        };

        auto remove = [&](int v) {
            auto it = left.find(v);

            if (it != left.end()) {
                left.erase(it);
                sum1 -= v;
            } else {
                it = right.find(v);
                right.erase(it);
                sum2 -= v;
            }
            balance();
        };

        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                long long med = *left.rbegin();

                long long ans = med * left.size() - sum1
                              + sum2 - med * right.size();

                cost.push_back(ans);
            }
        }

        const long long INF = 1e18;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {
                dp[j][i] = dp[j][i - 1];

                if (i >= x && dp[j - 1][i - x] != INF) {
                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};