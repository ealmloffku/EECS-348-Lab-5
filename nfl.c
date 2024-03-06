#include <stdio.h>

// • Touchdown (TD) worth 6 POINTS
// • Field goal (FG) worth 3 POINTS
// • Safety worth 2 POINTS
// • Touchdown (TD) + 2-point conversion worth 8 POINTS
// • Touchdown (TD) + 1-point field goal worth 7 POINTS
int POINTS[5] = {
    8,
    7,
    6,
    3,
    2,
};
char *NAMES[5] = {
    "TD + 2pt",
    "TD + FG",
    "TD",
    "3pt FG",
    "Safety",
};

void checkSolution(int currentSolution[5], int goalScore)
{
    // Check if the current solution is valid
    int pointSum = 0;
    for (int scoreIndex = 0; scoreIndex < 5; scoreIndex++)
    {
        pointSum += POINTS[scoreIndex] * currentSolution[scoreIndex];
    }
    if (pointSum == goalScore)
    {
        // 0 TD + 2pt, 0 TD + FG, 0 TD, 1 3pt FG, 11 Safety
        for (int scoreIndex = 0; scoreIndex < 4; scoreIndex++)
        {
            printf("%d %s, ", currentSolution[scoreIndex], NAMES[scoreIndex]);
        }
        printf("%d %s\n", currentSolution[4], NAMES[4]);
    }
}

void permuteScore(int currentSolution[5], int goalIndex, int goalScore)
{
    if (goalIndex > 4)
    {
        return;
    }

    int maxScoreCount = goalScore / POINTS[goalIndex];
    for (int scoreCount = 0; scoreCount <= maxScoreCount; scoreCount++)
    {
        currentSolution[goalIndex] = scoreCount;

        permuteScore(currentSolution, goalIndex + 1, goalScore);

        checkSolution(currentSolution, goalScore);
    }
}

int main()
{
    int lastScore;
    while (1)
    {
        printf("Enter 0 or 1 to STOP\nEnter the NFL score: ");
        scanf("%d", &lastScore);

        if (lastScore == 0 || lastScore == 1)
        {
            return 0;
        }

        // Brute force the problem by looking through each possible number of each score
        int currentSolution[5] = {0, 0, 0, 0, 0};
        permuteScore(currentSolution, 0, lastScore);
    };
}
