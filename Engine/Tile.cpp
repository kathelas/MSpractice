#include "Tile.h"
#include "SpriteCodex.h"

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
			SpriteCodex::DrawTileBomb;
		break;
	}
}

bool Tile::HasBomb()
{
	return hasBomb;
}

void Tile::SpawnBomb()
{
	hasBomb = true;
}
