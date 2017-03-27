//
//  MainACT.cpp
//  FishingEat
//
//  Created by eisoo on 14-2-14.
//
//
#include <regex.h>
#include "GameACT.h"

namespace Game
{
    //当前index
    long long GameLayer::colRowToInt(int col,int row)
    {
        long long temp = (long long)col*100000 + (long long)row*1000;
        
        return temp;
    }
    CellIndex GameLayer::intToColRow(long long colrowint)
    {
        CellIndex index;
        long long col = colrowint/100000;
        long long row = (colrowint-(col*100000))/1000;
        index.rowPos = (int)row;
        index.columnPos = (int)col;
        return index;
    }
    //目标index
    long long GameLayer::colRowToInt2(int col,int row)
    {
        long long temp = ((long long)col*100000 + (long long)row*1000)*1000000;
        
        return temp;
    }
    //col1 左边界，col2右边界，col3掉落口
    long long GameLayer::squareandbehand(int col1,int col2,long long col3)
    {
        long long temp = (long long)col1 + (long long)col2*100 + (long long)col3*10000;
        return temp;
    }
    
    CellSquare GameLayer::benhandsquare(long long square)
    {
        CellSquare tsquare;
        tsquare.columnPos3 = square/10000;
        tsquare.columnPos2 = int((square-(tsquare.columnPos3*10000))/100);
        tsquare.columnPos1 = int(square-(tsquare.columnPos3*10000+tsquare.columnPos2*100));
        
        return tsquare;
    }
    
    //未移动前的可消除cell的目标index
    CellIndex GameLayer::preCanDeleteTargetCellIndex(long long colrowint)
    {
        
        colrowint/=1000000;
        CellIndex index;
        long long col = colrowint/100000;
        long long row = (colrowint-(col*100000))/1000;
        index.rowPos = (int)row;
        index.columnPos = (int)col;
        return index;
    }
    //未移动前的可消除cell的当前index
    CellIndex GameLayer::preCanDeleteCurrentCellIndex(long long colrowint)
    {
        colrowint%=1000000;
        CellIndex index;
        long long col = colrowint/100000;
        long long row = (colrowint-(col*100000))/1000;
        index.rowPos = (int)row;
        index.columnPos = (int)col;
        return index;
    }
    /*
     int status ,i;
     int cflags = REG_EXTENDED;
     regmatch_t pmatch[1];
     const size_t nmatch = 1;
     regex_t reg;
     string str = "([\\d])\\1{2,}";
     const char * pattern = str.c_str();
     const char *buf = "122233344";
     ss.c_str();
     
     regcomp(&reg, pattern, cflags);
     status = regexec(&reg, buf, nmatch, pmatch, 0);
     if ( status!=REG_NOMATCH) {
     for (i=pmatch[0].rm_so; i<pmatch[0].rm_eo; ++i) {
     
     }
     }
     regfree(&reg);
     */
    
    DeleteTotalUnitList GameLayer::findRowDelete(string ss,int row)
    {
        DeleteTotalUnitList totalunitlist;
        
        char temp=NULL;
        int count=0;
        for (int i=0;i<ss.size();i++)
        {
            if (temp==ss[i]&&ss[i]!='_')
            {
                count++;
            }else
            {
                temp=ss[i];
                if (count>=2)
                {
                    DeleteUnitList unitlist;
                    count++;
                    int ff=i;
                    for (int column=0; column<count; column++) {
                        ff--;
                        FruntCell *cell = getCellWithIndex({row,ff});
                        if (cell){
                            unitlist.push_back(colRowToInt(ff, row));
                        }
                    }
                    totalunitlist.push_back(unitlist);
                }
                count=0;
            }
        }
        return totalunitlist;
    }
    
    DeleteTotalUnitList GameLayer::findRowDelete2(string ss,int row,int row1,int col1,int row2,int col2)
    {
        DeleteTotalUnitList dellist;
        char temp=NULL;
        int count=0;
        for (int i=0;i<ss.size();i++)
        {
            if (temp==ss[i]&&ss[i]!='_')
            {
                count++;
            }else
            {
                temp=ss[i];
                if (count>=2)
                {
                    DeleteUnitList delmap;
                    count++;
                    int ff=i;
                    for (int column=0; column<count; column++) {
                        ff--;
                        FruntCell *cell = getCellWithIndex({row,ff});
                        if (cell){
                            if (row1==row && col1==ff) {
                                delmap.push_back(colRowToInt(col2, row2));
                            }else
                            if (row2==row&& col2==ff) {
                                delmap.push_back(colRowToInt(col1, row1));
                            }else
                                delmap.push_back(colRowToInt(ff, row));
                        }
                    }
                    dellist.push_back(delmap);
                }
                count=0;
            }
        }
        return dellist;
    }
    
    DeleteTotalUnitList GameLayer::findColDelete2(string ss,int column,int row1,int col1,int row2,int col2)
    {
        DeleteTotalUnitList dellist;
        char temp=NULL;
        int count=0;
        for (int i=0;i<ss.size();i++)
        {
            if (temp==ss[i]&&ss[i]!='_')
            {
                count++;
            }else
            {
                temp=ss[i];
                if (count>=2)
                {
                    DeleteUnitList delmap;
                    count++;
                    int ff=i;
                    for (int row=0; row<count; row++) {
                        ff--;
                        FruntCell *cell = getCellWithIndex({ff,column});
                        if (cell) {
                            if (row1==ff && col1==column) {
                                delmap.push_back(colRowToInt(col2, row2));
                            }else
                                if (row2==ff&& col2==column) {
                                    delmap.push_back(colRowToInt(col1, row1));
                                }else
                                    delmap.push_back(colRowToInt(column, ff));
                        }
                    }
                    dellist.push_back(delmap);
                }
                
                count=0;
            }
        }
        return dellist;
    }
    
    DeleteTotalUnitList GameLayer::findColDelete(string ss,int column)
    {
        DeleteTotalUnitList dellist;
        char temp=NULL;
        int count=0;
        for (int i=0;i<ss.size();i++)
        {
            if (temp==ss[i]&&ss[i]!='_')
            {
                count++;
            }else
            {
                temp=ss[i];
                if (count>=2)
                {
                    DeleteUnitList delmap;
                    count++;
                    int ff=i;
                    for (int row=0; row<count; row++) {
                        ff--;
                        FruntCell *cell = getCellWithIndex({ff,column});
                        if (cell) {
                            delmap.push_back(colRowToInt(column, ff));
                        }
                    }
                    dellist.push_back(delmap);
                }
                
                count=0;
            }
        }
        return dellist;
    }
    
    string GameLayer::getCellTypeString(int row,int column)
    {
        FruntCell *cell=getCellWithIndex({row,column});
        char temps[2]="";
        if (!cell) {
            std::sprintf(temps, "_");
        }else
            std::sprintf(temps, "%u",cell->cellType);
        std::string sg(temps);
        return sg;
    }
    
