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

const unsigned int WINDOW_WIDTH = 1200; // window width
const unsigned int WINDOW_HEIGHT = 900; // window height