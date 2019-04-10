#include<stdio.h>
#include<math.h>
#include<conio.h>
int main()
{
	double pnm, pm, mat, mp, eat,pfr;
	printf("Enter the time for Page Fault not modified in milliseconds: ");
	scanf("%lf",&pnm);
	pnm *=pow(10,-3);
	printf("Enter the time for Page Fault modified in milliseconds: ");
	scanf("%lf",&pm); 
	pm *=pow(10,-3);                    //millisecond
	printf("Enter the time for Memory Access in nano seconds: ");
	scanf("%lf",&mat);
	mat *=pow(10,-9);                 //nanosecond
	printf("Enter the modified percentage: ");
	scanf("%lf",&mp);
	mp = mp/100;
	printf("Enter the time for Efficiency Access in nano seconds: ");
	scanf("%lf",&eat);
	eat *=pow(10,-9); 
	printf("PAGE FAULT RATE: ");
	pfr = (eat-mat)/(mp*pm + (1-mp)*pnm - mat);
	printf("%lf",pfr);
	
	getch();
}
