/// <summary>
/// Globals
/// 
/// Includes enum class Status for enemy behavior
/// </summary>

#pragma once



enum class Status {
	fleeing, // default
	dead,
	entering,
	following,
};

enum class GameState {
	gameScreen,
	endScreen
};

const unsigned int WINDOW_WIDTH = 1200; // window width
const unsigned int WINDOW_HEIGHT = 900; // window height