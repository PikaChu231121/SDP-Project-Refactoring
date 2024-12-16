#include "sceneGame.h"
USING_NS_CC;

/**************��ʼ������*************/
bool sceneGame::init()
{
    if (!mainMenu::init())
    {
        return false;
    }
    mapInit();
    whichTurn();
    /*******��ʼ����Ƶ*******/

    smallHero* myyhero1 = new smallHero();
    this->myyhero = myyhero1->initSmall();
    myyhero->moveByMouse_R(myyhero);
    myyhero->setPosition(150, 200);
   

    this->addChild(map, 0);

    this->addChild(afterFight, 1);

    this->addChild(myyhero, 2);

    this->addChild(heroExist, 3);

    this->addChild(playerLayer, 4);

    this->addChild(shopLayer, 5);

    this->addChild(settingsLayer, 6);

    //this->addChild(info, 6);

    this->scheduleUpdate();

    map->scheduleUpdate();
    playerLayer->scheduleUpdate();

    return true;
}

void sceneGame::mapInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    float original_x = visibleSize.width / 4 - SPATIAL_DEVIATION_CORRECTION_WIDTH;
    float original_y = visibleSize.height / 2 - SPATIAL_DEVIATION_CORRECTION_HEIGHT;

    float eachCell_x = (visibleSize.width / 2 + SPATIAL_DEVIATION_CORRECTION) / CHESS_IN_A_ROW;
    float eachCell_y = (visibleSize.height / 2 + SPATIAL_DEVIATION_CORRECTION) / CHESS_IN_A_COL;

    for (int i = 0; i < CHESS_IN_A_ROW; i++)
    {
        for (int j = 1; j < CHESS_IN_A_COL + 1; j++)
        {
            chessMap[j][i].x = original_x + eachCell_x / 2 + i * eachCell_x;
            chessMap[j][i].y = original_y + eachCell_y / 2 + (j - 1) * eachCell_y;
        }
        chessMap[0][i].x = original_x + eachCell_x / 2 + eachCell_x * (i - 1) + HERO_SLOT_CORRECTION_WIDTH;
        chessMap[0][i].y = original_y - HERO_SLOT_CORRECTION_HEIGHT;
        chessMap[CHESS_IN_A_COL + 1][i].x = original_x + eachCell_x / 2 + eachCell_x * (i - 1) + HERO_SLOT_CORRECTION_WIDTH;
        chessMap[CHESS_IN_A_COL + 1][i].y = original_y + CHESS_IN_A_COL * eachCell_y + HERO_SLOT_CORRECTION_HEIGHT;
    }
}

void sceneGame::whichTurn()
{
    globalGameData->changeGameTurn();
    auto turn_label = Label::createWithTTF("TURN", "fonts/Marker Felt.ttf", 24);
    turn_label->setPosition(200, 800);
    this->addChild(turn_label, 2);
    char* mTurn = new char[8];
    sprintf(mTurn, "Turn %02d", globalGameData->gameTurn);
    turn_label->setString(mTurn);
}

/**************������***************/

void sceneGame::mouseInit()
{
    if (afterFight->totalTime<1e-2 && afterFight->totalTime>-1e-2) // ��ս���ڼ�ų�ʼ��
    {
        if (chessSelected < SEPARATION && chessSelected != -1)
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected - 1]);
            crt->setPosition(inWhichCell(crt->getTempPosition()));
            crt->set(crt->getTempPosition());
            chessSelected = -1; // �������ӵ�λ�ò����ѡ��״̬
        }
    }
}

void sceneGame::mouseMainEvent()
{
    auto MouseListener = EventListenerMouse::create();
    MouseListener = EventListenerMouse::create();
    MouseListener->onMouseMove = CC_CALLBACK_1(sceneGame::mouseMove, this);
    MouseListener->onMouseUp = CC_CALLBACK_1(sceneGame::mouseUp, this);
    MouseListener->onMouseDown = CC_CALLBACK_1(sceneGame::mouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);
}

