//
//  SceneManager.h
//  FishingEat
//
//  Created by eisoo on 14-2-14.
//
//

#ifndef __FishingEat__SceneManager__
#define __FishingEat__SceneManager__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class SceneManager{
public:
    static void pauseScene();
    static void resumeScene();
    static void pushScene(Scene *scene);
    static void popScene();
    static void replaceScene(Scene *scene);
};
#endif /* defined(__FishingEat__SceneManager__) */
