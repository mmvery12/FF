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
    
    DeleteList GameLayer::findRowDelete(string ss,int row)
    {
        DeleteList dellist;
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
                    Deletemultimap delmap;
                    count++;
                    int ff=i;
                    for (int column=0; column<count; column++) {
                        ff--;
                        Node *node=this->getChildByTag(row*7+ff);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell){
                            delmap.insert(pair<int, int>(ff,row));
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
    
    DeleteList GameLayer::findRowDelete2(string ss,int row,int row1,int col1,int row2,int col2)
    {
        DeleteList dellist;
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
                    Deletemultimap delmap;
                    count++;
                    int ff=i;
                    for (int column=0; column<count; column++) {
                        
                        ff--;
                        Node *node=this->getChildByTag(row*7+ff);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell){
                            if (row1==row && col1==ff) {
                                delmap.insert(pair<int, int>(col2, row2));
                            }else
                            if (row2==row&& col2==ff) {
                                delmap.insert(pair<int, int>(col1,row1));
                            }else
                                delmap.insert(pair<int, int>(ff,row));
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
    
    DeleteList GameLayer::findColDelete2(string ss,int column,int row1,int col1,int row2,int col2)
    {
        DeleteList dellist;
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
                    Deletemultimap delmap;
                    count++;
                    int ff=i;
                    for (int row=0; row<count; row++) {
                        ff--;
                        Node *node=this->getChildByTag(ff*7+column);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell) {
                            if (row1==ff && col1==column) {
                                delmap.insert(pair<int, int>(col2, row2));
                            }else
                                if (row2==ff&& col2==column) {
                                    delmap.insert(pair<int, int>(col1,row1));
                                }else
                                    delmap.insert(pair<int, int>(column,ff));
                        }
                    }
                    dellist.push_back(delmap);
                }
                
                count=0;
            }
        }
        return dellist;
    }
    
    DeleteList GameLayer::findColDelete(string ss,int column)
    {
        DeleteList dellist;
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
                    Deletemultimap delmap;
                    count++;
                    int ff=i;
                    for (int row=0; row<count; row++) {
                        ff--;
                        Node *node=this->getChildByTag(ff*7+column);
                        FruntCell *cell=dynamic_cast<FruntCell *>(node);
                        if (cell) {
                            delmap.insert(pair<int, int>(column,ff));
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
        Node *node=this->getChildByTag(row*7+column);
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
        DeleteList rowList;
        DeleteList colList;
        
        for (int row=0; row<7; row++) {
            std::string ss;
            for (int column=0; column<7; column++) {
                string sg = getCellTypeString(row, column);
                ss+=sg;
            }
            ss+='_';
            DeleteList temp1 = findRowDelete(ss, row);
            DeleteListIterator delit=temp1.begin();
            for (;delit!=temp1.end();delit++)
            {
                rowList.push_back(*delit);
            }
        }
        for (int column=0; column<7; column++) {
            std::string ss;
            for (int row=0; row<7; row++) {
                string sg = getCellTypeString(row, column);
                ss+=sg;
            }
            ss+='_';
            DeleteList temp2 = findColDelete(ss, column);
            DeleteListIterator delit=temp2.begin();
            for (;delit!=temp2.end();delit++)
            {
                colList.push_back(*delit);
            }
        }
        
        
        
        
        
        DeleteListIterator rowdelit=rowList.begin();
        DeleteListIterator coldelit=colList.begin();
        if (!rowList.empty() || !colList.empty()) {
            
        }
        
        if (rowList.empty() || colList.empty()) {
            for (;rowdelit!=rowList.end();rowdelit++)
            {
                Deletemultimap rowmap = * rowdelit;
                fnmap.insert(pair<int, Deletemultimap>(rowmap.size(),rowmap));
            }
            for (;coldelit!=colList.end();coldelit++)
            {
                Deletemultimap colmap = * coldelit;
                fnmap.insert(pair<int, Deletemultimap>(colmap.size(),colmap));
            }
        }else
        {

            DeleteList tempCompairRow;
            DeleteList tempCompairCol;
            
            for (;rowdelit!=rowList.end();rowdelit++)
            {
                Deletemultimap rowmap = * rowdelit;
                DeleteIterator rowmapit = rowmap.begin();
                
                Deletemultimap tolmap;
                Deletemultimap tempColmap;
                for (; rowmapit!=rowmap.end(); rowmapit++) {
                    for (;coldelit!=colList.end();coldelit++){
                        Deletemultimap colmap = * coldelit;
                        DeleteIterator colmapit = colmap.begin();
                        if (colmap.count(rowmapit->first)!=0) {
                            for (; colmapit!=colmap.end(); colmapit++) {
                                if (rowmapit->first==colmapit->first && rowmapit->second==colmapit->second) {
                                    tempColmap = colmap;
                                    tempCompairRow.push_front(rowmap);
                                    tempCompairCol.push_front(colmap);
                                    break;
                                }
                            }
                            if (!tempColmap.empty()) {
                                break;
                            }
                        }else
                        {
                            break;
                        }
                        
                    }
                    if (!tempColmap.empty()) {
                        break;
                    }
                }
                
                if (!tempColmap.empty()) {
                    rowmapit = rowmap.begin();
                    DeleteIterator colmapit = tempColmap.begin();
                    for (; rowmapit!=rowmap.end(); rowmapit++) {
                        tolmap.insert(pair<int, int>(rowmapit->first,rowmapit->second));
                    }
                    for (; colmapit!=tempColmap.end(); colmapit++) {
                        tolmap.insert(pair<int, int>(colmapit->first,colmapit->second));
                    }
                    fnmap.insert(pair<int, Deletemultimap>(tolmap.size(),tolmap));
                }
            }
            rowdelit=tempCompairRow.begin();
            for (; rowdelit != tempCompairRow.end() && !rowList.empty(); rowdelit++) {
                rowList.remove(*rowdelit);
            }
            
            coldelit=tempCompairCol.begin();
            for (; coldelit != tempCompairCol.end() && !colList.empty(); coldelit++) {
                colList.remove(*coldelit);
            }
            
            rowdelit=rowList.begin();
            for (; rowdelit!=rowList.end(); rowdelit++) {
                Deletemultimap tempmap = * rowdelit;
                fnmap.insert(pair<int, Deletemultimap>(tempmap.size(),tempmap));
            }
            
            coldelit=colList.begin();
            for (; coldelit!=colList.end(); coldelit++) {
                Deletemultimap tempmap = * coldelit;
                fnmap.insert(pair<int, Deletemultimap>(tempmap.size(),tempmap));
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
        CCLOG("---> GameLayer : click at index column=%d row=%d tag=%d\r\n",index.columnPos,index.rowPos,index.rowPos*7+index.columnPos);
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
    
    void GameLayer::moving(Layer *cell)
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
        _isDrop.push_back(1);
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
        _isDrop.pop_back();
    }
    
#pragma mark click delegate end
    
    void GameLayer::timeCallBack()
    {
        
//        pthread_mutex_lock(&mutex);
        
        ;
    
        TODO_DropCell();
        TODO_DeleteCell();
        TODO_ResetCell();
        if (_isMoving.empty() && _isDrop.empty() && _isDeleteing.empty()) {
            findCurrent();
        }

//		pthread_mutex_unlock(&mutex);
        
    }

    
    Deletemultimap GameLayer::sortMapByRow(pair<DeleteIterator,DeleteIterator> Findpair,int column)
    {
        DeleteIterator dit=Findpair.first;
        Deletemultimap temp;
        //<------------------------ sort & erase same --------------------------
        for (; dit!=Findpair.second;dit++) {
            temp.insert(pair<int, int>(dit->first,dit->second));
        }
        vector<PAIR> name_score_vec(temp.begin(), temp.end());
        sort(name_score_vec.begin(), name_score_vec.end(), CmpByValue());
        vector<PAIR>::iterator vecIt=name_score_vec.begin();
        
        temp.erase(column);
        PAIR same;
        for (; vecIt!=name_score_vec.end(); vecIt++) {
            if (same==*vecIt) {
                continue;
            }
            same=*vecIt;
            temp.insert(*vecIt);
        }
        return temp;
        //------------------------ sort & erase same -------------------------->
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
                int type = delit->first;
                
                Deletemultimap map = delit->second;
                DeleteIterator mapit = map.begin();
                for (; mapit!=map.end(); mapit++) {
                    CellIndex temp;
                    temp.rowPos=mapit->second;
                    temp.columnPos=mapit->first;
                    
                    Node *node1=this->getChildByTag(temp.rowPos*7+temp.columnPos);
                    if (node1) {
                        FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
                        cell1->joinCellAnimation(DeleteAnimation, temp);
                        cell1->setCellStatus(cellDestory);
                    }
                }
            }
        }
        return true;
    }
    
    bool GameLayer::TODO_ResetCell()
    {
        
        for (int i=0; i<7; i++) {
            for (int j=0; j<7; j++) {
                
                Node *node=this->getChildByTag(i*7+j);
                FruntCell *cell=dynamic_cast<FruntCell *>(node);
                
                
                if (cell &&
                    cellsStatus[cell->getCellIndex().rowPos][cell->getCellIndex().columnPos]==0 &&
                    !cell->isCellIndexEqual(cell->getCellIndex(), cell->getToCellIndex()) &&
                    !cell->isAnimation) {
                    
                    Node *node2=this->getChildByTag(cell->getToCellIndex().rowPos*7+cell->getToCellIndex().columnPos);
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
    
    bool GameLayer::TODO_DropCell()
    {
        for (int column=0; column<7; column++) {
            for (int row=6; row>=0; row--) {
                int type = cellsStatus[row][column];
                if (type==5) {
                    
                }
            }
        }
        return true;
    }
    
    void GameLayer::showTag()
    {
        for (int row=0; row<7; row++) {
            CCLOG("-------->");
            CCLOG("%d %d %d %d %d %d %d",cellsStatus[row][0],cellsStatus[row][1],cellsStatus[row][2],cellsStatus[row][3],cellsStatus[row][4],cellsStatus[row][5],cellsStatus[row][6]);
            CCLOG("<--------");
        }
    }
    
    
    
    void GameLayer::registTwoCell(CellIndex c1, CellIndex c2)
    {
        Node *node1=this->getChildByTag(c1.rowPos*7+c1.columnPos);
        Node *node2=this->getChildByTag(c2.rowPos*7+c2.columnPos);
        FruntCell *cell1=dynamic_cast<FruntCell *>(node1);
        FruntCell *cell2=dynamic_cast<FruntCell *>(node2);
        if (node1!=NULL&&node2!=NULL &&
            !cell1->isAnimation && !cell2->isAnimation) {
            cell1->joinCellAnimation(OnlyMoveAnimation, c2);
            cell2->joinCellAnimation(OnlyMoveAnimation, c1);
        }
    }

    
    
   
    void GameLayer::addNewCells(int column)
    {

        for (int row=0; row<7; row++) {
            int count=0;
            for (int index=row; index<14; index++) {
                Node *node=this->getChildByTag(index*7+column);
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
        for (int row=0; row<MAXCOUNT; row++) {
            for (int column=0; column<MAXCOUNT; column++) {
                for (int i =1; i<=4; i++) {
                    CellIndex lastedindex;
                    lastedindex.rowPos = row;
                    lastedindex.columnPos = column;
                    CellIndex index = compute2((MoveDirection)i,lastedindex);
                    if (index.rowPos!=-1 && index.columnPos!=-1) {
                        DeleteFNMap temp = TODO_FindDeleteCells2(row, column, index.rowPos, index.columnPos);
                        DeleteFNMapIterator delit=temp.begin();
                        for (;delit!=temp.end();delit++)
                        {
                            delmap.insert(pair<int, Deletemultimap>(delit->first,delit->second));
                        }
                    }
                }
            }
        }
        if (!delmap.empty()) {
            prefnmap = delmap;
        }
    }
    
    
    DeleteFNMap GameLayer::TODO_FindDeleteCells2(int trow,int tcolumn,int trow2,int tcolumn2)
    {
        DeleteFNMap fnmap;
        DeleteList rowList;
        DeleteList colList;
        
        {//按行／列找计算可通过滑动消失的cell
            
            for (int row=0; row<7; row++) {
                std::string ss;
                for (int column=0; column<7; column++) {
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
                DeleteList temp = findRowDelete2(ss, row,trow,tcolumn,trow2,tcolumn2);
                DeleteListIterator delit=temp.begin();
                
                for (;delit!=temp.end();delit++)
                {
                    rowList.push_back(*delit);
                }
            }
            for (int column=0; column<7; column++) {
                std::string ss;
                for (int row=0; row<7; row++) {
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
                DeleteList temp = findColDelete2(ss, column,trow,tcolumn,trow2,tcolumn2);
                DeleteListIterator delit=temp.begin();
                for (;delit!=temp.end();delit++)
                {
                    rowList.push_back(*delit);
                }
            }
        }
        
        
        {
            DeleteListIterator rowdelit=rowList.begin();
            DeleteListIterator coldelit=colList.begin();
            if (!rowList.empty() || !colList.empty()) {
                
            }
            
            if (rowList.empty() || colList.empty()) {
                for (;rowdelit!=rowList.end();rowdelit++)
                {
                    Deletemultimap rowmap = * rowdelit;
                    fnmap.insert(pair<int, Deletemultimap>(rowmap.size(),rowmap));
                }
                for (;coldelit!=colList.end();coldelit++)
                {
                    Deletemultimap colmap = * coldelit;
                    fnmap.insert(pair<int, Deletemultimap>(colmap.size(),colmap));
                }
            }else
            {
                
                DeleteList tempCompairRow;
                DeleteList tempCompairCol;
                
                for (;rowdelit!=rowList.end();rowdelit++)
                {
                    Deletemultimap rowmap = * rowdelit;
                    DeleteIterator rowmapit = rowmap.begin();
                    
                    Deletemultimap tolmap;
                    Deletemultimap tempColmap;
                    for (; rowmapit!=rowmap.end(); rowmapit++) {
                        for (;coldelit!=colList.end();coldelit++){
                            Deletemultimap colmap = * coldelit;
                            DeleteIterator colmapit = colmap.begin();
                            if (colmap.count(rowmapit->first)!=0) {
                                for (; colmapit!=colmap.end(); colmapit++) {
                                    if (rowmapit->first==colmapit->first && rowmapit->second==colmapit->second) {
                                        tempColmap = colmap;
                                        tempCompairRow.push_front(rowmap);
                                        tempCompairCol.push_front(colmap);
                                        break;
                                    }
                                }
                                if (!tempColmap.empty()) {
                                    break;
                                }
                            }else
                            {
                                break;
                            }
                            
                        }
                        if (!tempColmap.empty()) {
                            break;
                        }
                    }
                    
                    if (!tempColmap.empty()) {
                        rowmapit = rowmap.begin();
                        DeleteIterator colmapit = tempColmap.begin();
                        for (; rowmapit!=rowmap.end(); rowmapit++) {
                            tolmap.insert(pair<int, int>(rowmapit->first,rowmapit->second));
                        }
                        for (; colmapit!=tempColmap.end(); colmapit++) {
                            tolmap.insert(pair<int, int>(colmapit->first,colmapit->second));
                        }
                        fnmap.insert(pair<int, Deletemultimap>(tolmap.size(),tolmap));
                    }
                }
                rowdelit=tempCompairRow.begin();
                for (; rowdelit != tempCompairRow.end() && !rowList.empty(); rowdelit++) {
                    rowList.remove(*rowdelit);
                }
                
                coldelit=tempCompairCol.begin();
                for (; coldelit != tempCompairCol.end() && !colList.empty(); coldelit++) {
                    colList.remove(*coldelit);
                }
                
                rowdelit=rowList.begin();
                for (; rowdelit!=rowList.end(); rowdelit++) {
                    Deletemultimap tempmap = * rowdelit;
                    fnmap.insert(pair<int, Deletemultimap>(tempmap.size(),tempmap));
                }
                
                coldelit=colList.begin();
                for (; coldelit!=colList.end(); coldelit++) {
                    Deletemultimap tempmap = * coldelit;
                    fnmap.insert(pair<int, Deletemultimap>(tempmap.size(),tempmap));
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
        
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
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
        
        
        int temp[7][7] = {
            {-1, -1, -1, 2, -1, -1, -1},
            {-1, -1,  5, 6,  7, -1, -1},
            {-1,  3,  5, 6,  7,  2, -1},
            {-1,  3,  4, 4,  7,  1, -1},
            {-1,  1,  3, 3,  5,  1, -1},
            {-1, -1,  4, 5,  6, -1, -1},
            {-1, -1, -1, 5, -1, -1, -1}
        };
        //make 7*7 cells
        for (int column=0; column<7; column++) {
            for (int row=6; row>=0; row--) {
                if (temp[row][column]==-1) {
                    createNewCell(column, row,false,temp[row][column],7,-1);
                }else
                if (temp[row][column]==99) {
                    createNewCell(column, row,false,temp[row][column],7,99);
                }else
                    createNewCell(column, row,false,temp[row][column],7,0);
            }
        }
    }
}
