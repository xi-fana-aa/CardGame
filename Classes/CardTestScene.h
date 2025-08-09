#pragma once
#include "cocos2d.h"

/**
 * @brief 卡牌游戏测试场景类
 * 
 * 该类负责创建和初始化卡牌游戏的测试场景，包括：
 * - 设置游戏界面的设计分辨率（1080*2080）
 * - 创建主牌区和堆牌区的背景
 * - 加载关卡配置并生成游戏模型
 * - 创建游戏控制器
 * - 添加回退按钮
 * 
 * 使用场景：用于测试卡牌游戏的各种功能，包括卡牌移动、匹配和回退等操作
 */
class CardTestScene : public cocos2d::Layer
{
public:
    /**
     * @brief 创建卡牌测试场景
     * @return 返回创建的场景对象指针
     */
    static cocos2d::Scene* createScene();
    
    /**
     * @brief 初始化测试场景
     * @return 初始化成功返回true，失败返回false
     */
    virtual bool init() override;
    
    CREATE_FUNC(CardTestScene);
};
