#ifndef GAME_H_
#define GAME_H_

void game_play(void); //Infinite loop controlling the game until game over break.
void game_print_highscore( void );
void game_reset_highscore ( void );
void game_change_mode( int  );
void game_change_difficulty( int );

#endif