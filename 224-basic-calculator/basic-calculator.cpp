class Solution {
public:
    int calculate(string s) {
        stack<long long> st;

        long long result = 0;
        long long number = 0;
        long long sign = 1;

        for (char c : s) {
            if (isdigit(c)) {
                number = number * 10 + (c - '0');
            }
            else if (c == '+') {
                result += sign * number;
                number = 0;
                sign = 1;
            }
            else if (c == '-') {
                result += sign * number;
                number = 0;
                sign = -1;
            }
            else if (c == '(') {
                st.push(result);
                st.push(sign);

                result = 0;
                sign = 1;
            }
            else if (c == ')') {
                result += sign * number;
                number = 0;

                long long oldSign = st.top();
                st.pop();

                long long oldResult = st.top();
                st.pop();

                result = oldResult + oldSign * result;
            }
        }

        result += sign * number;

        return (int)result;
    }
};