    DeleteFNMap GameLayer::TODO_FindDeleteCells()
    {
        DeleteFNMap fnmap;
        DeleteTotalUnitList rowtotalunitList;
        DeleteTotalUnitList coltotalunitList;
        
        for (int row=0; row<CELLNUM; row++) {
            std::string ss;
            for (int column=0; column<CELLNUM; column++) {
                string sg = getCellTypeString(row, column);
                ss+=sg;
            }
            ss+='_';
            DeleteTotalUnitList temp1 = findRowDelete(ss, row);
            DeleteTotalUnitListIterator delit=temp1.begin();
            for (;delit!=temp1.end();delit++)
            {
                rowtotalunitList.push_back(*delit);
            }
        }
        for (int column=0; column<CELLNUM; column++) {
            std::string ss;
            for (int row=0; row<CELLNUM; row++) {
                string sg = getCellTypeString(row, column);
                ss+=sg;
            }
            ss+='_';
            DeleteTotalUnitList temp2 = findColDelete(ss, column);
            DeleteTotalUnitListIterator delit=temp2.begin();
            for (;delit!=temp2.end();delit++)
            {
                coltotalunitList.push_back(*delit);
            }
        }
        
        DeleteTotalUnitListIterator rowtotalunitdelit=rowtotalunitList.begin();
        DeleteTotalUnitListIterator coltotalunitdelit=coltotalunitList.begin();
        if (!rowtotalunitList.empty() || !coltotalunitList.empty()) {
            
        }
        
        if (rowtotalunitList.empty() || coltotalunitList.empty()) {
            for (;rowtotalunitdelit!=rowtotalunitList.end();rowtotalunitdelit++)
            {
                DeleteUnitList rowmap = * rowtotalunitdelit;
                DeleteUnitListIterator it = rowmap.begin();
                
                DeleteFNMapIterator premapit = prefnmap.begin();
                for (; premapit!=prefnmap.end(); premapit++) {
                    DeleteUnitList temprowmap = premapit->second;
                    DeleteUnitList temp = rowmap;
                    temprowmap.merge(temp);
                    temprowmap.unique();
                }
                
                it++;
                if (rowmap.size()==3) {
                    fnmap.insert(pair<int, DeleteUnitList>(rowmap.size()+*it,rowmap));
                }
                if (rowmap.size()==4) {
                    fnmap.insert(pair<int, DeleteUnitList>(rowmap.size()+*it,rowmap));
                }
                if (rowmap.size()>4) {
                    it++;
                    fnmap.insert(pair<int, DeleteUnitList>(rowmap.size()+*it,rowmap));
                }
            }
            for (;coltotalunitdelit!=coltotalunitList.end();coltotalunitdelit++)
            {
                DeleteUnitList colmap = * coltotalunitdelit;
                DeleteUnitListIterator it = colmap.begin();
                
                DeleteFNMapIterator premapit = prefnmap.begin();
                for (; premapit!=prefnmap.end(); premapit++) {
                    DeleteUnitList tempcowmap = premapit->second;
                    DeleteUnitList temp = colmap;
                    tempcowmap.merge(temp);
                    tempcowmap.unique();
                }
                
                it++;
                if (colmap.size()==3) {
                    fnmap.insert(pair<int, DeleteUnitList>(colmap.size()+*it,colmap));
                }
                if (colmap.size()==4) {
                    fnmap.insert(pair<int, DeleteUnitList>(colmap.size()+*it,colmap));
                }
                if (colmap.size()>4) {
                    it++;
                    fnmap.insert(pair<int, DeleteUnitList>(colmap.size()+*it,colmap));
                }
            }
        }else
        {
            
            DeleteTotalUnitList tempCompairRow;
            DeleteTotalUnitList tempCompairCol;
            rowtotalunitdelit = rowtotalunitList.begin();
            for (;rowtotalunitdelit!=rowtotalunitList.end();rowtotalunitdelit++)
            {
                DeleteUnitList rowunit = * rowtotalunitdelit;
                DeleteUnitList samemergeunit;
                int saverowcolint;
                DeleteUnitList colunit;
                coltotalunitdelit = coltotalunitList.begin();
                for (;coltotalunitdelit!=coltotalunitList.end() && !rowunit.empty();coltotalunitdelit++){
                    colunit = * coltotalunitdelit;
                    
                    DeleteUnitList rowunit2 = rowunit;
                    DeleteUnitList colunit2 = colunit;
                    
                    DeleteUnitList temp;
                    temp.merge(rowunit2);
                    temp.merge(colunit2);
                    temp.sort();
                    DeleteUnitList samemergeunit2 = temp;
                    temp.unique();
                    if (temp.size()!=rowunit.size()+colunit.size()) {//有重复元素
                        samemergeunit = temp;
                        //下面通过map计数找出重复的cell的int表述
                        map<int,int> kkk;
                        DeleteUnitListIterator samemergeunit2it = samemergeunit2.begin();
                        for (; samemergeunit2it!=samemergeunit2.end(); samemergeunit2it++) {
                            int value = kkk[*samemergeunit2it];
                            kkk[*samemergeunit2it] = ++value;
                        }
                        map<int, int>::iterator kkkit = kkk.begin();
                        int tempvalue = 0;
                        int tempkey = 0;
                        for (; kkkit!=kkk.end(); kkkit++) {
                            int value = kkkit->second;
                            if (value>=tempvalue) {
                                tempvalue = value;
                                tempkey = kkkit->first;
                            }
                        }
                        saverowcolint = tempkey;
                        break;
                    }
                }
                
                if (!samemergeunit.empty() && !rowunit.empty()) {
                    DeleteUnitList samemergeunittemp = samemergeunit;
                    DeleteUnitList rowunittemp = rowunit;
                    DeleteUnitList colunittemp = colunit;

                    fnmap.insert(pair<int, DeleteUnitList>(samemergeunittemp.size()+saverowcolint,samemergeunittemp));
                    coltotalunitList.remove(colunittemp);
                    rowtotalunitList.erase(rowtotalunitdelit++);
                }
                samemergeunit.clear();
                
            }
            {//单独循环出单行
                rowtotalunitdelit = rowtotalunitList.begin();
                for (;rowtotalunitdelit!=rowtotalunitList.end();rowtotalunitdelit++){
                    DeleteUnitList tempmap = * rowtotalunitdelit;
                    DeleteUnitListIterator it = tempmap.begin();
                    it++;
                    fnmap.insert(pair<int, DeleteUnitList>(tempmap.size()+*it,tempmap));
                }
                coltotalunitdelit = coltotalunitList.begin();
                for (;coltotalunitdelit!=coltotalunitList.end();coltotalunitdelit++){
                    DeleteUnitList tempmap = * coltotalunitdelit;
                    DeleteUnitListIterator it = tempmap.begin();
                    it++;
                    fnmap.insert(pair<int, DeleteUnitList>(tempmap.size()+*it,tempmap));
                }
            }
            
            
        }
        
        return fnmap;
    }


    
    pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    bool flag = true;
    
    void *thr_fun(void *arge)
    {
        /*
        GameLayer *tempLay=(GameLayer *)arge;
        
        struct timeval now;
        struct timespec outtime;
        
        
        while (flag) {
            log("thr_fun");
            
            
            gettimeofday(&now, NULL);
            outtime.tv_sec = now.tv_sec;
            outtime.tv_nsec = now.tv_usec+10000000;
            if (outtime.tv_nsec>=1000000000) {
                outtime.tv_sec+=1;
                outtime.tv_nsec=1000000000-outtime.tv_nsec;
            }
            pthread_mutex_lock(&mutex);
            pthread_cond_timedwait(&cond, &mutex, &outtime);
            pthread_mutex_unlock(&mutex);
            
        }
        */
        return NULL;
    }
    
    

#pragma mark click delegate begin
    
    void GameLayer::clickAtInde(CellIndex index)
    {
        if (isKoCellIndex(index) && !getCellWithIndex(index)) {
            return;
        }
        CCLOG("---> GameLayer : click at index column=%d row=%d tag=%d\r\n",index.columnPos,index.rowPos,index.rowPos*CELLNUM+index.columnPos);
        
    }
    
    void GameLayer::direction(MoveDirection dir,CellIndex lastedClick)
    {
        CellIndex _tempIndex = compute(dir,lastedClick);
        if (_tempIndex.columnPos!=-1 && _tempIndex.rowPos!=-1  && getCellWithIndex(_tempIndex) && getCellWithIndex(lastedClick)){
            registTwoCell(lastedClick, _tempIndex);
        }
    }
    
    CellIndex GameLayer::compute(MoveDirection dir,CellIndex lastedClick)
    {
        CellIndex _tempIndex=lastedClick;
        bool flag=false;
        if (dir==DOWN) {
            _tempIndex.rowPos-=1;
            flag=_tempIndex.rowPos<0?false:true;
            //若_lasted正上方存在则移动
        }
        if (dir==UP) {
            _tempIndex.rowPos+=1;
            flag=_tempIndex.rowPos>(CELLNUM-1)?false:true;
            //若_lasted正下方存在则移动
        }
        if (dir==LEFT) {
            _tempIndex.columnPos-=1;
            flag=_tempIndex.columnPos<0?false:true;
            //若_lasted正左方存在则移动
        }
        if (dir==RIGHT) {
            _tempIndex.columnPos+=1;
            flag=_tempIndex.columnPos>(CELLNUM-1)?false:true;
            //若_lasted正右方存在则移动
        }
        if (flag) {
            return _tempIndex;
        }
        _tempIndex.columnPos = -1;
        _tempIndex.rowPos = -1;
        return _tempIndex;
    }
    
