#pragma once
#include "Graphics.h"
#include "Vei2.h"

class Tile
{
public:
	enum class State
	{
		Hidden,
		Revealed,
		Flagged,
		FlaggedRev
	};

public:
	void Draw( const Vei2& screenpos, Graphics& gfx ) const;
	bool HasBomb() const;
	void SpawnBomb();
	void Reveal();
	void RevealFlag();
	void ToggleFlag();
	const Tile::State GetState() const;
	void SetCloseBombs( int nBombs );
	int GetCloseBombs() const;

private:
	State state = State::Hidden;
	bool hasBomb = false;
	int closeBombs = -1;
};
