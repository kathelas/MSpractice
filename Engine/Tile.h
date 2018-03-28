#pragma once
#include "Graphics.h"
#include "Vei2.h"

class Tile
{
public:
	void Draw( const Vei2& screenpos, Graphics& gfx );
	bool HasBomb();
	void SpawnBomb();

private:
	enum class State
	{
		Hidden,
		Revealed,
		Flagged
	};


	State state = State::Hidden;
	bool hasBomb = false;
};
