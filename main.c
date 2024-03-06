#include <stdio.h>
// #include "table.h"

#define MONTHS 12

void printFormattedMoney(float amount)
{
    printf("$%8.2f", amount);
}

int main()
{
    FILE *salesData;

    // Open a file in read mode
    salesData = fopen("sales_data.txt", "r");

    char *months[MONTHS] = {
        "January",
        "Febuary",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December",
    };
    float monthlySales[MONTHS];
    for (int i = 0; i < MONTHS; i++)
    {
        fscanf(salesData, "%f", &monthlySales[i]);
    }
    printf("Monthly sales report for 2022:\n");

    for (int i = 0; i < MONTHS; i++)
    {
        printf("%-12s", months[i]);
        printFormattedMoney(monthlySales[i]);
        printf("\n");
    }

    printf("Sales summary:\n");

    int minIndex = 0;

    for (int i = 1; i < MONTHS; i++)
    {
        if (monthlySales[i] < monthlySales[minIndex])
        {
            minIndex = i;
        }
    }

    printf("Minimum sales: ");
    printFormattedMoney(monthlySales[minIndex]);
    printf(" (%s)\n", months[minIndex]);

    int maxIndex = 0;

    for (int i = 1; i < MONTHS; i++)
    {
        if (monthlySales[i] > monthlySales[maxIndex])
        {
            maxIndex = i;
        }
    }

    printf("Maximum sales: ");
    printFormattedMoney(monthlySales[maxIndex]);
    printf(" (%s)\n", months[maxIndex]);

    float salesSum = 0;

    for (int i = 1; i < MONTHS; i++)
    {
        salesSum += monthlySales[i];
    }

    float salesAverage = salesSum / MONTHS;

    printf("Average sales: ");
    printFormattedMoney(salesAverage);
    printf("\n");

    printf("Six-Month Moving Average Report:\n");

    float movingSum = 0.0;
    int movingSumMaxLength = 6;
    for (int i = 0; i < MONTHS; i++)
    {
        movingSum += monthlySales[i];
        if (i + 1 >= movingSumMaxLength)
        {
            float movingAverage = movingSum / movingSumMaxLength;
            char *startMonth = months[i + 1 - movingSumMaxLength];
            char *endMonth = months[i];
            printf("%-12s - %-12s ", startMonth, endMonth);
            printFormattedMoney(movingAverage);
            printf("\n");
            movingSum -= monthlySales[i + 1 - movingSumMaxLength];
        }
    }

    // Sales Report (Highest to Lowest):
    printf("Sales Report (Highest to Lowest):\n");

    int monthIndiciesSortedBySales[MONTHS];
    // Very simple sorting, just add the maximum that doesn't exist each time
    for (int i = 0; i < MONTHS; i++)
    {
        int maxIndex = -1;
        for (int salesIndex = 0; salesIndex < MONTHS; salesIndex++)
        {
            int alreadyInArray = 0;
            // Make sure this index doesn't already exist in our array
            for (int inner = 0; inner < i; inner++)
            {
                if (monthIndiciesSortedBySales[inner] == salesIndex)
                {
                    alreadyInArray = 1;
                }
            }
            if (alreadyInArray == 0)
            {
                if (maxIndex == -1 || monthlySales[maxIndex] < monthlySales[salesIndex])
                {
                    maxIndex = salesIndex;
                }
            }
        }
        monthIndiciesSortedBySales[i] = maxIndex;
    }

    for (int i = 0; i < MONTHS; i++)
    {
        int monthIndex = monthIndiciesSortedBySales[i];
        printf("%-12s", months[monthIndex]);
        printFormattedMoney(monthlySales[monthIndex]);
        printf("\n");
    }

    fclose(salesData);
    return 0;
}
