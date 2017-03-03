//
//  BeginACT.h
//  FishingEat
//
//  Created by eisoo on 14-2-14.
//
//

#ifndef __FishingEat__BeginACT__
#define __FishingEat__BeginACT__
#include "SceneManager.h"
#include <iostream>
#include "cocos2d.h"
#include "GameACT.h"
using namespace cocos2d;
namespace Begin {
    
    class BackGroundLayer : public Layer {
    public:
        static Scene *createBeginS(int actionnum);
        virtual bool init();
        CREATE_FUNC(BackGroundLayer);
    };
    
    class MainLayer : public Layer {
    public:
        virtual bool init();
        CREATE_FUNC(MainLayer);
        void menu_beginGame(Ref* pSender);
    };
}


#endif /* defined(__FishingEat__BeginACT__) */
