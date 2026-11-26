
class Solution {
public:
    bool canAliceWin(int n) {
        int stones = n;
        int remove = 10;
        int turn = 0;

        while (stones >= remove) {
            stones -= remove;
            remove--;
            turn++;
        }

        return turn % 2 == 1;
    }
};
