//
//  MapInfo.h
//  testTileMap
//
//  Created by chenquanjun on 14-3-12.
//
//

#ifndef __testTileMap__MapInfo__
#define __testTileMap__MapInfo__

#include "cocos2d.h"
#include "MapPath.h"
#include "MapGeneral.h"
USING_NS_CC;

//地图信息类
//传入地图创建此类
//tmx文件读取完相关信息后即释放
//tmx文件暂时是写死读取的格式，
//layer用background字段，object用object字段，object里面的精灵用objectid标记类型，类型的枚举见MapGeneral.h

//通过传入开始和结束ID获得路径
//1、第一次开始寻路算法，生成路径后将路径与相反路径保存下来，以后直接调用；
//2、暂时只设计了MapInfoType::Block是不可走
#define MAPINFO_ASTAR_DIRECTION_NUM 4
#define MAPINFO_MAX_STEP_NUM 10000
#define MAPINFO_MAX_STORE_PATH_SIZE 10000

class MapInfo : public Object{
public:
    //使用tmx文件创建
    static MapInfo* create(const std::string& filename);
    
    //获得地图路径
    MapPath* getMapPath(int startId, int endId);
    
    //获得点坐标形式的路径
    PointArray* getPointPath(int startId, int endId);
    
    //获得相应类型的信息对应表
    ValueVector getMapInfoTypeVec(MapInfoType type);
    
    //根据类型获得随机mapId
    int getRandomMapIdByType(MapInfoType type);
    
    //根据类型获得随机地图网格的点
    Point getRandomPointByType(MapInfoType type);
    
    //根据类型获得随机地图网格的中点
    Point getRandomPointMidByType(MapInfoType type);
    
    //把点转换成mapId
    int convertPointToId(Point point);
    
    //把mapid转换成点坐标(网格的左下角)
    Point convertIdToPoint(int mapId);
    
    //把mapid转换成点坐标(网格中心，适合精灵使用)
    Point convertIdToPointMid(int mapId);
    
    //地图大小(PS:此处的大小是网格大小)
    CC_SYNTHESIZE_READONLY(Size, _mapGridSize, MapGridSize);
    //点大小
    CC_SYNTHESIZE_READONLY(Size, _pointSize, PointSize);

private:
    //A星点结构
    struct PointNode
    {
        PointNode()  {nIndex = 0; nG = 0; pParent = NULL;}
        int nIndex;
        int nG;
        PointNode* pParent;
    };
    
private:
    MapInfo(void);
    
    virtual ~MapInfo(void);
    
    virtual bool init(const std::string& filename);
    
    int GetIndexByDir(int nIndex, int nDir);
    int GetGByIndex(int nStartIndex, int nEndIndex);
    int GetHByIndex(int nIndex);
    PointNode *InTable(int nIndex, std::vector<PointNode*> &vecTbl);
    
    //A星寻路
    MapPath *findPath();
    //从缓存获得路径
    MapPath *getPathFromCache();
 
private:
    int m_nStartIndex;
    int m_nEndIndex;
    
    ValueVector _mapInfoTypeVec; //传入地图后转化成vector保存
    
    ValueMapIntKey _mapInfoTypeMap;//根据类型保存在字典里面
    
    Map<int, MapPath*> _mapPathCacheMap; //已经生成的路径缓存
    
    int m_nKeyOffset;//保存key值的偏移
    
};

#endif /* defined(__testTileMap__MapInfo__) */