    CellIndex GameLayer::compute2(MoveDirection dir,CellIndex lastedClick)
    {
        CellIndex _tempIndex=lastedClick;
        bool flag=false;
        if (dir==DOWN) {
            _tempIndex.rowPos-=1;
            flag=_tempIndex.rowPos<0?false:true;
            //若_lasted正上方存在则移动
        }
        if (dir==UP) {
            _tempIndex.rowPos+=1;
            flag=_tempIndex.rowPos>6?false:true;
            //若_lasted正下方存在则移动
        }
        if (dir==LEFT) {
            _tempIndex.columnPos-=1;
            flag=_tempIndex.columnPos<0?false:true;
            //若_lasted正左方存在则移动
        }
        if (dir==RIGHT) {
            _tempIndex.columnPos+=1;
            flag=_tempIndex.columnPos>6?false:true;
            //若_lasted正右方存在则移动
        }
        if (flag) {
            return _tempIndex;
        }
        _tempIndex.columnPos = -1;
        _tempIndex.rowPos = -1;
        return _tempIndex;
    }
    
    /*!
     click callback
     change cellStatus
     */
    void GameLayer::willAnimate(Layer *cell)
    {
        
    }
    
    void GameLayer::moving(Layer *cell)
    {
        _isMoving.push_back(1);
    }
    
    void GameLayer::deleteing(Layer *cell)
    {
        _isDeleteing.push_back(1);
    }
    void GameLayer::droping(Layer *cell)
    {
        _isDropping.push_back(1);
        _lastDropCell = dynamic_cast<FruntCell *>(cell);
    }
    
    
    void GameLayer::movingComplete(Layer *cell)
    {
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        temp->joinCellAnimation(OnlyMoveAnimation2, temp->getPreviseCellIndex(),temp->getCellIndex());
        if (!_isMoving.empty()) {
            _isMoving.pop_back();
        }
        temp->showAnimation();
    }

    void GameLayer::movingComplete2(Layer *cell)
    {
        if (!_isMoving.empty()) {
            _isMoving.pop_back();
        }
    }

    void GameLayer::deleteComplete(Layer *cell)
    {
        this->removeChild(cell);
        if (!_isDeleteing.empty()) {
            _isDeleteing.pop_back();
        }
        if (_isDeleteing.empty()) {//所有cell删除之后执行下落//先下落，再根据＝5的状态判断左右下落
            
            //qujianlist = findQuJian();
            IIIIII();
            _lastDeleteCell = NULL;
        }
    }
    
    void GameLayer::lighting(Layer *cell)
    {
        _islighting.push_back(1);
    }
    void GameLayer::lightComplete(Layer *cell)
    {
        if (!_islighting.empty()) {
            _islighting.pop_back();
        }
        if (_isDeleteing.empty()) {//所有cell删除之后执行下落//先下落，再根据＝5的状态判断左右下落
            
            //qujianlist = findQuJian();
            IIIIII();
            _lastDeleteCell = NULL;
        }
    }
    
    void GameLayer::moveAndDeleteing(Layer *cell)
    {
        _isMoveAndDeleteing.push_back(1);
    }
    void GameLayer::moveAndDeleteComplete(Layer *cell)
    {
        this->removeChild(cell);
        if (!_isMoveAndDeleteing.empty()) {
            _isMoveAndDeleteing.pop_back();
        }
        if (_isDeleteing.empty()) {
            IIIIII();
            _lastDeleteCell = NULL;
        }
    }
    
    void GameLayer::dropComplete(Layer *cell)
    {
        if (!_isDropping.empty()) {
            _isDropping.pop_back();
        }
        if (_isDropping.empty()) {
            
            for (int col = 0; col<CELLNUM; col++) {
                for (int row = 0; row<CELLNUM; row++) {
                    FruntCell *cell1=getCellWithIndex({row,col});
                    if (cell1) {
                        cell1->_canTouch = true;
                    }
                }
            }
            _lastDropCell = NULL;
        }
    }
    
    /*
    QUJIANlist GameLayer::findQuJian()
    {
        //尝试从cell的可掉落口?统计出某个区间右那几个下落口负责，具体格式//(区间开头,区间结尾)(下落口)//，下落口可能相同，可能不同
        list<long long>qujianlist;
        list<long long>chuizhiqujianlist;
        //统计下落口及其负责的区间
        list<long long>::iterator frontdropTumpit;
        list<long long>::iterator behinddropTumpit;
        behinddropTumpit = frontdropTumpit = dropTumpit = dropTump.begin();
        
        for (int i=0; dropTumpit!=dropTump.end(); dropTumpit++,i++) {
            behinddropTumpit = frontdropTumpit = dropTumpit;
            
            CellIndex index = intToColRow(*dropTumpit);
            if (isNormalCellIndex({index.rowPos,index.columnPos})) {
                
                CellIndex behindindex;
                CellIndex frontindex;
                //找左侧可下落的
                bool haveleft = false;
                for (behinddropTumpit--; behinddropTumpit!=dropTump.begin(); behinddropTumpit--) {
                    CellIndex index = intToColRow(*behinddropTumpit);
                    if (isNormalCellIndex({index.rowPos,index.columnPos})) {
                        behindindex = index;
                        haveleft = true;
                        break;
                    }
                }
                //找右侧可下落的
                bool haveright = false;
                for (frontdropTumpit++; frontdropTumpit!=dropTump.end(); frontdropTumpit++) {
                    CellIndex index = intToColRow(*frontdropTumpit);
                    if (isNormalCellIndex({index.rowPos,index.columnPos})) {
                        frontindex = index;
                        haveright = true;
                        break;
                    }
                }
                
                if (!haveleft) {//左侧没有可下落的
                    if (index.columnPos!=0) {//非最最左边界
                        qujianlist.push_front(squareandbehand(index.columnPos ,0, colRowToInt(index.columnPos, index.rowPos)));
                    }
                }else if (haveleft && behindindex.columnPos<index.columnPos) {//左侧右可下落的，且不靠近
                    qujianlist.push_front(squareandbehand(index.columnPos ,behindindex.columnPos, colRowToInt(index.columnPos, index.rowPos)));
                }
                if (!haveright) {//右侧没可下落的
                    if (index.columnPos!=CELLNUM-1) {//非最右侧边界
                        qujianlist.push_front(squareandbehand(index.columnPos ,CELLNUM-1, colRowToInt(index.columnPos, index.rowPos)));
                    }
                }else
                    if (haveright && frontindex.columnPos>index.columnPos) {//右侧有可下落的，切不靠近
                        qujianlist.push_front(squareandbehand(index.columnPos ,frontindex.columnPos, colRowToInt(index.columnPos, index.rowPos)));
                    }
                if ((haveleft && behindindex.columnPos+1==index.columnPos &&
                     haveright && frontindex.columnPos-1==index.columnPos)||
                    (!haveleft && index.columnPos==0 &&
                     haveright && frontindex.columnPos-1==index.columnPos)||
                    (!haveright && index.columnPos==CELLNUM-1 &&
                     haveleft && behindindex.columnPos+1==index.columnPos)) {//左右都有可下落且靠近的/左侧没有可下落且是左边边界和且右边有可下落且靠近的/右侧没有可下落且是有边界和左侧有可下落且靠近的
                        qujianlist.push_front(squareandbehand(index.columnPos ,index.columnPos, colRowToInt(index.columnPos, index.rowPos)));
                    }
            }
        }
        
        
        return qujianlist;
    }
    */

