//
//  ClickDelegate.h
//  FruitEat
//
//  Created by eisoo on 14-3-31.
//
//

#ifndef __FruitEat__ClickDelegate__
#define __FruitEat__ClickDelegate__

#include <iostream>
#include "help.h"
#include "cocos2d.h"
using namespace cocos2d;
class ClickDelegate
{
public:
    inline ClickDelegate(){};
    inline ~ClickDelegate(){};
    virtual void clickAtInde(CellIndex index)=0;
    virtual void direction(MoveDirection dir,CellIndex lastedClick)=0;
    
    virtual void willAnimate(Layer *cell)=0;
    
    virtual void exchanging(Layer *cell)=0;
    virtual void movingComplete(Layer *cell)=0;
    virtual void movingComplete2(Layer *cell)=0;
    
    virtual void droping(Layer *cell)=0;
    virtual void dropComplete(Layer *cell)=0;
    
    virtual void deleteing(Layer *cell)=0;
    virtual void deleteComplete(Layer *cell)=0;
    
    virtual void lighting(Layer *cell)=0;
    virtual void lightComplete(Layer *cell)=0;
    
    virtual void moveAndDeleteing(Layer *cell)=0;
    virtual void moveAndDeleteComplete(Layer *cell)=0;
    //    virtual void exchangeComplete(Layer *cell);
};
#endif /* defined(__FruitEat__ClickDelegate__) */
