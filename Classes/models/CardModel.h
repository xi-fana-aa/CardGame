#pragma once
#include "cocos2d.h"
#include "configs/models/CardResConfig.h"

/**
 * @brief 卡牌模型类
 * 
 * 该类表示一张卡牌的数据模型，包含卡牌的基本信息：
 * - 唯一标识ID
 * - 花色类型
 * - 点数类型
 * - 位置坐标
 * 
 * 主要功能：
 * - 存储卡牌的基本属性
 * - 提供卡牌信息的访问接口
 * - 作为卡牌数据的传输对象
 * 
 * 使用场景：在游戏模型和视图之间传递卡牌数据
 */
class CardModel {
public:
    /**
     * @brief 构造函数
     * @param id 卡牌唯一标识ID
     * @param suit 卡牌花色类型
     * @param face 卡牌点数类型
     * @param pos 卡牌位置坐标
     */
    CardModel(int id, CardSuitType suit, CardFaceType face, const cocos2d::Vec2& pos)
        : _id(id), _suit(suit), _face(face), _position(pos) {}

    /**
     * @brief 获取卡牌ID
     * @return 返回卡牌唯一标识ID
     */
    int getId() const { return _id; }
    
    /**
     * @brief 获取卡牌花色
     * @return 返回卡牌花色类型
     */
    CardSuitType getSuit() const { return _suit; }
    
    /**
     * @brief 获取卡牌点数
     * @return 返回卡牌点数类型
     */
    CardFaceType getFace() const { return _face; }
    
    /**
     * @brief 获取卡牌位置
     * @return 返回卡牌位置坐标
     */
    cocos2d::Vec2 getPosition() const { return _position; }

private:
    int _id;                    //卡牌唯一标识ID
    CardSuitType _suit;         //卡牌花色类型
    CardFaceType _face;         //卡牌点数类型
    cocos2d::Vec2 _position;    //卡牌位置坐标
};
