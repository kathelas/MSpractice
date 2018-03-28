#include "Tile.h"
#include "SpriteCodex.h"

void Tile::Draw( const Vei2& screenpos, Graphics& gfx )
{
	SpriteCodex::DrawTileButton( screenpos, gfx );
}
