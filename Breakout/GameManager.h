//
//  GameManager.h
//  SDLTut
//
//  Created by Dennis Hubley on 2020-01-15.
//  Copyright © 2020 triOS College. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h
#include <SDL.h>
#include "Timer.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "StartScreen.h"

#include "ScreenManager.h"

namespace SDLFramework {

class GameManager {
private:
    // singleton
    static GameManager * sInstance;
    // loop control
    bool mQuit;
    // modules
    Graphics * mGraphics;
    AssetManager* mAssetManager;

    InputManager* mInputManager;
    
   

    AudioManager* mAudioManager;
   
    SDL_Event mEvent;
    
   
   
    StartScreen* mStartScreen;
    ScreenManager* mScreenManager;

    const int FRAME_RATE = 60;
    Timer* mTimer;
    
    // sanity test
    GameEntity * mParent;
    GameEntity * mChild;
    
    AnimatedTexture* mTex;
    Texture* mFontTex;

public:
    static GameManager * Instance();
    static void Release();
    
    void Run();
    
    void Update();
    void LateUpdate();
    
    void Render();
    
    GameManager();

    ~GameManager();

    
    
};

}

#endif /* GameManager_h */
