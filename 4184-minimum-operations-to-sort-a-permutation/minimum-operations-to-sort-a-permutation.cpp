class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int zero = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                zero = i;
                break;
            }
        }

        int ans = INT_MAX;

        for (int step = 1; step >= -1; step -= 2) {
            bool valid = true;

            for (int i = 1; i < n; i++) {
                int prev = (zero + (i - 1) * step + n) % n;
                int curr = (zero + i * step + n) % n;

                if (nums[prev] > nums[curr]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                if (step == 1) {
                    ans = min(ans, zero);
                    ans = min(ans, n - zero + 2);
                } else {
                    ans = min(ans, zero + 2);
                    ans = min(ans, n - zero);
                }
            }
        }

        if (ans == INT_MAX) {
            return -1;
        }

        return ans;
    }
};
