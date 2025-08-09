#pragma once
#include "cocos2d.h"
#include "configs/models/CardResConfig.h"

/**
 * @brief 回退操作类型枚举
 * 
 * 定义了游戏中所有可能的回退操作类型
 */
enum class UndoActionType {
    kStackCardClick,        // 手牌区翻牌点击操作
    kStackCardReplace,      // 手牌区翻牌替换操作
    kPlayfieldCardMatch,    // 桌面牌匹配替换操作
    kMoveCard               // 普通卡牌移动操作
};

/**
 * @brief 回退操作模型类
 * 
 * 该类用于记录和存储游戏中的回退操作信息，包括：
 * - 卡牌移动的起始和目标位置
 * - 相关卡牌的ID和操作类型
 * - 被替换卡牌的完整状态信息
 * 
 * 主要用途：
 * - 记录游戏操作历史
 * - 支持回退功能
 * - 保存卡牌状态信息
 * 
 * 使用场景：在游戏控制器中用于实现回退功能
 */
struct UndoModel {
    cocos2d::Vec2 fromPosition;        // 卡牌移动的起始位置
    cocos2d::Vec2 toPosition;          // 卡牌移动的目标位置
    int cardId;                        // 相关卡牌的唯一标识ID
    UndoActionType actionType;         // 操作类型
    
    // 被替换卡牌的完整信息（用于桌面牌匹配时的回退）
    int replacedCardId;                // 被替换卡牌的ID
    CardSuitType replacedCardSuit;     // 被替换卡牌的花色
    CardFaceType replacedCardFace;     // 被替换卡牌的点数
    cocos2d::Vec2 replacedCardPosition; // 被替换卡牌的位置

    /**
     * @brief 默认构造函数
     * 初始化所有成员为默认值
     */
    UndoModel() : fromPosition(cocos2d::Vec2::ZERO), toPosition(cocos2d::Vec2::ZERO), 
                  cardId(-1), actionType(UndoActionType::kMoveCard),
                  replacedCardId(-1), replacedCardSuit(CST_HEARTS), 
                  replacedCardFace(CFT_ACE), replacedCardPosition(cocos2d::Vec2::ZERO) {}

    /**
     * @brief 构造函数（带操作类型）
     * @param from 起始位置
     * @param to 目标位置
     * @param id 卡牌ID
     * @param type 操作类型，默认为kMoveCard
     */
    UndoModel(cocos2d::Vec2 from, cocos2d::Vec2 to, int id, UndoActionType type = UndoActionType::kMoveCard)
        : fromPosition(from), toPosition(to), cardId(id), actionType(type),
          replacedCardId(-1), replacedCardSuit(CST_HEARTS), 
          replacedCardFace(CFT_ACE), replacedCardPosition(cocos2d::Vec2::ZERO) {
    }
    
    /**
     * @brief 构造函数（用于桌面牌匹配）
     * @param from 起始位置
     * @param to 目标位置
     * @param id 卡牌ID
     * @param type 操作类型
     * @param replacedId 被替换卡牌ID
     * @param replacedSuit 被替换卡牌花色
     * @param replacedFace 被替换卡牌点数
     * @param replacedPos 被替换卡牌位置
     */
    UndoModel(cocos2d::Vec2 from, cocos2d::Vec2 to, int id, UndoActionType type,
              int replacedId, CardSuitType replacedSuit, CardFaceType replacedFace, cocos2d::Vec2 replacedPos)
        : fromPosition(from), toPosition(to), cardId(id), actionType(type),
          replacedCardId(replacedId), replacedCardSuit(replacedSuit), 
          replacedCardFace(replacedFace), replacedCardPosition(replacedPos) {
    }
};
