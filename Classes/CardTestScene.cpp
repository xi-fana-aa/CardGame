#include "CardTestScene.h"
#include "controllers/GameController.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "services/GameModelFromLevelGenerator.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* CardTestScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CardTestScene::create();
    scene->addChild(layer);
    return scene;
}

bool CardTestScene::init()
{
    if (!Layer::init())
        return false;

    // 设置设计分辨率
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1080, 2080, ResolutionPolicy::SHOW_ALL);

    // 主牌区背景（浅蓝色）
    auto mainArea = LayerColor::create(Color4B(173, 216, 230, 255), 1080, 1500);
    mainArea->setAnchorPoint(Vec2::ZERO);
    mainArea->setPosition(Vec2(0, 580));
    this->addChild(mainArea, -1);

    // 堆牌区背景（浅粉色）
    auto stackArea = LayerColor::create(Color4B(255, 182, 193, 255), 1080, 580);
    stackArea->setAnchorPoint(Vec2::ZERO);
    stackArea->setPosition(Vec2(0, 0));
    this->addChild(stackArea, -1);

    // 从 JSON 文件加载关卡配置
    std::string jsonPath = "configs/levels/level_001.json";
    LevelConfig levelConfig = LevelConfigLoader::loadFromJson(jsonPath);

    // 生成游戏模型
    GameModel gameModel = GameModelFromLevelGenerator::generateFromLevelConfig(levelConfig);

    // 创建GameController
    auto gameController = GameController::create(gameModel);
    gameController->setPosition(Vec2::ZERO);
    this->addChild(gameController);

    // 创建一个回退按钮
    auto undoButton = ui::Button::create();
    undoButton->setTitleText("Undo");
    undoButton->setTitleFontSize(50);
    undoButton->setTitleColor(Color3B::WHITE);
    undoButton->setScale9Enabled(true);
    undoButton->setContentSize(Size(200, 100));
    undoButton->setPosition(Vec2(120, 100));
    undoButton->addClickEventListener([gameController](Ref* sender) {
        gameController->undo();
        });
    this->addChild(undoButton, 10);


    return true;
}
