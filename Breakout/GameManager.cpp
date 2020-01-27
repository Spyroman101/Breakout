//
//  GameManager.cpp
//  SDLTut
//
//  Created by Dennis Hubley on 2020-01-15.
//  Copyright © 2020 triOS College. All rights reserved.
//

#include "GameManager.h"

namespace SDLFramework {

GameManager * GameManager::sInstance = nullptr;

GameManager * GameManager::Instance() {
    if (sInstance == nullptr) {
        sInstance = new GameManager();
    }
    return sInstance;
}

void GameManager::Release() {
    delete sInstance;
    sInstance = nullptr;
}

void GameManager::Run() {
    // main game loop
    while (!mQuit) {
        mTimer->Update();
        // event processing loop
        while (SDL_PollEvent(&mEvent)) {
            switch (mEvent.type) {
                case SDL_QUIT:
                    mQuit = true;
                    break;
            }
        }
        if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
            Update();
            LateUpdate();
            Render();
            mTimer->Reset();
        }
    }
}

void GameManager::Update() {
    mInputManager->Update();

    mScreenManager->Update();
   
    mStartScreen->Update();
    if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
        mTex->Translate(Vector2(0,-40.0f) * mTimer->DeltaTime(), GameEntity::World);
    } else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
        mTex->Translate(Vector2(0,40.0f) * mTimer->DeltaTime(), GameEntity::World);
    }
    
    if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
        mTex->Translate(Vector2(-40.0f,0.0f) * mTimer->DeltaTime(), GameEntity::World);
    } else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
        mTex->Translate(Vector2(40.0f,0.0f) * mTimer->DeltaTime(), GameEntity::World);
    }
    if (mInputManager->KeyDown(SDL_SCANCODE_1)) {
        mAudioManager->PlaySFX("SFX/coin_credit.wav", 0, -1);
    }
    
    if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
        mTex->Rotate(-1.0f * mTimer->DeltaTime());
    } else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
        mTex->Rotate(1.0f * mTimer->DeltaTime());
    }
    
    if (mInputManager->KeyDown(SDL_SCANCODE_Z)) {
        float newScale = mTex->Scale().x * 0.99f;
        mTex->Scale(Vector2(newScale,newScale));
    } else if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
        float newScale = mTex->Scale().x * 1.01f;
        mTex->Scale(Vector2(newScale,newScale));
    }
    
    if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
        std::cout << "Space pressed!" << std::endl;
    }
    if (mInputManager->KeyReleased(SDL_SCANCODE_SPACE)) {
        std::cout << "Space released!" << std::endl;
    }
    
    if (mInputManager->MouseButtonPressed(InputManager::Left)) {
        std::cout << "Left mouse button pressed!" << std::endl;
    }
    if (mInputManager->MouseButtonReleased(InputManager::Left)) {
        std::cout << "Left mouse button released!" << std::endl;
    }
   
    mTex->Update();
    
    

}

void GameManager::LateUpdate() {
    mInputManager->UpdatePrevInput();
}

void GameManager::Render() {
    mGraphics->ClearBackBuffer();
    mScreenManager->Render();
  
    mStartScreen->Render();

    mGraphics->Render();
}

GameManager::GameManager() : mQuit(false) {
    // create Graphics singleton
    mGraphics = Graphics::Instance();
    // verify Graphics module is ready
    if (!Graphics::Initialized()) {
        mQuit = true;
    }
    
    mAssetManager = AssetManager::Instance();
    
    mInputManager = InputManager::Instance();
    mAudioManager = AudioManager::Instance();
   
    mTimer = Timer::Instance();
    
    // sanity test
    mParent = new GameEntity(100.0f, 400.0f);
    mChild = new GameEntity(100.0f, 500.0f);
    
    // print local position of mChild with no parent set
    printf("Child local pos: (%f, %f)\n",
        mChild->Position(GameEntity::Local).x,
        mChild->Position(GameEntity::Local).y);
    
    // set parent of mChild to mParent
    mChild->Parent(mParent);
    
    // print local position of mChild with parent set
    printf("Child local pos: (%f, %f)\n",
          mChild->Position(GameEntity::Local).x,
          mChild->Position(GameEntity::Local).y);
    
    mTex = new AnimatedTexture("GalagaSpriteSheet.png", // filename
        204, // x clip
        45, // y clip
        40, // clip w
        38, // clip h
        4, // total frames
        0.5f, // animation length in second
        AnimatedTexture::Horizontal); //frame layout
    mTex->Position(Vector2(Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f));

    
   
    mStartScreen = new StartScreen();
    mScreenManager = ScreenManager::Instance();
}

GameManager::~GameManager() {
    delete  mStartScreen;
    mStartScreen = nullptr;

   
   

    delete mTex;
    mTex = nullptr;
    
    Timer::Release();
    mTimer = nullptr;
    
    AudioManager::Release();
    mAudioManager = nullptr;

    InputManager::Release();
    mInputManager = nullptr;
    
    AssetManager::Release();
    mAssetManager = nullptr;
    
    // release modules
    Graphics::Release();
    mGraphics = nullptr;
    
    // Quit SDL subsystems
    SDL_Quit();
}

}
