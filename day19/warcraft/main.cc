#include "warcraft.h"


#if 1
int test0()
{
//武士生命值设置时的顺序
vector<WarriorType> types1 = {
DRAGON_TYPE,
NINJA_TYPE,
ICEMAN_TYPE,
LION_TYPE,
WOLF_TYPE
};
//Red武士制造的顺序
vector<WarriorType> types2 = {
ICEMAN_TYPE,
LION_TYPE,
WOLF_TYPE,
NINJA_TYPE,
DRAGON_TYPE,
};
//Blue武士制造的顺序
vector<WarriorType> types3 = {
LION_TYPE,
DRAGON_TYPE,
NINJA_TYPE,
ICEMAN_TYPE,
WOLF_TYPE
};

#if 1
//先测游戏配置类
//GameConfig::getInstance()->setWarriorOrder(types1.begin(),types1.end());
GameConfig::getInstance()->readFromFile("warcraft.conf");
//GameConfig::getInstance()->readFromFile(argv[1]);
//GameConfig::getInstance()->readFromConsole();
//GameConfig::getInstance()->debug();
//cout <<  "_groups  count =" << GameConfig::getInstance()->group() << endl;
// GameConfig::getInstance()->nextGroupId();
//cout << "this group city count = " << GameConfig::getInstance()->cityCount() << endl;
//cout << "this group DRAGON_TYPE lifecount = " << GameConfig::getInstance()->warriorInitalLife(ICEMAN_TYPE) << endl;
#endif
WarcraftWorld warcraftWorld;
warcraftWorld.setBlueWarriorCreateOrder(types3.begin(), types3.end());
warcraftWorld.setRedWarriorCreateOrder(types2.begin(), types2.end());
warcraftWorld.start();
// warcraftWorld.~WarcraftWorld();
// GameConfig::destory();
// GameTime::destory();

#if 0
//再测游戏时间类
for(int idx = 0; idx != 100; ++idx)
{
GameTime::getInstance()->showTime();
GameTime::getInstance()->updateTime();
GameTime::getInstance()->showTime();
GameTime::getInstance()->updateTime();
}
#endif

#if 0
//然后再测魔兽世界类。
//测试数据时，先测一组。当一组的测试数据没有问题之后，再测下一组
size_t groups = GameConfig::getInstance()->groups();
for(size_t groupId = 0; groupId != groups; ++groupId) {
//for(size_t groupId = 0; groupId != 1; ++groupId) {
printf("Case:%lu\n", groupId + 1);

WarcraftWorld wow;
wow.setRedWarriorCreatingOrder(types2.begin(), types2.end());
wow.setBlueWarriorCreatingOrder(types3.begin(), types3.end());
wow.start();
GameConfig::getInstance()->nextGroupId();
GameTime::getInstance()->reset();
}
#endif

//GameConfig::destroy();
//Mylogger::destroy();
return 0;
}
#endif

int main(void)
{
    test0();
    return 0;
}