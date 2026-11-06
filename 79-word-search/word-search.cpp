
class Solution {
public:
    bool solve(vector<vector<char>>& board, string word, int i, int j, int k) {
        if (k == word.size()) {
            return true;
        }

        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] != word[k]) {
            return false;
        }

        char ch = board[i][j];
        board[i][j] = '#';

        bool ans = solve(board, word, i + 1, j, k + 1) ||
                   solve(board, word, i - 1, j, k + 1) ||
                   solve(board, word, i, j + 1, k + 1) ||
                   solve(board, word, i, j - 1, k + 1);

        board[i][j] = ch;

        return ans;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (solve(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};
