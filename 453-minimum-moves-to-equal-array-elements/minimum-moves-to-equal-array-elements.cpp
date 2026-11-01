class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mini = nums[0];

        
        for (int i = 1; i < nums.size(); i++) {
            mini = min(mini, nums[i]);
        }

        int moves = 0;

        
        for (int i = 0; i < nums.size(); i++) {
            moves += nums[i] - mini;
        }

        return moves;
    }
};