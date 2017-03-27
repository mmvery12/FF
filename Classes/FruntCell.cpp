//
//  FruntCell.cpp
//  FruitEat
//
//  Created by eisoo on 14-3-31.
//
//

#include "FruntCell.h"

namespace Game {
    bool FruntCell::isCellIndexEqual(CellIndex cell1,CellIndex cell2)
    {
        if (cell1.columnPos==cell2.columnPos&&cell1.rowPos==cell2.rowPos) return true;
        return false;
    }
    
    void FruntCell::setNowIndex(int row,int column)
    {
        nowIndex= {row,column};
        setTag(row*CELLNUM+column);
    }
    
    void FruntCell::joinCellAnimation(AnimationType type, CellIndex moveTo,CellIndex from)
    {
        AnimationStruct temp;
        temp.animationtype = type;
        temp.toIndex = moveTo;
        temp.preIndex = from;
        switch (type) {
            case OnlyMoveAnimation:
                movingAnimation(temp);
                break;
            case OnlyMoveAnimation2:
                movingAnimation2(temp);
                break;
            case DeleteAnimation:
                deleteAnimation(temp);
                break;
            case DropAnimation:
                dropAnimation(temp);
                break;
            case MoveAndDeleteAnimate:
                moveAndDeleteAnimate(temp);
                break;
            case LightAnimate:
                lightAnimatimate(temp);
                break;
            default:
                break;
        }
        previseIndex = nowIndex;
        setNowIndex(moveTo.rowPos, moveTo.columnPos);
    }
    
    
    void FruntCell::showAnimation()
    {
        if (!animationList.empty()) {
            stopAllActions();
            Sequence *seq = Sequence::create(animationList);
            runAction(seq);
            animationList.clear();
        }
    }
    
