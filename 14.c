// Question Number: 14

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Please start reading program from the main function for better clarity and flow of execution.

// Structure to hold the different thimgs related to the single process.
struct process_info
{
	int process_number;
	int burst_time;
	int arrival_time;
	int priority;
	int flag;	  // To check whether process is waiting for 2 seconds when other process is running.
	int completed; // To check whether process has completed its burst time. 0 for false, 1 for true.
};

// Swapping the two processes, This helper function is used in sort_by_priority function.
void swap(struct process_info *a, struct process_info *b)
{
	struct process_info temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// It takes all the processes entered by the user, and sort them according to the priority. Sorting is done of only of the processes which arrived at that particular time. So if five processes are there in total and only two arrive at the particular time then these two processes will be sorted on the basis of priority and rest processes will be shifted after them according to their process number.
void sort_by_priority(struct process_info processes[], int len, int current_time)
{
	struct process_info curr_processes[10]; // Array to hold the processes that arrived at the current_time.
	int index[10];							// Array to hold the process_number of process that arrived at current_time.
	int j = 0;
	// Adding processes and index according to current_time.
	for (int i = 0; i < len; i++)
	{
		if (processes[i].arrival_time <= current_time && processes[i].completed != 1)
		{
			curr_processes[j] = processes[i];
			index[j++] = i;
		}
	}
	//Bubble sort to sort the processes
	for (int i = 0; i < j; i++)
	{
		for (int k = 1; k < j; k++)
		{
			// Sort by priority
			if (curr_processes[k].priority < curr_processes[k - 1].priority)
			{
				swap(&curr_processes[k], &curr_processes[k - 1]);
			}
			// Sort by process number, if priority is same.
			if (curr_processes[k].priority == curr_processes[k - 1].priority)
			{
				if (curr_processes[k].process_number < curr_processes[k - 1].process_number)
				{
					swap(&curr_processes[k], &curr_processes[k - 1]);
				}
			}
		}
	}

	// Adding the remaining processes from the parameter processes array to the current processes which are not arrived at the current_time, so processes array can be modified later on.
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
	// Copying the value from the curr_processes to processes so that we have updated value of processes in main function according to priority of processes and arrival time.
	for (int i = 0; i < len; i++)
		processes[i] = curr_processes[i];
}

// Increasing priority of the process if they are waiting for other process to complete.
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

// Increasing flag of the process if it is waiting for the other process to complete.
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

// To check whether the process is completed and make it completed if its burst time reduce to zero.
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

int number_of_process; // Total number of processes.
int total_cpu_time;	// Total burst time of all the processes.

int main()
{
	freopen("in.txt", "r", stdin);

	struct process_info p_info[10]; // Array of all the proceeses. For convention I have taken maximum number of processes as 10.

	printf("Enter Number of Process:");
	scanf("%d", &number_of_process);

	if (number_of_process > 10)
	{
		printf("Re-run the program with atmost 10 process only");
		return -1;
	}

	printf("\nEnter Burst Time, Arrival Time and Priority of processes\n");
	// Taking input in p_info array.
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
		// Assigining process_number, flag and completed to each process.
		p_info[i].process_number = i + 1;
		p_info[i].flag = 0;
		p_info[i].completed = 0;
	}
	int gantt_chart[100]; // Array to calculate gantt chart of processes. Its size cis equal to total_cpu_time but I have assumed it to 100.

	int waiting_time[11];				// Array which wil hold waiting time of processes.
	int number_of_premptions[11];	 // Array to hold, how many times a particular process preempts.
	int local_burst_time[11] = {0};   // Array to hold, burst time of all processes.
	int local_arrival_time[11] = {0}; // Array to hold, arrival time of all processes.
	int turn_around_time[11] = {0};   // Array to hold, turn around time of all processes.

	printf("\n\n Gantt Chart \n");
	// Running the CPU for total_cpu_time and calling the necessary functions to design the scenario.
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

	// Storing the arrival time of processes.
	for (int i = 0; i < number_of_process; i++)
	{
		local_arrival_time[p_info[i].process_number] = p_info[i].arrival_time;
	}

	// Storing the burst time of all the processes.
	for (int i = 0; i < total_cpu_time; i++)
	{
		local_burst_time[gantt_chart[i]]++;
	}

	// Calculating the waiting time of each process from the gantt chart.
	for (int i = 1; i <= number_of_process; i++)
	{
		int counter = 0;
		waiting_time[i] = 0;
		number_of_premptions[i] = 0;
		for (int j = 0; j < total_cpu_time; j++)
		{
			// If J  process doesn't  matches in gantt chart with I, increase waiting time.
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

	// Calculating the number of pre-emptions in each process to tackle time wasted in context switching.
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
	// Calculating final waiting time of process by subtracting arrival time, and also calculating total waiting and turn around time.
	for (int i = 0; i < number_of_process; i++)
	{
		waiting_time[i + 1] -= local_arrival_time[i + 1];
		turn_around_time[i + 1] = waiting_time[i + 1] + local_burst_time[i + 1];
		total_waiting_time += waiting_time[i + 1];
		total_turn_around_time += turn_around_time[i + 1];
	}

	printf("\n");
	// Adding the time wasted in context switching.
	for (int i = 1; i <= number_of_process; i++)
	{
		waiting_time[i] += number_of_premptions[i] * 2;
		turn_around_time[i] += number_of_premptions[i] * 2;
		total_waiting_time += number_of_premptions[i] * 2;
		total_turn_around_time += number_of_premptions[i] * 2;
	}

	// Printing Everything.
	double avg_waiting_time = total_waiting_time / (float)number_of_process;
	double avg_turn_around_time = total_turn_around_time / (float)number_of_process;

	printf("\nProcess_Number \t Waiting Time \t Turn Around Time");
	for (int i = 1; i <= number_of_process; i++)
	{
		printf("\n%d \t\t %d \t\t %d", i, waiting_time[i], turn_around_time[i]);
	}
	printf("\n---------------------------");
	printf("\nAverage waiting time: %f", avg_waiting_time);
	printf("\nAverage turn around time: %f", avg_turn_around_time);
}