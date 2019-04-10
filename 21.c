#include <stdio.h>
int main()
{
    int i;
    int j;
    int n;
    int a[50];
    int frame[10];
    int no;
    int k;
    int avail;
    int count = 0;
    printf("Enter the number of pages:\n");
    scanf("%d", &n);
    printf("Enter page number:\n");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("Enter the number of frames:");
    scanf("%d", &no);
    for (i = 0; i < no; i++)
    {
        frame[i] = -1;
    }
    j = 0;
    printf("\tReference string\t Page Frames\n");
    for (i = 1; i <= n; i++)
    {
        printf("%d\t\t", a[i]);
        avail = 0;
        for (k = 0; k < no; k++)
            if (frame[k] == a[i])
                avail = 1;
        if (avail == 0)
        {
            frame[j] = a[i];
            j = (j + 1) % no;
            count++;
            for (k = 0; k < no; k++){
                printf("%d\t", frame[k]);
            }
        }
        printf("\n");
    }
    printf("Page fault is %d", count);
    return 0;
}
