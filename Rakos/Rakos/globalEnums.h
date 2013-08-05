#pragma once

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* I use an underscore to know I'm using a enum.						*
* Except for Direction enum, because allegro 5 uses _UP...			*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

enum GameState {
	_Tutorial
};

enum Direction {
	DOWN,
	LEFT,
	RIGHT,
	UP
};

enum LivingBeingType {
	_Player,
	_NPC,
	_Creature
};

enum TimerType {
	_RegularTimer,
	_MouseAnimTimer,
	_DrawTimer,
	_PlayerAnimTimer,
	_PortalAnimTimer
};

enum WeaponType {
	_None,
	_Knife
};