#include "GameModelFromLevelGenerator.h"

using namespace std;

GameModel GameModelFromLevelGenerator::generateFromLevelConfig(const LevelConfig& levelConfig) {
    std::vector<CardModel> playfieldCards;
    std::vector<CardModel> stackCards;

    int id = 0;  // id µÝÔö¼ÆÊýÆ÷

    for (const auto& cardCfg : levelConfig.playfield) {
        CardSuitType suit = static_cast<CardSuitType>(cardCfg.cardSuit);
        CardFaceType face = static_cast<CardFaceType>(cardCfg.cardFace);
        cocos2d::Vec2 pos = cardCfg.position;

        playfieldCards.emplace_back(id++, suit, face, pos);
    }
    for (const auto& cardCfg : levelConfig.stack) {
        CardSuitType suit = static_cast<CardSuitType>(cardCfg.cardSuit);
        CardFaceType face = static_cast<CardFaceType>(cardCfg.cardFace);
        cocos2d::Vec2 pos = cardCfg.position;

        stackCards.emplace_back(id++, suit, face, pos);
    }

    return GameModel(playfieldCards, stackCards);
}
