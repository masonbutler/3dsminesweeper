#include "Game.h"
#include "Common.h"
#include <time.h>

Game::Game()
{	
	srand(time(NULL));
    romfsInit();
	gfxInitDefault();
	gfxSet3D(true);
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
	mLeftImage = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	mRightImage = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);


	mSheet = C2D_SpriteSheetLoad("romfs:/gfx/bg.t3x");
	if (mSheet == nullptr)
    { 
	    svcBreak(USERBREAK_PANIC);
    }

	mBackground = C2D_SpriteSheetGetImage(mSheet, 0);

	int boardWidth = 20;
	int boardHeight = 14;

	mBoard = std::make_unique<Board>(boardWidth, boardHeight, 24);
	
	int horizontalOffset = mBoard->GetHorizontalOffset();
	int verticalOffset = mBoard->GetVerticalOffset();

    mCursor = std::make_unique<Cursor>(horizontalOffset + ((boardWidth / 2) * TILE_SIZE), 
										verticalOffset + ((boardHeight / 2) * TILE_SIZE), 
										horizontalOffset, 
										verticalOffset, 
										boardWidth * TILE_SIZE, 
										boardHeight * TILE_SIZE);
	mBoard->SetupBoard();
}

Game::~Game()
{
	C2D_SpriteSheetFree(mSheet);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
}

 void Game::HandleInput()
 {
    hidScanInput();
    unsigned int keysPressed = hidKeysDown();
	float sliderValue = osGet3DSliderState();

	// Exit back to HB menu
    if (keysPressed & KEY_START) 
    {
        return;
    }

	if(keysPressed & KEY_UP)
	{
		mCursor->SetPositionRelative(0.0f, -TILE_SIZE);
	}
	else if(keysPressed & KEY_DOWN)
	{
		mCursor->SetPositionRelative(0.0f, TILE_SIZE);
	}
	else if(keysPressed & KEY_RIGHT)
	{
		mCursor->SetPositionRelative(TILE_SIZE, 0.0f);
	}
	else if(keysPressed & KEY_LEFT)
	{
		mCursor->SetPositionRelative(-TILE_SIZE, 0.0f);
	}
	else if(keysPressed & KEY_A)
	{
		int indexX = (mCursor->GetX() - mBoard->GetHorizontalOffset()) / TILE_SIZE;
		int indexY = (mCursor->GetY() - mBoard->GetVerticalOffset()) / TILE_SIZE;
		mBoard->ShowTile(indexX, indexY);
	}
	else if(keysPressed & KEY_B)
	{
		int indexX = (mCursor->GetX() - mBoard->GetHorizontalOffset()) / TILE_SIZE;
		int indexY = (mCursor->GetY() - mBoard->GetVerticalOffset()) / TILE_SIZE;
		mBoard->SetFlag(indexX, indexY);
	}
	else if(keysPressed & KEY_SELECT)
	{
		mBoard->SetupBoard();
	}

	Calculate3DOffset(sliderValue);
 }

 void Game::Update()
 {

 }

 void Game::Render()
 {
	printf("\x1b[0;0H\n3DS Minesweeper v0.1 by Mason Butler\n\nControls:\nA - Reveal Tile\nB - Set Flag\nSELECT - Reset board\n");

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

	// Render image for left eye
	{
		C2D_TargetClear(mLeftImage, C2D_Color32(0xff, 0xff, 0xff, 0xff));
		C2D_SceneBegin(mLeftImage);

		C2D_DrawImageAt(mBackground, 0.0f, 0.0f, 0.0f, nullptr, 2.0f, 2.0f);
		mBoard->Render(mEyeOffsetLeft[OFFSET_FG_3D], mEyeOffsetLeft[OFFSET_TILE_3D]);
        mCursor->Render(mEyeOffsetLeft[OFFSET_BG_3D]);	
	}

	// Render image for right eye
	{
		C2D_TargetClear(mRightImage, C2D_Color32(0xff, 0xff, 0xff, 0xff));
		C2D_SceneBegin(mRightImage);

		C2D_DrawImageAt(mBackground, 0.0f, 0.0f, 0.0f, nullptr, 2.0f, 2.0f);
		mBoard->Render(mEyeOffsetRight[OFFSET_FG_3D], mEyeOffsetRight[OFFSET_TILE_3D]);
        mCursor->Render(mEyeOffsetRight[OFFSET_BG_3D]);	
	}

    C3D_FrameEnd(0);
 }

 void Game::Calculate3DOffset(float offset)
 {
	// TODO: Do this better
	mEyeOffsetLeft[OFFSET_FG_3D] = (-(OFFSET_DISTANCE_3D + 2)) * offset;
	mEyeOffsetRight[OFFSET_FG_3D] = (OFFSET_DISTANCE_3D + 2) * offset;

	mEyeOffsetLeft[OFFSET_TILE_3D] = (-(OFFSET_DISTANCE_3D + 1)) * offset;
	mEyeOffsetRight[OFFSET_TILE_3D] = (OFFSET_DISTANCE_3D + 1) * offset;

	mEyeOffsetLeft[OFFSET_BG_3D] = (-OFFSET_DISTANCE_3D) * offset;
	mEyeOffsetRight[OFFSET_BG_3D] = (OFFSET_DISTANCE_3D) * offset;
 }