/// <summary>
/// Leon Nolte
/// C00263935
/// 06 March 2022
/// Est. time: 20 hours
/// Session 1: 16:45 - 18:00 (06/03/22)
/// Session 2: 21:30 - 22:15 (06/03/22)
/// Session 3: 9:15 - 10:55 (07/03/22)
/// Session 4: 10:00 - 11:55 (09/03/22)
/// Session 5: 20:00 -22:40 (09/03/22)
/// Session 6: 10:15 - 10:50 (10/03/22)
/// Session 7: 10:05 - 10:50 (14/03/22)
/// Session 8: 9:30 - 10:55 (16/03/22)
/// Session 9: 17:30 - 20:15 (19/03/22)
/// Session 10: 13:15 - 16:15 (20/03/22)
/// Session 11: 9:30 - 10:45 (21/03/22)
/// Session 12: 9:40 - 11:00 (23/03/22)
/// Session 13: 16:00 - 17:15 (23/03/22)
/// Session 14: 13:30 - 13:55 (24/03/22)
/// Session 15: 12:00 - 13:00 (27/03/22)
/// Session 16: 16:10 - 19:15 (27/03/22) (includes 45 minute break)
/// Session 17: 9:30 - 10:55 (28/03/22)
/// Session 18: 9:45 - 10:55 (30/03/22)
/// -----------------------------------------------------------------------------
/// Simple game in which the player takes control over an archer, who is fending of waves of Kobolds.
/// Move using WASD, shoot by clicking the left mouse button.
/// There are two types of enemies: Kobold "Stabbers" and Kobold "Throwers." Stabbers approach the player in a zig-zag pattern and stab when close. 
/// Throwers run towards the player a bit, throw their Javelins, and then leave the battlefield. The player must survive three waves to win the game.
/// The player will receive a score based on how much health they have left, and how many Kobolds they killed.
/// For more details, see the Game Design Document.
/// -----------------------------------------------------------------------------
/// Known bugs: Kobolds can be knocked out of bound by player
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#include "Game.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>success or failure</returns>
int main()
{
	Game game;
	game.run();

	return 1; // success
}