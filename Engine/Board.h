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
	~Board();
	void Draw() const;
	void SpawnBombs( int amount );



private:

	Vei2& GridPosToScreenPos( Vei2& input ) const;

	Vei2 boardPos = { 0, 0 };

	int width;
	int height;

	Tile* pTiles = nullptr;

	Graphics& gfx;

};