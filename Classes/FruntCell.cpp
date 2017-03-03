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
        nowIndex.rowPos=row;
        nowIndex.columnPos=column;
        setTag(row*7+column);
        toIndex = nowIndex;
    }
    
    void FruntCell::joinCellAnimation(AnimationType type, CellIndex moveTo)
    {
        
        animationIterator=animationList.begin();
        if (animationIterator!=animationList.end())
        {
            AnimationStruct temp=*animationIterator;
            if (type==DeleteAnimation && temp.animationtype==DeleteAnimation) {
                return;
            }
        }
        AnimationStruct animationStruct;
        animationStruct.animationtype=type;
        animationStruct.toIndex=moveTo;
        
        
        animationList.push_back(animationStruct);
        if (animationList.size()>1) {
            CCLOG("***************** WARM *****************");
            animationIterator=animationList.begin();
            
            for (;animationIterator!=animationList.end();animationIterator++)
            {
                AnimationStruct temp=*animationIterator;
                CCLOG("[%d][%d] to [%d][%d]",nowIndex.rowPos,nowIndex.columnPos,temp.toIndex.rowPos,temp.toIndex.columnPos);
            }
            CCLOG("****************************************");
        }
        if (isAnimation==false) {
            _layer->willAnimate((Layer *)this);
            showAnimation();
        }
    }
    
    
    void FruntCell::showAnimation()
    {
        
        animationIterator=animationList.begin();
        if (animationIterator!=animationList.end()) {
            isAnimation=true;
            AnimationStruct temp=*animationIterator;
            toIndex=temp.toIndex;
            switch (temp.animationtype) {
                case OnlyMoveAnimation:
                    movingAnimation(temp.toIndex);
                    break;
                case OnlyMoveAnimation2:
                    movingAnimation2(temp.toIndex);
                    break;
                case DeleteAnimation:
                    deleteAnimation(temp.toIndex);
                    break;
                case DropAnimation:
                    dropAnimation(temp.toIndex);
                    break;
                default:
                    break;
            }
        }else isAnimation=false;
    }
    
    void FruntCell::movingAnimation(CellIndex temp)
    {
        if (isCellIndexEqual(nowIndex, getToCellIndex())) {
            animationList.pop_front();
            return;
        }
        _canTouch=false;
        _isMoving=true;
        _layer->moving((Layer *)this);
        isAnimation=true;
        
        toIndex.rowPos = temp.rowPos;
        toIndex.columnPos = temp.columnPos;
        
        double width=Director::getInstance()->getWinSize().width/7;
        double cloumnPos=width*(temp.columnPos%7);
        double rowPos=width*temp.rowPos;
        FiniteTimeAction *act2=MoveTo::create(3, Vec2(cloumnPos, rowPos));
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::movingAnimationComplete, this));
        Sequence *actList=Sequence::create(act2,act3,NULL);
        runAction(actList);
    }
    
    void FruntCell::movingAnimation2(CellIndex temp)
    {
        if (isCellIndexEqual(nowIndex, getToCellIndex())) {
            animationList.pop_front();
            return;
        }
        _canTouch=false;
        _isMoving=true;
        _layer->moving((Layer *)this);
        isAnimation=true;
        
        toIndex.rowPos = temp.rowPos;
        toIndex.columnPos = temp.columnPos;
        
        double width=Director::getInstance()->getWinSize().width/7;
        double cloumnPos=width*(temp.columnPos%7);
        double rowPos=width*temp.rowPos;
        FiniteTimeAction *act2=MoveTo::create(3, Vec2(cloumnPos, rowPos));
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::movingAnimationComplete2, this));
        Sequence *actList=Sequence::create(act2,act3,NULL);
        runAction(actList);
    }
    
    void FruntCell::deleteAnimation(CellIndex temp)
    {
        _canTouch=false;
        _isMoving=true;
        _layer->deleteing(this);
        isAnimation=true;
        double width=Director::getInstance()->getWinSize().width/7;
        double cloumnPos=width*(temp.columnPos%7);
        double rowPos=width*temp.rowPos;
        if (isCellIndexEqual(nowIndex, getToCellIndex())) {
            FiniteTimeAction *act1=Blink::create(3, 2);
            ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::deleteAnimationComplete, this));
            //create(this, callfunc_selector(FruntCell::deleteAnimationComplete));
            Sequence *actList=Sequence::create(act1,act3,NULL);
            runAction(actList);
        }else
        {
            FiniteTimeAction *act1=Blink::create(3, 2);
            FiniteTimeAction *act2=MoveTo::create(3, Vec2(cloumnPos, rowPos));
            ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::deleteAnimationComplete, this));
            //create(this, callfunc_selector(FruntCell::deleteAnimationComplete));
            Sequence *actList=Sequence::create(act1,act2,act3,NULL);
            runAction(actList);
        }
    }
    
    void FruntCell::dropAnimation(CellIndex temp)
    {
        if (isCellIndexEqual(nowIndex, getToCellIndex())) {
            animationList.pop_front();
            return;
        }
        _canTouch=false;
        _isMoving=true;
        _isDrop=true;
        _layer->droping(this);
        isAnimation=true;
        double width=Director::getInstance()->getWinSize().width/7;
        double cloumnPos=width*(temp.columnPos%7);
        double rowPos=width*temp.rowPos;
        
        FiniteTimeAction *act2=MoveTo::create(3, Vec2(cloumnPos, rowPos));
        ActionInstant *act3=CallFunc::create(CC_CALLBACK_0(FruntCell::dropAnimationComplelte, this));
        //create(this, callfunc_selector(FruntCell::dropAnimationComplelte));
        Sequence *actList=Sequence::create(act2,act3,NULL);
        runAction(actList);
    }
    
    void FruntCell::movingAnimationComplete()
    {
        _canTouch=true;
        _isMoving=false;
        isAnimation=false;
        _layer->movingComplete((Layer *)this);
        animationList.pop_front();
        exchangeIndex();
    }
    
    void FruntCell::movingAnimationComplete2()
    {
        _canTouch=true;
        _isMoving=false;
        isAnimation=false;
        _layer->movingComplete((Layer *)this);
        animationList.pop_front();
        setNowIndex(toIndex.rowPos, toIndex.columnPos);
    }
    
    
    void FruntCell::deleteAnimationComplete()
    {
        _isMoving=false;
        isAnimation=false;
        _layer->deleteComplete((Layer *)this);
        animationList.pop_front();
        
    }
    
    void FruntCell::dropAnimationComplelte()
    {
        _canTouch=true;
        _isMoving=false;
        _isDrop=false;
        isAnimation=false;
        _layer->dropComplete((Layer *)this);
        if (animationList.size()==0) {
            CCLOG("error_animationList.size()==0");
        }
        animationList.pop_front();
        exchangeIndex();
        showAnimation();
    }
    
    void FruntCell::exchangeIndex()
    {
        CellIndex temp=nowIndex;
        setNowIndex(toIndex.rowPos, toIndex.columnPos);
        toIndex=temp;
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
    CellIndex FruntCell::getToCellIndex()
    {
        return toIndex;
    }
    CellIndex FruntCell::getAnimationToIndex()
    {
        if (isAnimation) {
            animationIterator=animationList.begin();
			if (animationIterator!=animationList.end())
			{
				AnimationStruct temp=*animationIterator;
				return temp.toIndex;
			}else
			{
				return nowIndex;
			}
			
            
        }else
            return nowIndex;
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
        isAnimation=false;
		_isDeleteing=false;
		_isDrop=false;
        setTouchEnabled(true);
        _status=cellNormale;
        
        int temp=cellType=0;
        temp=1+std::rand()%7;
        cellType=temp;
        char pic[30]="";
        std::sprintf(pic, "fruit0%d-HD.png",cellType);
        fruntSp=Sprite::create(pic);
        this->addChild(fruntSp);
        return true;
    }
    
    void FruntCell::setType(int type)
    {
        cellType=type;
        char pic[30]="";
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
        Size tempsize = getContentSize();
        Point temppos = getPosition();
        
        Rect thispos= Rect(temppos.x, temppos.y, tempsize.width, tempsize.height);
        
        Point _p=pTouch->getLocation();
        if (_isMoving) {
            //CCLOG("ismoving");
        }else
        {
            //CCLOG("notmoving");
        }
        
        if (thispos.containsPoint(_p)&&_isMoving==false) {
            _layer->clickAtInde(getCellIndex());
            return true;
        }else
            return false;
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
        if (_xDir>10&&fabs(_yDir)<winw/7) {
            return LEFT;
        }else if (_yDir>10&&fabs(_xDir)<winw/7)
        {
            return DOWN;
        }else if (_xDir<-10&&fabs(_yDir)<winw/7)
        {
            return RIGHT;
        }else if (_yDir<-10&&fabs(_xDir)<winw/7)
            return UP;
        return NONE;
    }
}

