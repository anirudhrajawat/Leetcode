class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n, 0), sz(n, 1);
        vector<int> heavy(n, -1), head(n), pos(n);
        vector<int> order;
        order.reserve(n);

        vector<int> st = {0};
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            int best = 0;

            for (int v : adj[u]) {
                if (parent[v] != u) continue;

                sz[u] += sz[v];

                if (sz[v] > best) {
                    best = sz[v];
                    heavy[u] = v;
                }
            }
        }

        int timer = 0;
        vector<pair<int, int>> todo = {{0, 0}};

        while (!todo.empty()) {
            auto [u, h] = todo.back();
            todo.pop_back();

            for (int v = u; v != -1; v = heavy[v]) {
                head[v] = h;
                pos[v] = timer++;

                for (int w : adj[v]) {
                    if (parent[w] == v && w != heavy[v]) {
                        todo.push_back({w, w});
                    }
                }
            }
        }

        int size = 1;
        while (size < n) size *= 2;

        vector<int> seg(size * 2, 0);

        for (int i = 0; i < n; i++) {
            seg[size + pos[i]] = 1 << (s[i] - 'a');
        }

        for (int i = size - 1; i > 0; i--) {
            seg[i] = seg[i * 2] ^ seg[i * 2 + 1];
        }

        auto update = [&](int p, int val) {
            p += size;
            seg[p] = val;

            for (p /= 2; p > 0; p /= 2) {
                seg[p] = seg[p * 2] ^ seg[p * 2 + 1];
            }
        };

        auto rangeQuery = [&](int l, int r) {
            int ans = 0;
            l += size;
            r += size;

            while (l <= r) {
                if (l % 2 == 1) ans ^= seg[l++];
                if (r % 2 == 0) ans ^= seg[r--];

                l /= 2;
                r /= 2;
            }

            return ans;
        };

        auto pathQuery = [&](int u, int v) {
            int ans = 0;

            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]]) {
                    swap(u, v);
                }

                ans ^= rangeQuery(pos[head[u]], pos[u]);
                u = parent[head[u]];
            }

            if (depth[u] > depth[v]) swap(u, v);

            ans ^= rangeQuery(pos[u], pos[v]);

            return ans;
        };

        vector<bool> ans;

        for (string q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                s[u] = c;
                update(pos[u], 1 << (c - 'a'));
            } else {
                int v;
                ss >> v;

                int mask = pathQuery(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
