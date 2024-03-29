#include "warcraft.h"

GameConfig* GameConfig::_pInstance = nullptr;
//这个单例模式没有使用懒汉模式，后面可以加上
GameConfig* GameConfig::getInstance()
{
    if(!_pInstance)//这里有疑问，没有初始化，_pInstance 是空吗
    {
        _pInstance = new GameConfig();
    }
    return _pInstance;
}

void GameConfig::destory()
{
    if(_pInstance)
    {
        delete _pInstance;
    }
}

//void Gameconfig::readFromConsole() //从控制台获取测试数据

//c++格式化读取和C语言比用起来太爽了
void GameConfig::readFromFile(const string& filename)//从配置文件中获取测试数据
{
    ifstream  ifs;
    ifs.open(filename);
    int count_groups;
    InitData initData;
    size_t recVal;//用于接收魔兽的血量和攻击力
    //读取数据的组数
    ifs >> count_groups;
    //读取每组数据
    for(int i = 0; i < count_groups; ++i)
    {
        ifs >> initData._initElements 
            >> initData._cityCount
            >> initData._minutes;
        for(int j = 0; j < 5; ++j)
        {
            ifs >> recVal;
            initData._initLifes[WarriorType(DRAGON_TYPE + j)] = recVal ;
        }
        for(int j = 0; j < 5; ++j)
        {
            ifs >> recVal;
            initData._initAttacks[WarriorType(DRAGON_TYPE + j)] = recVal ;
        }
        _groups.emplace_back(initData);
    }
    ifs.close();
}

size_t GameConfig::cityCount() const
{
    return _groups[_currentGroupId]._cityCount;
}

size_t GameConfig::headquartersInitialElements() const
{
    return _groups[_currentGroupId]._initElements;
}
size_t GameConfig::warriorInitalLife(WarriorType key) const
{
     auto it = _groups[_currentGroupId]._initLifes.find(key);
     if(it != _groups[_currentGroupId]._initLifes.end())
     {
         return it->second;
     }
     else
     {
         return 0;
     }
}
size_t GameConfig::warriorINitalAttack(WarriorType key) const
{
     auto it = _groups[_currentGroupId]._initAttacks.find(key);
     if(it != _groups[_currentGroupId]._initAttacks.end())
     {
         return it->second;
     }
     else
     {
         return 0;
     }
}


/************GameTime****时间类****************/
GameTime* GameTime::_pInstance = nullptr;
GameTime* GameTime::getInstance()
{
    if(!_pInstance)
    {
        _pInstance = new GameTime();
    }
    return _pInstance;
}
void GameTime::destory()
{
    if(_pInstance)
    {
        delete _pInstance;
    }
}

void GameTime::showTime() const
{
    cout << std::setfill('0') << std::setw(3) << _hour << ":" 
         << std::setfill('0') << std::setw(2)  << _minute << "  ";     
}

void GameTime::updateTime()
{
    if(_minute == 50)
    {
        ++_hour;
        _minute = 0;
    }
    else
    {
        _minute += 10;
    }

}

/*************Warrior******武士类*************/
void Warrior::march()//行军
{
    if(_color == RED)
    {
        _cityId++;
    }
    else
    {
        _cityId--;
    }
    
}

bool Warrior::reachDestination()
{   //cout << "调试5" << endl;
    if(_color == RED)
    { 
        if(_cityId == GameConfig::getInstance()->cityCount() + 1)
        {
            return true;
        }
    }
    else
    {
        if(_cityId == 0)
        {
            return true;
        }
    }
    return false;
}
void Warrior::attack(Warrior* warrior)//攻击另一个武士
{
    size_t beforeAttackHp = warrior->getHp();
    if(warrior->getHp() - this->_forces <= 0)
    {
        warrior->setHp(0);
    }
    else
    {
        warrior->setHp(warrior->getHp() - this->_forces);
    }
    if(warrior->getHp() == 0 && warrior->getType() == LION_TYPE)
    {
        _hp += beforeAttackHp;
    }
}
void Warrior::defense(Warrior* warrior)//反击另一个武士
{
    size_t beforeAttackHp = warrior->getHp();
    if(warrior->getHp() <= this->_forces/2)
    {
        warrior->setHp(0);
    }
    else
    {
        warrior->setHp(warrior->getHp() - this->_forces/2);
    }
    if(warrior->getHp() < 0 && warrior->getType() == LION_TYPE)
    {
        _hp += beforeAttackHp;
    }
}

