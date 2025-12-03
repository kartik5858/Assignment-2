#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));

    int x = 1;                  // player position (0 to 2)
    int step = 0;               // obstacle vertical movement (0 to 10)
    int obstaclePos = rand() % 3;   // 0,1,2 lane
    int lives = 3;              // player live
    int score = 0;              // player score
    int min_delay=30;
    int max_delay=150;

    while (1) {

        // ---- INPUT ----
	 if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0)        // LEFT arrow
                x--;

            if (ch == 77 && x < 2)        // RIGHT arrow
                x++;
        }



        // ---- DRAW ----
        system("cls");
        printf("Lives: %d   Score: %d\n", lives, score);
        printf("|--- --- ---|\n");

        for (int i = 0; i < 10; i++) {
            if (i == step) {

                if (obstaclePos == 0)
                    printf("| %c        |\n", 1); 

                else if (obstaclePos == 1)
                    printf("|     %c    |\n", 1);   
                else if (obstaclePos == 2)
                    printf("|        %c |\n", 1);   

            } else {
                printf("|           |\n");
            }
        }

        // ---- PLAYER ----
        if (x == 0)
            printf("| %c        |\n", 6);
        else if (x == 1)
            printf("|     %c    |\n", 6);
        else if (x == 2)
            printf("|        %c |\n", 6);

        // ---- COLLISION ----
        if (step == 10 && x == obstaclePos) {
            lives--;

            if (lives == 0) {
                printf("\nGAME OVER!\n");
                printf("Final Score: %d\n", score);
                break;
            } else {
                printf("\nYou crashed! Lives left: %d\n", lives);
                Sleep(2000);          // pause 

                // Reset obstacle after crash 
                step = 0;
                obstaclePos = rand() % 3;
                continue;           
            }
        }

			// difficulty
			int level = score / 5;      // increse level every 5 score
			if (level > 6) level = 6;   // max level at score 30+

			int delay = max_delay - level * 20;   // goes from 150 to 30 in 6 levels 
			if (delay < min_delay) delay = min_delay;

			Sleep(delay);


        // Move obstacle down
        step++;

        // Reset when reaches bottom
        if (step > 10) {
            step = 0;
            obstaclePos = rand() % 3; 
            score++;                  
        }
    }

    return 0;
}
