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

	this->setDJ(DiscJockey::getInstance());

	Node *optionNode = CSLoader::createNode("optionNode.csb");//传入Studio2.x的资源路径
	optionNode->setPosition(Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2)));
	this->addChild(optionNode);
	optionNode->setName("optionNode");

	this->setAnchorPoint(Point(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);
	this->setPosition(Point(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2)));


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
	for (auto node : optionNode->getChildren())
	{
		auto textNode = dynamic_cast<ui::Text*>(node);
		if (textNode)
		{
			textNode->enableOutline(Color4B(25, 26, 25, 155), 2);
		}
	}

	auto musicBox = dynamic_cast<ui::CheckBox*>(optionNode->getChildByName("soundCheck"));
	musicBox->addEventListenerCheckBox(this, checkboxselectedeventselector(OptionLayer::musicCheckBoxCallback));
	auto effectBox = dynamic_cast<ui::CheckBox*>(optionNode->getChildByName("effectCheck"));
	effectBox->addEventListenerCheckBox(this, checkboxselectedeventselector(OptionLayer::effectCheckBoxCallback));
	musicBox->setSelectedState(getDJ()->isMusicOn());
	effectBox->setSelectedState(getDJ()->isEffectOn());

	int curSpeed = CommandCenter::getInstance()->getSpeedLevel();
	auto textNode = dynamic_cast<ui::Text*>(optionNode->getChildByName("textCurSpeed"));
	textNode->setText(String::createWithFormat("%d", curSpeed)->getCString());
	auto speedSlider = dynamic_cast<ui::Slider*>(optionNode->getChildByName("speedSlider"));
	speedSlider->addEventListenerSlider(this, sliderpercentchangedselector(OptionLayer::speedSliderCallback));
	speedSlider->setPercent(curSpeed * 10);
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
	getDJ()->playClickEffect();
	auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, -(originPoint.y + visibleSize.height / 2))), FadeOut::create(0.3f), ScaleBy::create(0.3f, 0.3f), nullptr);
	auto set = CallFunc::create(CC_CALLBACK_0(OptionLayer::setVisible, this, false));
	auto remove = CallFunc::create(CC_CALLBACK_0(OptionLayer::removeFromParent, this));
	auto action_ = Sequence::create(action, set, remove, nullptr);
	this->runAction(action_);

	//this->removeFromParent();
	
}

void OptionLayer::musicCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type)
{
	switch (event_type)
	{
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		DiscJockey::getInstance()->setMusicOn(true);
		break;
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		DiscJockey::getInstance()->setMusicOn(false);
		break;
	}
}

void OptionLayer::effectCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type)
{

	switch (event_type)
	{
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		DiscJockey::getInstance()->setEffectOn(true);
		break;
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		DiscJockey::getInstance()->setEffectOn(false);
		break;
	}
}

void OptionLayer::speedSliderCallback(Ref*pSender, ui::SliderEventType event_type)
{
	if (event_type == SliderEventType::SLIDER_PERCENTCHANGED)
	{
		Slider* pSlider = (Slider*)pSender;
		int percent = pSlider->getPercent();
		int tem = percent / 10;
		auto textNode = dynamic_cast<ui::Text*>(this->getChildByName("optionNode")->getChildByName("textCurSpeed"));
		textNode->setText(String::createWithFormat("%d", tem)->getCString());
		CommandCenter::getInstance()->setSpeedLevel(tem);
	}

}