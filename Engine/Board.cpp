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
		nBombs = 15;
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

	pBg = std::make_unique<RectI>( boardPos, width * SpriteCodex::tileSize, height * SpriteCodex::tileSize );

	pTiles = std::make_unique<Tile[]>(width * height);

	SpawnBombs( nBombs );

	CountBombs();
}

void Board::Draw() const
{
	for( int i = pBg->left; i < pBg->right; i++ )
	{
		for( int j = pBg->top; j < pBg->bottom; j++ )
		{
			gfx.PutPixel( i, j, SpriteCodex::baseColor );
		}
	}

	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			Vei2 temp = { i, j };
			GridPosToScreenPos( temp );
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
		int temp = -1;
		do
		{
			temp = dist( rng );
		}
		while( pTiles[temp].HasBomb() );

		pTiles[temp].SpawnBomb();
	}

}

bool Board::RevealTileAt( Vei2 mousepos )
{
	ScreenPosToGridPos( mousepos );
	int pos = mousepos.y * width + mousepos.x;
	if( pTiles[pos].GetState() == Tile::State::Hidden )
	{
		pTiles[pos].Reveal();
		if( pTiles[pos].HasBomb() )
			return false;
		else if( pTiles[pos].GetCloseBombs() == 0 )
		{
			for( int x = -1; x <= 1; x++ )
			{
				for( int y = -1; y <= 1; y++ )
				{
					if( !(x == 0 && y == 0) )
					{
						Vei2 temp = mousepos;
						temp.x += x;
						temp.y += y;
						if( temp.x >= 0 && temp.y >= 0 && temp.x < width && temp.y < height )
						{
							GridPosToScreenPos( temp );
							RevealTileAt( temp );
						}
					}
				}
			}
			return true;
		}
		else
			return true;
	}
	else
	{
		return true;
	}
}

void Board::FlagTileAt( Vei2 mousepos )
{
	ScreenPosToGridPos( mousepos );
	int pos = mousepos.y * width + mousepos.x;
	if( pTiles[pos].GetState() == Tile::State::Hidden || pTiles[pos].GetState() == Tile::State::Flagged )
	{
		pTiles[pos].ToggleFlag();
	}
}

void Board::RevealAllBombs()
{
	for( int i = 0; i < width * height; i++ )
	{
		if( pTiles[i].HasBomb() )
		{
			if( pTiles[i].GetState() == Tile::State::Hidden )
				pTiles[i].Reveal();
			if( pTiles[i].GetState() == Tile::State::Flagged )
				pTiles[i].RevealFlag();
		}
	}
}

void Board::CountBombs()
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			int bombs = 0;

			auto count = [=, &bombs]( int a, int b ) {
				int temp = (j + a) * width + i + b;
				if( i + b < width && i + b >= 0 && j + a<height && j + a >= 0 )
				{
					if( pTiles[temp].HasBomb() )
					{
						bombs += 1;
					}
				}
			};

			for( int x = -1; x <= 1; x++ )
			{
				for( int y = -1; y <= 1; y++ )
				{
					count( x, y );
				}
			}

			assert( bombs >= 0 && bombs <= 8 );

			pTiles[j * width + i].SetCloseBombs( bombs );
		}
	}
}

Vei2& Board::GridPosToScreenPos( Vei2& input ) const
{
	input *= SpriteCodex::tileSize;
	input += boardPos;
	return input;
}

Vei2& Board::ScreenPosToGridPos( Vei2& input ) const
{
	input -= boardPos;
	input /= SpriteCodex::tileSize;
	return input;


}