void sceneGame::mouseUp(Event* event)
{
    auto e = static_cast<EventMouse*>(event);

    if ((int)e->getMouseButton() == 0) // ���
    {
        if (chessSelected >= 0 && chessSelected < SEPARATION) // ѡ��ս��������
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
            if (haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] == 1)   // �����ظ�ѡ��
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));

            }
            else if (pairReturn(crt->getPosition()).x != 0 && pairReturn(crt->getPosition()).x != 7)   //�����ڵȺ���
            {
                crt->setPosition(inWhichCell(crt->getPosition()));
                crt->set(inWhichCell(crt->getPosition()));
                haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] = 1;
                haveChess[pairReturn(crt->getTempPosition()).x][pairReturn(crt->getTempPosition()).y] = 0;
                crt->setTempPosition();
            }
            else
            {
                toWaitingArray(crt, myPlayerData);
            }
        }
        else if (chessSelected >= SEPARATION) // ѡ�б�ս��������
        {
            auto crt = static_cast<Hero*>(myPlayerData.waitingArray->arr[chessSelected - SEPARATION]);
            if (haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] == 1)   // �����ظ�ѡ��
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
            }
            else if (pairReturn(crt->getPosition()).x == 0 || pairReturn(crt->getPosition()).x == 7)  //���ڵȺ���
            {
                //Point temppoint = inWhichCell(temp->getPosition());
                crt->setPosition(inWhichCell(crt->getPosition()));
                crt->set(inWhichCell(crt->getPosition()));

                haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] = 1;
                haveChess[pairReturn(crt->getTempPosition()).x][pairReturn(crt->getTempPosition()).y] = 0;
                crt->setTempPosition();
            }
            else if (afterFight->totalTime > 1e-6)//���뱸սʱ��
            {
                if (myPlayerData.battleArray->num < myPlayerData.playerLevel)
                    toBattleArray(crt, myPlayerData);
                else
                {
                    crt->setPosition(inWhichCell(crt->getTempPosition()));
                    crt->set(inWhichCell(crt->getTempPosition()));
                    auto label = Label::createWithTTF("Not enough Grade!", "fonts/Marker Felt.ttf", 36);
                    this->addChild(label);
                    label->setTextColor(Color4B::WHITE);
                    label->setPosition(800, 400);
                    auto move = FadeOut::create(2.0f);
                    label->runAction(move);

                    chessSelected = -1;
                }
            }
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
            }
        }
        chessSelected = -1;
    }

}

void sceneGame::mouseDown(Event* event)
{
    auto e = static_cast<EventMouse*>(event);

    // �ж���갴�����ڱ�ս������ս����
    if (mouseInBattleArray(myPlayerData.battleArray, e) == 1) // �����chessSelected
        mouseInBattleArray(myPlayerData.waitingArray, e);
}

void sceneGame::mouseMove(Event* event)
{
    auto e = static_cast<EventMouse*>(event);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float eachCell_y = (visibleSize.height / 2 + SPATIAL_DEVIATION_CORRECTION) / CHESS_IN_A_COL;

    if (chessSelected != -1)
    {
        if (chessSelected < SEPARATION && afterFight->totalTime < 1e-2)// ûʱ����,�������ƶ�����
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]); // -1?
            crt->setPosition(inWhichCell(crt->getTempPosition()));
            crt->set(inWhichCell(crt->getTempPosition()));
            chessSelected = -1; // ��ɲ��������ص�δѡ��״̬
            return;
        }
        else if (chessSelected < SEPARATION) // �����ƶ�ս����������
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);// -1?
            auto crtPosition = inWhichCell(crt->getPosition());

            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[3][0].y + eachCell_y / 2) //  ����ǽ���������ҷ�����
            {
                crt->setPosition(e->getCursorX(), e->getCursorY());
                crt->set(e->getCursorX(), e->getCursorY());  // �ƶ�
            }
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1;  // �������ӵ�λ�ò����ѡ��״̬
            }
        }
        else if (chessSelected >= SEPARATION) // ���ڱ�ս��������
        {
            auto crt = static_cast<Hero*>(myPlayerData.waitingArray->arr[chessSelected - SEPARATION]);//-1?
            auto crtPosition = inWhichCell(crt->getPosition());
            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[3][0].y + eachCell_y / 2) //  ����ǽ���������ҷ����� chessMap��x��width������Ҫ��y
            {
                crt->setPosition(e->getCursorX(), e->getCursorY());
                crt->set(e->getCursorX(), e->getCursorY());  // �ƶ�
            }
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1; // �������ӵ�λ�ò����ѡ��״̬
            }
        }
    }
}

Point sceneGame::inWhichCell(const Point point) const
{
    for (int i = 0; i < CHESS_IN_A_COL + 2; i++)
    {
        for (int j = 0; j < CHESS_IN_A_ROW; j++)
        {
            if (sqrt((point.x - chessMap[i][j].x) * (point.x - chessMap[i][j].x)
                + (point.y - chessMap[i][j].y) * (point.y - chessMap[i][j].y)) < 80)
                return Point(chessMap[i][j].x, chessMap[i][j].y);
        }
    }
    return Point(-1, -1);
}

