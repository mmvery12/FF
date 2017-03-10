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
    void int2str(const long long  &int_temp,string &string_temp)
    {
        stringstream stream;
        stream<<int_temp;
        string_temp=stream.str();
    }
    
    void str2int(long long  &int_temp,const string &string_temp)
    {
        stringstream stream(string_temp);
        stream>>int_temp;
    }
    
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
    
    long long GameLayer::colRowToInt2(int col,int row)
    {
        long long temp = ((long long)col*100000 + (long long)row*1000)*1000000;
        
        return temp;
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
                        Node *node=this->getChildByTag(row*CELLNUM+ff);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell){
                            unitlist.push_back(colRowToInt(ff, row));
                            log("---> GameLayer : destory cell [%d][%d] findRowDelete",row,ff);
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
                        Node *node=this->getChildByTag(row*CELLNUM+ff);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell){
                            if (row1==row && col1==ff) {
                                delmap.push_back(colRowToInt(col2, row2));
                                //delmap.insert(pair<int, int>(col2, row2));
                            }else
                            if (row2==row&& col2==ff) {
                                delmap.push_back(colRowToInt(col1, row1));
                                //delmap.insert(pair<int, int>(col1,row1));
                            }else
                                delmap.push_back(colRowToInt(ff, row));
                                //delmap.insert(pair<int, int>(ff,row));
                            log("---> GameLayer : destory cell [%d][%d] findRowDelete",row,ff);
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
                        Node *node=this->getChildByTag(ff*CELLNUM+column);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell) {
                            if (row1==ff && col1==column) {
                                delmap.push_back(colRowToInt(col2, row2));
                                //delmap.insert(pair<int, int>(col2, row2));
                            }else
                                if (row2==ff&& col2==column) {
                                    delmap.push_back(colRowToInt(col1, row1));
                                    //delmap.insert(pair<int, int>(col1,row1));
                                }else
                                    delmap.push_back(colRowToInt(column, ff));
                                    //delmap.insert(pair<int, int>(column,ff));
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
                        Node *node=this->getChildByTag(ff*CELLNUM+column);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell) {
                            delmap.push_back(colRowToInt(column, ff));
                            //delmap.insert(pair<int, int>(column,ff));
                            log("---> GameLayer : destory cell [%d][%d] findColDelete",ff,column);
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
        Node *node=this->getChildByTag(row*CELLNUM+column);
        FruntCell *cell=dynamic_cast<FruntCell *>(node);
        char temps[2]="";
        
        if (this->cellsStatus[row][column]!=0||
            node==NULL) {
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
                it++;
                if (rowmap.size()==3) {
                    fnmap.insert(pair<int, DeleteUnitList>(rowmap.size()+*it,rowmap));
                }
                if (rowmap.size()==4) {
                    fnmap.insert(pair<int, DeleteUnitList>(rowmap.size()+*it,rowmap));
                }
                
            }
            for (;coltotalunitdelit!=coltotalunitList.end();coltotalunitdelit++)
            {
                DeleteUnitList colmap = * coltotalunitdelit;
                DeleteUnitListIterator it = colmap.begin();
                it++;
                if (colmap.size()==3) {
                    fnmap.insert(pair<int, DeleteUnitList>(colmap.size()+*it,colmap));
                }
                if (colmap.size()==4) {
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
                    if (temp.size()!=rowunit2.size()+colunit2.size()) {//有重复元素
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
        if (cellsStatus[index.rowPos][index.columnPos]!=0) {
            return;
        }
        CCLOG("---> GameLayer : click at index column=%d row=%d tag=%d\r\n",index.columnPos,index.rowPos,index.rowPos*CELLNUM+index.columnPos);
        _lastedClick=index;
    }
    
    void GameLayer::direction(MoveDirection dir,CellIndex lastedClick)
    {
        CellIndex _tempIndex = compute(dir,lastedClick);
        if (_tempIndex.columnPos!=-1 && _tempIndex.rowPos!=-1 && cellsStatus[_tempIndex.rowPos][_tempIndex.columnPos]==0 && cellsStatus[lastedClick.rowPos][lastedClick.columnPos]==0) {
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
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        if (temp->getCellIndex().rowPos==5 && temp->getCellIndex().columnPos==4 ) {
            
        }

        
        cellsStatus[temp->getCellIndex().rowPos][temp->getCellIndex().columnPos]=1;
    }
    
    void GameLayer::exchanging(Layer *cell)
    {
        _isMoving.push_back(1);
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        cellsStatus[temp->getCellIndex().rowPos][temp->getCellIndex().columnPos]=2;
    }
    void GameLayer::deleteing(Layer *cell)
    {
        _isDeleteing.push_back(1);
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        cellsStatus[temp->getCellIndex().rowPos][temp->getCellIndex().columnPos]=4;
    }
    void GameLayer::droping(Layer *cell)
    {
        _isDropping.push_back(1);
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        cellsStatus[temp->getCellIndex().rowPos][temp->getCellIndex().columnPos]=3;
    }
    
    
    void GameLayer::movingComplete(Layer *cell)
    {
//		pthread_mutex_lock(&mutex);
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        cellsStatus[temp->getCellIndex().rowPos][temp->getCellIndex().columnPos]=0;
//		pthread_mutex_unlock(&mutex);
        _isMoving.pop_back();
        temp->joinCellAnimation(OnlyMoveAnimation2, temp->getToCellIndex());
    }
    
    
    
    void GameLayer::movingComplete2(Layer *cell)
    {
        //		pthread_mutex_lock(&mutex);
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        cellsStatus[temp->getCellIndex().rowPos][temp->getCellIndex().columnPos]=0;
        //		pthread_mutex_unlock(&mutex);
        _isMoving.pop_back();
    }

    void GameLayer::deleteComplete(Layer *cell)
    {
//        pthread_mutex_lock(&mutex);
    
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        cellsStatus[temp->getCellIndex().rowPos][temp->getCellIndex().columnPos]=5;
        this->removeChild(cell);
        
        _isDeleteing.pop_back();
//        pthread_mutex_unlock(&mutex);
        
    }
    
    void GameLayer::dropComplete(Layer *cell)
    {
//		pthread_mutex_lock(&mutex);
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
		cellsStatus[temp->getToCellIndex().rowPos][temp->getToCellIndex().columnPos]=0;
//		pthread_mutex_unlock(&mutex);
        _isDropping.pop_back();
    }
    
    void GameLayer::moveAndDeleteComplete(Layer *cell)
    {
        FruntCell *temp=dynamic_cast<FruntCell *>(cell);
        cellsStatus[temp->getToCellIndex().rowPos][temp->getToCellIndex().columnPos]=5;
        //		pthread_mutex_unlock(&mutex);
        _isDropping.pop_back();
    }
    
#pragma mark click delegate end
    
    void GameLayer::timeCallBack()
    {
        
//        pthread_mutex_lock(&mutex);
        
        ;
    
        //TODO_DropCell();
        //TODO_DeleteCell();
        //TODO_ResetCell();
        if (_isMoving.empty() && _isDropping.empty() && _isDeleteing.empty()) {
            findCurrent();
        }

//		pthread_mutex_unlock(&mutex);
        
    }

    
    
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
                            cellsStatus[temp.rowPos][temp.columnPos]=0;
                        }
                    }else
                    {
                        if (node1) {
                            FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
                            cell1->joinCellAnimation(DeleteAnimation, temp);
                            cell1->setCellStatus(cellDestory);
                        }
                    }
                    
                    
                    
                }
            }
        }
        return true;
    }
    
    bool GameLayer::TODO_ResetCell()
    {
        
        for (int i=0; i<CELLNUM; i++) {
            for (int j=0; j<CELLNUM; j++) {
                
                Node *node=this->getChildByTag(i*CELLNUM+j);
                FruntCell *cell=dynamic_cast<FruntCell *>(node);
                
                if (cell &&
                    cellsStatus[cell->getCellIndex().rowPos][cell->getCellIndex().columnPos]==0 &&
                    !cell->isCellIndexEqual(cell->getCellIndex(), cell->getToCellIndex()) &&
                    !cell->isAnimation()) {
                    
                    Node *node2=this->getChildByTag(cell->getToCellIndex().rowPos*CELLNUM+cell->getToCellIndex().columnPos);
                    FruntCell *cell2=dynamic_cast<FruntCell *>(node2);
                    
                    if (cellsStatus[cell2->getCellIndex().rowPos][cell2->getCellIndex().columnPos]==0) {
                        cell->joinCellAnimation(OnlyMoveAnimation2, cell->getToCellIndex());
                    }else
                        cell->setNowIndex(cell->getToCellIndex().rowPos, cell->getToCellIndex().columnPos);
                    
                }
            }
        }
        return true;
    }
    //垂直方向最上一行有固定消除物的，不可添加新的cell，从固定的点物理偏移过来
    //垂直方向最上一行有固定不可消除物的，不可添加新的cell,从固定的点无聊偏移过来
    bool GameLayer::TODO_DropCell()
    {
        for (int column=0; column<CELLNUM; column++) {
            dropCount[column].clear();
            for (int row=CELLNUM-1; row>=0; row--) {
                int type = cellsStatus[row][column];
                if (type==5) {
                    dropCount[column].push_back(column);
                }
            }
        }
        
        return true;
    }
    
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
                if ((cell1->isCellIndexEqual(c1, index1) && cell2->isCellIndexEqual(c2, index2)) ||
                    (cell1->isCellIndexEqual(c1, index2) && cell2->isCellIndexEqual(c2, index1))) {
                    have = true;
                    prefnmap.erase(it);
                    break;
                }
            }
            if (have) {
                cell1->joinCellAnimation(OnlyMoveAnimation2, c2);
                cell2->joinCellAnimation(OnlyMoveAnimation2, c1);
            }else
            {
                cell1->joinCellAnimation(OnlyMoveAnimation, c2);
                cell2->joinCellAnimation(OnlyMoveAnimation, c1);
            }
            
        }
    }

    
    
   
    void GameLayer::addNewCells(int column)
    {

        for (int row=0; row<CELLNUM; row++) {
            int count=0;
            for (int index=row; index<14; index++) {
                Node *node=this->getChildByTag(index*CELLNUM+column);
                FruntCell *cell=dynamic_cast<FruntCell *>(node);
                if (cellsStatus[index][column]==5||
                    cellsStatus[index][column]==1||
                    cellsStatus[index][column]==3) {
                    
                    count++;
                    if (cellsStatus[index][column]==3) {
                        count=cell->getToCellIndex().rowPos;
                    }
                }else if(node!=NULL)
                {
                    CellIndex temp;
                    if (cellsStatus[index][column]==3) {
                        temp.rowPos=count+1;
                    }else
                        temp.rowPos=index-count;
                    temp.columnPos=column;
                    if (!cell->isCellIndexEqual(temp, cell->getCellIndex())) {
                        cell->joinCellAnimation(DropAnimation, temp);
                        log("---> GameLayer : drop cell at index[%d][%d] to index[%d][%d]",cell->getCellIndex().rowPos,cell->getCellIndex().columnPos,index-count,column);
                    }

                    break;
                }
            }
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
        DeleteFNMap delmap;
        
        DeleteFNMap beDelMap = TODO_FindDeleteCells();
        if (beDelMap.empty()) {
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
                            {//5004003
                                long long celldropint = delit->first+colRowToInt(lastedindex.columnPos, lastedindex.rowPos)+colRowToInt2(index.columnPos, index.rowPos);
                                delmap.insert(pair<long long, DeleteUnitList>(celldropint,delit->second));
                            }
                        }
                    }
                }
            }
            if (!delmap.empty()) {
                prefnmap.clear();
                prefnmap = delmap;
            }
        }else
        {
            DeleteFNMapIterator it = beDelMap.begin();
            for (; it!=beDelMap.end(); it++) {
                CellIndex index = intToColRow(it->first);
                int count = (int)(it->first - colRowToInt(index.columnPos, index.rowPos));
                DeleteUnitList list = it->second;
                DeleteUnitListIterator listit = list.begin();
                for (; listit!=list.end(); listit++) {
                    CellIndex temp = intToColRow(*listit);
                    Node *node1=this->getChildByTag(temp.rowPos*CELLNUM+temp.columnPos);
                    FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
                    if (cell1) {
                        if (count==3) {
                            cell1->joinCellAnimation(DeleteAnimation, cell1->getToCellIndex());
                        }
                        if (cell1->isCellIndexEqual(index, temp)) {
                            cell1->joinCellAnimation(LightAnimate, index);
                        }else
                        {
                            if (count==4) {
                                cell1->joinCellAnimation(MoveAndDeleteAnimate, index);
                            }
                            if (count>=5) {
                                cell1->joinCellAnimation(MoveAndDeleteAnimate, index);
                            }
                        }
                    }
                }
            }
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
                    if (temp.size()!=rowunit2.size()+colunit2.size()) {//有重复元素
                        samemergeunit = temp;
                        //下面通过map计数找出重复的cell的int表述
                        map<int,int> kkk;
                        DeleteUnitListIterator samemergeunit2it = samemergeunit2.begin();
                        for (; samemergeunit2it!=samemergeunit2.end(); samemergeunit2it++) {
                            long long value = kkk[*samemergeunit2it];
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
                    
                    fnmap.insert(pair<int, DeleteUnitList>(samemergeunittemp.size(),samemergeunittemp));
                    coltotalunitList.remove(colunittemp);
                    rowtotalunitList.erase(rowtotalunitdelit++);
                }
                samemergeunit.clear();
                
            }
            {//单独循环出单行
                rowtotalunitdelit = rowtotalunitList.begin();
                for (;rowtotalunitdelit!=rowtotalunitList.end();rowtotalunitdelit++){
                    DeleteUnitList tempmap = * rowtotalunitdelit;
                    fnmap.insert(pair<int, DeleteUnitList>(tempmap.size(),tempmap));
                }
                coltotalunitdelit = coltotalunitList.begin();
                for (;coltotalunitdelit!=coltotalunitList.end();coltotalunitdelit++){
                    DeleteUnitList tempmap = * coltotalunitdelit;
                    fnmap.insert(pair<int, DeleteUnitList>(tempmap.size(),tempmap));
                }
            }
            
            
        }
         
        return fnmap;
    }
    
    
    
    FruntCell * GameLayer::createNewCell(int column,int row,bool isPlaying,int type, int rowcount,int status)
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
        
        middlerDropCenter = CELLNUM/2+1;
        int temp[9][9] = {
            {99, 99, 99, 99, 1, 99, 99,99,99},
            {99, 99, 99,  6, 7,  1, 99,99,99},
            {99, 99,  5,  6, 3,  2,  1,99,99},
            {99,  3,  4,  4,  7,  2,  2, 1,99},
            { 1,  1,  3,  3,  5,  1,  3, 4, 1},
            {99,  1,  4,  5,  6,  1,  2, 1,99},
            {99, 99,  1,  5,  1,  5,  1,99,99},
            {99, 99, 99,  1,  2,  1, 99,99,99},
            {99, 99, 99, 99,  1, 99, 99,99,99}
        };
        //make CELLNUM*CELLNUM cells
        for (int column=0; column<CELLNUM; column++) {
            for (int row=CELLNUM-1; row>=0; row--) {
                if (temp[row][column]==-1) {
                    createNewCell(column, row,false,temp[row][column],CELLNUM,-1);
                }else
                if (temp[row][column]==99) {
                    createNewCell(column, row,false,temp[row][column],CELLNUM,99);
                }else
                    createNewCell(column, row,false,temp[row][column],CELLNUM,0);
            }
        }
    }
}
