#include "Board.h"

Board::Board( Graphics& gfx, Size size )
	:
	gfx ( gfx )
{
	switch( size )
	{
	case Size::Small:
		width = 10;
		height = 8;
		break;
	case Size::Medium:
		width = 20;
		height = 16;
		break;
	case Size::Big:
		width = 40;
		height = 32;
		break;
	}


	pTiles = new Tile[width * height];


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

Vei2& Board::GridPosToScreenPos( Vei2& input ) const
{
	input *= SpriteCodex::tileSize;
	return input;
}
