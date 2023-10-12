#include <stdio.h>

int main() {

    int possible_points[] = {2, 3, 6, 7, 8};  // The possible totals in order from least to greatest
    char possible_names[][32] = {"Safety", "Field Goal", "Touchdown", "Touchdown + EP", "Touchdown + 2PC"};  // The names of the various points, I ended up not using these, but decided to leave them in for clarification and for each expansion in the future

    int request = 5;

    while (request > 1) {
        
        printf("\nEnter 0 or 1 to STOP\nEnter the NFL score: ");
        scanf("%d", &request);

        int point_maxes[5];

        // This calculates the most any one given scoring type without going over our target
        for (int i = 0; i < 5; i++) {  // Loops through each scoring type
            int current_max = 0;
            int current_index = 0;
            while (current_max != 1) {
                if ((request - (current_index * possible_points[i])) < 0) {  // Checks if the total number of them * their point total is greater than the requested score
                    current_max = 1;  // If it is bigger, we set the flag variable to true
                    current_index--;  // Reduce the index by 1 to get less than the total
                    point_maxes[i] = current_index;  // Stores the value in the array of maxes
                } else {
                    current_index++;  // If it's still smaller than the total, add another
                }
            }
        }

        // At this point we have generated an array of the maximum number of each of these without going over.
        // This works by using several nested FOR loops with each going from 0 to the maximum of the number of each scoring type.
        printf("\npossible combinations of scoring plays:\n");
        for (int s_counter = 0; s_counter <= point_maxes[0]; s_counter++) {
            for (int fg_counter = 0; fg_counter <= point_maxes[1]; fg_counter++) {
                for (int td_counter = 0; td_counter <= point_maxes[2]; td_counter++) {
                    for (int tdep_counter = 0; tdep_counter <= point_maxes[3]; tdep_counter++) {
                        for (int tdtp_counter = 0; tdtp_counter <= point_maxes[4]; tdtp_counter++) {
                            // For each possible combination, if it calculates the total points for each
                            int total = (possible_points[0]*s_counter) + (possible_points[1]*fg_counter) + (possible_points[2] * td_counter) + (possible_points[3]*tdep_counter) + (possible_points[4]*tdtp_counter);
                            if (total == request) {  // If the total points is exactly equal to the requested amount
                                printf("%d TD + 2pt, %d TD + EP, %d TD, %d FG, %d Safety\n", tdtp_counter, tdep_counter, td_counter, fg_counter, s_counter);  // Print the totals to the console
                            }
                        }
                    }
                }
            }
        }
        

    }
    
    return 0;
}