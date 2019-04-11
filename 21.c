#include <stdio.h>
int main()
{

    int n; // To store number of pages.
    int page_number[50]; // Page numbers
    int frame[10]; // Frames
    int no;
    int avail;
    int count = 0;
    // Takin input
    printf("Enter the number of pages:\n");
    scanf("%d", &n);
    printf("Enter page number for %d pages:\n", n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &page_number[i]);
    }
    printf("Enter the number of frames:");
    scanf("%d", &no);
    // Initializing all frames to -1.
    for (int i = 0; i < no; i++)
    {
        frame[i] = -1;
    }
    int j = 0;
    printf("\tReference string\t Page Frames\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d\t\t", page_number[i]);
        avail = 0;
        for (int  k = 0; k < no; k++)
            if (frame[k] == page_number[i])
                avail = 1;
        if (avail == 0)
        {
            frame[j] = page_number[i];
            j = (j + 1) % no;
            count++;
            for (int k = 0; k < no; k++){
                printf("%d\t", frame[k]);
            }
        }
        printf("\n");
    }
    printf("Page fault is %d", count);
    return 0;
}
