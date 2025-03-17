#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH  512 //宽度
#define GAME_HEIGHT 768 //高度
#define GAME_TITLT "飞机大战 v1.0" //标题
#define GAME_RES_PATH "./plane.rcc"//rcc文件路径位置
#define GAME_RATE 10   //定时器刷新的时间间隔单位是毫秒，每十毫秒地图滚动两像素
/************ 地图的配置数据************/
#define MAP_SCROLL_SPEED 2 //地图滚动的速度

#define BULLET_SPEED 5 //子弹移动速度

#define BULLET_NUM 30     //弹匣中子弹数
#define BULLET_INTERVAL 20   //发射子弹时间间隔

#define ENEMY_SPEED 5 //敌机移动速度
#define ENEMY_NUM  20 //敌机总数量
#define ENEMY_INTERVAL  30 //敌机出场时间间隔

#define BOMB_PATH "C://Users/wangxia/Documents/planeWar/res/bomb-%1.png"
#define BOMB_NUM 20
#define BOMB_MAX 3
#define BOMB_INTERVAL 15

#define SOUND_BACKGROUND "C://Users/wangxia/Documents/planeWar/res/bg.wav"
#define SOUND_BOMB "C://Users/wangxia/Documents/planeWar/res/bomb.wav"


#endif // CONFIG_H
