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
		Flagged
	};

public:
	void Draw( const Vei2& screenpos, Graphics& gfx );
	bool HasBomb();
	void SpawnBomb();
	void Reveal();
	const Tile::State GetState() const;

private:
	State state = State::Hidden;
	bool hasBomb = false;
};