void Warrior::beRewarded()
{
     _headquarters->reward();
}

void Warrior::beWinner()
{
     _headquarters->addWinner(this);
}

void Warrior::sentElementsToHeadquarters()
{
    _headquarters->increaseElements(_earnElements);
    _headquarters->setElements();
}
void Iceman::march() 
{
    if(_color == RED)
    {
        _cityId++;
    }
    else
    {
        _cityId--;
    }
    _steps++;
    if( _steps % 2 == 0)
    {
        if(this->_hp > 9)
        {
            this->_hp -= 9;
        }
        else
        {
            this->_hp = 1;
        }
        this->_forces += 20;
    }
}

void Wolf::attack(Warrior* warrior)
{
    size_t beforeAttackHp = warrior->getHp(); 
    size_t hp = warrior->getHp() - this->_forces;
    warrior->setHp(hp);
    if(warrior->getHp() <= 0)
    {
        _killTimes++;
        if(_killTimes % 2 == 0)
        {
            _hp *= 2;
            _forces *= 2;
            if(warrior->getType() == LION_TYPE)
            {
                _hp += beforeAttackHp;
            }
        }
    }
}

/*************city***********城市类************/
void City::produceElements()//城市生产生命元
{
    _elements += 10;
}
void City::attach(Warrior* warrior)//某武士进入该城市
{
    if(warrior->getColor() == RED)
    {
        
        _redWarriors.push_back(warrior);
       // cout << " warrior " << warrior->getName() << " reach " << _id << endl;
       // cout << " 空 =  " << _redWarriors.empty() << endl;

    }
    else
    {
        
        _blueWarriors.push_back(warrior);
       // cout << " warrior " << warrior->getName() << " reach " << _id << endl;
        //cout << " 空 =  " << _blueWarriors.empty() << endl;
    }
}
void City::detach(Warrior* warrior)
{
    if(warrior->getColor() == RED)
    {
        _redWarriors.pop_back();
    }else {
        _blueWarriors.pop_back();
    }

}
bool City::startBattle()//开始战斗
{ 
    //cout << "red empty " << _redWarriors.empty() << " blue " << _blueWarriors.empty() << endl;
    if(!_redWarriors.empty() && !_blueWarriors.empty())
    {
        return battle(_redWarriors.back(), _blueWarriors.back());
    }
    return false;//返回值表示在这次战斗中是否换旗子
}
bool City::battle(Warrior* warriorRed, Warrior* warriorBlue)//两名武士具体战斗状况
{   
    bool flag = 0; //表示是否换旗子 0否 1 是
    BattleView redBattleView(warriorRed, warriorBlue);
    BattleView blueBattleView(warriorBlue, warriorRed);
    WarriorView redWarriorView(warriorRed);
    WarriorView blueWarriorView(warriorBlue);
    DragonView redDragonView(warriorRed);
    DragonView blueDragonView(warriorBlue);
    if(_flag == RED || _flag == NOTSET && this->_id % 2 != 0)
    {  
        GameTime::getInstance()->showTime(); 
        redBattleView.showBattle();
        cout << endl;

        warriorRed->attack(warriorBlue);
        if(warriorBlue->getHp() > 0)
        {
            GameTime::getInstance()->showTime();
            blueBattleView.showDefense();
            cout << endl;

            warriorBlue->defense(warriorRed);
            if(warriorRed->getHp() <= 0)
            {
                GameTime::getInstance()->showTime();
                redWarriorView.showDeath();
                cout << endl;
                _blueWinCount++;
                _lastWin = 2;
                _redWarriors.pop_back();
                warriorBlue->beWinner();
            }
            if(warriorBlue->getHp() > 0 && warriorBlue->getType() == DRAGON_TYPE)
            {
                GameTime::getInstance()->showTime();
                blueDragonView.showYell();
                cout << endl;
            }
            if(warriorRed->getHp() > 0 && warriorRed->getType() == DRAGON_TYPE)
            {
                GameTime::getInstance()->showTime();
                redDragonView.showYell();
                cout << endl;
            }
        }
        else
        {
            GameTime::getInstance()->showTime();
            blueWarriorView.showDeath();
            cout << endl;

            if(_lastWin == 1)
            {
                isChangingFlag();
                flag = true;
            }
            _redWinCount++;
            _lastWin = 1;
            _blueWarriors.pop_back();
            warriorRed->beWinner();
        }
    }
    else
    {
        GameTime::getInstance()->showTime();
        blueBattleView.showBattle();
        cout << endl;

        warriorBlue->attack(warriorRed);
        if(warriorRed->getHp() > 0)
        {
            GameTime::getInstance()->showTime();
            redBattleView.showDefense();
            cout << endl;

            warriorRed->defense(warriorBlue);
            if(warriorBlue->getHp() <= 0)
            {
                GameTime::getInstance()->showTime();
                blueWarriorView.showDeath();
                cout << endl;

                _blueWarriors.pop_back();
                _redWinCount++;
                _lastWin = 1;
                warriorRed->beWinner();
            }
            if(warriorBlue->getHp() > 0 && warriorBlue->getType() == DRAGON_TYPE)
            {
                GameTime::getInstance()->showTime();
                blueDragonView.showYell();
                cout << endl;
            }
            if(warriorRed->getHp() > 0 && warriorRed->getType() == DRAGON_TYPE)
            {
                GameTime::getInstance()->showTime();
                redDragonView.showYell();
                cout << endl;
            }
        }
        else
        {
            GameTime::getInstance()->showTime();
            redWarriorView.showDeath();
            cout << endl;

            if(_lastWin == 2)
            {
                isChangingFlag();
                flag = true;
            }
            _blueWinCount++;
            _lastWin = 2;
            _redWarriors.pop_back();
            warriorBlue->beWinner();
        }
        
    }
    return flag;
}

