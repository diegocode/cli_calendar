/*
 * Command line Calendar
 *
 * CC-BY-SA 4.0
 *
 * diego.Codevilla
 */

#include <stdio.h>
#include <time.h>

const char * day_name[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char * month_name[] = {"January", "February", "March",
                            "April", "May", "June",
                            "July", "August", "September",
                            "October", "November", "December"};

int days_in_month(int m, int y);
void print_cal(int month, int year);

int main(int argc, char **argv)
{
    int year, month;

    /*
     * uncomment the following three lines
     * to get input from user and print the calendar 
     */

    // scanf("%d",&year);
    // scanf("%d",&month);
    // print_cal(month, year);


    // Prints calendars of 2019
    year = 2019;
    for (int m = 1; m <= 12; m++) {
        print_cal(m, year);
    }

    return 0;
}

/*
 * Prints the calendar of the given month / year
 */
void print_cal(int month, int year) {
    time_t rtime; struct tm * time_aux;
    int wd;

    /*
     * Populate struct_tm
     * with system's date/time
     */
    time(&rtime);
    time_aux = localtime ( &rtime );

    /*
     * Then set year & month desired
     */
    time_aux->tm_year = year - 1900;
    time_aux->tm_mon = month - 1;
    time_aux->tm_mday = 1;

    /*
     * Adjust values of the struct_tm
     */
    mktime (time_aux);

    // Finally! Gets number of day (Sunday = 0)
    wd = time_aux->tm_wday;

    // Prints month name
    printf("\n===========================\n");
    printf("%s\n", month_name[month - 1]);
    printf("---------------------------\n");

    // Prints days' names
    for(int i = 0; i < 7; i++)
        printf("%s ", day_name[i]);
    printf("\n");

    /*
     * Prints calendar
     *
     */
    for(int d = 1 - wd; d <= days_in_month(month, year); d++) {
        if (d < 1) {
            printf("    ");
        } else {
            printf(" %2d ", d);
            wd++;
            if (wd > 6) {
                wd = 0;
                printf("\n");
            }
        }
    }
    printf("\n");
}

/*
 * Returns the number of days in a given month
 * Needs the year because is "Leap-year-aware"
 *
 */
int days_in_month(int m, int y) {
    time_t rtime; struct tm * time_aux;

    /*
     * Populate struct_tm
     * with system's date/time
     */
    time(&rtime);
    time_aux = localtime ( &rtime );

    /*
     * Then set year & month desired
     * Sets Days to 31
     */
    time_aux->tm_year = y - 1900;
    time_aux->tm_mon = m - 1;
    time_aux->tm_mday = 31;

    /*
     * Adjust values of the struct_tm
     */
    mktime (time_aux);

    /*
     * If month have less than 31 days, the day in struct_tm
     * overflows -because we assigned 31 days above-
     * So... if September (30 days) => mday = 1,
     * if february, non-leap-year => mday = 3
     * if february, leap year => mday = 2
     */
    return (time_aux->tm_mday == 31) ? 31 : (31 - time_aux->tm_mday);
}
