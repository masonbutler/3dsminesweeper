#ifndef _GAME_H_
#define _GAME_H_
#include <citro2d.h>
#include "Cursor.h"
#include <memory>
#include "Board.h"

class Game
{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();

private:
    void Calculate3DOffset(float offset);

    C3D_RenderTarget *mLeftImage;
    C3D_RenderTarget *mRightImage;

    // TODO: Refactor this later
    int mEyeOffsetLeft[3], mEyeOffsetRight[3];

    C2D_SpriteSheet mSheet;
    C2D_Image mBackground;

    std::unique_ptr<Cursor> mCursor;
    std::unique_ptr<Board> mBoard;
};


#endif