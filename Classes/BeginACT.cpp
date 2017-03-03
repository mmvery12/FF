//
//  BeginACT.cpp
//  FishingEat
//
//  Created by eisoo on 14-2-14.
//
//

#include "BeginACT.h"

namespace Begin
{
    Scene *BackGroundLayer::createBeginS(int actionNumber)
    {
        Scene *pScene=Scene::create();
        BackGroundLayer *bglayer = BackGroundLayer::create();
        pScene->addChild(bglayer, 0);
        MainLayer *mainlayer = MainLayer::create();
        pScene->addChild(mainlayer,1);
        return pScene;
    }
    
    bool BackGroundLayer::init()
    {
        if (!Layer::init()) {
            return false;
        }
        
        return true;
    }
    
    bool MainLayer::init()
    {
        if (!Layer::init()) {
            return false;
        }

        Label *label1 = Label::createWithTTF("Hello", "fonts/Marker Felt.ttf", 24);
        MenuItemLabel *ccLabel1=MenuItemLabel::create(label1, CC_CALLBACK_1(MainLayer::menu_beginGame, this));
        Menu *menu=Menu::create(ccLabel1,NULL);
        menu->setPosition(Vec2(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
        this->addChild(menu);
        return true;
    }
    
    void MainLayer::menu_beginGame(Ref* pSender)
    {
        SceneManager::pushScene(Game::GameLayer::createGameACTScene());
    }
}
