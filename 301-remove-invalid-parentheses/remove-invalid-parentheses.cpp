class Solution {
public:

    bool isValid(string s) {
        int count = 0;

        for (char ch : s) {

            if (ch == '(') {
                count++;
            }
            else if (ch == ')') {
                count--;
            }

            if (count < 0) {
                return false;
            }
        }

        return count == 0;
    }

    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;

        queue<string> q;
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {

            int size = q.size();

            while (size--) {

                string current = q.front();
                q.pop();

                // If valid, add it to answer
                if (isValid(current)) {
                    ans.push_back(current);
                    found = true;
                }

                // If we already found valid strings,
                // don't remove more characters
                if (found) {
                    continue;
                }

                // Try removing each character
                for (int i = 0; i < current.length(); i++) {

                    // Only remove parentheses
                    if (current[i] != '(' && current[i] != ')') {
                        continue;
                    }

                    string next = current.substr(0, i) +
                                  current.substr(i + 1);

                    if (visited.find(next) == visited.end()) {

                        visited.insert(next);
                        q.push(next);
                    }
                }
            }

            // Minimum removals found
            if (found) {
                break;
            }
        }

        return ans;
    }
};