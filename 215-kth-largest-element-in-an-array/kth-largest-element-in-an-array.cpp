#include <vector>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int target = n - k;
        int left = 0, right = n - 1;

        while (left <= right) {
            int p = partition(nums, left, right);
            if (p == target) return nums[p];
            else if (p < target) left = p + 1;
            else right = p - 1;
        }
        return -1;
    }

private:
    int partition(vector<int>& nums, int left, int right) {
        int r = left + rand() % (right - left + 1);
        swap(nums[r], nums[right]);

        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; j++) {
            if (nums[j] < pivot) {
                swap(nums[i], nums[j]);
                i++;
            }
        }
        swap(nums[i], nums[right]);
        return i;
    }
};