    void GameLayer::IIIIII()
    {
        for (int i=0; i<CELLNUM; i++) {
            addCount[i] = 1;
        }
        /////////////
        bool flag = false;
        int ff = 1;
        do {
            flag = false;
            FruntCell *cell;
            for (int row=0; row<CELLNUM; row++) {
                for (int col=0; col<CELLNUM; col++) {

                    
                    if (isNormalCellIndexAndNullCell({row,col}) && isNormalCellIndex({row,col}) && row==CELLNUM-1) {//最顶层下落点没有cell，即添加cell
                        long long tag = colRowToInt(col, row);
                        dropTumpit = dropTump.begin();
                        for (; dropTumpit!=dropTump.end(); dropTumpit++) {
                            long long temp = *dropTumpit;
                            if (temp==tag) {
                                tag = true;
                                break;
                            }
                        }
                        if (tag) {
                            
                            cell = createNewCell2(col, (int)addCount[col]+row, col, row, CELLNUM);
                            CellIndex tempindex;
                            tempindex.columnPos = col;
                            tempindex.rowPos = row;
                            cell->joinCellAnimation(DropAnimation, tempindex,{(int)addCount[col]+row,col});
                            addCount[col] = addCount[col]+1;
                            
                            log("row %d col %d to create",row,col);
                        }
                        
                    }
                    
                    
                    if (isNormalCellIndexAndCell({row,col})) {//有cell则判断左右或直接下落
                        bool downIsNull = false;
                        bool downIsCell = false;
                        bool downIsKo = false;
                        if (row!=0) {
                            downIsNull = isNormalCellIndexAndNullCell({row-1,col});
                            downIsCell = isNormalCellIndexAndCell({row-1,col});
                            downIsKo = isKoCellIndex({row-1,col});
                        }
                        
                    
                        bool downLeftIsNull = false;
                        bool downRightIsNUll = false;
                        bool leftIsKo = false;
                        bool rightIsKo = false;
                        
                        //向右下落
                        if (row!=0 &&
                            isNormalCellIndexAndNullCell({row-1,col+1}) && col!=CELLNUM-1) {
                            downRightIsNUll = true;
                        }
                        if (downRightIsNUll && isKoCellIndex({row,col+1}) && col!=CELLNUM-1) {
                            for (int i=row; i<CELLNUM ; i++) {
                                for (int j=col; j>=0; j--) {
                                    if (isKoCellIndex({i,j+1}) && isNormalCellIndex({i,j})) {
                                        rightIsKo = true;
                                        
                                        break;
                                    }
                                }
                                
                                for (int k=i; k>row; k--) {
                                    if (isKoCellIndex({k,col})) {
                                        break;
                                    }
                                    if (isNormalCellIndexAndNullCell({k,col})) {
                                        continue;
                                    }
                                    if (isNormalCellIndexAndCell({k,col})) {
                                        rightIsKo = false;
                                        break;
                                    }
                                }
                                if (rightIsKo) {
                                    break;
                                }
                            }
                        }
                        
                        //向左下落
                        if (col!=0 && row!=0 &&
                            isNormalCellIndexAndNullCell({row-1,col-1})) {
                            downLeftIsNull = true;
                        }
                        if (downLeftIsNull && isKoCellIndex({row,col-1})) {
                            for (int i=row; i<CELLNUM; i++) {
                                for (int j=col; j<CELLNUM; j++) {
                                    if (isKoCellIndex({i,j-1}) && isNormalCellIndex({i,j})) {
                                        leftIsKo = true;
                                        break;
                                    }
                                }
                                
                                for (int k=i; k>row; k--) {
                                    if (isKoCellIndex({k,col})) {
                                        break;
                                    }
                                    if (isNormalCellIndexAndNullCell({k,col})) {
                                        continue;
                                    }
                                    if (isNormalCellIndexAndCell({k,col})) {
                                        leftIsKo = false;
                                        break;
                                    }
                                }
                                if (leftIsKo) {
                                    break;
                                }
                            }
                        }
                        
                        
                        cell = getCellWithIndex({row,col});
                        if (downIsNull) {
                            flag = true;
                            cell->joinCellAnimation(DropAnimation, {row-1,col}, cell->getCellIndex());
                            log("row %d col %d to down row %d col %d",row,col,row-1,col);
                            
                        }else
                        if ((downIsCell || downIsKo) && downLeftIsNull && leftIsKo) {
                            flag = true;
                            cell->joinCellAnimation(DropAnimation, {row-1,col-1}, cell->getCellIndex());
                            log("row %d col %d to lef row %d col %d",row,col,row-1,col-1);
                            
                        }else
                        if ((downIsCell || downIsKo) && downRightIsNUll && rightIsKo) {
                            
                            flag = true;
                            log("row %d col %d to right row %d col %d",row,col,row-1,col+1);
                            if (col==8) {
                                
                            }else
                                cell->joinCellAnimation(DropAnimation, {row-1,col+1}, cell->getCellIndex());
                            
                        }
                    }
                }
            }
            
            
            
            if (flag==false && ff == 1) {
                flag =true;
                ff++;
            }
        } while (flag);
        
        for (int i=0; i<CELLNUM; i++) {
            for (int j=0; j<CELLNUM; j++) {
                FruntCell *cell1=getCellWithIndex({i,j});
                if (cell1) {
                    cell1->showAnimation();
                }
            }
        }
        
        /*
        return;
        /////////////
        list<long long>::iterator chuizhiqujianlistit = qujianlist.begin();
        for (; chuizhiqujianlistit!=qujianlist.end(); chuizhiqujianlistit++) {
            CellSquare square = benhandsquare(*chuizhiqujianlistit);
            DDDDDD(square.columnPos1, square.columnPos2, 0);//递归填坑
        }
        chuizhiqujianlistit = qujianlist.begin();
        for (; chuizhiqujianlistit!=qujianlist.end(); chuizhiqujianlistit++) {
            CellSquare square = benhandsquare(*chuizhiqujianlistit);
            DDDDDD(square.columnPos1, square.columnPos2, 0);//递归填坑
        }
         */
    }
    
    /*
    FruntCell *GameLayer::DDDDDD(int fromcol,int endcol,long long dropcolrow)
    {
        JJJJJJ();
        CellIndex returnColrow = {-1,-1};
        if (dropcolrow!=0) {
            returnColrow = intToColRow(dropcolrow);
        }
        //
        //发现有可侧滑时，通过当前是左往右，还是右往左来拉可侧滑口左侧或右侧的cell
        //
        if (fromcol==endcol) {
            for (int row = 0; row<CELLNUM; row++) {
                
                bool zhongjianyoumeiyouzhedang = false;
                long long koindexcolrow;
                for (int i=row; i<CELLNUM; i++) {
                    if (isKoCellIndex({i,fromcol})) {
                        zhongjianyoumeiyouzhedang = true;
                        koindexcolrow = colRowToInt(fromcol, i);
                        break;
                    }
                }
                CellIndex cehuaindex = intToColRow(koindexcolrow);
                FruntCell *cell = getCellWithIndex({row,fromcol});
                //todo 发现可侧滑
                
                if (isNormalCellIndexAndNullCell({row,endcol})&&
                    zhongjianyoumeiyouzhedang)
                {
                    if (isNormalCellIndex({cehuaindex.rowPos,cehuaindex.columnPos+1})) {
                        cell = getCellWithIndex({cehuaindex.rowPos,cehuaindex.columnPos+1});
                    }else
                    if (isNormalCellIndex({cehuaindex.rowPos,cehuaindex.columnPos-1}) ){
                        cell = getCellWithIndex({cehuaindex.rowPos,cehuaindex.columnPos-1});
                    }
                    if (cell) {
                        cell->joinCellAnimation(DropAnimation, {row,fromcol}, cell->getCellIndex());
                        JJJJJJ();
                    }
                    
                }else
                 
                if (isNormalCellIndexAndNullCell({row,endcol})&&
                    !zhongjianyoumeiyouzhedang) {
                    cell = createNewCell2(endcol, (int)addCount[endcol]+row, endcol, row, CELLNUM);
                    CellIndex tempindex;
                    tempindex.columnPos = endcol;
                    tempindex.rowPos = row;
                    cell->joinCellAnimation(DropAnimation, tempindex,{(int)addCount[endcol]+row,endcol});
                    addCount[endcol]=addCount[endcol]+1;
                    _lastDropCell = cell;
                }
                if (cell && row==returnColrow.rowPos) {
                    return cell;
                }
            }
            return _lastDropCell;
        }
        if (fromcol>endcol) {//向右扫描f:4 e:0
            for (int col=endcol; col<=fromcol; col++) {
                
                long long currenttopreturncolrow = 0;
                for (int row=0; row<CELLNUM; row++) {
                    if (isNormalCellIndex({row,col}) &&
                        isNormalCellIndex({row+1,col+1})) {
                        currenttopreturncolrow = colRowToInt(col+1,row+1);
                    }
                }
                
                CellIndex topIndex = intToColRow(currenttopreturncolrow);
                topIndex.rowPos = topIndex.rowPos-1;
                long long koindexcolrow;
                for (int row=0; row<CELLNUM; row++) {
                    bool zhongjianyoumeiyouzhedang = false;
                    for (int i=row; i<topIndex.rowPos; i++) {
                        if (isKoCellIndex({i,col})) {
                            zhongjianyoumeiyouzhedang = true;
                            koindexcolrow = colRowToInt(col+1, i);
                            break;
                        }
                    }
                    CellIndex cehuaindex = intToColRow(koindexcolrow);
                    FruntCell *cell = getCellWithIndex({row,col});
                    //todo 发现可侧滑
                    if (cell==NULL && zhongjianyoumeiyouzhedang
                        && isNormalCellIndexAndNullCell({row,col})
                        && isNormalCellIndex({cehuaindex.rowPos,cehuaindex.columnPos})
                        && row<=topIndex.rowPos) {
                        if (col==fromcol) {
                            cell = getCellWithIndex({cehuaindex.rowPos,col-1});
                        }else
                            cell = DDDDDD(fromcol, col+1, koindexcolrow);
                        if (cell) {
                            cell->joinCellAnimation(DropAnimation, {row,col}, cell->getCellIndex());
                            JJJJJJ();
                        }
                    }else
                    if (cell==NULL && isNormalCellIndexAndNullCell({row,col}) && !zhongjianyoumeiyouzhedang && row<=topIndex.rowPos && col!=fromcol) {
                        cell = DDDDDD(fromcol, col+1, currenttopreturncolrow);
                        cell->joinCellAnimation(DropAnimation, {row,col}, cell->getCellIndex());
                    }
                    if (row==returnColrow.rowPos && returnColrow.rowPos!=-1) {
                        return cell;
                    }
                }
            }
        }
        if (fromcol<endcol) {//想左扫描 f:4 e:8
            for (int col = endcol; col>=fromcol; col--) {

                long long currenttopreturncolrow = 0;
                for (int row=0; row<CELLNUM; row++) {
                    if (isNormalCellIndex({row,col}) &&
                        isNormalCellIndex({row+1,col-1})) {
                        currenttopreturncolrow = colRowToInt(col-1,row+1);
                    }
                }
                
                CellIndex topIndex = intToColRow(currenttopreturncolrow);
                topIndex.rowPos = topIndex.rowPos-1;
                long long koindexcolrow;
                for (int row=0; row<CELLNUM; row++) {
                    bool zhongjianyoumeiyouzhedang = false;
                    for (int i=row; i<topIndex.rowPos; i++) {
                        if (isKoCellIndex({i,col})) {
                            zhongjianyoumeiyouzhedang = true;
                            koindexcolrow = colRowToInt(col-1, i);
                            break;
                        }
                    }
                    CellIndex cehuaindex = intToColRow(koindexcolrow);
                    FruntCell *cell = getCellWithIndex({row,col});
                    //todo 发现可侧滑
                    if (cell==NULL && zhongjianyoumeiyouzhedang
                        && isNormalCellIndexAndNullCell({row,col})
                        && isNormalCellIndex({cehuaindex.rowPos,cehuaindex.columnPos})
                        && row<=topIndex.rowPos ) {
                        if (col==fromcol) {
                            cell = getCellWithIndex({cehuaindex.rowPos,col+1});
                        }else
                            cell = DDDDDD(fromcol, col-1, koindexcolrow);
                        if (cell) {
                            cell->joinCellAnimation(DropAnimation, {row,col}, cell->getCellIndex());
                            JJJJJJ();
                        }
                        
                    }else
                    if (cell==NULL && isNormalCellIndexAndNullCell({row,col}) && !zhongjianyoumeiyouzhedang&& row<=topIndex.rowPos && col!=fromcol) {
                        cell = DDDDDD(fromcol, col-1, currenttopreturncolrow);
                        cell->joinCellAnimation(DropAnimation, {row,col}, cell->getCellIndex());
                    }
                    if (row==returnColrow.rowPos && returnColrow.rowPos!=-1) {
                        return cell;
                    }
                }
                
            }
        }

        return  NULL;
    }
    */
    
