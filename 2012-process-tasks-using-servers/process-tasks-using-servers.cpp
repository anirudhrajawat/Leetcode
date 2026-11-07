class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        using P = pair<int, int>;
        using T = tuple<long long, int, int>;

        priority_queue<P, vector<P>, greater<P>> freeQ;
        priority_queue<T, vector<T>, greater<T>> busyQ;

        for (int i = 0; i < (int)servers.size(); ++i)
            freeQ.push({servers[i], i});

        int m = tasks.size();
        vector<int> ans(m);
        long long t = 0;

        for (int j = 0; j < m; ++j) {
            t = max(t, (long long)j);
            if (freeQ.empty())
                t = max(t, get<0>(busyQ.top()));

            while (!busyQ.empty() && get<0>(busyQ.top()) <= t) {
                auto [fin, w, i] = busyQ.top();
                busyQ.pop();
                freeQ.push({w, i});
            }

            auto [w, i] = freeQ.top();
            freeQ.pop();
            ans[j] = i;
            busyQ.push({t + tasks[j], w, i});
        }
        return ans;
    }
};