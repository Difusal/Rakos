#pragma once

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* I use an underscore to know I'm using a enum.						*
* Except for Direction enum, because allegro 5 uses _UP...			*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

enum GameState {
	_Tutorial
};

enum Alignment {
	_Center,
	_Bottom
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
	_PlayerMoveTimer,
	_NPCMoveTimer,
	_SlowCreatureMoveTimer,
	_MouseAnimTimer,
	_DrawTimer,
	_PlayerAnimTimer,
	_WeaponAnimTimer,
	_PortalAnimTimer
};

enum WeaponType {
	_None,
	_Knife
};