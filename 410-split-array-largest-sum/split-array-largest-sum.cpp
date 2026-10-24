
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int left = 0, right = 0;

        for (int x : nums) {
            left = max(left, x);
            right += x;
        }

        while (left < right) {
            int mid = left + (right - left) / 2;

            int parts = 1;
            int sum = 0;

            for (int x : nums) {
                if (sum + x > mid) {
                    parts++;
                    sum = 0;
                }

                sum += x;
            }

            if (parts > k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};
