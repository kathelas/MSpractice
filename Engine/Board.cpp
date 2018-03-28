#include "Board.h"
#include <random>
#include <cassert>

Board::Board( Graphics& gfx, Size size )
	:
	gfx ( gfx )
{
	int nBombs;

	switch( size )
	{
	case Size::Small:
		width = 10;
		height = 8;
		nBombs = 20;
		break;
	case Size::Medium:
		width = 20;
		height = 16;
		nBombs = 40;
		break;
	case Size::Big:
		width = 40;
		height = 32;
		nBombs = 80;
		break;
	}

	pTiles = new Tile[width * height];

	SpawnBombs( nBombs );
}

Board::~Board()
{
	delete[] pTiles;
	pTiles = nullptr;
}

void Board::Draw() const
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			Vei2 temp = { i, j };
			GridPosToScreenPos( temp );
			temp += boardPos;
			pTiles[j * width + i].Draw( temp, gfx );
		}
	}
	
}

void Board::SpawnBombs( int amount )
{
	assert( amount > 0 && amount < width * height - 1 );

	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<int> dist( 0, width * height - 1 );

	for( int count = 0; count < amount; count++ )
	{
		int temp;
		do
		{
			temp = dist( rng );
		}
		while( pTiles[temp].HasBomb() );

		pTiles[temp].SpawnBomb();
	}

}

Vei2& Board::GridPosToScreenPos( Vei2& input ) const
{
	input *= SpriteCodex::tileSize;
	return input;
}
