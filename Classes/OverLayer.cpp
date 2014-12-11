#include "OverLayer.h"


bool OverLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}
	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	addLayer();

	return true;
}

void OverLayer::addLayer()
{

	this->setDJ(DiscJockey::getInstance());

	Node *optionNode = CSLoader::createNode("overNode.csb");//传入Studio2.x的资源路径
	optionNode->setPosition(Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2)));
	this->addChild(optionNode);

	this->setAnchorPoint(Point(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);
	this->setPosition(Point(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2)));


	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(OverLayer::onTouchBegan, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(OverLayer::onTouchCancelled, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(OverLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

	auto restartButton = dynamic_cast<ui::Button*> (optionNode->getChildByName("restartButton"));
	if (restartButton)
	{
		restartButton->addClickEventListener(CC_CALLBACK_1(OverLayer::restart, this));
	}

}

bool OverLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void OverLayer::onTouchEnded(Touch* touch, Event* event)
{

}

void OverLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void OverLayer::onEnter()
{

	Layer::onEnter();
	//this->setScale(1.0f);
	auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2))), FadeIn::create(0.3f), nullptr);

	this->runAction(action);
	//	this->setVisible(true);

}
//
void OverLayer::onExit()
{

	Layer::onExit();

}

void OverLayer::restart(Ref* sender)
{
	getDJ()->playClickEffect();
	auto action = Spawn::create(MoveTo::create(0.3f, Point(-(originPoint.x + visibleSize.width) , (originPoint.y + visibleSize.height / 2))), FadeOut::create(0.3f),nullptr);
	auto set = CallFunc::create(CC_CALLBACK_0(OptionLayer::setVisible, this, false));
	auto remove = CallFunc::create(CC_CALLBACK_0(OptionLayer::removeFromParent, this));
	auto go = CallFunc::create(CC_CALLBACK_0(CommandCenter::goState, CommandCenter::getInstance(), GAME_STATE::GAME));
	auto action_ = Sequence::create(action, set, remove, go,nullptr);
	this->runAction(action_);
	//this->removeFromParent();

}

