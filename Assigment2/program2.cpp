#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>   
#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////////
// sample events
//Events are used to change the State(the amount of processes in the Ready Queue)
#define EVENT1 1 //Process Arrival
#define EVENT2 2 //Process Completion
#define EVENT3 3 //Time-Slice Occurance
// .. add more events

////////////////////////////////////////////////////////////////
// Process Structure
struct process {
	int id = 0;
	float arrivalTime = 0;
	float serviceTime = 0;
	float remainingServiceTime = 0;
	int priority = 0;
	//add more
};

////////////////////////////////////////////////////////////////     
//event structure
struct event {
	float time = 0; //service time
	int   type = 0;
	// add more fields
	float enter_time; //arrival time
	struct event* next = NULL;
	struct process* p = NULL;
};

////////////////////////////////////////////////////////////////
// function definition
void init();
int run_sim();
void generate_report();
void SRTF_Helper();
void schedule_readyQue(struct event* eve);
void schedule_event(struct event*);
void process_event1(struct event* eve);
void process_event2(struct event* eve);
void process_event3(struct event* eve);
void process_event4(struct event* eve);
void FCFS(struct event* current_event);
void SRTF(struct event* current_event);
void RR(struct event* current_event, float);

////////////////////////////////////////////////////////////////
//Global variables
struct event* head = new event;// head of event queue
struct event* readyque_head = new event; //head of ready queue
float clock1; // simulation clock
float process_lamda;
float average_arrival;
float quantum_number;
float Total_turnaround = 0;
float total_throughput = 0;
int algorithm_type;
bool server_idle; //replace with using process* server pointing to the process being serviced, NULL indicates idle
int readyque_count = 0; //Replace with FIFO queue (or more general, a priority queue) of processes (pointers to processes)
float total_time = 0;
//Alogrithms add events to the event queue

////////////////////////////////////////////////////////////////
//FCFC
void FCFS(struct event* current_event)
{
	//Keep track of top node in ready queue
	//struct event* top = readyque_head;

	/*struct process* current_process = new process;
	struct event* new_event = new event;
	current_process = current_event->p;
	new_event->enter_time = (current_event->enter_time) + (current_process->serviceTime);
	new_event->type = 2; //Event type is completion
	//Call schedule event and place the event into the event queue
	schedule_event(current_event); */

	//Add event at the point where the event is completed
	struct process* new_process = new process;
	//new_process->arrivalTime = current_event
	struct event* new_event = new event;
	new_event->enter_time = (current_event->enter_time) + (current_event->p->remainingServiceTime);
	new_event->type = 2;
	new_event->p = current_event->p;
	schedule_event(new_event);
}

////////////////////////////////////////////////////////////////
//SRTF
void SRTF(struct event* current_event)
{
	//Rearrange ready queue list every interation from least remaining time to most remaining time 
	struct process* new_process = new process;
	struct event* new_event = new event;

	new_event->enter_time = current_event->enter_time;
	new_event->p = current_event->p;
	new_event->time = current_event->time;
	new_event->next = NULL;
	new_event->type = 3;

	schedule_readyQue(new_event); //Function call to put even in order of time
	
	//Function call to run readyQue for X amount of time
	SRTF_Helper();


}

////////////////////////////////////////////////////////////////
//SRTF Helper to interate the SRFT in the ready queue for as along as the 
void SRTF_Helper()
{
	
	float past_clock = 0;
	float clock_runtime = 0;
	clock_runtime = clock1 - past_clock;
	if (readyque_head)
	{
		//run until there isnt a ready queue node or runtime is 0
		while (clock_runtime != 0 || readyque_head)
		{
			//Run while checking if the next node is smaller time than current node
			//Condtion if checking if node after is small than ready queue head
			if (readyque_head->next->p->remainingServiceTime < readyque_head->p->remainingServiceTime)
			{
				struct event* new_event = new event;
				new_event = readyque_head->next;
				schedule_event(new_event);
			}
			else
			{
				float time_sprint = 0; //The time different between the ready_que head node and the node after to get the sprint time 
				time_sprint = (readyque_head->p->remainingServiceTime) - (readyque_head->next->p->remainingServiceTime);
				readyque_head->p->remainingServiceTime = (readyque_head->p->remainingServiceTime) - time_sprint;
				struct event* temp1_event = new event;
				temp1_event = readyque_head;
				readyque_head = readyque_head->next;
				free(temp1_event); //delete eve
				temp1_event = NULL;
			}
			
		}
	}
	else
	{
		std::cout << "readyqueue head empty" << std::endl;
	}
	past_clock = clock1;
}

