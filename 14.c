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

void check_completed(struct process_info processes[], int len)
{
	for (int i = 0; i < len; i++)
	{
		if (processes[i].burst_time == 0 && processes[i].completed != 1)
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

	printf("Enter Number of Process:");
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
	int gantt_chart[100];
	// int inserter = 0;
	int waiting_time[11];
	// int turn_around_time[11];
	int number_of_premptions[11];
	int local_burst_time[11] = {0};
	int local_arrival_time[11] = {0};
	int turn_around_time[11] = {0};

	for (int a = 0; a < total_cpu_time; a++)
	{

		sort_by_priority(p_info, number_of_process, a);
		p_info[0].burst_time -= 1;
		printf("%d ", p_info[0].process_number); // printing gantt chart
		gantt_chart[a] = p_info[0].process_number;
		increase_flag(p_info, number_of_process, p_info[0].process_number, a);
		increase_priority(p_info, number_of_process, a);
		check_completed(p_info, number_of_process);
	}

	for (int i = 0; i < number_of_process; i++)
	{
		local_arrival_time[p_info[i].process_number] = p_info[i].arrival_time;
	}

	for (int i = 0; i < total_cpu_time; i++)
	{
		local_burst_time[gantt_chart[i]]++;
	}

	for (int i = 1; i <= number_of_process; i++)
	{
		int counter = 0;
		waiting_time[i] = 0;
		turn_around_time[i] = 0;
		number_of_premptions[i] = 0;
		for (int j = 0; j < total_cpu_time; j++)
		{
			if (gantt_chart[j] != i)
			{
				if (counter <= local_burst_time[i])
				{
					waiting_time[i]++;
				}
			}
			else
			{
				counter++;
			}
			if (counter == local_burst_time[gantt_chart[j]])
			{
				break;
			}
		}
	}

	for (int i = 1; i <= number_of_process; i++)
	{
		int burst = 0;
		int counter = 0;
		for (int j = 0; j < total_cpu_time; j++)
		{
			if (gantt_chart[j] == i)
			{
				burst++;
				counter = 1;
			}
			else
			{
				if (counter == 1 && burst != local_burst_time[i])
				{
					number_of_premptions[i]++;
					counter = 0;
				}
			}
			if (counter == local_burst_time[gantt_chart[j]])
			{
				break;
			}
		}
	}

	int total_waiting_time = 0;
	int total_turn_around_time = 0;
	printf("\n");
	for (int i = 0; i < number_of_process; i++)
	{
		waiting_time[i + 1] -= local_arrival_time[i + 1];
		turn_around_time[i + 1] = waiting_time[i + 1] + local_burst_time[i + 1];
		total_waiting_time += waiting_time[i + 1];
		total_turn_around_time += turn_around_time[i + 1];
	}


	printf("\n");
	for (int i = 1; i <= number_of_process; i++)
	{
		waiting_time[i] += number_of_premptions[i] * 2;
		turn_around_time[i] += number_of_premptions[i] * 2;
		total_waiting_time += number_of_premptions[i] * 2;
		total_turn_around_time += number_of_premptions[i] * 2;
				// printf("%d ", waiting_time[i]);
		// printf("%d ", number_of_premptions[i]);
	}


	double avg_waiting_time = total_waiting_time / (float)number_of_process;
	double avg_turn_around_time = total_turn_around_time / (float)number_of_process;

	printf("\nProcess_Number \t Waiting Time \t Turn Around Time");
	for(int i = 1; i <= number_of_process; i++){
		printf("\n%d \t\t %d \t\t %d", i, waiting_time[i], turn_around_time[i]);
	}
	printf("\n---------------------------");
	printf("\nAverage waiting time: %f", avg_waiting_time);
	printf("\nAverage turn around time: %f", avg_turn_around_time);
}