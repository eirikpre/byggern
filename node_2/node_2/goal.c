#include <stdlib.h>
#include "goal.h"
#include "driver/ADC.h"
#include "driver/can_com.h"

void check_and_report_goal( void ){
	int threshold = 10;
	static int recent_goal = 0;
	static int recent_goal_counter = 0;
	can_message_t goal_msg = {'g',0};
	
	if (recent_goal == 0)
	{
		goal_msg.data[0] = ADC_read();
		if(goal_msg.data[0] < threshold)
		{
			recent_goal = 1;
			can_message_send(&goal_msg);
		}
	}
	else
	{
		recent_goal_counter += 1;
		if (recent_goal_counter > 1000/40)
		{
			recent_goal_counter = 0;
			if (ADC_read() > threshold){
				recent_goal = 0;
			}
		}
	}
}