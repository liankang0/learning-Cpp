#ifndef _warcraft_H_
#define _warcraft_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::map;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ifstream;


enum Color
{
    RED,
    BLUE,
    NOTSET
};

enum WarriorType
{
    DRAGON_TYPE,
    NINJA_TYPE,
    ICEMAN_TYPE,
    LION_TYPE,
    WOLF_TYPE    
};


//为了通过某种颜色或者武士类型，得到字符串，所以实现了以下inline函数.
inline string toString(Color color)
{
    return (color == RED) ? string("red"): string("bule");
}

inline string toString(WarriorType type)
{
    switch (type)
    {
    case DRAGON_TYPE: return "dragon";
    case NINJA_TYPE: return "ninja";
    case ICEMAN_TYPE: return "iceman";
    case LION_TYPE: return "lion";
    case WOLF_TYPE: return "wolf";
    default:
        return string();
    }
}
class Headquarters;

//单例模式
class GameConfig
{
public:
    static GameConfig* getInstance();
    static void destory();

    //void readFromConsole(); //从控制台获取测试数据
    void readFromFile(const string& filename);//从配置文件中获取测试数据
    void nextGroupId() {    ++_currentGroupId;  }//测试系一组数据

    size_t group() const {  return _groups.size();  }
    size_t currentGroupId() const { return _currentGroupId; }
    size_t cityCount() const;
    size_t headquartersInitialElements() const;
    size_t warriorInitalLife(WarriorType key) const;
    size_t warriorINitalAttack(WarriorType key) const;

private:
    ~GameConfig() {   cout << "~GameConfig()" << endl;  }

    struct InitData
    {
        size_t _initElements;
        size_t _cityCount;
        size_t _minutes;
        map<WarriorType, size_t> _initLifes;
        map<WarriorType, size_t> _initAttacks;
    };
private:
    static GameConfig* _pInstance;

    vector<InitData> _groups;//N组数据
    size_t _currentGroupId;//当前正在测试的一组数据
    vector<WarriorType> _initWarriorOrder;//输入时武士的生命值和攻击力的设置顺序
};

class GameTime
{
public:
    static GameTime* getInstance();
    static void destory();

    void showTime() const;
    void updateTime();
    void reset() {  _hour = 0; _minute = 0; }

private:
    GameTime(size_t hour = 0, size_t minute = 0)
    :_hour(hour)
    ,_minute(minute)
    {

    }

private:
    static GameTime* _pInstance;
    size_t _hour;
    size_t _minute;
};


/*************Warrior******武士类*************/
class Warrior
{
public:
    Warrior(Color color,
            const string& name,
            size_t id,
            size_t hp,
            size_t forces,
            WarriorType type)
        :_color(color)
        ,_name(name)
        ,_id(id)
        ,_forces(forces)
        ,_type(type)
        {    }
    virtual ~Warrior(){ }

    virtual void march();//行军
    virtual void attack(Warrior* warrior);//攻击另一个武士
    virtual void defense(Warrior* warrior);//反击另一个武士
    virtual size_t getLoyalty() const { };
    void beWinner(Warrior* warrior) ;
    void beRewarded();
    //void bekill() { }//从司令部和城市删除
    void setElements(size_t elements)  {    _earnElements += elements; }
    void sentElementsToHeadquarters(); 
    void setHp(size_t hp) { _hp = hp;   }
    void setCity(size_t id) {  _cityId = id;   }
    void setHeadquarters(Headquarters* headquarters) { _headquarters = headquarters;    }
    Color getColor() const {    return _color;  }
    string getName() {  return _name;   }
    size_t getId() {    return _id; }
    size_t getHp() {    return _hp;    }
    size_t getCityId() {    return _cityId; }
    size_t getElements() const {    return _earnElements;   }
    size_t getForces() const { return _forces;  }
    WarriorType getType() const {   return _type;   }


protected:
    Color _color;
    string _name;
    size_t _id;
    size_t _hp;
    size_t _forces;
    size_t _cityId;
    size_t _earnElements;
    WarriorType _type;
    Headquarters* _headquarters;

};

class Dragon
:public Warrior
{
public:
    Dragon(Color color, size_t id, size_t hp, size_t forces)
    :Warrior(color, "dragon", id, hp, forces, DRAGON_TYPE)
    { }
};

