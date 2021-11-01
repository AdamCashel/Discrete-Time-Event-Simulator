#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////////////////////////////////////////////////////////////
// sample events
#define EVENT1 1
#define EVENT2 2
// .. add more events

////////////////////////////////////////////////////////////////     
//event structure
struct event{
  float time;
  int   type;
  // add more fields
  int enter_time;
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

////////////////////////////////////////////////////////////////
//Global variables
struct event* head; // head of event queue
float clock; // simulation clock

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
		struct event* temp = head;
		while(temp->next != NULL)
		{

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
		process_event1(eve);
		break;
	case EVENT2:
		process_event2(eve);
		break;

	// add more events

	default:	
		// error 
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
  // parse arguments
  if(argc == 1){

  }
  //If algorithm_type == 1 run First Come First Serve , If algorithm_type == 2 run Shortest Remaining Time First, If algorithm_type == 3 run Round Robin with quantum value
  int algorithm_type = argv[1]

  init();
  run_sim(); 
  generate_report();
  return 0;
}
