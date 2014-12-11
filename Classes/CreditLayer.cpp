#include "CreditLayer.h"

bool CreditLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setDJ(DiscJockey::getInstance());
	this->show();

	return true;
}

void CreditLayer::show()
{

	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	this->setAnchorPoint(Point(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);
	this->setPosition(Point(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2)));

	setCreditString();

	setEventListener();

}

void CreditLayer::setCreditString()
{
	std::string file = "menu/menuPanel.png";
	auto creditView = Sprite::createWithSpriteFrameName(file);
	creditView->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2 - 100);
	this->addChild(creditView);
	//:createWithTTF(
	//const std::string& text, 
	//const std::string& fontFile, 
	//float fontSize, 
	//const Size& dimensions /* = Size::ZERO */,
	//TextHAlignment hAlignment /* = TextHAlignment::LEFT */, 
	//TextVAlignment vAlignment /* = TextVAlignment::TOP */)
	//label
	std::string thanks_str = "\nC R E D I T S\n\n---------\ncoding:\nhitlolo\n\nSpecial thanks:\nwww.kenney.nl\nwww.1001.com\n---------";
	std::string font_name = "kenpixel_future.ttf";
	Label* thanks = Label::createWithTTF(thanks_str, font_name, 28);
	thanks->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	thanks->setPosition(originPoint.x + creditView->getContentSize().width / 2, originPoint.y + creditView->getContentSize().height - 200);
	thanks->enableOutline(Color4B(25, 26, 25, 155), 2);
	creditView->addChild(thanks);

}

void CreditLayer::setEventListener()
{
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(CreditLayer::onTouchBegan, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(CreditLayer::onTouchCancelled, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(CreditLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

bool CreditLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (isVisible())
	{
		this->cancel();
	}
	return true;
}

void CreditLayer::onTouchEnded(Touch* touch, Event* event)
{
}

void CreditLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void CreditLayer::onEnter()
{
	Layer::onEnter();
	this->setVisible(true);
	auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2))), FadeIn::create(0.3f), nullptr);
	this->runAction(action);
}

void CreditLayer::cancel()
{
	getDJ()->playClickEffect();
	auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2))), FadeOut::create(0.3f), ScaleBy::create(0.3f, 0.3f), nullptr);
	auto set = CallFunc::create(CC_CALLBACK_0(CreditLayer::setVisible, this, false));
	auto remove = CallFunc::create(CC_CALLBACK_0(CreditLayer::removeFromParent, this));
	auto action_ = Sequence::create(action, set, remove, nullptr);
	this->runAction(action_);
}

