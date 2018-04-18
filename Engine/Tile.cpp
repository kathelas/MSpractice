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
			SpriteCodex::DrawTileBomb( screenpos, gfx );
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton( screenpos, gfx );
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
	closeBombs = nBombs;
}
