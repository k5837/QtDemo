#include "mainscene.h"
#include"config.h"
#include<QIcon>
#include<QPainter>
#include<QMouseEvent>
#include<ctime>
#include<QSound>
mainscene::mainscene(QWidget *parent)
    : QWidget(parent)
{
    //调用初始化场景的接口
    initScene();
    //启动游戏
    playGame();
}

mainscene::~mainscene()
{
}

void mainscene::initScene()
{
    //设置窗口固定尺寸
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置标题
    setWindowTitle(GAME_TITLT);
    //加载图标
    setWindowIcon(QIcon(":/res/QQ图片20200511165027.png"));
    //定时器的初始化
    m_Timer.setInterval(GAME_RATE);
    //敌机出场时间间隔 初始化
    m_recorder=0;

    //随机数种子
    srand((unsigned int)time(NULL));
}

void mainscene::playGame()
{
    //启动背景音乐
       QSound::play(SOUND_BACKGROUND);
    //启动定时器
    m_Timer.start();
    //监听定时器发送的信号
    connect(&m_Timer,&QTimer::timeout,[=](){
        //敌机出场
        enemyToScene();
        //更新游戏中元素的坐标
       updatePosition();
        //绘制到屏幕中
        update();
        //碰撞检测调用
         collisionDetection();

    });
}

void mainscene::updatePosition()
{

    //更新地图的坐标
    m_map.mapPosition();
    //发射子弹
    m_hero.shoot();
    //计算所有非空闲子弹的当前坐标
    for(int i=0;i<BULLET_NUM;i++)
       {
            //如果非空闲，计算发射位置
            if(m_hero.m_bullets[i].m_Free==false)
            {
                m_hero.m_bullets[i].updatePosition();
            }
        }

    //敌机出场
    for(int i=0;i<ENEMY_NUM;i++)
    {
        //如果是空闲的敌机，出场
        if(m_enemys[i].m_Free==false)
        {
            m_enemys[i].updatePosition();
        }
    }
    //计算爆炸的播放的图片
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free==false)
        {
            m_bombs[i].updateInfo();
        }
    }

    //测试子弹
    //temp_Bullet.m_Free=false;
    //temp_Bullet.updatePosition();

}

void mainscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制英雄飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);

    //绘制子弹 非空闲的子弹
    for(int i=0;i<BULLET_NUM;i++)
       {
            //非空闲开始绘制
        if(m_hero.m_bullets[i].m_Free==false)
        {

            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }
       }

    //绘制敌机
    for(int i=0;i<ENEMY_NUM;i++)
       {
            //非空闲开始绘制
        if(m_enemys[i].m_Free==false)
        {

            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
       }

    //绘制爆炸
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free==false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }


    //测试子弹
    //painter.drawPixmap(temp_Bullet.m_X,temp_Bullet.m_Y,temp_Bullet.m_Bullet);
}

void mainscene::mouseMoveEvent(QMouseEvent * event)
{
    int x= event->x()-m_hero.m_Rect.width()*0.5;
    int y= event->y()-m_hero.m_Rect.height()*0.5;

    //边界检测
    if(x<=0)
    {
        x=0;
    }
    if(x>=GAME_WIDTH-m_hero.m_Rect.width())
    {
        x=GAME_WIDTH-m_hero.m_Rect.width();
    }
    if(y<=0)
    {
        y=0;
    }
    if(y>=GAME_HEIGHT-m_hero.m_Rect.height())
    {
        x=GAME_HEIGHT-m_hero.m_Rect.height();
    }

    m_hero.setPosition(x,y);
}

void mainscene::enemyToScene()
{
    m_recorder++;
    //未达到出场间隔，直接return
    if(m_recorder<ENEMY_INTERVAL)
    {
        return;
    }
    m_recorder=0;
    for(int i=0;i<ENEMY_NUM;i++)
    {
        //如果是空闲的敌机，出场
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free=false;
            //坐标
            m_enemys[i].m_X=rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y=-m_enemys[i].m_Rect.height();
            break;
        }
    }

}

void mainscene::collisionDetection()
{
    //遍历所有非空闲敌机
    for(int i=0;i<ENEMY_NUM;i++)
    {
        //如果是空闲的敌机，执行下一次循环
        if(m_enemys[i].m_Free)
        {
           continue;
        }
        //遍历非空闲的子弹
        for(int j=0;j<BULLET_NUM;j++)
        {
            //空闲子弹执行下一次循环
            if(m_hero.m_bullets[j].m_Free)
                {
                   continue;
                }
            //如果子弹和飞机相交，发生碰撞，同时将飞机和子弹空闲状态设置为真
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                m_enemys[i].m_Free=true;
                m_hero.m_bullets[j].m_Free=true;


                //播放爆炸效果
                for(int k=0;k<BOMB_NUM;k++)
                   {
                        if(m_bombs[k].m_Free)
                        {
                            //播放爆炸音效
                            QSound::play(SOUND_BOMB);
                             m_bombs[k].m_Free=false;
                             //更新爆炸坐标
                             m_bombs[k].m_X=m_enemys[i].m_X;
                             m_bombs[k].m_Y=m_enemys[i].m_Y;
                             break;
                        }
                    }

              }
        }
    }
}

