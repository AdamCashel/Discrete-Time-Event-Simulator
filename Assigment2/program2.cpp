#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>   
#include <iostream>

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
void schedule_event(struct event*);
void process_event1(struct event* eve);
void process_event2(struct event* eve);
void process_event3(struct event* eve);
void process_event4(struct event* eve);
void FCFS();
void SRTF();
void RR(int);

////////////////////////////////////////////////////////////////
//Global variables
struct event* head = new event;// head of event queue
struct event* readyque_head;
float clock1; // simulation clock
float process_lamda;
float average_arrival;
float quantum_number;
float Total_turnaround = 0;
int algorithm_type;
bool server_idle; //replace with using process* server pointing to the process being serviced, NULL indicates idle
int readyque_count = 0; //Replace with FIFO queue (or more general, a priority queue) of processes (pointers to processes)

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
	new_event->enter_time = (current_event->enter_time) + (current_event->time);
	new_event->type = 2;
	schedule_event(new_event);
}

////////////////////////////////////////////////////////////////
//SRTF
void SRTF()
{
	//Rearrange ready queue list every interation from least remaining time to most remaining time 

}

////////////////////////////////////////////////////////////////
//RR
void RR(int quantum_number)
{

}

////////////////////////////////////////////////////////////////
//Arrival Event
void process_event1(struct event* eve)
{
	if (algorithm_type == 1)
	{
		FCFS(eve);
	}

}

////////////////////////////////////////////////////////////////
//process completion
void process_event2(struct event* eve)
{
	//collect data
	Total_turnaround += (clock1 - eve->enter_time);
	std::cout << "Total Check: " << clock1 << " " << eve->enter_time << std::endl;
}

////////////////////////////////////////////////////////////////
//
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
	head->enter_time = 0;
	//std::cout << "start of init" << std::endl;
	bool server_idle = false;
	clock1 = 0;
	//std::cout << "start of init5" << std::endl;
	int state = 0;
	srand(time(NULL));
	/*Generate over 10,000 process based on the average arrival time and average service time and if RR
	quantum number but will stop after 10,000 processes have been served by the given alogrithm */
	for (int i = 0; i < 10000; i++)
	{
		//std::cout << "start of init2" << std::endl;
		//Make new process
		process* process_temp = new process;
		//process_temp->arrivalTime =
		//std::cout << "start of init222" << std::endl;
		process_temp->id = rand() % 900000 + 1;
		//std::cout << "start of init2333" << std::endl;
		process_temp->remainingServiceTime = process_temp->arrivalTime;
		process_temp->serviceTime = 0;
		process_temp->priority = 0;

		//Make new event that has the arrival time of the process
		struct event* temp = new event;
		temp->enter_time = genexp(average_arrival);
		temp->time = genexp(process_lamda);
		temp->type = 1;
		temp->p = process_temp;
		//Put event into event queue through scedule_event function
		schedule_event(temp);
		//std::cout << "out of init2" << std::endl;
	}


	//Print linked list to check if in order of time
	/*struct event* temp4 = new event;
	temp4 = head;
	
	std::cout << "Before Check" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << temp4->enter_time << std::endl;
		temp4 = temp4->next;
	}
	std::cout << "After Check" << std::endl;

	//std::cout << "out of init1" << std::endl; */
}
////////////////////////////////////////////////////////////////
void generate_report()
{
	// output statistics
	float average_turnaround = 10000 / Total_turnaround;
	std::cout << "Average Turnaround: " << average_turnaround << std::endl;
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
	}
	else
	{
		//Place the input event based on the enter_time of the even in the orgainized queue based on enter_time
		struct event* current_node = head;
		struct event* previous_node = NULL;
		bool found = true;

		while (current_node != NULL && current_node->enter_time < new1->enter_time)
		{
			previous_node = current_node;
			current_node = current_node->next;
		}

		if (previous_node == NULL)
		{
			head = new1;
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
			std::cout << "Error" << std::endl;
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
	algorithm_type = atoi(argv[1]);
	process_lamda = atoi(argv[2]);
	average_arrival = atoi(argv[3]);

	if (argc == 5)
	{
		quantum_number = atoi(argv[4]);
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
