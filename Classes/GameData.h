#pragma once
            
#define BLOCK_WIDTH           32
#define BLOCK_HEIGHT          32

#define PIECE_SIZE            4

#define BOARD_WIDTH           10
#define BOARD_HEIGHT          20


#define SPAWN_POINT           Point((BLOCK_WIDTH * BOARD_WIDTH)/2 - BLOCK_WIDTH * 2, BLOCK_HEIGHT * BOARD_HEIGHT - (BLOCK_HEIGHT * PIECE_SIZE))
#define BOARD_AT              Point(544, 64)  //32*16 32*2  x= 16 y=2  anchor 0,0
typedef enum class game_state
{
	LOGO = 0,
	MENU,
	GAME,
	OVER
}GAME_STATE;

typedef bool FieldOrTetro;
typedef bool OccupOrEmpty;

#define OCCUPIED true
#define EMPTY    false

#define PLAYFIELD true
#define TETROMINO false


typedef enum class piece_type
{
	O = 0,
	I,
	J,
	L,
	Z,
	S,
	T,
	NOTHING      //means this is for board
}TETROMINO_TYPE;



typedef struct 
{
	FieldOrTetro      _isFieldOrTetro;
	OccupOrEmpty      _isOccupOrEmpty;
	TETROMINO_TYPE    _tetroType;
	int               _coordinateX;
	int               _coordinateY;

}BlockDef;

