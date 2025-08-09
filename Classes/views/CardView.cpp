#include "CardView.h"

USING_NS_CC;
using namespace std;

CardView* CardView::create(CardSuitType suit, CardFaceType face, bool isRed, bool isBig, int id) {
	CardView* ret = new (nothrow) CardView();
	if (ret && ret->init(suit, face, isRed, isBig)) {
		ret->setId(id);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


bool CardView::init(CardSuitType suit, CardFaceType face, bool isRed, bool isBig) {
	if (!Node::init())return false;

	//空白牌面背景
	this->setContentSize(Size(182, 282));
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
	_cardBg = Sprite::create(CardResConfig::getCardBackImage());
	_cardBg->setScale(4.0f);
	_cardBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_cardBg->setPosition(getContentSize() / 2);
	this->addChild(_cardBg);

	//花色
	_cardSuit = Sprite::create();
	_cardSuit->setScale(4.0f);
	_cardSuit->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	_cardSuit->setPosition(Vec2(getContentSize().width - 20, getContentSize().height - 25));
	this->addChild(_cardSuit);

	//小数字
	_smallFace = Sprite::create();
	_smallFace->setScale(4.0f);
	_smallFace->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_smallFace->setPosition(Vec2(20, getContentSize().height - 25));
	this->addChild(_smallFace);

	//大数字
	_bigFace = Sprite::create();
	_bigFace->setScale(4.0f);
	_bigFace->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_bigFace->setPosition(Vec2(getContentSize().width / 2, 110));
	this->addChild(_bigFace);


	setCard(suit, face, isRed, isBig);
	initTouchListener();

	return true;
}

void CardView::setCard(CardSuitType suit, CardFaceType face, bool isRed, bool isBig) {
	_suit = suit;
	_face = face;

	if (suit == CST_HEARTS || suit == CST_DIAMONDS)isRed = true;
	else isRed = false;
	_isRed = isRed;
	_isBig = isBig;

	//空白牌面背景
	if (_cardBg)_cardBg->setTexture(CardResConfig::getCardBackImage());
	//花色
	if (_cardSuit)_cardSuit->setTexture(CardResConfig::getSuitImage(suit));
	//小数字
	if (_smallFace)_smallFace->setTexture(CardResConfig::getFaceImage(face, isRed, false));
	//大数字
	if (_bigFace)_bigFace->setTexture(CardResConfig::getFaceImage(face, isRed, true));
}

void CardView::setInteractable(bool interactable) {
	_isInteractable = interactable;
}

void CardView::setClickCallback(const std::function<void(CardView*)>& callback) {
	_onClickCallback = callback;
}

void CardView::initTouchListener() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		if (!_isInteractable) return false;

		Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
		Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
		return rect.containsPoint(locationInNode);
		};

	listener->onTouchEnded = [&](Touch* touch, Event* event) {
		if (_onClickCallback) {
			_onClickCallback(this);
		}
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CardView::moveTo(const Vec2& targetPos, float duration) {
	this->stopAllActions();
	auto move = MoveTo::create(duration, targetPos);
	this->runAction(move);
}

void CardView::rememberCurrentPosition() {
	_originalPosition = this->getPosition();
}

void CardView::moveBackToOriginalPosition(float duration) {
	this->stopAllActions();
	auto move = MoveTo::create(duration, _originalPosition);
	this->runAction(move);
}

int CardView::getFace() const {
	return _face;
}

int CardView::getSuit() const {
	return _suit;
}

void CardView::setId(int id) {
	_id = id;
}

int CardView::getId() const {
	return _id;
}