    /*
    void GameLayer::JJJJJJ()
    {
        //重置dropCount中每列的空缺cell数量
        for (int j=0; j<CELLNUM; j++) {
            dropCount[j].clear();
            for (int i = 0; i<CELLNUM; i++) {
                if (isKoCellIndex({i,j})) {
                    continue;
                }
                if (isNormalCellIndexAndNullCell({i,j})) {
                    dropCount[j].push_back(i);
                }
            }
        }
        for (int col=0; col<CELLNUM; col++) {//先下落现有的
            list<int> tempdrop = dropCount[col];
            if (tempdrop.empty()) {
                continue;
            }
            //应该从下向上统计，遇到＝5list中的cell需下落个数count ＋1，遇到＝－1、100、CDestoryKO，count重置
            map<long long ,int> temodropmap;
            int ddcount = 0;
            for (int row = 0; row<CELLNUM; row++) {
                if (getCellWithIndex({row,col}) && ddcount>0){//正常cell,切可下落个数不为空
                    temodropmap.insert(pair<long long, int>(colRowToInt(col, row),ddcount));
                }
                if (isNormalCellIndexAndNullCell({row,col})) {//遇到可下落点，可下落书＋＋
                    ddcount++;
                }
                if (isKoCellIndex({row,col})) {//当遇到阻碍物时，重置加入flag
                    ddcount=0;
                }
            }
            {
                map<long long ,int>::iterator temodropmapit = temodropmap.begin();
                for (; temodropmapit!=temodropmap.end(); temodropmapit++) {
                    CellIndex index = intToColRow(temodropmapit->first);
                    int tempcount = temodropmapit->second;
                    FruntCell *cell1=getCellWithIndex({index.rowPos,index.columnPos});
                    if (cell1 && tempcount>0) {
                        index.rowPos-=tempcount;
                        cell1->joinCellAnimation(DropAnimation, index,cell1->getCellIndex());
                    }
                }
            }
        }
    }
    
    bool GameLayer::KKKKKK(CellSquare square,int row)
    {
        bool hascehua = false;
        if (square.columnPos1==square.columnPos2) {
            int col = square.columnPos1;
            if (1) {
                if (isNormalCellIndexAndNullCell({row,col}) &&
                    !isNormalCellIndex({row+1,col}) &&
                    isNormalCellIndexAndCell({row-1,col})) {
                    FruntCell *cell1= getCellWithIndex({row+1,col+1});
                    FruntCell *cell2= getCellWithIndex({row+1,col-1});
                    if (cell1 && isNormalCellIndex({row+1,col+1})) {
                        CellIndex index;
                        index.rowPos = row;
                        index.columnPos = col;
                        cell1->joinCellAnimation(DropAnimation, index,cell1->getCellIndex());
                        hascehua = true;
                    }else
                        if (cell2 && isNormalCellIndex({row+1,col-1})) {
                            CellIndex index;
                            index.rowPos = row;
                            index.columnPos = col;
                            cell1->joinCellAnimation(DropAnimation, index,cell1->getCellIndex());
                            hascehua = true;
                        }
                }
            }
        }
        if (square.columnPos1>square.columnPos2) {
            for (int col=square.columnPos1; col>=square.columnPos2; col--) {
                if (1) {
                    if (isNormalCellIndexAndNullCell({row,col}) &&
                        !isNormalCellIndex({row+1,col}) &&
                        isNormalCellIndexAndCell({row-1,col})) {
                        if (col+1!=CELLNUM-1 && row+1!=CELLNUM-1) {
                            FruntCell *cell1=getCellWithIndex({row+1,col+1});
                            if (cell1) {
                                CellIndex index;
                                index.rowPos = row;
                                index.columnPos = col;
                                cell1->joinCellAnimation(DropAnimation, index,cell1->getCellIndex());
                                hascehua = true;
                            }
                        }
                    }
                }
            }
        }
        if (square.columnPos1<square.columnPos2) {
            for (int col=square.columnPos1+1; col<=square.columnPos2; col++) {
                if (1) {
                    if (isNormalCellIndexAndNullCell({row,col}) &&
                        !isNormalCellIndex({row+1,col}) &&
                        isNormalCellIndexAndCell({row-1,col})) {
                        if (col-1!=0 && row+1!=CELLNUM-1) {
                            FruntCell *cell1 = getCellWithIndex({row+1,col-1});
                            if (cell1) {
                                
                                CellIndex index;
                                index.rowPos = row;
                                index.columnPos = col;
                                cell1->joinCellAnimation(DropAnimation, index,cell1->getCellIndex());
                                hascehua = true;
                            }
                            
                        }
                    }
                }
            }
        }
        
        return hascehua;
    }
    */

    
    
#pragma mark click delegate end
    
