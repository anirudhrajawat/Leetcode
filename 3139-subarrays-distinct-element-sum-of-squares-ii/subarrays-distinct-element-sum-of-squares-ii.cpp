class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long squares = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int start, int end, long long val) {
        long long len = end - start + 1;

        tree[node].squares =
            (tree[node].squares + 2 * val % MOD * tree[node].sum
             + len % MOD * val % MOD * val) % MOD;

        tree[node].sum =
            (tree[node].sum + len * val) % MOD;

        tree[node].lazy = (tree[node].lazy + val) % MOD;
    }

    void push(int node, int start, int end) {
        if (tree[node].lazy == 0 || start == end) return;

        int mid = (start + end) / 2;
        long long val = tree[node].lazy;

        apply(node * 2, start, mid, val);
        apply(node * 2 + 1, mid + 1, end, val);

        tree[node].lazy = 0;
    }

    void update(int node, int start, int end,
                int left, int right, long long val) {
        if (right < start || end < left) return;

        if (left <= start && end <= right) {
            apply(node, start, end, val);
            return;
        }

        push(node, start, end);

        int mid = (start + end) / 2;

        update(node * 2, start, mid, left, right, val);
        update(node * 2 + 1, mid + 1, end, left, right, val);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;

        tree[node].squares =
            (tree[node * 2].squares +
             tree[node * 2 + 1].squares) % MOD;
    }

    long long query(int node, int start, int end,
                    int left, int right) {
        if (right < start || end < left) return 0;

        if (left <= start && end <= right)
            return tree[node].squares;

        push(node, start, end);

        int mid = (start + end) / 2;

        return (query(node * 2, start, mid, left, right) +
                query(node * 2 + 1, mid + 1, end, left, right)) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n + 5);

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int previous = -1;

            if (last.count(nums[i]))
                previous = last[nums[i]];

            update(1, 0, n - 1, previous + 1, i, 1);

            ans = (ans + query(1, 0, n - 1, 0, i)) % MOD;

            last[nums[i]] = i;
        }

        return ans;
    }
};