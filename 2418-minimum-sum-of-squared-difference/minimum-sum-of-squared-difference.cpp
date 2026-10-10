class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<int> diff(n);
        int maxi = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxi = max(maxi, diff[i]);
        }

        if (k >= accumulate(diff.begin(), diff.end(), 0LL)) {
            return 0;
        }

        int low = 0, high = maxi;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long operations = 0;

            for (int d : diff) {
                if (d > mid) {
                    operations += d - mid;
                }
            }

            if (operations <= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        int level = low;
        long long ans = 0;

        for (int d : diff) {
            int remaining = min(d, level);
            ans += 1LL * remaining * remaining;
            if (d > level) {
                k -= d - level;
            }
        }

        for (int i = 0; i < n && k > 0; i++) {
            if (diff[i] >= level && level > 0) {
                ans -= 1LL * level * level;
                ans += 1LL * (level - 1) * (level - 1);
                k--;
            }
        }

        return ans;
    }
};