void City::takenBy()//生命元被某武士取走
{
    if(1 == _redWarriors.size() + _blueWarriors.size())
    {
        if(!_redWarriors.empty())
        {
            
            _redWarriors.back()->setElements(_elements);
            _elements = 0;
            _redWarriors.back()->sentElementsToHeadquarters();
            GameTime::getInstance()->showTime();
            WarriorView warriorView(_redWarriors.back());
            warriorView.showEarnElements();
            cout << endl;
        }
        else
        {
            _blueWarriors.back()->setElements(_elements);
            _elements = 0;
            _blueWarriors.back()->sentElementsToHeadquarters();
            GameTime::getInstance()->showTime();
            WarriorView warriorView(_blueWarriors.back());
            warriorView.showEarnElements();
            cout << endl;
        }
        
    }
}


bool City::isChangingFlag()
{
    if(_flag == RED && _lastWin == 2) 
    {
        _flag = BLUE;

    }
    else if(_flag == BLUE && _lastWin == 1)
    {
        _flag = RED;
    }

}


/**************Headquarters******司令部***********/
 //创建武士
Warrior* Headquarters::create()
{
    GameConfig* gameConfig = GameConfig::getInstance();
    switch (_warriorCreatingOrder[_nextWarriorIndex++])
    {
    case  DRAGON_TYPE: 
    {
        createDragon(_warriorId++, gameConfig->warriorInitalLife(DRAGON_TYPE), gameConfig->warriorINitalAttack(DRAGON_TYPE));
        break;
    }
    case NINJA_TYPE:
    {
        createNinja(_warriorId++, gameConfig->warriorInitalLife(NINJA_TYPE), gameConfig->warriorINitalAttack(NINJA_TYPE));
        break;
    }
    case ICEMAN_TYPE:
    {
        createIceman(_warriorId++, gameConfig->warriorInitalLife(ICEMAN_TYPE), gameConfig->warriorINitalAttack(ICEMAN_TYPE));
        break;
    }
    case LION_TYPE:
    {
        createLion(_warriorId++, gameConfig->warriorInitalLife(LION_TYPE), gameConfig->warriorINitalAttack(LION_TYPE));
        break;
    }
    case WOLF_TYPE:
    {
        createWolf(_warriorId++, gameConfig->warriorInitalLife(WOLF_TYPE), gameConfig->warriorINitalAttack(WOLF_TYPE));
        break;
    }
    
    default:
        break;
    }
}

