#include "LevelConfigLoader.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
using namespace rapidjson;

LevelConfig LevelConfigLoader::loadFromJson(const string& path) {
    LevelConfig config;
    string jsonStr = FileUtils::getInstance()->getStringFromFile(path);
    Document doc;
    doc.Parse(jsonStr.c_str());

    int nextId = 0;

    auto parseArray = [&nextId](const rapidjson::Value& array, vector<CardConfig>& out) {
        for (SizeType i = 0; i < array.Size(); ++i) {
            const auto& a = array[i];
            CardConfig c;
            c.cardFace = a["CardFace"].GetInt();
            c.cardSuit = a["CardSuit"].GetInt();
            c.position.x = a["Position"]["x"].GetFloat();
            c.position.y = a["Position"]["y"].GetFloat();
            c.id = nextId++;
            out.push_back(c);
        }
        };

    if (doc.HasMember("Playfield")) {
        parseArray(doc["Playfield"], config.playfield);
    }
    if (doc.HasMember("Stack")) {
        parseArray(doc["Stack"], config.stack);
    }

    return config;
}
