#include "map.h"
#include "config.h"
Map::Map()
{
    //初始化地图加载对象
    m_map1.load(":/res/QQ图片20200511155828.jpg");
    m_map2.load(":/res/QQ图片20200511155828.jpg");
    //初始化y轴的坐标
    m_map1_posY= -GAME_HEIGHT;
    m_map2_posY= 0;
    //地图的滚动速度
    m_scrol1_speed= MAP_SCROLL_SPEED;

}

void Map::mapPosition()
{
  //处理第一张图片的滚动位置
    m_map1_posY+=m_scrol1_speed;
    if(m_map1_posY>=0)
    {
        m_map1_posY= -GAME_HEIGHT;
    }
    //处理第二张图片的滚动位置
    m_map2_posY+=m_scrol1_speed;
    if(m_map2_posY>=GAME_HEIGHT)
    {
        m_map2_posY=0;
    }
}
