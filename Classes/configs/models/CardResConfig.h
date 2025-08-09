#pragma once

// 花色类型
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS=0,      // 梅花
    CST_DIAMONDS=1,   // 方块
    CST_HEARTS=2,     // 红桃
    CST_SPADES=3,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

// 正面类型
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE=0,
    CFT_TWO=1,
    CFT_THREE=2,
    CFT_FOUR=3,
    CFT_FIVE=4,
    CFT_SIX=5,
    CFT_SEVEN=6,
    CFT_EIGHT=7,
    CFT_NINE=8,
    CFT_TEN=9,
    CFT_JACK=10,
    CFT_QUEEN=11,
    CFT_KING=12,
    CFT_NUM_CARD_FACE_TYPES
};

struct CardResConfig
{
    //获取花色图片资源路径
    static std::string getSuitImage(CardSuitType suit)
    {
        switch (suit)
        {
        case CST_CLUBS:    return "res/suits/club.png";
        case CST_DIAMONDS: return "res/suits/diamond.png";
        case CST_HEARTS:   return "res/suits/heart.png";
        case CST_SPADES:   return "res/suits/spade.png";
        default:           return "";
        }
    }
    //获取数字图片资源路径
    static std::string getFaceImage(CardFaceType face,bool isRed, bool isBig)
    {
        std::string sizeNum = isBig ? "big" : "small";
        std::string colorNum = isRed ? "red" : "black";
        switch (face)
        {
        case CFT_ACE:   return "res/number/" + sizeNum + "_" + colorNum + "_" + "A.png";
        case CFT_JACK:  return "res/number/" + sizeNum + "_" + colorNum + "_" + "J.png";
        case CFT_QUEEN: return "res/number/" + sizeNum + "_" + colorNum + "_" + "Q.png";
        case CFT_KING:  return "res/number/" + sizeNum + "_" + colorNum + "_" + "K.png";
        default:        return "res/number/" + sizeNum + "_" + colorNum + "_" + std::to_string(static_cast<int>(face+1)) + ".png";
        }
    }
    //获取卡牌空白背景图片资源路径
    static std::string getCardBackImage()
    {
        return "res/card_general.png";
    }
};