class Ninja
:public Warrior
{
public:
    Ninja(Color color, size_t id, size_t hp, size_t forces)
    :Warrior(color, "ninja", id, hp, forces, NINJA_TYPE)
    { }
    //挨打不反击，需要覆盖
    virtual void defense(Warrior* warrior) override { };
};

class Iceman
:public Warrior
{
public:
    Iceman(Color color, size_t id, size_t hp, size_t forces)
    :Warrior(color, "iceman", id, hp, forces, ICEMAN_TYPE)
    ,_steps(0)
    { }
    //iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。
    //但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。
    //需覆盖
    virtual void march() override;

private:
    size_t _steps;//前进的步数
};

class Lion
:public Warrior
{
public:
    Lion(Color color, size_t id, size_t hp, size_t forces)
    :Warrior(color, "lion", id, hp, forces, LION_TYPE)
    {}
};

class Wolf
:public Warrior
{
public:
    Wolf(Color color, size_t id, size_t hp, size_t forces)
    :Warrior(color, "wolf", id, hp, forces, WOLF_TYPE)
    ,_killTimes(0)
    {   }
    /*在一个wolf 通过主动攻击杀死敌人的次数达到偶数的时刻（次数从1开始算）
    ，在战斗完成后，该 wolf 生命 值和攻击力都增加1倍。
    如果其杀死的敌人是lion,则攻击力和生命值先加倍，
    然后才吸取lion的生命值。获取 总部的生命元奖励，发生在加倍之后。
    只有在主动攻击杀死敌人时才能有加倍的事情，反击杀死敌人则不不会发
     生加倍。需覆盖*/
    virtual void attack(Warrior* warrior) override;
private:
    int _killTimes;//击杀次数
};

/*************city***********城市类************/
class City
{
public:
    City(size_t id, size_t elements = 0)
    :_flag(Color::NOTSET)
    ,_id(id)
    ,_lastWin(0)
    ,_elements(elements)
    ,_redWinCount(0)
    ,_blueWinCount(0)
    {}

    void produceElements();//城市生产生命元
    void attach(Warrior*);//某武士进入该城市
    void detach(Warrior*);
    void startBattle();//开始战斗
    void takenBy();//生命元被某武士取走
private:
    void battle(Warrior* warrior1, Warrior* warrior2);//两名武士具体战斗状况
    bool isChangingFlag();//是否更换旗帜
private:
    Color _flag;//城市旗子的颜色
    size_t _lastWin;//0是上一局没战斗，1是红赢， 2是蓝赢
    size_t _id;
    size_t _elements;
    size_t _redWinCount; 
    size_t _blueWinCount;
    vector<Warrior*> _redWarriors;
    vector<Warrior*> _blueWarriors;

};



/**************Headquarters******司令部***********/
class Headquarters
{
public:
    Headquarters(Color color, size_t elements)
    :_color(color)
    ,_elements(elements)
    ,_earnElements(0)
    ,_nextWarriorIndex(0)
    { }
    
    virtual ~Headquarters() {   }

    //创建武士
    Warrior* create();

    //添加胜利者
    void addWinner(Warrior* warrior);
    
    //奖励胜利者
    void reward();

    //统计从城市获取的生命元
    void increaseElements(size_t elements) {    _earnElements += elements;  }

    //设置所剩生命元的数量
    void setElements() { _elements += _earnElements; _earnElements = 0;   }

    template <typename Iterator>
    void setWarriorCreatingOrder(Iterator beg, Iterator end)
    {
        for(; beg != end; ++beg)
        {
            _warriorCreatingOrder.push_back(*beg);
        }
    }

    size_t getId() const {  return _id; }
    void setId(size_t id) { _id = id;   }
    Color getColor() const {    return _color;  }
    size_t getElements() const {    return _elements;  }
    size_t getWarriorCount() const {    return _warriors.size(); }
    vector<Warrior*> & getWarriors()  {    return _warriors;}
    


private:
    //生产各种武士
    Warrior* createIceman(size_t id, size_t hp, size_t forces);
    Warrior* createLion(size_t id, size_t hp, size_t forces);
    Warrior* createWolf(size_t id, size_t hp, size_t forces);
    Warrior* createNinja(size_t id, size_t hp, size_t forces);
    Warrior* createDragon(size_t id, size_t hp, size_t forces);

