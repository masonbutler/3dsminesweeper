#include "Board.h"
#include "Common.h"
#include <random>

Board::Board(int width, int height, int numMines) : mWidth(width), mHeight(height), mNumMines(numMines)
{
	mSheet = C2D_SpriteSheetLoad("romfs:/gfx/tiles.t3x");
	if (mSheet == nullptr)
    { 
	    svcBreak(USERBREAK_PANIC);
    }

	int numTilesInSheet = C2D_SpriteSheetCount(mSheet);

	for(int i = 0; i < numTilesInSheet; i++)
	{
		mTiles.push_back(C2D_SpriteSheetGetImage(mSheet, i));
	}

	mHorizontalOffset = (TOP_SCREEN_WIDTH_PIXELS / 2) - ((mWidth * TILE_SIZE) / 2);
	mVerticalOffset = (TOP_SCREEN_HEIGHT_PIXELS / 2) - ((mHeight * TILE_SIZE / 2));

	int totalTilesNum = mWidth * mHeight;
	for(int i = 0; i < totalTilesNum; i++)
	{
		mGameBoard.push_back(sTile{});
	}

	/* Limit number of mines so we don't have a board that is ridiculous.
	   This quantity is arbitarily decided to be half the board
	*/
	int maxMines = ( mWidth * mHeight ) / 2;
	if(mNumMines > maxMines)
	{
		mNumMines = maxMines;
	}
}

 Board::~Board()
 {
	C2D_SpriteSheetFree(mSheet);
 }

void Board::SetupBoard()
{
	// Set up tiles for the board
	for(int x = 0; x < mWidth; x++)
	{
		for(int y = 0; y < mHeight; y++)
		{
			mGameBoard[y * mWidth + x] = {
					.hasMine = false,
					.hidden = true,
					.flagged = false,
					.numMinesNear = 0,
				};
				
		}
	}

	// Place the mines
	for(int mines = mNumMines; mines > 0;)
	{
		int mineX = rand() % mWidth;
		int mineY = rand() % mHeight;

		if(!mGameBoard[mineY * mWidth + mineX].hasMine)
		{
			mGameBoard[mineY * mWidth + mineX].hasMine = true;
			mines--;
		}
	}

	/* Count mines near each tile and update the number so we can see have the 
	 * "mine count" for each tile with a num */
	for(int x = 0; x < mWidth; x++)
	{
		for(int y = 0; y < mHeight; y++)
		{
			if(!mGameBoard[y * mWidth + x].hasMine)
			{
				mGameBoard[y * mWidth + x].numMinesNear = CountNearbyMines(x, y);
			}
		}
	}
}

void Board::Render(float offsetLow, float offsetHigh)
{
	u32 col = C2D_Color32(0x5A, 0x69, 0x88, 0xFF);
	C2D_DrawRectSolid(mHorizontalOffset - 2 + offsetLow, mVerticalOffset -2, 0.0f, (mWidth * TILE_SIZE) + 4, (mHeight * TILE_SIZE) + 4, col);
	RenderTiles(offsetLow, offsetHigh);
}

void Board::RenderTiles(float offsetLow, float offsetHigh)
{
	for(int x = 0; x < mWidth; x++)
	{
		for(int y = 0; y < mHeight; y++)
		{
			RenderTile(&mGameBoard[y * mWidth + x], x, y, offsetLow, offsetHigh);
		}
	}
}

void Board::ShowTile(int x, int y)
{
	if(IsValidIndex(x, y))
	{
		if(!mGameBoard[y * mWidth + x].hidden || mGameBoard[y * mWidth + x].flagged)
		{
			return;
		}

		mGameBoard[y * mWidth + x].hidden = false;

		if(mGameBoard[y * mWidth + x].hasMine)
		{
			// TODO: Game Over state
		}
		else
		{
			if(mGameBoard[y * mWidth + x].numMinesNear == 0)
			{
				ShowConnectedTiles(x, y);
			}

			// TODO: Win state
			/*if(alltilesrevaled >= ( mWidth * mHeight - minesLeft ))
			{
				//win condition
			}*/
		}
	}
}

void Board::SetFlag(int x, int y)
{
    if(IsValidIndex(x, y))
	{ 
		mGameBoard[y * mWidth + x].flagged = !mGameBoard[y * mWidth + x].flagged;
	}
}

int Board::CountNearbyMines(int x, int y)
{
	int count = 0;
	for(int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for(int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if(xOffset == 0 && yOffset == 0)
			{
				continue;
			}

			if(IsValidIndex(x + xOffset, y + yOffset))
			{
				if(mGameBoard[(y + yOffset) * mWidth + (x + xOffset) ].hasMine)
				{
					count++;
				}
			}
		}
	}

	return count;

}

bool Board::IsValidIndex(int x, int y)
{
	return ( x >= 0 && x < mWidth && y >= 0 && y < mHeight );
}

void Board::RenderTile(sTile *tile, int x, int y, float offsetLow, float offsetHigh)
{
	int tileIndex = 0;
	float offset = offsetHigh;
	if(!tile->hidden)
	{
		if(tile->hasMine)
		{
			tileIndex = 10;
			offset = offsetLow;
		}
		else
		{
			tileIndex = tile->numMinesNear + 1;
			offset = offsetLow;
		}
	}
	else if(tile->flagged)
	{
		tileIndex = 11;
		offset = offsetHigh;
	}
		
	C2D_DrawImageAt(mTiles[tileIndex], (x * TILE_SIZE) + mHorizontalOffset + offset, (y * TILE_SIZE) + mVerticalOffset, 0.0f);
}

void Board::ShowConnectedTiles(int x, int y)
{
	for(int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for(int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if(xOffset == 0 && yOffset == 0)
			{
				continue;
			}

			if(IsValidIndex(x + xOffset, y + yOffset))
			{
				ShowTile(x + xOffset, y + yOffset);
			}

		}
	}
}

float Board::GetHorizontalOffset()
{
	return mHorizontalOffset;
}

float Board::GetVerticalOffset()
{
	return mVerticalOffset;
}
