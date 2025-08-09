#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "models/UndoModel.h"
#include "views/CardView.h"
#include "managers/UndoManager.h"
#include <vector>

/**
 * @brief 卡牌状态结构体
 * 
 * 用于保存卡牌的完整状态信息，包括ID、花色、点数和位置
 */
struct CardState {
    int id = -1;                    //卡牌唯一标识ID
    CardSuitType suit;              //卡牌花色类型
    CardFaceType face;              //卡牌点数类型
    cocos2d::Vec2 position;         //卡牌位置坐标
};

/**
 * @brief 游戏控制器类
 * 
 * 该类是卡牌游戏的核心控制器，负责：
 * - 管理游戏中的所有卡牌视图
 * - 处理卡牌点击和交互逻辑
 * - 实现卡牌移动和匹配功能
 * - 管理回退操作和历史记录
 * - 协调主牌区和堆牌区的卡牌状态
 * 
 * 主要职责：
 * - 初始化游戏界面和卡牌布局
 * - 处理用户交互（点击、拖拽等）
 * - 实现游戏规则（卡牌匹配、替换等）
 * - 管理回退功能
 * 
 * 使用场景：作为卡牌游戏的主要控制器，协调各个组件的工作
 */
class GameController : public cocos2d::Node {
public:
    /**
     * @brief 创建游戏控制器实例
     * @param model 游戏模型对象，包含游戏数据和配置
     * @return 返回创建的游戏控制器指针，失败返回nullptr
     */
    static GameController* create(const GameModel& model);

    /**
     * @brief 初始化游戏控制器
     * @param model 游戏模型对象
     * @return 初始化成功返回true，失败返回false
     */
    bool init(const GameModel& model);

    /**
     * @brief 处理桌面卡牌点击事件
     * @param clickedCardView 被点击的卡牌视图指针
     */
    void onCardClicked(CardView* clickedCardView);
    
    /**
     * @brief 处理手牌区卡牌点击事件
     * @param clickedCardView 被点击的手牌区卡牌视图指针
     */
    void onStackCardClicked(CardView* clickedCardView);

    /**
     * @brief 替换堆顶卡牌
     * @param newCardView 新的卡牌视图指针
     */
    void replaceStackCard(CardView* newCardView);

    /**
     * @brief 执行回退操作
     * 根据回退栈中的记录，恢复游戏状态到上一步
     */
    void undo();
    
    /**
     * @brief 记录回退操作（带操作类型）
     * @param cardView 相关卡牌视图指针
     * @param from 起始位置
     * @param to 目标位置
     * @param actionType 操作类型
     */
    void recordUndoAction(CardView* cardView, const cocos2d::Vec2& from, const cocos2d::Vec2& to, UndoActionType actionType);
    
    /**
     * @brief 记录回退操作（向后兼容版本）
     * @param cardView 相关卡牌视图指针
     * @param from 起始位置
     * @param to 目标位置
     */
    void recordUndoAction(CardView* cardView, const cocos2d::Vec2& from, const cocos2d::Vec2& to);

    // 回退处理方法
    /**
     * @brief 处理手牌区点击回退
     * @param action 回退操作信息
     */
    void handleStackCardClickUndo(const UndoModel& action);
    
    /**
     * @brief 处理桌面牌匹配回退
     * @param action 回退操作信息
     */
    void handlePlayfieldCardMatchUndo(const UndoModel& action);
    
    /**
     * @brief 处理手牌区替换回退
     * @param action 回退操作信息
     */
    void handleStackCardReplaceUndo(const UndoModel& action);
    
    /**
     * @brief 处理普通卡牌移动回退
     * @param action 回退操作信息
     */
    void handleMoveCardUndo(const UndoModel& action);

private:
    std::vector<CardView*> _playfieldCardViews;  // 桌面卡牌视图列表
    std::vector<CardView*> _stackCardViews;      // 手牌区卡牌视图列表
    std::vector<CardView*> _cardViews;           // 所有卡牌视图列表
    GameModel _gameModel;                        // 游戏模型对象
    CardView* _currentStackView = nullptr;       // 当前堆顶卡牌视图指针
    UndoManager _undoManager;                    // 回退管理器
    CardState _oldStackCardState;                // 保存的旧堆顶牌状态

    /**
     * @brief 初始化桌面卡牌
     * 根据游戏模型创建桌面上的卡牌视图
     */
    void initPlayfieldCards();

    /**
     * @brief 初始化手牌区
     * 根据游戏模型创建手牌区的卡牌视图
     */
    void initStack();
};