    //void nextWarriorType();

    WarriorType getNextWarriorType()
    {   return _warriorCreatingOrder[_nextWarriorIndex];    }

protected:
    Color _color;//红或蓝
    size_t _id;
    size_t _elements;
    size_t _earnElements;
    size_t _nextWarriorIndex;
    vector<WarriorType> _warriorCreatingOrder;//武士生产顺序
    struct WarriorComparator
    {
         bool operator()(Warrior* a, Warrior* b)
         {
             return a->getCityId() < b->getCityId();
         }
    };
    //一次战斗时间结束后，胜利的所有武士
    priority_queue<Warrior*, vector<Warrior*>, WarriorComparator> _winners;
    

    vector<Warrior*> _warriors;//生产所有武士

    //各种类型武士的数量
    unordered_map<WarriorType, size_t> _warriortypeAmounts;
};

/********************WarcraftWorld******控制类********/
class WarcraftWorld
{
public:
    explicit
    WarcraftWorld()
    :_redHeadquarters(nullptr)
    ,_blueHeadquarters(nullptr)
    {   init(); }

    void start()
    {
        while(1)
        {
            createWarrior();
            if(!warriorMarch())
            {
                break;
            }
            cityProduceElements();
            takeCityElements();
            battle();
            headquartersReportElements();
        }
    }

    template <typename Iterator>
    void setRedWarriorCreateOrder(Iterator beg, Iterator end);

    template <typename Iterator>
    void setBlueWarriorCreateOrder(Iterator beg, Iterator end);

    ~WarcraftWorld()
    {
        if(_redHeadquarters) delete _redHeadquarters;
        if(_blueHeadquarters) delete _blueHeadquarters;
    }


private:
    void init();
    //--------------事件begin------------------
    void createWarrior();
    bool warriorMarch();
    void cityProduceElements();
    void takeCityElements();
    void battle();
    void headquartersReportElements();
    //---------------事件end---------------------

    bool createWarrior(Headquarters*);
    void warriorMarch(Headquarters* Headquarters);
    bool checkRedHeadquarterBeTaken();
    bool checkBlueHeadquarterBeTaken();
private:
    Headquarters* _redHeadquarters;
    Headquarters* _blueHeadquarters;
    vector<City> _citis;
};

 template <typename Iterator>
void WarcraftWorld::setRedWarriorCreateOrder(Iterator beg, Iterator end)
{
    _redHeadquarters->setWarriorCreatingOrder(beg, end);
}

template <typename Iterator>
void WarcraftWorld::setBlueWarriorCreateOrder(Iterator beg, Iterator end)
{
    _blueHeadquarters->setWarriorCreatingOrder(beg, end);
}

/**************武士视图****************/
class WarriorView
{
public: 
    WarriorView(Warrior* warrior)
    :_warrior(warrior)
    {}
    
    void showBorn() const;
    void showMarch() const;
    void showEarnElements() const;
    void showRearchDestination() const;
protected:
    void showName() const;
    void showToCity() const;
    void showInCity() const;
    void showDeath() const;
    void showElementsAndForces() const;
protected:
    Warrior* _warrior;
};

/********dragon欢呼视图***********/
class DragonView
:public WarriorView
{
public:
    DragonView(Warrior* warrior)
    :WarriorView(warrior)
    {}

    void showYell() const;
};

/***********战斗视图***************/
class BattleView
{
public:
    BattleView(Warrior* warrior1, Warrior* warrior2)
    :_warrior1(warrior1)
    ,_warrior2(warrior2)
    {}
    void showBattle() const;
    void showDefense() const;

private:
    Warrior* _warrior1;
    Warrior* _warrior2;
};

/*************司令部视图**************/
class HeadquarterView
{
public:
    HeadquarterView(Headquarters* headquarters)
    :_headquarters(headquarters)
    {}

    void showLeftElements() const;

    void showBeTaken() const;
private:
    Headquarters* _headquarters;
};

/*************城市视图****************/
class CityView
{
public: 
    CityView(City* city)
    :_city(city)
    {}

    void showFlag() const;
private:
    City* _city;
};

#endif

