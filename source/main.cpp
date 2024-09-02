#include <citro2d.h>
#include "Common.h"
#include "Game.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
	Game game;

	while (aptMainLoop())
	{
		game.HandleInput();
		game.Update();
		game.Render();
	}

	return 0;
}