Warrior* Headquarters::createIceman(size_t id, size_t hp, size_t forces)
{
    if(_elements >= hp)
    {
        Iceman* iceman = new Iceman(_color, id, hp, forces);
        _warriors.push_back(iceman);
        _warriortypeAmounts[ICEMAN_TYPE]++;
        _elements -= hp;
    }
    

}
Warrior* Headquarters::createLion(size_t id, size_t hp, size_t forces)
{
    if(_elements >= hp)
    {
        Lion* lion = new Lion(_color, id, hp, forces);
        _warriors.push_back(lion);
        _warriortypeAmounts[LION_TYPE]++;
        _elements -= hp;
    }

}
Warrior* Headquarters::createWolf(size_t id, size_t hp, size_t forces)
{
    if(_elements >= hp)
    {
        Wolf* wolf = new Wolf(_color, id, hp, forces);
        _warriors.push_back(wolf);
        _warriortypeAmounts[WOLF_TYPE]++;
        _elements -= hp;
    }
    
}
Warrior* Headquarters::createNinja(size_t id, size_t hp, size_t forces)
{
    if(_elements >= hp)
    {
        Ninja* ninja = new Ninja(_color, id, hp, forces);
        _warriors.push_back(ninja);
        _warriortypeAmounts[NINJA_TYPE]++;
        _elements -= hp;
    }
    
}
Warrior* Headquarters::createDragon(size_t id, size_t hp, size_t forces)
{
    if(_elements >= hp)
    {
        Dragon* dragon = new Dragon(_color, id, hp, forces);
        _warriors.push_back(dragon);
        _warriortypeAmounts[DRAGON_TYPE]++;
        _elements -= hp;
    }
  
}


void Headquarters::addWinner(Warrior* warrior)
{
    _winners.push(warrior);
}

 void Headquarters::reward()
 {
     if(_elements < 8)
     {
         while(!_winners.empty())
         {
             _winners.pop();
         }
     }
     if(_winners.size() > 0)
     { 
        //如果是红色第一个加8，如果是蓝色最后一个加8
        if(_color == BLUE)
        {
            while(_winners.size() != 1)
            {
                _winners.pop();
            }
        }        
        _winners.top()->setHp(_winners.top()->getHp() + 8);
        _elements -= 8;
        //奖励结束后清空
        while(!_winners.empty())
        {
            _winners.pop();
        }
    }
 }

/********************WarcraftWorld******控制类********/

void WarcraftWorld::init()
{
    GameConfig* gameConfig = GameConfig::getInstance();
    _redHeadquarters = new Headquarters(RED, gameConfig->headquartersInitialElements());
    _blueHeadquarters = new Headquarters(BLUE, gameConfig->headquartersInitialElements());
    _redHeadquarters->setId(0);//红色司令部id = 0
    _blueHeadquarters->setId(gameConfig->cityCount() + 1);//蓝色司令部id = n + 1
    for(int i = 1; i <= gameConfig->cityCount(); i++)
    {   
        _citis.push_back(* ( new City(i) ) );
    }
}

