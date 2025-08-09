#pragma once
#include "cocos2d.h"
#include "configs/models/LevelConfig.h"
#include "models/CardModel.h"
#include "models/GameModel.h"

/**
 * @brief 游戏模型生成器类
 * 
 * 该类负责根据关卡配置生成游戏模型，将关卡配置数据转换为游戏所需的数据结构。
 * 作为数据转换服务，连接配置系统和游戏逻辑。
 * 
 * 主要功能：
 * - 解析关卡配置数据
 * - 生成卡牌模型对象
 * - 创建游戏模型实例
 * - 数据格式转换
 * 
 * 使用场景：在游戏初始化时，将JSON配置文件转换为游戏模型
 */
class GameModelFromLevelGenerator {
public:
    /**
     * @brief 根据关卡配置生成游戏模型
     * @param levelConfig 关卡配置对象，包含桌面卡牌和手牌区卡牌的配置信息
     * @return 返回生成的游戏模型对象
     */
    static GameModel generateFromLevelConfig(const LevelConfig& levelConfig);
};