// Question number: 21

#include <stdio.h>
#include <math.h>
#include <conio.h>
int main()
{
    double page_not_modified,
        page_modified,
        memory_access_time,
        modified_percentage,
        efficiency_access_time,
        page_fault_rate;

    printf("Enter the time for Page Fault not modified in milliseconds: ");
    scanf("%lf", &page_not_modified);
    page_not_modified *= pow(10, -3);

    printf("Enter the time for Page Fault modified in milliseconds: ");
    scanf("%lf", &page_modified);
    page_modified *= pow(10, -3); //millisecond

    printf("Enter the time for Memory Access in nano seconds: ");
    scanf("%lf", &memory_access_time);
    memory_access_time *= pow(10, -9); //nanosecond

    printf("Enter the modified percentage: ");
    scanf("%lf", &modified_percentage);
    modified_percentage = modified_percentage / 100;

    printf("Enter the time for Efficiency Access in nano seconds: ");
    scanf("%lf", &efficiency_access_time);
    efficiency_access_time *= pow(10, -9);

    printf("PAGE FAULT RATE: ");
    page_fault_rate = (efficiency_access_time - memory_access_time) / (modified_percentage * page_modified + (1 - modified_percentage) * page_not_modified - memory_access_time);
    printf("%lf", page_fault_rate);

    return 0;
}