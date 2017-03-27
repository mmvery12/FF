//
//  FruntCell.h
//  FruitEat
//
//  Created by eisoo on 14-3-31.
//
//

#ifndef __FruitEat__FruntCell__
#define __FruitEat__FruntCell__

#include <iostream>
#include  <list>
#include "define.h"
#include "help.h"
#include "ClickDelegate.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;


namespace Game {
    static bool isCellIndexEqual(CellIndex cell1,CellIndex cell2);
    class FruntCell: public Layer
    {
        
        typedef struct {
            AnimationType animationtype;
            CellIndex toIndex;
            CellIndex preIndex;
        }AnimationStruct;
        
        typedef Vector<FiniteTimeAction *> AnimationList;
        typedef AnimationList::iterator AnimationIterator;
    private:
        
        bool _isDropping;
        bool _isDeleteing;
        bool _isMoving;
        
        Sprite *fruntSp;
        
        void spheightLight();
        void spNormal();
        void spDestory();
        CellStatus _status;
        void changeStauts(CellStatus status);
        ClickDelegate *_layer;
        MoveDirection computeDirection(Point p1,Point p2);
        void movingComplete();
        void exchangeComplete();
        void deleteComplete();
        void dropComplete();
        void searchNearCells();
        bool _topH;
        bool _leftH;
        bool _rightH;
        bool _bottomH;
        
        CellIndex previseIndex;
        CellIndex nowIndex;
        //
        
        
        void movingAnimation(AnimationStruct animate);
        void movingAnimation2(AnimationStruct animate);
        void deleteAnimation(AnimationStruct animate);
        void dropAnimation(AnimationStruct animate);
        void moveAndDeleteAnimate(AnimationStruct animate);
        void lightAnimatimate(AnimationStruct animate);
        void movingAnimationComplete();
        void movingAnimationComplete2();
        void deleteAnimationComplete();
        void dropAnimationComplelte();
        void moveAndDeleteAnimateComplete();
        void lightAnimatimateComplete();
        void exchangeIndex();
        void exchangeIndex(CellIndex index);
        
        AnimationList animationList;
        AnimationIterator animationIterator;
    public:
        void setType(int type);
        
        //new
        
        void setNowIndex(int row,int column);
        void joinCellAnimation(AnimationType type, CellIndex moveTo,CellIndex from);
        void showAnimation();
        CellIndex getCellIndex();
        CellIndex getPreviseCellIndex();//cell上个状态的index
        
        
        
        
//        virtual void update(float delta);
        
        bool isAnimation();
        //old
        inline FruntCell(){};
        inline ~FruntCell(){};
        unsigned cellType;//1,2...9
        
        CellStatus getCellStatus();
        
        bool _canTouch;
        void registDelegate(ClickDelegate *layer);
        void setCellStatus(CellStatus status);
        int dropPreVi;//1:left,2:Ver,3:right
        
        CREATE_FUNC(FruntCell);
        //virtual void registerWithTouchDispatcher(void);
        virtual bool init();
        virtual void onEnter();
        virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
        virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
        virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
        
    };
}




#endif /* defined(__FruitEat__FruntCell__) */
