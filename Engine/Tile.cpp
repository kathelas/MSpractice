#include "Tile.h"
#include "SpriteCodex.h"
#include <cassert>

void Tile::Draw( const Vei2& screenpos, Graphics& gfx )
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
	}
}

bool Tile::HasBomb()
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

const Tile::State Tile::GetState() const
{
	return state;
}