    void GameLayer::timeCallBack()
    {
        if (_isMoving.empty() && _isDropping.empty() && _isDeleteing.empty() && _isMoveAndDeleteing.empty() && _islighting.empty()) {
            findCurrent();
            _exchangeClick = {-1,-1};
            _exchangeClick2 = {-1,-1};
        }
    }

    
    /*
    bool GameLayer::TODO_DeleteCell()
    {
        DeleteFNMap delmap=TODO_FindDeleteCells();
        if (delmap.empty()) {
            return false;
        }
        {
            DeleteFNMapIterator delit=delmap.begin();
            for (;delit!=delmap.end();delit++)
            {
                //爆炸效果跟随元素或是在固定位置
                long long  type = delit->first;
                CellIndex index = intToColRow(type);
                long long  count = type - colRowToInt(index.columnPos, index.rowPos);
                
                DeleteUnitList map = delit->second;
                DeleteUnitListIterator mapit = map.begin();
                for (; mapit!=map.end(); mapit++) {
                    CellIndex temp = intToColRow(*mapit);
                    Node *node1=this->getChildByTag(temp.rowPos*CELLNUM+temp.columnPos);
                    if (temp.rowPos==index.rowPos && temp.columnPos==index.columnPos && count>3) {
                        if (node1) {
                            FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
                            if (count==4) {
                                
                            }
                            if (count>=5) {
                                
                            }
                        }
                    }else
                    {
                        if (node1) {
                            FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
                            cell1->joinCellAnimation(DeleteAnimation, temp,cell1->getCellIndex());
                            cell1->setCellStatus(cellDestory);
                        }
                    }
                }
            }
        }
        return true;
    }
     */
    /*
    bool GameLayer::TODO_ResetCell()
    {
        
        for (int i=0; i<CELLNUM; i++) {
            for (int j=0; j<CELLNUM; j++) {
                
                FruntCell *cell=getCellWithIndex({i,j});
                if (cell  &&
                    !cell->isCellIndexEqual(cell->getCellIndex(), cell->getPreviseCellIndex()) &&
                    !cell->isAnimation()) {
                    
                    Node *node2=this->getChildByTag(cell->getPreviseCellIndex().rowPos*CELLNUM+cell->getPreviseCellIndex().columnPos);
                    FruntCell *cell2=dynamic_cast<FruntCell *>(node2);
                    
                    if (cellsStatus[cell2->getCellIndex().rowPos][cell2->getCellIndex().columnPos]==0) {
                        cell->joinCellAnimation(OnlyMoveAnimation2, cell->getPreviseCellIndex(),cell->getCellIndex());
                    }else
                        cell->setNowIndex(cell->getPreviseCellIndex().rowPos, cell->getPreviseCellIndex().columnPos);
                    
                }
            }
        }
        return true;
    }

    */
    void GameLayer::showTag()
    {
        for (int row=0; row<CELLNUM; row++) {
            CCLOG("-------->");
            CCLOG("%d %d %d %d %d %d %d",cellsStatus[row][0],cellsStatus[row][1],cellsStatus[row][2],cellsStatus[row][3],cellsStatus[row][4],cellsStatus[row][5],cellsStatus[row][6]);
            CCLOG("<--------");
        }
    }
    
    
    
