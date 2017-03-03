//
//  SceneManager.cpp
//  FishingEat
//
//  Created by eisoo on 14-2-14.
//
//

#include "SceneManager.h"

void SceneManager::pauseScene()
{
    Director::getInstance()->pause();
}

void SceneManager::resumeScene()
{
    Director::getInstance()->resume();
}

void SceneManager::pushScene(Scene *scene)
{
    Director::getInstance()->pushScene(scene);
}

void SceneManager::replaceScene(Scene *scene)
{
    Director::getInstance()->replaceScene(scene);
}

void SceneManager::popScene()
{
    Director::getInstance()->popScene();
}

