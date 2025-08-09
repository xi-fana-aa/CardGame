#pragma once
#include "cocos2d.h"
#include <vector>

/**
 * @brief 卡牌配置结构体
 * 
 * 用于存储关卡配置文件中单张卡牌的信息
 */
struct CardConfig 
{
    int cardSuit;              // 卡牌花色类型
    int cardFace;              // 卡牌点数类型
    cocos2d::Vec2 position;    // 卡牌位置坐标
    int id;                    // 卡牌唯一标识ID
};

/**
 * @brief 关卡配置结构体
 * 
 * 用于存储整个关卡的配置信息，包括桌面卡牌和手牌区卡牌
 */
struct LevelConfig
{
    std::vector<CardConfig> playfield;  // 桌面卡牌配置列表
    std::vector<CardConfig> stack;      //手牌区卡牌配置列表
};