    void GameLayer::registTwoCell(CellIndex c1, CellIndex c2)
    {
        Node *node1=this->getChildByTag(c1.rowPos*CELLNUM+c1.columnPos);
        Node *node2=this->getChildByTag(c2.rowPos*CELLNUM+c2.columnPos);
        FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
        FruntCell *cell2=dynamic_cast<FruntCell *>(node2);
        if (node1!=NULL&&node2!=NULL &&
            !cell1->isAnimation() && !cell2->isAnimation()) {
    
            //移动的cell在可消除cell序列中，则安步执行所有不可点击、消除、新增cell、下落cell、所有可点击步骤
            //移动的cell不在可消除cell序列中，先让所有cell不可颠，动画完成后让所有cell可点
            DeleteFNMapIterator it = prefnmap.begin();
            bool have = false;
            for (; it!=prefnmap.end(); it++) {
                CellIndex index1 = preCanDeleteCurrentCellIndex(it->first);
                CellIndex index2 = preCanDeleteTargetCellIndex(it->first);
                if ((isCellIndexEqual(c1, index1) && isCellIndexEqual(c2, index2)) ||
                    (isCellIndexEqual(c1, index2) && isCellIndexEqual(c2, index1))) {
                    have = true;
                    prefnmap.erase(it);
                    break;
                }
            }
            if (have) {
                cell1->joinCellAnimation(OnlyMoveAnimation2, c2,cell1->getCellIndex());
                cell2->joinCellAnimation(OnlyMoveAnimation2, c1,cell2->getCellIndex());
                _exchangeClick = c1;
                _exchangeClick2 = c2;
            }else
            {
                cell1->joinCellAnimation(OnlyMoveAnimation, c2,cell1->getCellIndex());
                cell2->joinCellAnimation(OnlyMoveAnimation, c1,cell2->getCellIndex());
            }
            cell1->showAnimation();
            cell2->showAnimation();
        }
    }

    
    
   
  
    
    void GameLayer::update(float dt)
    {
        
        float ct1 = progress->getPercentage();
        
        if (ct1 != 0)
        {
            dtf = ct1 - 0.1f;
            progress->setPercentage(dtf);
        }
        else
        {
            //            CCTransitionFade *tScene = CCTransitionFade::create(2, HelloWorld::scene(), ccWHITE);
            //            Director::getInstance()->replaceScene(tScene);
        }
        timeCallBack();
        
    }
    
    
    void GameLayer::findCurrent()
    {
        
        DeleteFNMap beDelMap = TODO_FindDeleteCells();
        if (beDelMap.empty()) {
            if (prefnmap.empty()) {
                DeleteFNMap delmap;
                for (int row=0; row<CELLNUM; row++) {
                    for (int column=0; column<CELLNUM; column++) {
                        for (int i =1; i<=4; i++) {
                            CellIndex lastedindex;
                            lastedindex.rowPos = row;
                            lastedindex.columnPos = column;
                            CellIndex index = compute2((MoveDirection)i,lastedindex);
                            if (index.rowPos!=-1 && index.columnPos!=-1) {
                                DeleteFNMap temp = TODO_FindDeleteCells2(row, column, index.rowPos, index.columnPos);
                                DeleteFNMapIterator delit=temp.begin();
                                for (;delit!=temp.end();delit++)
                                {//e.g. 5004003
                                    long long celldropint = delit->first+colRowToInt(lastedindex.columnPos, lastedindex.rowPos)+colRowToInt2(index.columnPos, index.rowPos);
                                    delmap.insert(pair<long long, DeleteUnitList>(celldropint,delit->second));
                                }
                            }
                        }
                    }
                }
                prefnmap.clear();
                prefnmap = delmap;
                if (delmap.empty()) {
                    
                }
            }
            
        }else
        {
            
            //有下落过程时，所有cell禁止touch
            for (int col = 0; col<CELLNUM; col++) {
                
                for (int row = 0; row<CELLNUM; row++) {
                    Node *node1=this->getChildByTag(row*CELLNUM+col);
                    FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
                    if (cell1) {
                        cell1->_canTouch = false;
                    }
                }
                dropCount[col].clear();
            }
            
            DeleteFNMapIterator it = beDelMap.begin();
            FruntCell *cellt;
            for (; it!=beDelMap.end(); it++) {
                CellIndex centerindex = intToColRow(it->first);
                int count = (int)(it->first - colRowToInt(centerindex.columnPos, centerindex.rowPos));
#warning 这里centerindex暂时没法直出
                if (!isCellIndexEqual(_exchangeClick, {-1,-1})) {
                    centerindex = {-1,-1};
                }
                
                DeleteUnitList list = it->second;
                DeleteUnitListIterator listit = list.begin();
                for (; listit!=list.end(); listit++) {
                    CellIndex temp = intToColRow(*listit);
                    FruntCell *cell1=getCellWithIndex(temp);
                    if (cell1) {
                        if (count==3) {
                            cell1->joinCellAnimation(DeleteAnimation, cell1->getCellIndex(),cell1->getCellIndex());
                        }else
                            if (count>=4) {
                                /*
                                DeleteFNMapIterator premapit = prefnmap.begin();
                                for (; premapit!=prefnmap.end(); premapit++) {
                                    
                                }
                                */
                                if (isCellIndexEqual(temp, _exchangeClick))
                                {
                                    cell1->joinCellAnimation(LightAnimate, cell1->getCellIndex(),cell1->getCellIndex());
                                    centerindex = _exchangeClick;
                                }else
                                if (isCellIndexEqual(temp, _exchangeClick2))
                                {
                                    cell1->joinCellAnimation(LightAnimate, cell1->getCellIndex(),cell1->getCellIndex());
                                    centerindex = _exchangeClick2;
                                }else
                                if (isCellIndexEqual(centerindex, temp)) {
                                    cell1->joinCellAnimation(LightAnimate, cell1->getCellIndex(),cell1->getCellIndex());
                                }else
                                {
                                    cell1->joinCellAnimation(DeleteAnimation, cell1->getCellIndex(),cell1->getCellIndex());
                                }
                            }
                        cellt = cell1;
                        dropCount[temp.columnPos].push_back(temp.rowPos);
                    }
                }
            }
            _lastDeleteCell = cellt;
            for (int i=0; i<CELLNUM; i++) {
                for (int j=0; j<CELLNUM; j++) {
                    FruntCell *cell1=getCellWithIndex({i,j});
                    if (cell1) {
                        cell1->showAnimation();
                    }
                }
            }
            prefnmap.clear();
            
        }
    }
    
    
    DeleteFNMap GameLayer::TODO_FindDeleteCells2(int trow,int tcolumn,int trow2,int tcolumn2)
    {
        DeleteFNMap fnmap;
        DeleteTotalUnitList rowtotalunitList;
        DeleteTotalUnitList coltotalunitList;
        
        {//按行／列找计算可通过滑动消失的cell
            
            for (int row=0; row<CELLNUM; row++) {
                std::string ss;
                for (int column=0; column<CELLNUM; column++) {
                    string sg = getCellTypeString(row, column);
                    if (trow==row && tcolumn==column) {
                        sg = getCellTypeString(trow2, tcolumn2);
                    }
                    if (trow2==row&& tcolumn2==column) {
                        sg = getCellTypeString(trow, tcolumn);
                    }
                    ss+=sg;
                }
                ss+='_';
                DeleteTotalUnitList temp = findRowDelete2(ss, row,trow,tcolumn,trow2,tcolumn2);
                DeleteTotalUnitListIterator delit=temp.begin();
                
                for (;delit!=temp.end();delit++)
                {
                    rowtotalunitList.push_back(*delit);
                }
            }
            for (int column=0; column<CELLNUM; column++) {
                std::string ss;
                for (int row=0; row<CELLNUM; row++) {
                    string sg = getCellTypeString(row, column);
                    if (trow==row && tcolumn==column) {
                        sg = getCellTypeString(trow2, tcolumn2);
                    }
                    if (trow2==row&& tcolumn2==column) {
                        sg = getCellTypeString(trow, tcolumn);
                    }
                    ss+=sg;
                }
                ss+='_';
                DeleteTotalUnitList temp = findColDelete2(ss, column,trow,tcolumn,trow2,tcolumn2);
                DeleteTotalUnitListIterator delit=temp.begin();
                for (;delit!=temp.end();delit++)
                {
                    coltotalunitList.push_back(*delit);
                }
            }
        }
        
        
        DeleteTotalUnitListIterator rowtotalunitdelit=rowtotalunitList.begin();
        DeleteTotalUnitListIterator coltotalunitdelit=coltotalunitList.begin();
        if (!rowtotalunitList.empty() || !coltotalunitList.empty()) {
            
        }
        
        if (rowtotalunitList.empty() || coltotalunitList.empty()) {
            for (;rowtotalunitdelit!=rowtotalunitList.end();rowtotalunitdelit++)
            {
                DeleteUnitList rowmap = * rowtotalunitdelit;
                DeleteUnitListIterator it = rowmap.begin();
                it++;
                if (rowmap.size()==3) {
                    fnmap.insert(pair<long long, DeleteUnitList>(rowmap.size(),rowmap));
                }
                if (rowmap.size()==4) {
                    fnmap.insert(pair<long long, DeleteUnitList>(rowmap.size(),rowmap));
                }
                
            }
            for (;coltotalunitdelit!=coltotalunitList.end();coltotalunitdelit++)
            {
                DeleteUnitList colmap = * coltotalunitdelit;
                if (colmap.size()==3) {
                    fnmap.insert(pair<long long, DeleteUnitList>(colmap.size(),colmap));
                }
                if (colmap.size()==4) {
                    fnmap.insert(pair<long long, DeleteUnitList>(colmap.size(),colmap));
                }
                
            }
        }else
        {
            
            DeleteTotalUnitList tempCompairRow;
            DeleteTotalUnitList tempCompairCol;
            rowtotalunitdelit = rowtotalunitList.begin();
            for (;rowtotalunitdelit!=rowtotalunitList.end();rowtotalunitdelit++)
            {
                DeleteUnitList rowunit = * rowtotalunitdelit;
                DeleteUnitList samemergeunit;
                long long saverowcolint;
                DeleteUnitList colunit;
                coltotalunitdelit = coltotalunitList.begin();
                for (;coltotalunitdelit!=coltotalunitList.end() && !rowunit.empty();coltotalunitdelit++){
                    colunit = * coltotalunitdelit;
                    
                    DeleteUnitList rowunit2 = rowunit;
                    DeleteUnitList colunit2 = colunit;
                    
                    DeleteUnitList temp;
                    temp.merge(rowunit2);
                    temp.merge(colunit2);
                    temp.sort();
                    DeleteUnitList samemergeunit2 = temp;
                    temp.unique();
                    if (temp.size()!=rowunit.size()+colunit.size()) {//有重复元素
                        samemergeunit = temp;
                        //下面通过map计数找出重复的cell的int表述
                        map<long long,long long> kkk;
                        DeleteUnitListIterator samemergeunit2it = samemergeunit2.begin();
                        for (; samemergeunit2it!=samemergeunit2.end(); samemergeunit2it++) {
                            long long value = kkk[*samemergeunit2it];
                            kkk[*samemergeunit2it] = ++value;
                        }
                        map<long long , long long>::iterator kkkit = kkk.begin();
                        long long tempvalue = 0;
                        long long tempkey = 0;
                        for (; kkkit!=kkk.end(); kkkit++) {
                            long long value = kkkit->second;
                            if (value>=tempvalue) {
                                tempvalue = value;
                                tempkey = kkkit->first;
                            }
                        }
                        saverowcolint = tempkey;
                        break;
                    }
                }
                
                if (!samemergeunit.empty() && !rowunit.empty()) {
                    DeleteUnitList samemergeunittemp = samemergeunit;
                    DeleteUnitList rowunittemp = rowunit;
                    DeleteUnitList colunittemp = colunit;
                    
                    fnmap.insert(pair<long long, DeleteUnitList>(samemergeunittemp.size(),samemergeunittemp));
                    coltotalunitList.remove(colunittemp);
                    rowtotalunitList.erase(rowtotalunitdelit++);
                }
                samemergeunit.clear();
                
            }
            {//单独循环出单行
                rowtotalunitdelit = rowtotalunitList.begin();
                for (;rowtotalunitdelit!=rowtotalunitList.end();rowtotalunitdelit++){
                    DeleteUnitList tempmap = * rowtotalunitdelit;
                    fnmap.insert(pair<long long, DeleteUnitList>(tempmap.size(),tempmap));
                }
                coltotalunitdelit = coltotalunitList.begin();
                for (;coltotalunitdelit!=coltotalunitList.end();coltotalunitdelit++){
                    DeleteUnitList tempmap = * coltotalunitdelit;
                    fnmap.insert(pair<long long, DeleteUnitList>(tempmap.size(),tempmap));
                }
            }
            
            
        }
         
        return fnmap;
    }
    
    
    
    FruntCell * GameLayer::createNewCell(int column,int row,int type, int rowcount,int status)
    {
        FruntCell *_fs=FruntCell::create();
        double width=Director::getInstance()->getWinSize().width/rowcount;
        _fs->setContentSize(Size(width, width));
        double _cloumnPos=width*(column%rowcount);
        double _rowPos;
        _rowPos=width*row;
        _fs->setPosition(Vec2(_cloumnPos, _rowPos));
        this->addChild(_fs);
        _fs->setNowIndex(row, column);
        _fs->registDelegate(this);
        cellsStatus[row][column]=status;
        _fs->setType(type);
        return _fs;
    }
    