/**************��ʱ��***************/
void sceneGame::update(float dt) // ʵʱ����
{
    if (afterFight->totalTime > 1e-6) //��սʱ��
    {
        heroExist->heroUpgrade(myPlayerData);
        heroExist->heroUpgrade(opPlayerData);
        //addHeroToWaiting(myPlayerData, 0);
        //addHeroToWaiting(opPlayerData, 1);
        AIPlayer.judgeGold();

    }
    addHeroToWaiting(myPlayerData, 0);
    addHeroToWaiting(opPlayerData, 1);
    mouseMainEvent();

    if (afterFight->totalTime < -1e-2) // ս��ʱ��
    {
        if (isAI)
        {
            AIPlayer.creatBattleArray();
            heroExist->aiShowBattleArray();  //��ʾ���������Ϣ
            heroExist->aiShowWaitingArray();
            if (opPlayerData.waitingArray->num == 8)
                soldHero(opPlayerData, AIPlayer.soldHero(), opPlayerData.waitingArray);   //����������
            isAI = 0;
        }
        mouseInit();   //ȡ����ս�������ӵ�ѡȡ
        afterFight->setPosition(10000, 10000);
        heroExist->scheduleUpdate();
        if (!this->battleStarted)
        {
            startBattle();
            battleStarted = true; // ȷ��ս��ֻ��ʼһ��
        }
        win();
    }
}

/**************����***************/

// ���Ӣ�۵��ȴ���
void sceneGame::addHeroToWaiting(playerData& player, int playerInfo)
{
    if (player.playerHaveNewHero)
    {
        bool haveAdded = false;
        auto selected = (static_cast<Hero*>(player.waitingArray->arr[player.waitingArray->num - 1]));
        if (playerInfo == 0)
        {
            for (int i = 0; i < CHESS_IN_A_ROW; i++)
            {
                if (haveChess[0][i] == 0)
                {
                    player.playerHaveNewHero = 0;
                    heroExist->addChild(selected);
                    //player.playerMoney -= selected->getPrice();
                    selected->setPosition(chessMap[0][i].x, chessMap[0][i].y);
                    selected->set(chessMap[0][i].x, chessMap[0][i].y);
                    selected->setTempPosition();
                    selected->retain();
                    selected->setPlayer(playerInfo);
                    player.heroNum[selected->getType()]++;
                    haveChess[0][i] = 1;
                    haveAdded = true;
                    break;
                }
            }
        }
        else
        {
            //player.playerMoney -= selected->getPrice();
            heroExist->addChild(selected);
            selected->setPosition(10000, 10000);
            selected->set(10000, 10000); // ?
            selected->setPlayer(playerInfo);
            player.heroNum[selected->getType()]++;
            player.playerHaveNewHero = 0;
            haveAdded = true;
        }
        if (!haveAdded)
        {
            ccArrayRemoveObject(player.waitingArray, selected);
            player.playerHaveNewHero = 0;
        }
    }
}

int sceneGame::endAlivePieces(const playerData& player) const
{
    int alive = 0;
    for (int i = 0; i < player.battleArray->num; i++)
    {
        auto crt = static_cast<Hero*>(player.battleArray->arr[i]);
        if (!crt->isDead())
        {
            alive++;
        }
    }
    return alive;
}

void sceneGame::win()
{
    int myAlivePieces = endAlivePieces(myPlayerData);
    int opAlivePieces = endAlivePieces(opPlayerData);

    if (!(myAlivePieces && opAlivePieces))
    {
        if (myAlivePieces == 0)
        {
            myPlayerData.playerHurt(BASICAL_HURT + EACH_CHESS_HURT * opAlivePieces);
        }
        else if (opAlivePieces == 0)
        {
            opPlayerData.playerHurt(BASICAL_HURT + EACH_CHESS_HURT * myAlivePieces);
        }
        afterWin(myPlayerData.waitingArray);
        afterWin(myPlayerData.battleArray);
        afterWin(opPlayerData.waitingArray);
        afterWin(opPlayerData.battleArray);
        /*********************************/
        // �����Ƶ
        heroExist->unscheduleUpdate();     
        /*********************************/

        myPlayerData.updateMoneyAndExp();
        opPlayerData.updateMoneyAndExp();
        battleStarted = false;
        if (myPlayerData.playerHealth > 0 && opPlayerData.playerHealth > 0) // ˫����Ȼ���
        {
            _director->replaceScene(sceneGame::createScene(playerName));
        }
        else
        {
            string winner = myPlayerData.playerHealth > 0 ? playerName : "opPlayer";
            winner += " win!";
            auto label = Label::createWithTTF(winner, "fonts/Marker Felt.ttf", 36);
            this->addChild(label);
            label->setTextColor(Color4B::WHITE);
            label->setPosition(800, 400);
            auto move = FadeOut::create(5.0f);
            label->runAction(move);


            auto sprite2 = Sprite::create("vict.png");
            this->addChild(sprite2);
            sprite2->setPosition(800, 460);
            sprite2->setScale(2.0f);
            auto move2 = FadeOut::create(2.0f);
            sprite2->runAction(move2);


            this->unscheduleUpdate();

            myPlayerData.playerInit();
            opPlayerData.playerInit();

            for (int i = 0; i < CHESS_IN_A_COL + 2; i++)
            {
                for (int j = 0; j < CHESS_IN_A_ROW; j++)
                {
                    haveChess[i][j] = false;
                }
            }
            _director->replaceScene(TransitionFade::create(8.0f, mainMenu::createScene()));
        }
    }
}

