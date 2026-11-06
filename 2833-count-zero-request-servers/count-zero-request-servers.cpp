
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(logs.begin(), logs.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
        });

        vector<pair<int, int>> q;

        for (int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(queries.size());
        unordered_map<int, int> mp;

        int left = 0, right = 0;

        for (int i = 0; i < q.size(); i++) {
            int start = q[i].first - x;
            int end = q[i].first;

            while (right < logs.size() && logs[right][1] <= end) {
                mp[logs[right][0]]++;
                right++;
            }

            while (left < right && logs[left][1] < start) {
                mp[logs[left][0]]--;

                if (mp[logs[left][0]] == 0) {
                    mp.erase(logs[left][0]);
                }

                left++;
            }

            ans[q[i].second] = n - mp.size();
        }

        return ans;
    }
};
