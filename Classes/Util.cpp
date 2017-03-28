//
//  Util.cpp
//  FruntMove2
//
//  Created by JD on 17/3/28.
//
//

#include "Util.hpp"

namespace Game{
 float getMapBottomPadding()
{
    return cocos2d::Director::getInstance()->getWinSize().width*100./750.;;
}

 float getMapLeftPadding()
{
    return cocos2d::Director::getInstance()->getWinSize().width*10./750.;;
}

 float getCellWidth(int count)
{
    return  (cocos2d::Director::getInstance()->getWinSize().width-getMapLeftPadding()*2)/count;
}
}
