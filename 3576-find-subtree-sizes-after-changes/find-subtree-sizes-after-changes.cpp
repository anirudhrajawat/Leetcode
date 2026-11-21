
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> last(26, -1);
        vector<int> newParent(n);

        function<void(int)> dfs = [&](int node) {
            int c = s[node] - 'a';

            int old = last[c];

            if (old != -1) {
                newParent[node] = old;
            } else {
                newParent[node] = parent[node];
            }

            last[c] = node;

            for (int child : adj[node]) {
                dfs(child);
            }

            last[c] = old;
        };

        dfs(0);

        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 1);

        function<void(int)> solve = [&](int node) {
            for (int child : tree[node]) {
                solve(child);
                ans[node] += ans[child];
            }
        };

        solve(0);

        return ans;
    }
};
