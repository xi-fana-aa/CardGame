#pragma once

#include "cocos2d.h"
#include "configs/models/CardResConfig.h"

/**
 * @brief 卡牌视图类
 * 
 * 该类负责显示卡牌，包括卡牌背景、花色和点数的可视化表示。
 * 继承自cocos2d::Node，提供卡牌的UI展示和交互功能。
 * 
 * 主要功能：
 * - 显示卡牌的外观（背景、花色、点数）
 * - 处理卡牌的点击交互
 * - 支持卡牌的移动动画
 * - 管理卡牌的状态（可交互性、位置等）
 * 
 * 使用场景：在游戏界面中显示各种卡牌，支持用户交互
 */
class CardView : public cocos2d::Node {
public:
    /**
     * @brief 创建卡牌视图实例
     * @param suit 卡牌花色类型
     * @param face 卡牌点数类型
     * @param isRed 是否为红色卡牌
     * @param isBig 是否为大号显示
     * @param id 卡牌唯一标识ID
     * @return 返回创建的卡牌视图指针
     */
    static CardView* create(CardSuitType suit, CardFaceType face, bool isRed, bool isBig, int id);

    /**
     * @brief 初始化卡牌视图
     * @param suit 卡牌花色类型
     * @param face 卡牌点数类型
     * @param isRed 是否为红色卡牌
     * @param isBig 是否为大号显示
     * @return 初始化成功返回true，失败返回false
     */
    bool init(CardSuitType suit, CardFaceType face, bool isRed, bool isBig);

    /**
     * @brief 设置卡牌显示内容
     * @param suit 卡牌花色类型
     * @param face 卡牌点数类型
     * @param isRed 是否为红色卡牌
     * @param isBig 是否为大号显示
     */
    void setCard(CardSuitType suit, CardFaceType face, bool isRed, bool isBig);

    /**
     * @brief 设置卡牌是否可交互
     * @param interactable 是否可交互
     */
    void setInteractable(bool interactable);

    /**
     * @brief 设置点击回调函数
     * @param callback 点击回调函数，参数为被点击的卡牌视图指针
     */
    void setClickCallback(const std::function<void(CardView*)>& callback);

    /**
     * @brief 移动卡牌到指定位置
     * @param targetPos 目标位置
     * @param duration 移动持续时间，默认2.5秒
     */
    void moveTo(const cocos2d::Vec2& targetPos, float duration = 2.5f);

    /**
     * @brief 记住当前位置为原始位置
     * 用于回退功能，记录当前位置以便后续恢复
     */
    void rememberCurrentPosition();

    /**
     * @brief 移动卡牌回原始位置
     * @param duration 移动持续时间，默认2.5秒
     */
    void moveBackToOriginalPosition(float duration = 2.5f);

    /**
     * @brief 获取卡牌点数
     * @return 返回卡牌点数
     */
    int getFace() const;
    
    /**
     * @brief 获取卡牌花色
     * @return 返回卡牌花色
     */
    int getSuit() const;
    
    /**
     * @brief 设置卡牌ID
     * @param id 卡牌唯一标识ID
     */
    void setId(int id);
    
    /**
     * @brief 获取卡牌ID
     * @return 返回卡牌唯一标识ID
     */
    int getId() const;

private:
    int _face;                          //卡牌点数
    int _suit;                          //卡牌花色
    bool _isInteractable = true;        //是否可交互
    bool _isRed = false;                //是否为红色卡牌
    bool _isBig = true;                 //是否为大号显示
    int _id = -1;                       //卡牌唯一标识ID，默认为无效

    cocos2d::Sprite* _cardBg = nullptr;           //卡牌背景
    cocos2d::Sprite* _cardSuit = nullptr;         //卡牌花色
    cocos2d::Sprite* _smallFace = nullptr;        //小号点数
    cocos2d::Sprite* _bigFace = nullptr;          //大号点数
    cocos2d::Vec2 _originalPosition;              //原始位置，用于回退功能

    std::function<void(CardView*)> _onClickCallback; //点击回调函数

    /**
     * @brief 初始化触摸监听器
     * 设置卡牌的触摸事件处理
     */
    void initTouchListener();
};