bool WarcraftWorld::createWarrior(Headquarters* headquarters)
{
    if(headquarters->getElements() >= headquarters->getCurWarriorLife())
    {
        headquarters->create();
        return true;
    }
    else
    {
        return false;
    }
    
    
}
bool WarcraftWorld::warriorMarch(Headquarters* Headquarters)
{
    //cout << "调试1" << endl;
    for(int i = 0; i < Headquarters->getWarriorCount(); i++)
    {
        //cout << "调试2" << endl;
        if(Headquarters->getWarriors()[i]->getHp() > 0 && !(Headquarters->getWarriors()[i]->reachDestination()))
        {//每一个活着且没有到达终点的魔兽
            //cout << "调试3" << endl;
            if(Headquarters->getWarriors()[i]->getCityId() > 0 && Headquarters->getWarriors()[i]->getCityId() < GameConfig::getInstance()->cityCount() + 1)
            {//不在司令部的魔兽都从城市中抛出
                 _citis[Headquarters->getWarriors()[i]->getCityId() - 1].detach(Headquarters->getWarriors()[i]);
            }
            Headquarters->getWarriors()[i]->march();//前进一步
            
            if(Headquarters->getWarriors()[i]->reachDestination())//到达终点
            {
                WarriorView warriorView(Headquarters->getWarriors()[i]);
                GameTime::getInstance()->showTime();
                warriorView.showRearchDestination();
                cout << endl;
            }
            else//还在途中
            {   
                //cout << "warriors " << Headquarters->getWarriors()[i]->getName() << " reach " <<  Headquarters->getWarriors()[i]->getCityId() << " city" << endl;
                _citis[Headquarters->getWarriors()[i]->getCityId() - 1].attach(Headquarters->getWarriors()[i]);
    
                WarriorView warriorView( Headquarters->getWarriors()[i]);
                GameTime::getInstance()->showTime();
                warriorView.showMarch();   
                cout << endl;//cout << "调试4" << endl;
            }       
        }
        if(checkRedHeadquarterBeTaken() | checkBlueHeadquarterBeTaken())
        {
            return true;
        }
    }
    return false;
}
bool WarcraftWorld::checkRedHeadquarterBeTaken()
{
    size_t flag = 0;//记录对方魔兽到达司令部个数
    for(int i = 0; i < _blueHeadquarters->getWarriorCount(); i++)
    {
        if(_blueHeadquarters->getWarriors()[i]->getCityId() == _redHeadquarters->getId())
        {
            flag++;
        }
    }
    if(flag >= 2)
    {
        HeadquarterView headquarterView(_redHeadquarters);
        GameTime::getInstance()->showTime();
        headquarterView.showBeTaken();
        cout << endl;
        return true;
    }
    return false;
}
bool WarcraftWorld::checkBlueHeadquarterBeTaken()
{
    size_t flag = 0;//记录对方魔兽到达司令部个数
    for(int i = 0; i < _redHeadquarters->getWarriorCount(); i++)
    {
        if(_redHeadquarters->getWarriors()[i]->getCityId() == _blueHeadquarters->getId())
        {
            flag++;
        }
    }
    if(flag >= 2)
    {
        HeadquarterView headquarterView(_blueHeadquarters);
        GameTime::getInstance()->showTime();
        headquarterView.showBeTaken();
        cout << endl;
        return true;
    }
    return false;
}

void WarcraftWorld::createWarrior()
{
    
    if(createWarrior(_redHeadquarters))
    {
        _redHeadquarters->getWarriors().back()->setHeadquarters(_redHeadquarters);
        WarriorView redWarriorView(_redHeadquarters->getWarriors().back());
        GameTime::getInstance()->showTime();
        redWarriorView.showBorn();
        cout << endl;
    }
    if(createWarrior(_blueHeadquarters))
    {
        _blueHeadquarters->getWarriors().back()->setHeadquarters(_blueHeadquarters);
        WarriorView blueWarriorView(_blueHeadquarters->getWarriors().back());
        GameTime::getInstance()->showTime();
        blueWarriorView.showBorn();
        cout << endl;
    }
}

bool WarcraftWorld::warriorMarch()
{
    GameTime::getInstance()->updateTime();
    if(warriorMarch(_redHeadquarters) | warriorMarch(_blueHeadquarters))
    {
        return true;
    }
    return false;
}