    FruntCell * GameLayer::createNewCell2(int column,int row,int tagcolumn,int tagrow, int rowcount)
    {
        FruntCell *_fs=FruntCell::create();
        double width=Director::getInstance()->getWinSize().width/rowcount;
        _fs->setContentSize(Size(width, width));
        double _cloumnPos=width*(column%rowcount);
        double _rowPos;
        _rowPos=width*row;
        _fs->setPosition(Vec2(_cloumnPos, _rowPos));
        this->addChild(_fs);
        
        _fs->setNowIndex(tagrow, tagcolumn);
        _fs->registDelegate(this);
        cellsStatus[tagrow][tagcolumn]=3;
        int temp=1+std::rand()%CELLNUM;
        _fs->setType(temp);
        return _fs;
    }
    
    bool GameLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
    {
        CCLOG("---> GameLayer : game layer click");
        return true;
    }
    void GameLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
    {
        
    }
    
    void GameLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
    {
        
    }
    
    Scene *GameLayer::createGameACTScene(void)
    {
        Scene *pScene=Scene::create();
        pScene->addChild(GameLayer::create(), 0);
        return pScene;
    }
    void GameLayer::pop(Ref *node)
    {
        SceneManager::popScene();
    }
    
	GameLayer::GameLayer()
	{
		cy=new Category;
	}
	GameLayer::~GameLayer()
	{
		delete cy;
	}
    
    bool GameLayer::init()
    {
        if (!Layer::init()) {
            return false;
        }
        
        
        _lastDropCell = NULL;
        _lastDeleteCell = NULL;
        for (int i = 0; i < CELLNUM; i++) {
            for (int j = 0; j < CELLNUM; j++) {
                cellsStatus[i][j] = 0;
            }
        }
        
        srand(time(0));
        Size size = Director::getInstance()->getWinSize();
        float winw = size.width;
        float winh = size.height;
        
        {//bg
            Sprite* pSprite = Sprite::create("bg-HD.png");
            pSprite->setPosition(Vec2(winw/2, winh/2));
            float spx = pSprite->getTextureRect().size.width;
            float spy = pSprite->getTextureRect().size.height;
            pSprite->setScaleX(winw/spx);
            pSprite->setScaleY(winh/spy);
            addChild(pSprite);
        }
        {
            Label *label1 = Label::createWithTTF("back", "fonts/Marker Felt.ttf", 45);
            MenuItemLabel *ccLabel1=MenuItemLabel::create(label1, CC_CALLBACK_1(GameLayer::pop, this));
            Menu *menu=Menu::create(ccLabel1,NULL);
            menu->setPosition(Vec2(60, Director::getInstance()->getWinSize().height-120));
            this->addChild(menu);
        }
        {//progress
            Sprite *pgBg=Sprite::create("progress2-HD.png");
            pgBg->setPosition(Vec2(winw/2, winh-50));
            pgBg->setContentSize(Size(winw-100, 20));
            addChild(pgBg);
            
            Sprite *pSp = Sprite::create("progress1-HD.png");
            progress = ProgressTimer::create(pSp);
            progress->setType(ProgressTimer::Type::BAR);
            progress->setPosition(Vec2(winw/2, winh-50));
            progress->setContentSize(Size(winw-100,20));
            progress->setPercentage(100);
            progress->setMidpoint(Vec2(0,1));
            progress->setBarChangeRate(Vec2(1,0));

            this->addChild(progress);
            dtf=100.0;
        }
        
        for (int i=0; i<CELLNUM; i++) {
            list<int> temp;
            dropCount[i] = temp;
        }
        loadGameMap();
        return true;
    }
    
    void GameLayer::onEnter()
    {
        Layer::onEnter();
        scheduleUpdate();
        //schedule(schedule_selector(GameLayer::update), 0.1, kCCRepeatForever, 0);
    }
    /* 3.x 废弃
    void GameLayer::registerWithTouchDispatcher(void)
    {
        Director *pDirector=Director::getInstance();
        pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    }
    */
    
    void GameLayer::loadGameMap()
    {
        int temp[9][9] = {
            {CDestoryKO,    1, CDestoryKO,          2, CDestoryKO,    1,    CDestoryKO,    2,   CDestoryKO},
            { 1,   CDestoryKO,          1, CDestoryKO,          1,   CDestoryKO,     1,   CDestoryKO,    1},
            {CDestoryKO,    2, CDestoryKO,          1,    CDestoryKO,    2,    CDestoryKO,    1,   CDestoryKO},
            {CDestoryKO,    5,          4,          3,          4,    2,     1,    2,   CDestoryKO},
            { 1,            2,          1,          1,          3,    5,     6,    4,    1},
            {CDestoryKO,    1,          5,          2,          3,    3,     2,    1,    7},
            { 3,            5,          3,          5,          4,    4,     3,    4,    4},
            { 4,            3,          5,          2,          5,    2,     2,    1,    5},
            { 3,            3,          5,          6,          1,    7,     3,    4,    5}
        };
        dropTump.push_back(colRowToInt(0, 8));
        dropTump.push_back(colRowToInt(1, 8));
        dropTump.push_back(colRowToInt(2, 8));
        dropTump.push_back(colRowToInt(3, 8));
        dropTump.push_back(colRowToInt(4, 8));
        dropTump.push_back(colRowToInt(5, 8));
        dropTump.push_back(colRowToInt(6, 8));
        dropTump.push_back(colRowToInt(7, 8));
        dropTump.push_back(colRowToInt(8, 8));
        //make CELLNUM*CELLNUM cells
        for (int column=0; column<CELLNUM; column++) {
            for (int row=0; row<CELLNUM; row++) {
                if (temp[row][column]==-1) {
                    createNewCell(column, CELLNUM-1 - row,temp[row][column],CELLNUM,-1);
                }else
                if (temp[row][column]==CDestoryKO) {
                    createNewCell(column, CELLNUM-1 - row,temp[row][column],CELLNUM,CDestoryKO);
                }else
                    if (temp[row][column]==100) {
                        createNewCell(column, CELLNUM-1 - row,temp[row][column],CELLNUM,100);
                    }else
                        createNewCell(column, CELLNUM-1 - row,temp[row][column],CELLNUM,0);
            }
        }
    }
    
    
    FruntCell * GameLayer::getCellWithIndex(CellIndex index)
    {
        if (cellsStatus[index.rowPos][index.columnPos]!=CDestoryKO && cellsStatus[index.rowPos][index.columnPos]!=100 && cellsStatus[index.rowPos][index.columnPos]!=-1) {
            Node *node1=this->getChildByTag(index.rowPos*CELLNUM+index.columnPos);
            FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
            return cell1;
        }
        return NULL;
    }
    
    FruntCell * GameLayer::getKoCellWithIndex(CellIndex index)
    {
        if (cellsStatus[index.rowPos][index.columnPos]==CDestoryKO) {
            Node *node1=this->getChildByTag(index.rowPos*CELLNUM+index.columnPos);
            FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
            return cell1;
        }
        return NULL;
    }
    //直出是否等于或存在，不能用与“否”表达式，只能用于验证是或着不是
    bool GameLayer::isNormalCellIndex(CellIndex index)
    {
        if (cellsStatus[index.rowPos][index.columnPos]!=CDestoryKO && cellsStatus[index.rowPos][index.columnPos]!=100 && cellsStatus[index.rowPos][index.columnPos]!=-1) {
            return true;
        }
        return false;
    }
    //直出是否等于或存在，不能用与“否”表达式，只能用于验证是或着不是
    bool GameLayer::isKoCellIndex(CellIndex index)
    {
        if (cellsStatus[index.rowPos][index.columnPos]==CDestoryKO || cellsStatus[index.rowPos][index.columnPos]==100 || cellsStatus[index.rowPos][index.columnPos]==-1) {
            return true;
        }
        return false;
    }
    //直出是否等于或存在，不能用与“否”表达式，只能用于验证是或着不是
    bool GameLayer::isNormalCellIndexAndNullCell(CellIndex index)
    {
        if (cellsStatus[index.rowPos][index.columnPos]!=CDestoryKO && cellsStatus[index.rowPos][index.columnPos]!=100 && cellsStatus[index.rowPos][index.columnPos]!=-1 && !getCellWithIndex(index)) {
            return true;
        }
        return false;
    }
    //直出是否等于或存在，不能用与“否”表达式，只能用于验证是或着不是
    bool GameLayer::isNormalCellIndexAndCell(CellIndex index)
    {
        if (cellsStatus[index.rowPos][index.columnPos]!=CDestoryKO && cellsStatus[index.rowPos][index.columnPos]!=100 && cellsStatus[index.rowPos][index.columnPos]!=-1 && getCellWithIndex(index)) {
            return true;
        }
        return false;
    }
    
}


