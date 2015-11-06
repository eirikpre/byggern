



int play_game( void )
{
	int score = 0;
	can_message_t message;
	
	
	while(1)
	{
		//Joystick
		joystick_msg.data[0] = get_position().x_pos;
		
		can_message_send(&joystick_msg);
			
		// Handle potential goals
		if (can_get_message(&message) == 1)
		{
			if(message.id == 'g'){
				score++;
			}
		}
			
	}
	return score;
}