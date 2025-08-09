#pragma once
#include "configs/models/LevelConfig.h"
#include <string>

/**
 * @brief 关卡配置加载器类
 * 
 * 该类负责从JSON文件中加载关卡配置数据，将JSON格式的配置文件转换为程序可用的数据结构。
 * 作为配置系统的入口，提供文件解析和数据转换功能。
 * 
 * 主要功能：
 * - 读取JSON配置文件
 * - 解析关卡配置数据
 * - 数据格式验证
 * - 错误处理
 * 
 * 使用场景：在游戏初始化时，从JSON文件加载关卡配置
 */
class LevelConfigLoader {
public:
    /**
     * @brief 从JSON文件加载关卡配置
     * @param path JSON配置文件的路径
     * @return 返回解析后的关卡配置对象
     */
    static LevelConfig loadFromJson(const std::string& path);
};