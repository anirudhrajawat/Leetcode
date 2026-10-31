class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size();
        int n = grid[0].size();
        vector<long long> dp(n, 0);
        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            long long left = 0;

            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {
                    long long temp = left;
                    left = dp[j];
                    dp[j] = temp;
                } 
                else {
                    long long total = (left + dp[j]) % MOD;
                    left = total;
                    dp[j] = total;
                }
            }
        }

        return dp[n - 1];
    }
};