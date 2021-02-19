#include <iostream>
#include "functions.h"


int main()
{
    std::cout << "Hello World!\n";
    player_flag = 1;


    InitializeStatus();

    int pass_f = 0;
    while (true) {
        ShowGrid();
        int put=PutStone(player_flag);
        if (put == -2) { break; }
        if (put >= 0) {
            pass_f = 0;
            ReverseStone(put, player_flag, JudgePuttable(put, player_flag));
        }
        else { pass_f++; }
        if (pass_f == 2) { break; }
        player_flag *= -1;
    }

    JudgeGame();
    ShowGrid();

    return 0;
}

