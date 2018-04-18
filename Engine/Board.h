#pragma once
#include "Tile.h"
#include "SpriteCodex.h"
#include <memory>

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
	void SpawnBombs( int amount );
	bool RevealTileAt( Vei2 mousepos );
	void FlagTileAt( Vei2 mousepos );



private:

	void CountBombs();

	Vei2& GridPosToScreenPos( Vei2& input ) const;
	Vei2& ScreenPosToGridPos( Vei2& input ) const;

	Vei2 boardPos = { 0, 0 };

	int width;
	int height;

	std::unique_ptr<RectI> pBg;

	std::unique_ptr<Tile[]> pTiles;

	Graphics& gfx;

};