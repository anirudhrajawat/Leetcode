class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                st.push(s[i]);
            } 
            else {
                if (st.empty())
                    return false;

                char temp = st.top();
                st.pop();

                if (temp == '(' && s[i] != ')')
                    return false;
                if (temp == '{' && s[i] != '}')
                    return false;
                if (temp == '[' && s[i] != ']')
                    return false;
            }
        }

        return st.empty();
    }
};