void sceneGame::afterWin(ccArray* crtArray)
{
    for (int i = 0; i < crtArray->num; i++)
    {
        Hero* crt = static_cast<Hero*>(crtArray->arr[i]);

        crt->retain();
        /************�ͷ�/�ָ�******************/
        crt->removeFromParent();
        crt->recover();
    }
}

void sceneGame::soldHero(playerData& player, Hero* hero, ccArray* Array)
{
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    myPlayerData.playerMoney += hero->soldMoney;
    hero->retain();
    heroExist->removeChild(hero);
    ccArrayRemoveObject(Array, hero);
}

bool sceneGame::mouseInBattleArray(ccArray* Array, EventMouse* e)
{
    int temp = (Array == myPlayerData.waitingArray) ? SEPARATION : 0;
    // ս������0��ʼ����ս����SEPARATION��ʼ

    if (afterFight->totalTime > 0 || afterFight->totalTime <= 0 && temp == SEPARATION)// ȷ���ڱ�սʱ��
    {
        for (int m = 0; m < Array->num; m++)
        {
            float distance = sqrt(
                (e->getCursorX() - (static_cast<Hero*>(Array->arr[m]))->getPosition().x)
                * (e->getCursorX() - (static_cast<Hero*>(Array->arr[m]))->getPosition().x) +
                (e->getCursorY() - (static_cast<Hero*>(Array->arr[m]))->getPosition().y)
                * (e->getCursorY() - (static_cast<Hero*>(Array->arr[m]))->getPosition().y));
            if (distance < CAN_BE_SELECTED)
            {
                if ((int)e->getMouseButton() == 0) // ���
                {
                    chessSelected = m + temp;
                }
                else if ((int)e->getMouseButton() == 1 && afterFight->totalTime > 1e-2) // �Ҽ��������ڱ�սʱ�䣬��������
                {
                    auto tempHero = static_cast<Hero*>(Array->arr[m]);
                    soldHero(myPlayerData, tempHero, Array);
                    return false;
                }
                (static_cast<Hero*>(Array->arr[m]))->setTempPosition();
                return false;
            }
        }
    }
    return true;
}

void sceneGame::toBattleArray(Hero* hero, playerData& player)
{
    hero->setPosition(inWhichCell(hero->getPosition()));
    hero->set(inWhichCell(hero->getPosition()));

    haveChess[pairReturn(hero->getPosition()).x][pairReturn(hero->getPosition()).y] = 1;      //�������Ӵ������
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    hero->setTempPosition();
    ccArrayAppendObject(myPlayerData.battleArray, hero);  //����ս����
    ccArrayRemoveObject(myPlayerData.waitingArray, hero);   //���±�ս��
}

void sceneGame::toWaitingArray(Hero* hero, playerData& player)
{
    hero->setPosition(inWhichCell(hero->getPosition()));
    hero->set(inWhichCell(hero->getPosition()));

    haveChess[pairReturn(hero->getPosition()).x][pairReturn(hero->getPosition()).y] = 1;      //�������Ӵ������
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    hero->setTempPosition();
    ccArrayAppendObject(myPlayerData.waitingArray, hero);    //���뱸ս��
    ccArrayRemoveObject(myPlayerData.battleArray, hero);   //����ս����
}

sceneGame* sceneGame::createScene(string& userName)
{
    playerName = userName;
    return sceneGame::create();
}

string sceneGame::getUserName() const
{
    return playerName;
}

sceneGame::sceneGame()
{

}

sceneGame::~sceneGame()
{

}

void sceneGame::startBattle()
{
    // ����ս���������е�ÿ�� Hero ���󲢵��� play ����
    for (int i = 0; i < myPlayerData.battleArray->num; i++)
    {
        auto hero = static_cast<Hero*>(myPlayerData.battleArray->arr[i]);
        hero->ofPlayer = HUMAN;
        hero->connection(myPlayerData);
        hero->Play(); 
    }
    for (int i = 0; i < opPlayerData.battleArray->num; i++)
    {
        auto hero = static_cast<Hero*>(opPlayerData.battleArray->arr[i]);
        hero->ofPlayer = AI;
        hero->Play();
    }
}
