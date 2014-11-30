#pragma once
            
#define BLOCK_WIDTH           24

#define PIECE_WIDTH           4
#define PIECE_HEIGHT          4

#define BOARD_WIDTH           10
#define BOARD_HEIGHT          20

typedef enum class game_state
{
	LOGO = 0,
	MENU,
	GAME,
	OVER
}GAME_STATE;

typedef enum class piece_type
{
	O = 0,
	I,
	J,
	L,
	Z,
	S,
	T
}TETROMINO_TYPE;

typedef enum class is_block
{
	EMPTY = 0,
	BLOCK
}IS_BLOCK;

typedef struct 
{
	TETROMINO_TYPE _type;
	IS_BLOCK       _isBlock;
	int            _coordinateX;
	int            _coordinateY;

}BlockDef;

