#include<stdio.h>

int main() {
    printf("A Game to solve the Cannibal's and Missionaries Problem!\n");
    
    int lCan = 3;
    int lMis = 3;
    int rMis = 0, rCan = 0;
    int a, b;

    while (rMis != 3 || rCan != 3) {
        if (lCan <= lMis && rCan <= rMis) {
            printf("Left to Right\n");
            printf("Enter Number of Missionaries to move: ");
            scanf("%d", &a);
            printf("Enter Number of Cannibals to move: ");
            scanf("%d", &b);

            lCan = lCan - b;
            lMis = lMis - a;
            rCan = rCan + b;
            rMis = rMis + a;

            // Check game-over conditions after the move
            if (lCan > lMis && lMis > 0 || rCan > rMis && rMis > 0) {
                printf("Error: Game Over! Cannibals ate the missionaries.\n");
                return 0;
            }

            // Display current state
            printf("Left side: %d Missionaries, %d Cannibals\n", lMis, lCan);
            printf("Right side: %d Missionaries, %d Cannibals\n", rMis, rCan);

            if (rMis == 3 && rCan == 3) {
                printf("Congratulations! You solved the problem.\n");
                return 0;
            }

            printf("Right to Left\n");
            printf("Enter Number of Missionaries to return: ");
            scanf("%d", &a);
            printf("Enter Number of Cannibals to return: ");
            scanf("%d", &b);

            rCan = rCan - b;
            rMis = rMis - a;
            lCan = lCan + b;
            lMis = lMis + a;

            // Check game-over conditions after the return
            if (lCan > lMis && lMis > 0 || rCan > rMis && rMis > 0) {
                printf("Error: Game Over! Cannibals ate the missionaries.\n");
                return 0;
            }

            // Display current state
            printf("Left side: %d Missionaries, %d Cannibals\n", lMis, lCan);
            printf("Right side: %d Missionaries, %d Cannibals\n", rMis, rCan);
        } else {
            printf("Error: Invalid move! Ensure missionaries are not outnumbered by cannibals on any side.\n");
        }
    }

    return 0;
}
