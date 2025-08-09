#pragma once
#include <stack>
#include "models/UndoModel.h"

/**
 * @brief 回退管理器类
 * 
 * 该类负责管理游戏中的回退操作，使用栈结构存储操作历史。
 * 提供回退功能的底层支持，包括操作的压栈、出栈和状态检查。
 * 
 * 主要功能：
 * - 存储游戏操作历史
 * - 支持回退操作
 * - 管理回退栈的状态
 * 
 * 使用场景：在游戏控制器中用于实现回退功能
 */
class UndoManager {
public:
    /**
     * @brief 将操作压入回退栈
     * @param action 要压入的回退操作
     */
    void push(const UndoModel& action);
    
    /**
     * @brief 检查是否可以执行回退操作
     * @return 如果回退栈不为空返回true，否则返回false
     */
    bool canUndo() const;
    
    /**
     * @brief 从回退栈中弹出最新的操作
     * @return 返回最新的回退操作，如果栈为空返回默认构造的UndoModel
     */
    UndoModel pop();

private:
    std::stack<UndoModel> _undoStack;  // 回退操作栈，存储游戏操作历史
};