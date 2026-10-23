
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = 0, right = 0;

        for (int w : weights) {
            left = max(left, w);
            right += w;
        }

        while (left < right) {
            int mid = left + (right - left) / 2;

            int dayCount = 1;
            int currentWeight = 0;

            for (int w : weights) {
                if (currentWeight + w > mid) {
                    dayCount++;
                    currentWeight = 0;
                }

                currentWeight += w;
            }

            if (dayCount > days) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};
