#include "Tile.h"
#include "SpriteCodex.h"
#include <cassert>

void Tile::Draw( const Vei2& screenpos, Graphics& gfx ) const
{
	switch( state )
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton( screenpos, gfx );
		break;
	case State::Revealed:
		SpriteCodex::DrawTile0( screenpos, gfx );
		if( hasBomb )
		{
			SpriteCodex::DrawTileBomb( screenpos, gfx );
		}
		else if( closeBombs > 0 )
		{
			switch( closeBombs )
			{
			case 1:
				SpriteCodex::DrawTile1( screenpos, gfx );
				break;
			case 2:
				SpriteCodex::DrawTile2( screenpos, gfx );
				break;
			case 3:
				SpriteCodex::DrawTile3( screenpos, gfx );
				break;
			case 4:
				SpriteCodex::DrawTile4( screenpos, gfx );
				break;
			case 5:
				SpriteCodex::DrawTile5( screenpos, gfx );
				break;
			case 6:
				SpriteCodex::DrawTile6( screenpos, gfx );
				break;
			case 7:
				SpriteCodex::DrawTile7( screenpos, gfx );
				break;
			case 8:
				SpriteCodex::DrawTile8( screenpos, gfx );
				break;
			}
		}
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton( screenpos, gfx );
		SpriteCodex::DrawTileFlag( screenpos, gfx );
		break;
	case State::FlaggedRev:
		SpriteCodex::DrawTile0( screenpos, gfx );
		if( hasBomb )
		{
			SpriteCodex::DrawTileBomb( screenpos, gfx );
		}
		SpriteCodex::DrawTileFlag( screenpos, gfx );
		break;
	}
}

bool Tile::HasBomb() const
{
	return hasBomb;
}

void Tile::SpawnBomb()
{
	assert( !hasBomb );
	hasBomb = true;
}

void Tile::Reveal()
{
	assert( state == State::Hidden );
	state = State::Revealed;
}

void Tile::RevealFlag()
{
	assert( state == State::Flagged );
	state = State::FlaggedRev;
}

void Tile::ToggleFlag()
{
	assert( state == State::Hidden || state == State::Flagged );
	if( state == State::Hidden )
		state = State::Flagged;
	else
		state = State::Hidden;
}

const Tile::State Tile::GetState() const
{
	return state;
}

void Tile::SetCloseBombs( int nBombs )
{
	assert( closeBombs == -1 );
	assert( nBombs >= 0 && nBombs <= 8 );
	closeBombs = nBombs;
}

int Tile::GetCloseBombs() const
{
	return closeBombs;
}
