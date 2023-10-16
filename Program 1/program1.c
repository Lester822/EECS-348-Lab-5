// ASSIGNMENT_NAME: EECS 348 Lab 5 Problem 1
// FUNCTION: Do math with inputted sales figures from data.txt
// INPUTS: data.txt
// OUTPUTS: Various tables with data from the inputted file
// AUTHOR_NAME: Michael Stang
// COLLABORATORS: NONE
// CREATION_DATE: 10/15/2023

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;  // file is a pointer pointing to the start of a file
    file = fopen("data.txt", "r");  // set that pointer to the file we want
    double values[12];  // var that will hold all of our data in the end
    char months[12][15] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    for (int i = 0; i < 12; i++) {
        char buffer[256];  // Var to temporarly hold the input data as strings
        fgets(buffer, sizeof(buffer), file);  // Reads one line of the input file and puts it into buffer
        values[i] = atof(buffer);  // Converts the string into a double
    }
        
    // Monthly Sales Report

    printf("Monthly sales report for 2023:\n\n"); 
    char header_one[] = "Month";
    char header_two[] = "Sales";
    printf("%-10s %s\n\n", header_one, header_two);

    for (int i = 0; i < 12; i++) {  // Loops for each month

        printf("%-10s ", months[i]);  // Prints the month name with 10 spaces guarenteed, causing padding
        printf("$%.2f\n", values[i]);  // Prints the values

    }

    // Sales Summary

    int biggest_index = 0;
    int smallest_index = 0;
    double sales_sum = 0;
    double sales_average;

    for (int i = 0; i < 12; i++) {  // Loops for every month

        if (values[i] > values[biggest_index]) {  // Checks if the value at the current index is bigger than the previous biggest index
            biggest_index = i;  // If so, update biggest index
        } else if (values[i] < values[smallest_index]) {  // Same a above, just with < and smallest_index
            smallest_index = i;
        }

        sales_sum += values[i];  // Sums up all the totals
    }
    sales_average = (sales_sum / 12);  // Calculates the average

        // Handles printing
    printf("\n\nSales summary:\n\n");
    printf("%-10s $%.2f (%s)\n", "Minimum Sales: ", values[smallest_index], months[smallest_index]);
    printf("%-10s $%.2f (%s)\n", "Maximum Sales: ", values[biggest_index], months[biggest_index]);
    printf("%-10s $%.2f\n", "Average Sales: ", sales_average);

    // Six-Month Moving Average Report
    double averages[7];
    printf("\n\nSix-Month Moving Average Report:\n\n");
    for (int i = 0; i < 7; i++) {  // Loops 6 times (one for each rolling period)
        double rolling_sum = 0;
        for (int j = i; j < i+6; j++) {  // Loops for each month in a rolling period
            rolling_sum += values[j];
        }
        rolling_sum /= 6;  // Calculates the average
        printf("%-10s - %-10s $%.2f\n", months[i], months[i+5], rolling_sum);  // Outputs to user
        averages[i] = rolling_sum;  // Keeps track of averages (not needed, but might as well if this was a real program)

    }

    // Sales Report (Highest to Lowest):

    int index_order[12];
    int values_copy[12];

    double least_value = values[smallest_index];
    
    for (int i = 0; i < 12; i++) {  // Makes a copy of values (named values_copy)
        values_copy[i] = values[i];
    }



    for (int i = 0; i < 12; i++) {  // Loops for every month
        int greatest_index = 0;  // Starts at the beginning of the array
        for (int j = 0; j < 12; j++) {  // Goes through every value
            if (values_copy[j] > values_copy[greatest_index]) {  // If the value at the current position is bigger than the value at the previously highest position (init 0)
                greatest_index = j;  // Sets that new position as the greatest index
            }
        }

        index_order[i] = greatest_index;  // Adds that index to the array of the order of greatest value
        values_copy[greatest_index] = least_value - 10;  // Sets the index of the highest value to 10 minus the lowest value (making sure it's not selected twice)
    }

        // Printing Handling
    printf("\n\nSales summary:\n\n");
    printf("%-10s %-10s\n\n", "Month", "Sales");
    for (int i = 0; i < 12; i++) {  // Loops through each month
        printf("%-10s %.2f\n", months[index_order[i]], values[index_order[i]]);  // Prints the months and earnings in order from highest to lowest
    }

    return 0;
}
