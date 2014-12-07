#include "OptionLayer.h"


bool OptionLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}
	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	addOption();
	return true;
}

void OptionLayer::addOption()
{


	Node *optionNode = CSLoader::createNode("optionNode.csb");//传入Studio2.x的资源路径
	optionNode->setPosition(Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2)));
	this->addChild(optionNode);

//	CCLOG("%f,%f,", optionNode->getPosition().x, optionNode->getPosition().y);
	this->setAnchorPoint(Point(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);
	this->setPosition(Point(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2)));
//	this->setPosition(0, 0);
//	CCLOG("%f,%f,", this->getPosition().x, this->getPosition().y); 


	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(OptionLayer::onTouchBegan, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(OptionLayer::onTouchCancelled, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(OptionLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

	auto cancelButton = dynamic_cast<ui::Button*> (optionNode->getChildByName("cancelButton"));
	if (cancelButton)
	{
		cancelButton->addClickEventListener(CC_CALLBACK_1(OptionLayer::cancel, this));
	}

	



	//set font name again due to the cocos studio 2.0 bugs (Text load ttf error)
	std::string ttf_file = "kenpixel_future.ttf";
	auto textSound = dynamic_cast<ui::Text*> (optionNode->getChildByName("textSound"));
	textSound->setFontName(ttf_file);
	auto textEffect = dynamic_cast<ui::Text*> (optionNode->getChildByName("textEffect"));
	textEffect->setFontName(ttf_file);
	auto textSpeed = dynamic_cast<ui::Text*> (optionNode->getChildByName("textSpeed"));
	textSpeed->setFontName(ttf_file);
	auto textCurSpeed = dynamic_cast<ui::Text*> (optionNode->getChildByName("textCurSpeed"));
	textCurSpeed->setFontName(ttf_file);
	auto textMinSpeed = dynamic_cast<ui::Text*> (optionNode->getChildByName("textMinSpeed"));
	textMinSpeed->setFontName(ttf_file);
	auto textMaxSpeed = dynamic_cast<ui::Text*> (optionNode->getChildByName("textMaxSpeed"));
	textMaxSpeed->setFontName(ttf_file);
}

bool OptionLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void OptionLayer::onTouchEnded(Touch* touch, Event* event)
{

}

void OptionLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void OptionLayer::onEnter()
{

	Layer::onEnter();
	//this->setScale(1.0f);
	auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2))), FadeIn::create(0.3f), nullptr);

	this->runAction(action);
//	this->setVisible(true);
	
	CCLOG("%f,%f,", this->getPosition().x, this->getPosition().y);
	
}
//
void OptionLayer::onExit()
{

	Layer::onExit();
	

}

void OptionLayer::cancel(Ref* sender)
{

	auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2))), FadeOut::create(0.3f), ScaleBy::create(0.3f, 0.3f), nullptr);
	auto set = CallFunc::create(CC_CALLBACK_0(OptionLayer::setVisible, this, false));
	auto remove = CallFunc::create(CC_CALLBACK_0(OptionLayer::removeFromParent, this));
	auto action_ = Sequence::create(action, set, remove, nullptr);
	this->runAction(action_);

	//this->removeFromParent();
	
}