////////////////////////////////////////////////////////////////
//RR
void RR(struct event* current_event, float quantum_number)
{

	struct process* new_process = new process;
	struct event* new_event = new event;



	//Have 2 Conditions
	//(1) If Remaning burst time is less than or equal to quantum number scehdule completion event
	//(2) Else remaining time is greater than qunatum number than subtract remaining time and
	if (current_event->p->remainingServiceTime <= quantum_number)
	{
		new_event->p = current_event->p;
		new_event->enter_time = current_event->enter_time + (quantum_number - new_event->p->remainingServiceTime);
		new_event->type = 2;
		new_event->p->remainingServiceTime = 0;
	}
	else
	{
		new_event->enter_time = current_event->enter_time + quantum_number;
		new_event->p = current_event->p;
		new_event->type = 1;
		new_event->p->remainingServiceTime = new_event->p->remainingServiceTime - quantum_number;
	}


	schedule_event(new_event);
}

////////////////////////////////////////////////////////////////
//Arrival Event
void process_event1(struct event* eve)
{
	if (algorithm_type == 1)
	{
		FCFS(eve);
	}
	if (algorithm_type == 3)
	{
		RR(eve, quantum_number);
	}
	if (algorithm_type == 2)
	{
		SRTF(eve);
	}
}

////////////////////////////////////////////////////////////////
//process completion
void process_event2(struct event* eve)
{
	
	if ((algorithm_type == 1) || (algorithm_type == 3))
	{
		//collect data
		Total_turnaround += (clock1 - eve->p->arrivalTime);
		//std::cout << "Total Check: " << clock1 << " " << eve->enter_time << std::endl;

		if (head->next == NULL)
		{
			float total_time = eve->enter_time;
			//std::cout << "Here: " << total_time << std::endl;
			total_throughput = 10000 / total_time;
		}
	}
	if (algorithm_type == 2)
	{
		//collect data
		Total_turnaround += (clock1 - eve->p->arrivalTime);

		if (readyque_head->next == NULL)
		{
			float total_time2 = eve->enter_time;
			//std::cout << "Here: " << total_time2 << std::endl;
			total_throughput = 10000 / total_time2;
		}
	}
}

////////////////////////////////////////////////////////////////
//Put events that are of type 1 into ready queue
void process_event3(struct event* eve)
{
	
}

////////////////////////////////////////////////////////////////
//
void process_event4(struct event* eve)
{

}

////////////////////////////////////////////////////////////////
// returns a random number between 0 and 1
float urand()
{
	return((float)rand() / RAND_MAX);
}

/////////////////////////////////////////////////////////////
// returns a random number that follows an exp distribution
float genexp(float lambda)
{
	float u, x;
	x = 0;
	while (x == 0)
	{
		u = urand();
		x = (-1 / lambda) * log(u);
	}
	return(x);
}

