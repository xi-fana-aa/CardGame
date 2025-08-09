#pragma once
#include "CardModel.h"
#include <vector>

/**
 * @brief 游戏模型类
 * 
 * 该类存储游戏中的所有卡牌数据，包括桌面卡牌和手牌区卡牌。
 * 作为游戏数据的核心容器，提供对卡牌数据的访问和管理功能。
 * 
 * 主要功能：
 * - 存储桌面卡牌数据
 * - 存储手牌区卡牌数据
 * - 提供卡牌数据的访问接口
 * - 管理游戏状态数据
 * 
 * 使用场景：在游戏控制器中作为数据源，提供游戏所需的所有卡牌信息
 */
class GameModel {
public:
    /**
     * @brief 构造函数
     * @param playfield 桌面卡牌列表
     * @param stack 手牌区卡牌列表
     */
    GameModel(const std::vector<CardModel>& playfield, const std::vector<CardModel>& stack)
        :_playfieldCards(playfield), _stackCards(stack) {
    }

    /**
     * @brief 获取桌面卡牌列表
     * @return 返回桌面卡牌的常量引用
     */
    const std::vector<CardModel>& getPlayfieldCards()const { return _playfieldCards; }
    
    /**
     * @brief 获取手牌区卡牌列表
     * @return 返回手牌区卡牌的常量引用
     */
    const std::vector<CardModel>& getStackCards()const { return _stackCards; }

    /**
     * @brief 默认构造函数
     */
    GameModel() = default;

    /**
     * @brief 获取手牌区顶部卡牌
     * @return 返回手牌区顶部卡牌的指针，如果手牌区为空返回nullptr
     */
    const CardModel* getTopStackCard()const {
        if (_stackCards.empty())return nullptr;
        return &_stackCards.back();
    }
private:
    std::vector<CardModel> _playfieldCards;  // 桌面卡牌列表
    std::vector<CardModel> _stackCards;      // 手牌区卡牌列表
};