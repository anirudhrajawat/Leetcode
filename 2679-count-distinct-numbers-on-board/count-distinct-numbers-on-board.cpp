class Solution {
public:
    int distinctIntegers(int n) {

        vector<int> nums;
        unordered_set<int> s;

        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }

        // for (int i = n - 1; i > 0; i--) {
        //     if (nums[i] % nums[i - 1] == 1) {
        //         s.insert(nums[i-1]);
        //     }
        // }
        s.insert(nums[n - 1]);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] % nums[j] == 1) {
                    s.insert(nums[j]);
                }
            }
        }

        return s.size();
    }
};
