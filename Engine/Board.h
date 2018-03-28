#pragma once
#include "Tile.h"
#include "SpriteCodex.h"

class Board

{
public:
	enum class Size
	{
		Small,
		Medium,
		Big
	};

public:
	Board() = default;
	Board( Graphics& gfx, Size size );
	void Draw() const;



private:

	Vei2& GridPosToScreenPos( Vei2& input ) const;

	Vei2 boardPos = { 0, 0 };

	int width;
	int height;

	Tile* pTiles = nullptr;

	Graphics& gfx;

};