////////////////////////////////////////////////////////////////
void init()
{

	// initialize all varilables, states, and end conditions
	// schedule first events
	//head->enter_time = 0;
	//std::cout << "start of init" << std::endl;
	head = NULL;
	bool server_idle = false;
	clock1 = 0;
	//std::cout << "start of init5" << std::endl;
	int state = 0;
	srand(time(NULL));
	/*Generate over 10,000 process based on the average arrival time and average service time and if RR
	quantum number but will stop after 10,000 processes have been served by the given alogrithm */
	for (int i = 0; i < 10000; i++)
	{

		process* process_temp = new process;

		process_temp->id = i + 1;


		process_temp->serviceTime = 0;
		process_temp->priority = 0;


		struct event* temp = new event;
		temp->enter_time = genexp(average_arrival);

		process_temp->arrivalTime = temp->enter_time;
		temp->time = genexp(process_lamda);
		process_temp->remainingServiceTime = temp->time;
		temp->type = 1;
		temp->p = process_temp;

		schedule_event(temp);

	}


	//Print linked list to check if in order of time
	/*struct event* temp4 = new event;
	temp4 = head;

	std::cout << "Before Check" << std::endl;
	for (int i = 0; i < 10000; i++)
	{
		std::cout << temp4->enter_time << std::endl;
		temp4 = temp4->next;
	}
	std::cout << "After Check" << std::endl; */

	//std::cout << "out of init1" << std::endl; 
}
////////////////////////////////////////////////////////////////
void generate_report()
{
	// output statistics
	float average_turnaround = 10000 / Total_turnaround;
	total_throughput = 10000 / total_time;
	std::cout << "Average Turnaround: " << average_turnaround << std::endl;
	std::cout << "Total Throughput: " << total_throughput << std::endl;

	std::ofstream report_file;
	report_file.open("report.csv", std::ofstream::app);
	report_file << process_lamda << ", " << average_turnaround << ", " << total_throughput << std::endl;
	report_file.close();
}
//////////////////////////////////////////////////////////////// 
//schedules an event in the future
void schedule_event(struct event* new1)
{
	// insert event in the event queue in its order of time
	//Check if theres an event after the event queue head node, if not place event after head node
	//If there is a node then place the node based on the time
	if (head == NULL)
	{
		head = new1;
		head->enter_time = clock1;
	}
	else
	{
		//Place the input event based on the enter_time of the even in the orgainized queue based on enter_time
		struct event* current_node = head->next;
		struct event* previous_node = head;
		bool found = true;

		while (current_node != NULL && current_node->enter_time < new1->enter_time)
		{
			previous_node = current_node;
			current_node = current_node->next;
		}

		if (current_node == NULL)
		{
			if (previous_node->enter_time > new1->enter_time)
			{
				new1->next = previous_node;
				previous_node->next = NULL;
			}
			else
			{
				previous_node->next = new1;
			}
		}
		else
		{
			previous_node->next = new1;
			new1->next = current_node;
		}

	}
}

//////////////////////////////////////////////////////////////// 
//schedules an event in the future
void schedule_readyQue(struct event* new1)
{
	// insert event in the ready queue in its order of time
	//Check if theres an event after the event queue head node, if not place event after head node
	//If there is a node then place the node based on the time
	if (readyque_head == NULL)
	{
		readyque_head = new1;
	}
	else
	{
		//Place the input event based on the enter_time of the even in the orgainized queue based on enter_time
		struct event* current_node = readyque_head;
		struct event* previous_node = NULL;
		bool found = true;

		while (current_node != NULL && current_node->p->remainingServiceTime < new1->p->remainingServiceTime)
		{
			previous_node = current_node;
			current_node = current_node->next;
		}

		if (previous_node == NULL)
		{
			readyque_head = new1;
			new1->next = current_node;
		}
		else
		{
			previous_node->next = new1;
			new1->next = current_node;
		}

	}
}

////////////////////////////////////////////////////////////
int run_sim()
{

	struct event* eve;
	while (head)
	{
		eve = head;
		clock1 = eve->enter_time;
		total_time = clock1;
		switch (eve->type)
		{
		case EVENT1:
			process_event1(eve); //process arrival event
			break;
		case EVENT2:
			process_event2(eve); //process completion
			break;
		case EVENT3:
			process_event3(eve); //time-slice occurrence event
		// add more events

		default:
			// error 
			std::cout << "Error: unknown event type: " << eve->type << std::endl;
		}

		head = eve->next;
		free(eve); //delete eve
		eve = NULL;
	}
	return 0;
}
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	//First Argument: scheduling algorithm number (1 to 3)
	//Second Argument: number of processes per second as the arrival rate, lamda
	//Third Argument: the average burst time for processes
	//Fourth Argument: quantum value (used for RR only)
	//parse arguments
	//If algorithm_type == 1 run First Come First Serve , If algorithm_type == 2 run Shortest Remaining Time First, If algorithm_type == 3 run Round Robin with quantum value

	std::cout << "start" << std::endl;
	algorithm_type = atof(argv[1]);
	process_lamda = atof(argv[2]);
	average_arrival = atof(argv[3]);

	if (argc == 5)
	{
		quantum_number = atof(argv[4]);
	}

	init();
	std::cout << "end of init" << std::endl;
	std::cout << "start of sim" << std::endl;
	run_sim();
	std::cout << "end of sim" << std::endl;
	generate_report();
	std::cout << "end generate report" << std::endl;
	return 0;
}