    void FruntCell::movingAnimation(AnimationStruct animate)
    {
        CellIndex temp = animate.toIndex;
        _canTouch=false;
        _isMoving=true;
        _layer->moving((Layer *)this);
        
        double width=Director::getInstance()->getWinSize().width/CELLNUM;
        double cloumnPos=width*(temp.columnPos%CELLNUM);
        double rowPos=width*temp.rowPos;
        FiniteTimeAction *act2=MoveTo::create(1, Vec2(cloumnPos, rowPos));
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::movingAnimationComplete, this));
        animationList.pushBack(act2);
        animationList.pushBack(act3);
    }
    
    void FruntCell::movingAnimation2(AnimationStruct animate)
    {
        CellIndex temp = animate.toIndex;
        _canTouch=false;
        _isMoving=true;
        _layer->moving((Layer *)this);
        double width=Director::getInstance()->getWinSize().width/CELLNUM;
        double cloumnPos=width*(temp.columnPos%CELLNUM);
        double rowPos=width*temp.rowPos;
        FiniteTimeAction *act2=MoveTo::create(1, Vec2(cloumnPos, rowPos));
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::movingAnimationComplete2, this));
        animationList.pushBack(act2);
        animationList.pushBack(act3);
    }
    
    
    
    void FruntCell::dropAnimation(AnimationStruct animate)
    {
        CellIndex temp = animate.toIndex;
        CellIndex pre = animate.preIndex;
        _canTouch=false;
        _isMoving=true;
        _isDropping=true;
        _layer->droping(this);
        double width=Director::getInstance()->getWinSize().width/CELLNUM;
        double cloumnPos=width*(temp.columnPos%CELLNUM);
        double rowPos=width*temp.rowPos;
        
        int time = abs(pre.rowPos-temp.rowPos);
        FiniteTimeAction *act2=MoveTo::create(time, Vec2(cloumnPos, rowPos));
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::dropAnimationComplelte, this));
        animationList.pushBack(act2);
        animationList.pushBack(act3);
    }
    
    void FruntCell::deleteAnimation(AnimationStruct animate)
    {
        CellIndex temp = animate.toIndex;
        _canTouch=false;
        _isMoving=true;
        _layer->deleteing(this);
        double width=Director::getInstance()->getWinSize().width/CELLNUM;
        double cloumnPos=width*(temp.columnPos%CELLNUM);
        double rowPos=width*temp.rowPos;
        FiniteTimeAction *act2=Blink::create(2.0f, 3);
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::deleteAnimationComplete, this));
        animationList.pushBack(act2);
        animationList.pushBack(act3);
    }
    
    void FruntCell::moveAndDeleteAnimate(AnimationStruct animate)
    {
        CellIndex temp = animate.toIndex;
        _canTouch=false;
        _isMoving=true;
        _isDropping=true;
        _layer->moveAndDeleteing(this);
        double width=Director::getInstance()->getWinSize().width/CELLNUM;
        double cloumnPos=width*(temp.columnPos%CELLNUM);
        double rowPos=width*temp.rowPos;
        FiniteTimeAction *act2=Blink::create(2.0f, 3);
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::moveAndDeleteAnimateComplete, this));
        animationList.pushBack(act2);
        animationList.pushBack(act3);
    }
    
    
    void FruntCell::lightAnimatimate(AnimationStruct animate)
    {
        CellIndex temp = animate.toIndex;
        _canTouch=false;
        _isMoving=true;
        _isDropping=true;
        _layer->lighting(this);
        double width=Director::getInstance()->getWinSize().width/CELLNUM;
        double cloumnPos=width*(temp.columnPos%CELLNUM);
        double rowPos=width*temp.rowPos;
        
        FiniteTimeAction *act2=Blink::create(2.0f, 3);
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::lightAnimatimateComplete, this));
        animationList.pushBack(act2);
        animationList.pushBack(act3);
    }
    
    void FruntCell::moveAndDeleteAnimateComplete()
    {
        _canTouch=true;
        _isMoving=false;
        
        _layer->moveAndDeleteComplete((Layer *)this);
    }
    
    void FruntCell::movingAnimationComplete()
    {
        _canTouch=true;
        _isMoving=false;
        
        _layer->movingComplete((Layer *)this);
    }
    
    void FruntCell::movingAnimationComplete2()
    {
        _canTouch=true;
        _isMoving=false;
        
        _layer->movingComplete2((Layer *)this);
    }
    
    
    void FruntCell::deleteAnimationComplete()
    {
        _isMoving=false;
        _layer->deleteComplete((Layer *)this);
    }
    
    void FruntCell::dropAnimationComplelte()
    {
        _canTouch=true;
        _isMoving=false;
        _isDropping=false;
        _layer->dropComplete((Layer *)this);
    }
    
    void FruntCell::lightAnimatimateComplete()
    {
        _canTouch=true;
        _isMoving=false;
        _isDropping=false;
        _layer->lightComplete((Layer *)this);
    }
    
    void FruntCell::exchangeIndex()
    {
        setNowIndex(previseIndex.rowPos, previseIndex.columnPos);
    }
    
    
    void FruntCell::registDelegate(ClickDelegate *layer)
    {
        _layer=layer;
    }
    
    void FruntCell::setCellStatus(CellStatus status)
    {
        changeStauts(status);
    }
    CellStatus FruntCell::getCellStatus()
    {
        return _status;
    }
    
    CellIndex FruntCell::getCellIndex()
    {
        return nowIndex;
    }
    CellIndex FruntCell::getPreviseCellIndex()
    {
        return previseIndex;
    }
    
    void FruntCell::changeStauts(CellStatus status)
    {
        if (status==cellNormale) {
            spNormal();
        }
        if (status==cellHeightLight) {
            spheightLight();
        }
        if (status==cellDestory) {
            spDestory();
        }
    }
    
    
    
    void FruntCell::spDestory()
    {
        _status=cellDestory;
    }
    
    void FruntCell::spNormal()
    {
        _status=cellNormale;
    }
    
    void FruntCell::spheightLight()
    {
        _status=cellHeightLight;
    }
    
    bool FruntCell::isAnimation()
    {
        bool flag = _isDropping || _isDeleteing || _isMoving;
        return flag;
    }
    
    bool FruntCell::init()
    {
        if (!Layer::init()) {
            return false;
        }
        
        auto sprListener=EventListenerTouchOneByOne::create();
        sprListener->setSwallowTouches(true);
        sprListener->onTouchBegan=CC_CALLBACK_2(FruntCell::onTouchBegan,this);
        sprListener->onTouchMoved=CC_CALLBACK_2(FruntCell::onTouchMoved,this);
        sprListener->onTouchEnded=CC_CALLBACK_2(FruntCell::onTouchEnded,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(sprListener,this);
        
        _canTouch=true;
        _isMoving=false;
        
        _isDeleteing=false;
        _isDropping=false;
        setTouchEnabled(true);
        _status=cellNormale;
        
        int temp=cellType=0;
        temp=1+std::rand()%CELLNUM;
        cellType=temp;
        char pic[30]="";
        std::sprintf(pic, "fruit0%d-HD.png",cellType);
        fruntSp=Sprite::create(pic);
        this->addChild(fruntSp);
        return true;
    }
    //-1没有图,0随机，1-9固定头像，99云朵
    void FruntCell::setType(int type)
    {
        cellType=type;
        if (type==0) {
            cellType=1+std::rand()%CELLNUM;
        }
        char pic[30]="";
        if (type==99) {
            std::sprintf(pic, "yun.png");
        }else
            if (type==100) {
                std::sprintf(pic, "100.png");
            }else
                std::sprintf(pic, "fruit0%d-HD.png",cellType);
        fruntSp->setTexture(pic);
    }
    /*
     void FruntCell::registerWithTouchDispatcher(void)
     {
     Director *pDirector=Director::sharedDirector();
     pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
     }
     */
    void FruntCell::onEnter()
    {
        Layer::onEnter();
        fruntSp->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
        fruntSp->setScaleX(this->getContentSize().width/fruntSp->getContentSize().width);
        fruntSp->setScaleY(this->getContentSize().height/fruntSp->getContentSize().height);
    }
    
    
    
    
    bool FruntCell::onTouchBegan(Touch *pTouch, Event *pEvent)
    {
        if (!_canTouch) {
            return false;
        }
        {
            auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());//获取的当前触摸的目标
            
            Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            if (rect.containsPoint(locationInNode) && !_isMoving)
            {//判断触摸点是否在目标的范围内
                _layer->clickAtInde(getCellIndex());
                return true;
            }
            else
                return false;
        }
    }
    
    void FruntCell::onTouchMoved(Touch *pTouch, Event *pEvent)
    {
        onTouchEnded(pTouch, pEvent);
    }
    
    
    void FruntCell::onTouchEnded(Touch *pTouch, Event *pEvent)
    {
        if (!_canTouch) {
            return;
        }
        Point _begin=pTouch->getStartLocation();
        Point _pos=pTouch->getLocation();
        _layer->direction(computeDirection(_begin, _pos),getCellIndex());
    }
    
    
    MoveDirection FruntCell::computeDirection(Point p1,Point p2)
    {
        double _xDir=p1.x-p2.x;
        double _yDir=p1.y-p2.y;
        Size size = Director::getInstance()->getWinSize();
        float winw = size.width;
        if (_xDir>10&&fabs(_yDir)<winw/CELLNUM) {
            return LEFT;
        }else if (_yDir>10&&fabs(_xDir)<winw/CELLNUM)
        {
            return DOWN;
        }else if (_xDir<-10&&fabs(_yDir)<winw/CELLNUM)
        {
            return RIGHT;
        }else if (_yDir<-10&&fabs(_xDir)<winw/CELLNUM)
            return UP;
        return NONE;
    }
}

