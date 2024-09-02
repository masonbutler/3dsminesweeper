#ifndef _CURSOR_H_
#define _CURSOR_H_
#include <citro2d.h>

class Cursor
{
public:
    Cursor(float x, float y, int horizOffset, int vertOffset, int boardWidth, int boardHeight);
    ~Cursor();

    void Render(float offset);

    void SetPosition(float x, float y);
    void SetPositionRelative(float x, float y);

    float GetX();
    float GetY();

private:
    C2D_Sprite mSprite;
    C2D_SpriteSheet mSheet;

    int mHorizontalOffset;
    int mVerticalOffset;

    int mBoardWidth;
    int mBoardHeight;
};


#endif