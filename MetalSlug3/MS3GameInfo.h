#pragma once

#define MAX_LINE 1024
#define BLOCK_SPACING 0.6f
// define game object type
#define MARCO_OBJECT_TYPE 0
#define CCHOWMEIN_OBJECT_TYPE 1
#define CLOCUST_OBJECT_TYPE 2
#define FLY_KILLER_OBJECT_TYPE 3
#define HUGE_HERMIT_OBJECT_TYPE 4
#define REBEL_SOLIDER_OBJECT_TYPE 5
#define BLOCK_OBJECT_TYPE 100
#define STAIR_OBJECT_TYPE 90
#define PLATFORM_OBJECT_TYPE 80
#define CHANGECAM_OBJECT_TYPE 70
#define STAIR2_OBJECT_TYPE 91
#define PORTAL_OBJECT_TYPE 60
#define GUN_BULLET_OBJECT_TYPE 11
#define Game_Map_Animation_ObjectType 12
#define HELPER_OBJECT_TYPE 13
#define OHUMEIN_CONGA_OBJECT_TYPE 14
#define BOAT_OBJECT_TYPE 15
// define type object
#define GAME_MAP_OBJECT 1
#define GAME_ENIMIES_OBJECT 2

// define Game File section
#define GAME_FILE_SECTION_UNKNOWN 0
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2
// define Scene section
#define SCENE_SECTION_UNKNOWN 0
#define SCENE_SECTION_ASSETS 1
#define SCENE_SECTION_OBJECTS 2
#define SCENE_SECTION_MAP 3

//define Assets section
#define ASSET_SECTION_UNKNOWN 0
#define ASSET_SECTION_SPRITE 1
#define ASSET_SECTION_ANIMATION 2

//define GameObject informations

//Marco informations
#define Marco_Speed_X 0.15f;
#define Marco_Speed_Y 0.02f;
#define Gun_Bullet_Speed 0.5f;
#define Marco_Firing_Speed 100;
enum class CRebel_Solider_states
{
	IDLE,
	Drop_down,
	Dead_drop_down,
	Dead,
	Throw_bomb
};
enum class leg_states {
	stand,
	run,
};
enum class Body_states {
	IDLE,
	jumping,
	sitting,
	looking_up
};

enum class Weapon_State {
	IDLE,
	FIRING
};

//Chowmein informations
#define CChowmein_Speed_X 0.08f;
#define CChowmein_Speed_Y 0.03f;
#define CChowmein_Buble_Speed 0.03f;
enum class CChowmein_States {
	IDLE,
	Walk,
	MeleeAttack,
	RangeAttack,
	Dead
};

//Locust informations
enum class Locust_states {
	flying,
	attack,
	preattack,
	turn
};

//Flying killer informations
#define Flying_killer_jump 0.02f;
#define Flying_killer_speed 0.1f;
enum class Flying_killer_states
{
	jump,
	attack
};


//Huge hermit informations

enum class CHuge_Hermit_States
{
	IDLE,
	Walk,
	Run,
	Deploying,
	Deployed,
	UnDeploying,
	Cannon_firing,
	Firing,
	Dead
};

//rebel solider informations
//helper 1 informations
enum class CHelper_1_state
{
	catched,
	drop_items,
	release,
	walk
};

enum class COhumein_Conga_states
{
	walk,
	IDLE,
	Melee_Attack
};