void WarcraftWorld::cityProduceElements()
{
    GameTime::getInstance()->updateTime();
    for(int i = 0; i < _citis.size(); i++)
    {
        _citis[i].produceElements();
    }
}

void WarcraftWorld::takeCityElements()
{
    GameTime::getInstance()->updateTime();
    for(int i = 0; i < _citis.size(); i++)
    {
        _citis[i].takenBy();
    }
}

void WarcraftWorld::battle()
{
    GameTime::getInstance()->updateTime();
    for(int i = 0; i < _citis.size(); i++)
    {
        if(_citis[i].startBattle())
        {   
            CityView cityView(&_citis[i]);
            GameTime::getInstance()->showTime();
            cityView.showFlag();
            cout << endl;
        }
    }
    _redHeadquarters->reward();
    _blueHeadquarters->reward();
    for(int i = 0; i < _citis.size(); i++)
    {
        _citis[i].takenBy();
    }
}

void WarcraftWorld::headquartersReportElements()
{
    GameTime::getInstance()->updateTime();
    //调用视图
    HeadquarterView redView(_redHeadquarters);
    HeadquarterView blueView(_blueHeadquarters);
    redView.showLeftElements();
    blueView.showLeftElements();
     GameTime::getInstance()->updateTime();
}

/**************武士视图****************/
void WarriorView::showBorn() const
{
    showName();
    cout << "born";
}
void WarriorView::showMarch() const
{
    showName();
    cout << "march ";
    showToCity();
    showElementsAndForces();
}
void WarriorView::showEarnElements() const
{
    showName();
    cout << "earned " << _warrior->getElements() << " for his headquarter";
}
void WarriorView::showRearchDestination() const
{
    showName();
    if(_warrior->getColor() == RED)
    {
        cout << "blue headquarter";
    }
    else
    {
        cout << "red headquarter";
    }
    showElementsAndForces();
}
void WarriorView::showName() const
{
    cout << toString(_warrior->getColor())  << " " << _warrior->getName() << " " << _warrior->getId() << " "; 
}
void WarriorView::showToCity() const
{
    cout << "to city " << _warrior->getCityId() << " ";
}
void WarriorView::showInCity() const
{
    cout << "in city " << _warrior->getCityId();
}
void WarriorView::showDeath() const
{
    showName();
    cout << "is killed ";
    showInCity();
}
void WarriorView::showElementsAndForces() const
{
    cout << "with " << _warrior->getHp() << " elements and force " << _warrior->getForces();
}
/********dragon欢呼视图***********/
void DragonView::showYell() const
{
    showName();
    cout << "yell ";
    showInCity();
}
/***********战斗视图***************/
void BattleView::showBattle() const
{ //red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
    cout << toString(_warrior1->getColor()) << " " << _warrior1->getName() << " " << _warrior1->getId() << " ";
    cout << "attacked ";
    cout << toString(_warrior2->getColor()) << " " << _warrior2->getName() << " " << _warrior2->getId() << " ";
    cout << "in city " << _warrior1->getCityId();
    cout << " with " << _warrior1->getHp() << " elements and force " << _warrior1->getForces();
}
void BattleView::showDefense() const
{
    cout << toString(_warrior1->getColor()) <<  " " <<  _warrior1->getName() << " "  << _warrior1->getId() << " ";
    cout << "fought back against ";
    cout << toString(_warrior2->getColor()) << " " <<  _warrior2->getName() << " " << _warrior2->getId() << " ";
    cout << "in city " << _warrior1->getCityId();
}
/*************司令部视图**************/
 void HeadquarterView::showLeftElements() const
 {  
     GameTime::getInstance()->showTime();
     cout << _headquarters->getElements() << " elements in " << toString(_headquarters->getColor())
          << " headquarter" << endl;
 }

 void HeadquarterView::showBeTaken() const
 {
     cout << toString(_headquarters->getColor()) << " headquarter was taken";
 }
 /*************城市视图****************/
 void CityView::showFlag() const
 {
     cout << toString(_city->getFlagColor()) << " flag raised ";
     cout << "in city " << _city->getId();
 }