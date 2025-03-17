#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include<QTimer>
#include<map.h>
#include"heroplane.h"
#include "bullet.h"
#include"enemyplane.h"
#include"bomb.h"
class mainscene : public QWidget
{
    Q_OBJECT

public:
    mainscene(QWidget *parent = nullptr);
    ~mainscene();
    //初始化场景
    void initScene();

    //启动游戏
    void playGame();

    //更新所有游戏中元素坐标
    void updatePosition();

    //绘制到屏幕中 函数名称不能改
    void paintEvent(QPaintEvent *);

    //重新鼠标移动事件 函数名称不能改
    void mouseMoveEvent(QMouseEvent *);

    //敌机出场
    void enemyToScene();

    //碰撞检测
    void collisionDetection();

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    //敌机出场间隔记录
    int m_recorder;

    //地图对象
    Map m_map;

    //飞机对象
    HeroPlane m_hero;

    //定时器
    QTimer m_Timer;

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];


    //测试子弹对象
   // Bullet temp_Bullet;
};
#endif // MAINSCENE_H
