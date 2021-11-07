#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////////////////////////////////////////////////////////////
// sample events
//Events are used to change the State(the amount of processes in the Ready Queue)
#define EVENT1 1 //Process Arrival
#define EVENT2 2 //Process Completion
#define EVENT3 3 //Time-Slice Occurance
// .. add more events

////////////////////////////////////////////////////////////////     
//event structure
struct event{
  float time; //service time
  int   type;
  // add more fields
  float enter_time; //arrival time
  struct event* next;
};

////////////////////////////////////////////////////////////////
// function definition
void init();
int run_sim();
void generate_report();
int schedule_event(struct event*);
int process_event1(struct event* eve);
int process_event2(struct event* eve);
void FCFS();
void SRTF();
void RR(int);

////////////////////////////////////////////////////////////////
//Global variables
struct event* head; // head of event queue
struct event* readyque_head;
float clock; // simulation clock
float process_lamda;
float average_arrival;
float quantum_number;
int algorithm_type;
bool server_idle;
int readyque_count = 0;
////////////////////////////////////////////////////////////////
//FCFC
void FCFS()
{
	//Keep track of top node in ready queue
	struct event* top = readyque_head;
	

}

////////////////////////////////////////////////////////////////
//SRTF
void SRTF()
{

}

////////////////////////////////////////////////////////////////
//RR
void RR(int quantum_number)
{

}

////////////////////////////////////////////////////////////////
//
int process_event1(eve)
{
	if(server_idle == true)
	{
		server_idle = false;
		//schedule event
	}
	else
	{
		readque_count++;
	}
	//scehdule event
}

////////////////////////////////////////////////////////////////
//
int process_event2(eve)
{

}

////////////////////////////////////////////////////////////////
//
int process_event3(eve)
{

}

////////////////////////////////////////////////////////////////
//
int process_event4(eve)
{
	if(readyque_count == 0)
	{
		server_idle = true;
	}
	else
	{
		readyque_count--;
		//schedule event
	}
}

////////////////////////////////////////////////////////////////
void init()
{
	// initialize all varilables, states, and end conditions
	// schedule first events
	bool server_idle = false;
	clock = 0;
	int state = 0;
	head->time = 0;
	head->next = NULL;

	/*Generate over 10,000 process based on the average arrival time and average service time and if RR 
	quantum number but will stop after 10,000 processes have been served by the given alogrithm */
	for(int i = 0; i < 10000; i++)
	{
		struct event* temp;
		temp->enter_time = genexp(average_arrival);
		temp->time = genexp(process_lamda);
		temp->type = 
		//Put process into event queue through scedule_event function
		schedule_event(temp);
	}


}
////////////////////////////////////////////////////////////////
void generate_report()
{
	// output statistics
}
//////////////////////////////////////////////////////////////// 
//schedules an event in the future
int schedule_event(struct event* new)
{
	// insert event in the event queue in its order of time
	//Check if theres an event after the event queue head node, if not place event after head node
	//If there is a node then place the node based on the time
	if(head->next == NULL)
	{
		head->next = new;
	}
	else
	{
		//Place the input event based on the enter_time of the even in the orgainized queue based on enter_time
		struct event* current_node = head;
		struct event* previous_node = head;
		bool found = true;

		while(current_node->next != NULL && found != false)
		{
			//Deal with condition of the node belongs to first node
			previous_node = head;
			current_node = current_node->next;

			if(current_node->enter_time >= new->enter_time)
			{
				previous_node->next = new;
				new->next = current_node;
				found = false;
			}
		}
	}
}
////////////////////////////////////////////////////////////////
// returns a random number between 0 and 1
float urand()
{
	return( (float) rand()/RAND_MAX );
}
/////////////////////////////////////////////////////////////
// returns a random number that follows an exp distribution
float genexp(float lambda)
{
	float u,x;
	x = 0;
	while (x == 0)
		{
			u = urand();
			x = (-1/lambda)*log(u);
		}
	return(x);
}
////////////////////////////////////////////////////////////
int run_sim()
{
  struct event* eve;
  while (!end_condition)
    {
      eve = head;
      clock = eve->time;
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
	case EVENT4:
		process_event4(eve); //process leaves event
	// add more events

	default:	
		// error 
		std:cout << "Error" << std:endl;
	}

      head = eve->next;
      free(eve);
      eve = NULL;
    }
  return 0;
}
////////////////////////////////////////////////////////////////
int main(int argc, char *argv[] )
{
  //First Argument: scheduling algorithm number (1 to 3)
  //Second Argument: number of processes per second as the arrival rate, lamda
  //Third Argument: the average burst time for processes
  //Fourth Argument: quantum value (used for RR only)
  //parse arguments
  //If algorithm_type == 1 run First Come First Serve , If algorithm_type == 2 run Shortest Remaining Time First, If algorithm_type == 3 run Round Robin with quantum value

  algorithm_type = argv[1];
  process_lamda = argv[2];
  average_arrival = argv[3];

  if(argc == 4)
  {
	quantum_number = argv[4];
  }
  
  init();
  run_sim(); 
  generate_report();
  return 0;
}
