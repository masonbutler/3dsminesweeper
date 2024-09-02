#ifndef _BOARD_H_
#define _BOARD_H_
#include <citro2d.h>
#include <vector>

typedef struct
{
	bool hasMine;
	bool hidden;
	bool flagged;
	int numMinesNear;
} sTile;

class Board
{
public:
    Board(int width, int height, int numMines);
    ~Board();

    void SetupBoard();

	void Render(float offsetLow, float offsetHigh);

	void ShowTile(int x, int y);
	void SetFlag(int x, int y);

	float GetHorizontalOffset();
	float GetVerticalOffset();

private:
	int CountNearbyMines(int x, int y);
	bool IsValidIndex(int x, int y);
	void RenderTile(sTile *tile, int x, int y, float offsetLow, float offsetHigh);
	void ShowConnectedTiles(int x, int y);
	void RenderTiles(float offsetLow, float offsetHigh);


	std::vector<sTile> mGameBoard;
	int mWidth, mHeight;
	int mHorizontalOffset, mVerticalOffset;
	int mNumMines;

    std::vector<C2D_Image> mTiles;
    C2D_SpriteSheet mSheet;
};
#endif