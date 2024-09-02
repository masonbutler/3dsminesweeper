#include "Cursor.h"
#include "Common.h"

Cursor::Cursor(float x, float y, int horizOffset, int vertOffset, int boardWidth, int boardHeight) 
        :       mHorizontalOffset(horizOffset), mVerticalOffset(vertOffset), mBoardWidth(boardWidth), 
                mBoardHeight(boardHeight) 
{
    mSheet = C2D_SpriteSheetLoad("romfs:/gfx/cursor.t3x");
    C2D_SpriteFromSheet(&mSprite, mSheet, 0);

	if (mSheet == nullptr)
    { 
	    svcBreak(USERBREAK_PANIC);
    }

    SetPosition(x, y);
}

Cursor::~Cursor()
{
    C2D_SpriteSheetFree(mSheet);
}

void Cursor::Render(float offset)
{
    C2D_DrawImageAt(mSprite.image, mSprite.params.pos.x + offset, mSprite.params.pos.y, 0.0f);
}

void Cursor::SetPosition(float x, float y)
{
    mSprite.params.pos.x = x;
    mSprite.params.pos.y = y;
}

void Cursor::SetPositionRelative(float x, float y)
{
    float newX = mSprite.params.pos.x + x;
    float newY = mSprite.params.pos.y + y;


    if(newX > (mHorizontalOffset + mBoardWidth - TILE_SIZE))
    {
        mSprite.params.pos.x = mHorizontalOffset;
    }
    else if(newX < mHorizontalOffset)
    {
        mSprite.params.pos.x = mHorizontalOffset + mBoardWidth - TILE_SIZE;
    }
    else
    {
        mSprite.params.pos.x = newX;
    }

    if(newY > (mVerticalOffset + mBoardHeight - TILE_SIZE))
    {
        mSprite.params.pos.y = mVerticalOffset;
    }
    else if(newY < mVerticalOffset)
    {
        mSprite.params.pos.y = mVerticalOffset + mBoardHeight - TILE_SIZE;
    }
    else
    {
        mSprite.params.pos.y = newY;
    }
}

float Cursor::GetX()
{
    return mSprite.params.pos.x;
}

float Cursor::GetY()
{
    return mSprite.params.pos.y;
}