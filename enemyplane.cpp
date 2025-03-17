#include "enemyplane.h"
#include"config.h"
EnemyPlane::EnemyPlane()
{
    //敌机图片加载
    m_enemy.load(":/res/QQ图片20200511165024.png");

    //低级位置
    m_X=0;
    m_Y=0;

    //敌机状态
    m_Free=true;

    //敌机速度
    m_Speed=ENEMY_SPEED;

    //敌机的矩形框（碰撞检测）
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void EnemyPlane::updatePosition()
{
    //空闲状态的敌机 不计算坐标
    if(m_Free)
    {
        return;
    }

    m_Y +=m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    //如果超出屏幕，重置空闲状态
    if(m_Y>=GAME_HEIGHT+m_Rect.height())
    {
        m_Free=true;
    }
}
