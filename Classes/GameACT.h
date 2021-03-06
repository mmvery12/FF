//
//  MainACT.h
//  FishingEat
//
//  Created by eisoo on 14-2-14.
//
//

#ifndef __FishingEat__GameACT__
#define __FishingEat__GameACT__


#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <deque>
#include <map>
#include <pthread.h>
#include <algorithm> 

#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "define.h"
#include "Category.h"
#include "FruntCell.h"
#include "help.h"
#include "ClickDelegate.h"
#include "define.h"
#include "Util.hpp"
#include "cocos2d.h"
using namespace cocos2d;
using std::string;
using namespace std;

#define CDestoryKO 9781
#define CNDestoryKO 9782
#define WhiteSpace  9783

namespace Game {
    
    
	typedef int _MAX_ROW;
    typedef int _ROW;
    typedef int _COLUMN;
    typedef int _DROPLENGTH;
    
    typedef map<_ROW,_COLUMN> DropRange;
    typedef DropRange::iterator RangeIterator;
    typedef multimap<DropRange ,_DROPLENGTH> DropSubMap;
    typedef DropSubMap::iterator SubMapIterator;
    
    
    
    typedef pair<int, int> CellPos;
    typedef multimap<CellPos,DropSubMap> DropMap;//
    typedef DropMap::iterator MapIterator;
    typedef list<DropMap> DropList;
    typedef DropList::iterator ListIterator;
    typedef deque<DropList> Dropdeque;
    typedef Dropdeque::iterator DequeIterator;
    
    
    
#define MAXCOUNT 9
    
    static bool isCellIndexEqual(CellIndex cell1,CellIndex cell2)
    {
        if (cell1.columnPos==cell2.columnPos&&cell1.rowPos==cell2.rowPos) return true;
        return false;
    }
    
    static void *thr_fun(void *arge);
    
    void recuse(DeleteUnitListIterator it,DropMap *map,pair<DeleteUnitListIterator, DeleteUnitListIterator> Findpair,int topIndex);
    
    class GameLayer : public Layer,ClickDelegate{
        
        GameLayer();
		virtual ~GameLayer();
        void showTag();
    public:
        
    private:
        
        list<long long> dropTump;
        list<long long>::iterator dropTumpit;
		Category *cy;
		FruntCell *_lastDeleteCell;
        FruntCell *_lastDropCell;
        long long colRowToInt(int col,int row);
        CellIndex intToColRow(long long colrowint);
        long long colRowToInt2(int col,int row);
        long long squareandbehand(int col1,int col2,long long col3);
        CellSquare benhandsquare(long long square);
        CellIndex preCanDeleteTargetCellIndex(long long colrowint);
        CellIndex preCanDeleteCurrentCellIndex(long long colrowint);
        
        
        
        CellIndex compute(MoveDirection dir,CellIndex lastedClick);
        CellIndex compute2(MoveDirection dir,CellIndex lastedClick);
        
        CellIndex _exchangeClick;
        CellIndex _exchangeClick2;
        
        list<int> dropCount[CELLNUM];
        
        void IIIIII();
        //void JJJJJJ();
        //bool KKKKKK(CellSquare square,int row);
        //FruntCell *DDDDDD(int fromcol,int tocol,long long dropcolrow);
        void loadGameMap();
        /*
         -1     NULL
         0      normal
         1      willanimate
         2      moving
         3      droping
         4      deleteing
         5      deleted
         CDestoryKO     storn//可消除物
         100    k.o.//不可消除物
         */
        int cellsStatus[CELLNUM][CELLNUM];
        int addCount[CELLNUM];
        DeleteFNMap prefnmap;
        struct CmpByValue {
            bool operator()(const PAIR& lhs, const PAIR& rhs) {
                return lhs.second >= rhs.second;
            }
        };
        
        DeleteFNMap TODO_FindDeleteCells();
        //bool TODO_DeleteCell();
        //bool TODO_ResetCell();
        
        DeleteUnitList sortMapByRow(pair<DeleteUnitListIterator,DeleteUnitListIterator> Findpair,int column);
        void addNewCell(int addcount,int column);
        
        void timeCallBack();
        
        void checkColumnHaveAnimation();
        void destory();
        
        void registTwoCell(CellIndex c1,CellIndex c2);
        void addNewCells(int column);
        //FruntCell * randNewCell(int columnPos,int rowPos,bool isPlaying);
        FruntCell * createNewCell(int column,int row,int type ,int rowcount,int status);
        FruntCell * createNewCell2(int column,int row,int tagcolumn,int tacolumn, int rowcount);
        ProgressTimer *progress;
        float dtf;
        void pop(Ref *node);
        
        
        list<int> _isDropping;
        list<int> _isDeleteing;
        list<int> _isMoving;
        list<int> _islighting;
        list<int> _isMoveAndDeleteing;
        
        void findCurrent();
        DeleteFNMap TODO_FindDeleteCells2(int row,int column,int row2,int column2);
        DeleteTotalUnitList findRowDelete(string ss,int row);
        DeleteTotalUnitList findColDelete(string ss,int column);
        DeleteTotalUnitList findRowDelete2(string ss,int row,int row1,int col1,int row2,int col2);
        DeleteTotalUnitList findColDelete2(string ss,int column,int row1,int col1,int row2,int col2);
        string getCellTypeString(int row,int column);
        
        FruntCell *getCellWithIndex(CellIndex index);//正常cell
        FruntCell *getKoCellWithIndex(CellIndex index);//无法移动的cell，除了－1
        bool isNormalCellIndex(CellIndex index);//正常的可下落空间
        bool isNormalCellIndexAndNullCell(CellIndex index);//正常的可下切cell是空
        bool isNormalCellIndexAndCell(CellIndex index);//正常的可下落且cell非空
        bool isKoCellIndex(CellIndex index);//非正常cell
        QUJIANlist findQuJian();
        QUJIANlist qujianlist;

    public:
        
        static Scene *createGameACTScene(void);
        virtual bool init();
        virtual void onEnter();
        virtual void update(float delta);
        CREATE_FUNC(GameLayer);
        //override for register one point touch
        //virtual void registerWithTouchDispatcher(void);
        //cctouch delegate
        virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
        virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
        virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
        
        //click delegate
        virtual void clickAtInde(CellIndex index);
        virtual void direction(MoveDirection dir,CellIndex lastedClick);
        
        virtual void willAnimate(Layer *cell);
        virtual void moving(Layer *cell);
        virtual void deleteing(Layer *cell);
        virtual void droping(Layer *cell);
        
        virtual void deleteComplete(Layer *cell);
        virtual void movingComplete(Layer *cell);
        virtual void movingComplete2(Layer *cell);
        virtual void dropComplete(Layer *cell);
        virtual void lighting(Layer *cell);
        virtual void lightComplete(Layer *cell);
        
        virtual void moveAndDeleteing(Layer *cell);
        virtual void moveAndDeleteComplete(Layer *cell);
    };
}
    
    

#endif /* defined(__FishingEat__GameACT__) */
