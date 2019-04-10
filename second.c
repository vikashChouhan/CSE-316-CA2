#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct process_info
{
	int process_number;
	int burst_time;
	int arrival_time;
	int priority;
	int flag;
	int completed;
};

void swap(struct process_info *a, struct process_info *b)
{
	struct process_info temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_by_priority(struct process_info processes[], int len, int current_time)
{
	struct process_info curr_processes[10];
	int index[10];
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (processes[i].arrival_time <= current_time && processes[i].completed != 1)
		{
			curr_processes[j] = processes[i];
			index[j++] = i;
		}
	}
	//sort
	for (int i = 0; i < j; i++)
	{
		for (int k = 1; k < j; k++)
		{
			if (curr_processes[k].priority < curr_processes[k - 1].priority)
			{
				swap(&curr_processes[k], &curr_processes[k - 1]);
			}
			if (curr_processes[k].priority == curr_processes[k - 1].priority)
			{
				if (curr_processes[k].process_number < curr_processes[k - 1].process_number)
				{
					swap(&curr_processes[k], &curr_processes[k - 1]);
				}
			}
		}
	}

	int x = j;
	for (int i = 0; i < len; i++)
	{
		int fg = 0;
		for (int k = 0; k < j; k++)
		{
			if (index[k] == i)
			{
				fg = 1;
				break;
			}
		}
		if (fg == 0)
			curr_processes[x++] = processes[i];
	}
	for (int i = 0; i < len; i++)
		processes[i] = curr_processes[i];
}

void increase_priority(struct process_info processes[], int len, int arrival_time)
{
	for (int i = 0; i < len; i++)
	{
		if (processes[i].flag == 2 && processes[i].arrival_time <= arrival_time && processes[i].completed != 1)
		{
			processes[i].flag = 0;
			processes[i].priority -= 1;
			if (processes[i].priority < 0)
			{
				processes[i].priority = 0;
			}
		}
	}
}

void increase_flag(struct process_info processes[], int len, int running_process_num, int arrival_time)
{
	for (int i = 0; i < len; i++)
	{
		if (processes[i].process_number != running_process_num && processes[i].arrival_time <= arrival_time && processes[i].completed != 1)
		{
			processes[i].flag += 1;
		}
	}
}

void check_completed(struct process_info processes[], int len){
	for (int i = 0; i < len; i++)
	{
		if (processes[i].burst_time == 0  && processes[i].completed != 1)
		{
			processes[i].completed = 1;
		}
	}
}

int number_of_process;
int total_cpu_time;

int main()
{
	freopen("in.txt", "r", stdin);

	struct process_info p_info[10];

	// printf("Enter Number of Process:");
	scanf("%d", &number_of_process);

	if (number_of_process > 10)
	{
		printf("Re-run the process with atmost 10 process only");
		return -1;
	}

	printf("\nEnter Burst Time, Arrival Time and Priority of processes\n");
	for (int i = 0; i < number_of_process; i++)
	{
		printf("\nP[%d]\n", (i + 1));
		printf("Enter Burst Time:");
		scanf("%d", &(p_info[i].burst_time));
		total_cpu_time += p_info[i].burst_time;
		printf("Enter Arrival Time:");
		scanf("%d", &(p_info[i].arrival_time));
		printf("Enter Priority:");
		scanf("%d", &(p_info[i].priority));
		p_info[i].process_number = i + 1;
		p_info[i].flag = 0;
		p_info[i].completed = 0;
	}

	for (int a = 0; a < total_cpu_time; a++)
	{

		sort_by_priority(p_info, number_of_process, a);
		p_info[0].burst_time -= 1;
		increase_flag(p_info, number_of_process, p_info[0].process_number, a);
		increase_priority(p_info, number_of_process, a);
		check_completed(p_info, number_of_process);
	}

	for (int i = 0; i < number_of_process; i++)
	{
		printf("%d\n", p_info[i].process_number);
	}
}