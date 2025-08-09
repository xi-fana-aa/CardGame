#include "GameController.h"
#include "models/UndoModel.h"
#include <algorithm>

USING_NS_CC;
using namespace std;

GameController* GameController::create(const GameModel& model) {
    GameController* ret = new(nothrow) GameController();
    if (ret && ret->init(model)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GameController::init(const GameModel& model) {
    if (!Node::init())return false;
    _gameModel = model;
    initPlayfieldCards();
    initStack();
    return true;
}

void GameController::initPlayfieldCards() {
    const auto& cardModels = _gameModel.getPlayfieldCards();
    for (const auto& model : cardModels) {
        auto card = CardView::create(model.getSuit(), model.getFace(), false, true, model.getId());
		cocos2d::Vec2 pos = model.getPosition();
        pos.x = clampf(pos.x, 0.f, 1080.f);
        pos.y = clampf(pos.y, 0.f, 1500.f);
        pos.y += 580.f;
        card->setPosition(pos);

        card->setInteractable(true);  // 开启卡牌触摸
        card->setClickCallback([this](CardView* clickedCard) {
            this->onCardClicked(clickedCard);
            });

        this->addChild(card);
        _playfieldCardViews.push_back(card);
        _cardViews.push_back(card);
    }
}

void GameController::initStack() {
    const auto& stackCards = _gameModel.getStackCards();

    const float kLeftX = 300.f; // 抽牌堆X坐标
    const float kBaseY = 290.f; // 抽牌堆起始Y坐标
    const float kRightX = 780.f; // 当前手牌X坐标
    const float kOffsetX = 50.f; // 每张牌在Y轴上的叠加偏移

    // 创建左侧叠堆卡牌（除最后一张）
    for (size_t i = 0; i + 1 < stackCards.size(); ++i) {
        auto model = stackCards[i];
        auto card = CardView::create(model.getSuit(), model.getFace(), false, true, model.getId());

        float posX = kLeftX + i * kOffsetX;
        card->setPosition(Vec2(posX, kBaseY));

        card->setInteractable(i == stackCards.size() - 2);
        card->setClickCallback([this](CardView* clickedCard) {
            this->onStackCardClicked(clickedCard);
            });

        this->addChild(card);
        _stackCardViews.push_back(card);
        _cardViews.push_back(card);

    }

    // 创建右侧当前手牌
    if (!stackCards.empty()) {
        const auto& topModel = stackCards.back();

        auto card = CardView::create(topModel.getSuit(), topModel.getFace(), false, true, topModel.getId());
        //card->setId(topModel.getId());
        card->setPosition(Vec2(kRightX, kBaseY));
        card->setInteractable(true);
        card->setClickCallback([this](CardView* clickedCard) {
            this->onCardClicked(clickedCard);
            });

        this->addChild(card);
        _currentStackView = card;
        _cardViews.push_back(card);
    }
}


void GameController::onStackCardClicked(CardView* clickedCardView) {
	if (!clickedCardView) return;

	Vec2 targetPos = _currentStackView->getPosition(); // 当前手牌位置

	// 保存当前堆顶牌的完整信息用于回退
	CardState oldStackState;
	oldStackState.id = _currentStackView->getId();
	oldStackState.suit = static_cast<CardSuitType>(_currentStackView->getSuit());
	oldStackState.face = static_cast<CardFaceType>(_currentStackView->getFace());
	oldStackState.position = _currentStackView->getPosition();

	// 记录撤销操作,手牌区替换，包含被替换卡牌的完整信息
	UndoModel undoAction(
		clickedCardView->getPosition(), 
		targetPos, 
		clickedCardView->getId(), 
		UndoActionType::kStackCardReplace,
		oldStackState.id,
		oldStackState.suit,
		oldStackState.face,
		oldStackState.position
	);
	_undoManager.push(undoAction);

	clickedCardView->retain(); 

	auto move = MoveTo::create(0.3f, targetPos);
	clickedCardView->runAction(Sequence::create(move, CallFunc::create([this, clickedCardView]() {
		// 重用现有堆顶卡牌对象
		replaceStackCard(clickedCardView);

		// 判断是否为空，避免pop_back导致崩溃
		if (!_stackCardViews.empty()) {
			_stackCardViews.pop_back();
		}

		// 更新新的堆顶卡牌交互状态
		if (!_stackCardViews.empty()) {
			auto newTop = _stackCardViews.back();
			newTop->setInteractable(true);
		}

		clickedCardView->release();
		}), nullptr));
}

void GameController::onCardClicked(CardView* clickedCardView) {
	if (!_currentStackView) return;

	auto clickedFace = clickedCardView->getFace();
	auto stackFace = _currentStackView->getFace();

	if (abs((int)clickedFace - (int)stackFace) == 1) {
		auto targetPos = _currentStackView->getPosition();

		// 保存当前堆顶牌的完整信息用于回退
		CardState oldStackState;
		oldStackState.id = _currentStackView->getId();
		oldStackState.suit = static_cast<CardSuitType>(_currentStackView->getSuit());
		oldStackState.face = static_cast<CardFaceType>(_currentStackView->getFace());
		oldStackState.position = _currentStackView->getPosition();

		// 记录撤销操作,桌面牌匹配替换，包含被替换卡牌的完整信息
		UndoModel undoAction(
			clickedCardView->getPosition(), 
			targetPos, 
			clickedCardView->getId(), 
			UndoActionType::kPlayfieldCardMatch,
			oldStackState.id,
			oldStackState.suit,
			oldStackState.face,
			oldStackState.position
		);
		_undoManager.push(undoAction);

		auto move = MoveTo::create(0.3f, targetPos);

		clickedCardView->runAction(Sequence::create(move, CallFunc::create([this, clickedCardView]() {
			replaceStackCard(clickedCardView);
			}), nullptr));
	}
}

void GameController::replaceStackCard(CardView* newCardView) {
    if (_currentStackView && newCardView) {
        // 保存旧牌状态
        _oldStackCardState.id = _currentStackView->getId();
        _oldStackCardState.suit = static_cast<CardSuitType>(_currentStackView->getSuit());
        _oldStackCardState.face = static_cast<CardFaceType>(_currentStackView->getFace());
        _oldStackCardState.position = _currentStackView->getPosition();

        // 更新现有堆顶卡牌
        Vec2 oldPos = _oldStackCardState.position;
        int newCardId = newCardView->getId();

        _currentStackView->setCard(
            static_cast<CardSuitType>(newCardView->getSuit()),
            static_cast<CardFaceType>(newCardView->getFace()),
            false, true);
        _currentStackView->setId(newCardId);
        _currentStackView->setPosition(oldPos);

        _currentStackView->setInteractable(true);
        _currentStackView->setClickCallback([this](CardView* clickedCard) {
            this->onCardClicked(clickedCard);
            });
    }
}

void GameController::recordUndoAction(CardView* cardView, const Vec2& from, const Vec2& to, UndoActionType actionType) {
	int id = cardView->getId();
	_undoManager.push(UndoModel(from, to, id, actionType));
}

void GameController::recordUndoAction(CardView* cardView, const Vec2& from, const Vec2& to) {
	recordUndoAction(cardView, from, to, UndoActionType::kMoveCard);
}

void GameController::undo() {
    if (!_undoManager.canUndo()) {
        return;
    }

    UndoModel action = _undoManager.pop();

    // 根据操作类型分别处理
    switch (action.actionType) {
        case UndoActionType::kStackCardReplace: {
            // 手牌区替换回退
            handleStackCardReplaceUndo(action);
            break;
        }
        case UndoActionType::kPlayfieldCardMatch: {
            // 桌面牌匹配回退
            handlePlayfieldCardMatchUndo(action);
            break;
        }
        case UndoActionType::kStackCardClick: {
            // 手牌区翻牌点击回退
            handleStackCardClickUndo(action);
            break;
        }
        case UndoActionType::kMoveCard:
        default: {
            // 普通卡牌移动回退
            handleMoveCardUndo(action);
            break;
        }
    }
}

void GameController::handleStackCardClickUndo(const UndoModel& action) {
    // 找到对应的卡牌
    CardView* targetCard = nullptr;
    for (auto card : _cardViews) {
        if (card->getId() == action.cardId) {
            targetCard = card;
            break;
        }
    }
    
    if (!targetCard) {
        return;
    }
    
    // 将卡牌移回原位置
    targetCard->moveTo(action.fromPosition, 0.3f);
    
    // 如果当前堆顶牌是目标卡牌，需要恢复堆顶状态
    if (targetCard == _currentStackView) {
        // 恢复堆顶牌为原来的状态
        targetCard->setCard(_oldStackCardState.suit, _oldStackCardState.face, false, true);
        targetCard->setId(_oldStackCardState.id);
        targetCard->setPosition(_oldStackCardState.position);
        targetCard->setInteractable(true);
        targetCard->setClickCallback([this](CardView* clickedCard) {
            this->onCardClicked(clickedCard);
        });
    }
}

void GameController::handlePlayfieldCardMatchUndo(const UndoModel& action) {
    // 找到对应的桌面卡牌
    CardView* playfieldCard = nullptr;
    for (auto card : _playfieldCardViews) {
        if (card->getId() == action.cardId) {
            playfieldCard = card;
            break;
        }
    }
    
    if (!playfieldCard) {
        return;
    }
    
    // 将桌面卡牌移回原位置
    playfieldCard->moveTo(action.fromPosition, 0.3f);
    
    // 恢复堆顶牌为原来的状态
    if (_currentStackView) {
        _currentStackView->setCard(action.replacedCardSuit, action.replacedCardFace, false, true);
        _currentStackView->setId(action.replacedCardId);
        _currentStackView->setPosition(action.replacedCardPosition);
        _currentStackView->setInteractable(true);
        _currentStackView->setClickCallback([this](CardView* clickedCard) {
            this->onCardClicked(clickedCard);
        });
    }
}

void GameController::handleStackCardReplaceUndo(const UndoModel& action) {
    CardView* targetCard = nullptr;
    for (auto card : _cardViews) {
        if (card->getId() == action.cardId) {
            targetCard = card;
            break;
        }
    }
    
    if (!targetCard) {
        return;
    }
    
    // 将当前堆顶牌移回原位置
    targetCard->moveTo(action.fromPosition, 0.3f);
    
    // 恢复堆顶牌为原来的状态
    if (_currentStackView) {
        _currentStackView->setCard(action.replacedCardSuit, action.replacedCardFace, false, true);
        _currentStackView->setId(action.replacedCardId);
        _currentStackView->setPosition(action.replacedCardPosition);
        _currentStackView->setInteractable(true);
        _currentStackView->setClickCallback([this](CardView* clickedCard) {
            this->onCardClicked(clickedCard);
        });
    }
    
    // 将被点击的牌重新加入手牌区列表
    if (std::find(_stackCardViews.begin(), _stackCardViews.end(), targetCard) == _stackCardViews.end()) {
        _stackCardViews.push_back(targetCard);
    }
    
    // 更新手牌区卡牌的交互状态
    if (!_stackCardViews.empty()) {
        auto newTop = _stackCardViews.back();
        newTop->setInteractable(true);
    }
}

void GameController::handleMoveCardUndo(const UndoModel& action) {
    // 普通卡牌移动回退
    for (auto card : _cardViews) {
        if (card->getId() == action.cardId) {
            card->moveTo(action.fromPosition, 0.3f);
            break;
        }
    }
}