#pragma once

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* I use an underscore to know I'm using a enum.						*
* Except for Direction enum, because allegro 5 uses _UP...			*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

enum Language {
	_English,
	_Portuguese
};

enum GameState {
	_MainMenu,
	_Tutorial,
	_Rakos
};

enum Vocation {
	_NoVocation,
	_Mage,
	_Warrior
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
	_NoWeapon,
	_Knife,
	_Wand,
	_Sword
};

enum ShieldType {
	_NoShield,
	_WoodenShield
};