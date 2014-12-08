#pragma once
            
#define BLOCK_WIDTH           32
#define BLOCK_HEIGHT          32

#define PIECE_SIZE            4
#define SHAPE_SIZE            4
#define BOARD_WIDTH           10
#define BOARD_HEIGHT          20

#define FIELD_BOTTOM          0
#define FIELD_TOP             19
#define FIELD_LEFT_BOARD      0
#define FIELD_RIGHT_BOARD     9

#define LOCK_DELAY_TAG        1001


#define SPAWN_POINT           Point((BLOCK_WIDTH * BOARD_WIDTH)/2 - BLOCK_WIDTH * 2, BLOCK_HEIGHT * BOARD_HEIGHT - (BLOCK_HEIGHT * (PIECE_SIZE-2)))
#define PRE_POINT             Point((BLOCK_WIDTH * BOARD_WIDTH)/2 + BLOCK_WIDTH * 6, BLOCK_HEIGHT * BOARD_HEIGHT - (BLOCK_HEIGHT * PIECE_SIZE))
#define BOARD_AT              Point(544, 32)  //32*16 32*2  x= 16 y=2  anchor 0,0


typedef bool FieldOrTetro;
typedef bool OccupOrEmpty;

#define OCCUPIED true
#define EMPTY    false

#define PLAYFIELD true
#define TETROMINO false


typedef enum class game_state
{
	LOGO = 0,
	MENU,
	GAME,
	OVER
}GAME_STATE;

typedef enum class shape_state
{
	SHAPE_0 = 0,
	SHAPE_R,
	SHAPE_2,
	SHAPE_L
}SHAPE_STATE;

typedef enum class piece_type
{
	O = 0,
	I,
	J,
	L,
	Z,
	S,
	T,	      
	NOTHING //means this is for board
}TETROMINO_TYPE;

typedef enum class piece_state
{
	SHOW = 0,
	PRE,
	GHOST
}TETROMINO_STATE;


typedef struct 
{
	FieldOrTetro      _isFieldOrTetro;
	OccupOrEmpty      _isOccupOrEmpty;
	TETROMINO_TYPE    _tetroType;
	int               _coordinateX;
	int               _coordinateY;
	bool              _isGhost;

}BlockDef;

static int speedLevel = 0;  //静态全局 表示砖块下落速度等级