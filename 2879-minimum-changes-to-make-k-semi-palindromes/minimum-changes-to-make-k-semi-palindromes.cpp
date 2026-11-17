class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();

        vector<vector<int>> cost(n, vector<int>(n, 100000));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;

                for (int d = 1; d < len; d++) {

                    if (len % d != 0)
                        continue;

                    int changes = 0;
                    int group = len / d;

                    for (int r = 0; r < d; r++) {

                        for (int x = 0; x < group / 2; x++) {

                            int a = i + r + x * d;
                            int b = i + r + (group - 1 - x) * d;

                            if (s[a] != s[b])
                                changes++;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 100000));

        dp[0][0] = 0;

        for (int p = 1; p <= k; p++) {

            for (int i = 2 * p; i <= n; i++) {

                for (int j = 2 * (p - 1); j <= i - 2; j++) {

                    dp[i][p] = min(dp[i][p], dp[j][p - 1] + cost[j][i - 1]);
                }
            }
        }

        return dp[n][k];
    }
};
