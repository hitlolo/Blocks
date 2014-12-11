#include "TouchLayer.h"

bool TouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	getAndSetButtons();
	return true;
}

void TouchLayer::getAndSetButtons()
{
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Node *rootNode = CSLoader::createNode("uiButton.csb");//传入Studio2.x的资源路径
	rootNode->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2));
	this->addChild(rootNode);
	rootNode->setName("buttonRoot");


	auto leftButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("leftButton"));
	if (leftButton)
	{

		leftButton->addTouchEventListener(CC_CALLBACK_2(TouchLayer::onLongLeftClick, this));
		leftButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onLeft, this));
	}

	auto rightButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("rightButton"));
	if (rightButton)
	{
		rightButton->addTouchEventListener(CC_CALLBACK_2(TouchLayer::onLongRightClick, this));
		rightButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onRight, this));

	}

	auto rotateButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("rotateButton"));
	if (rotateButton)
	{
		
		rotateButton->addTouchEventListener(CC_CALLBACK_2(TouchLayer::onLongRotateClick, this));
		rotateButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onRotation, this));
	}

	auto downButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("downButton"));
	if (downButton)
	{
		downButton->addTouchEventListener(CC_CALLBACK_2(TouchLayer::onLongDownClick, this));
		downButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onDown, this));
	}

	auto hardButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("hardButton"));
	if (hardButton)
	{
		hardButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onHardDrop, this));
	}

	auto holdButton = dynamic_cast<ui::Button*>(rootNode->getChildByName("holdButton"));
	if (holdButton)
	{
		holdButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onHold, this));
	}

	auto pauseBox = dynamic_cast<ui::CheckBox*>(rootNode->getChildByName("pauseCheck"));	
	if (pauseBox)
	{
		pauseBox->addEventListenerCheckBox(this, checkboxselectedeventselector(TouchLayer::pauseCheckBoxCallback));
	}

	

}

void TouchLayer::onLongLeftClick(Ref *pSender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		this->schedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongLeft), 0.2f);
		break;
	case ui::Widget::TouchEventType::MOVED:

		break;
	case ui::Widget::TouchEventType::ENDED:
		this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongLeft));
		break;
	case ui::Widget::TouchEventType::CANCELED:
		if (isScheduled(CC_SCHEDULE_SELECTOR(TouchLayer::onLongLeft)))
		{
			this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongLeft));
		}
		break;
	default:
		break;
	}
}

void TouchLayer::onLongRightClick(Ref *pSender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		this->schedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRight), 0.2f);
		break;
	case ui::Widget::TouchEventType::MOVED:

		break;
	case ui::Widget::TouchEventType::ENDED:
		this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRight));
		break;
	case ui::Widget::TouchEventType::CANCELED:
		if (isScheduled(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRight)))
				{
					this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRight));
				}
		break;
	default:
		break;
	}
}

void TouchLayer::onLongDownClick(Ref *pSender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		this->schedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongDown), 0.1f);
		this->getMyTouchDelegate()->onSoftDropStart();
		break;
	case ui::Widget::TouchEventType::MOVED:

		break;
	case ui::Widget::TouchEventType::ENDED:
		this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongDown));
		this->getMyTouchDelegate()->onSoftDropStop();
		break;
	case ui::Widget::TouchEventType::CANCELED:
		if (isScheduled(CC_SCHEDULE_SELECTOR(TouchLayer::onLongDown)))
				{
					this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongDown));
					this->getMyTouchDelegate()->onSoftDropStop();
				}
		break;
	default:
		break;
	}
}

void TouchLayer::onLongRotateClick(Ref *pSender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		this->schedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRotate), 0.2f);
		break;
	case ui::Widget::TouchEventType::MOVED:

		break;
	case ui::Widget::TouchEventType::ENDED:
		this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRotate));
		break;
	case ui::Widget::TouchEventType::CANCELED:
		if (isScheduled(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRotate)))
				{
					this->unschedule(CC_SCHEDULE_SELECTOR(TouchLayer::onLongRotate));
				}
		break;
	default:
		break;
	}
}


void TouchLayer::onLongLeft(float time)
{
	
	this->getMyTouchDelegate()->onLeft();
}

void TouchLayer::onLongRight(float time)
{
	this->getMyTouchDelegate()->onRight();
}

void TouchLayer::onLongDown(float time)
{
	this->getMyTouchDelegate()->onDown();
}

void TouchLayer::onLongRotate(float time)
{
	this->getMyTouchDelegate()->onRotate();
}


void TouchLayer::onLeft(Ref* sender)
{
	this->getMyTouchDelegate()->onLeft();
}

void TouchLayer::onRight(Ref* sender)
{
	this->getMyTouchDelegate()->onRight();
}

void TouchLayer::onRotation(Ref* sender)
{
	this->getMyTouchDelegate()->onRotate();
}

void TouchLayer::onDown(Ref* sender)
{
	this->getMyTouchDelegate()->onDown();
}

void TouchLayer::onHold(Ref* sender)
{
	this->getMyTouchDelegate()->onHold();
}

void TouchLayer::onHardDrop(Ref* sender)
{
	this->getMyTouchDelegate()->onHardDrop();
}


void TouchLayer::pauseCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type)
{

	auto buttonNode = this->getChildByName("buttonRoot");
	switch (event_type)
	{
	case CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		this->getMyTouchDelegate()->onPause();
	
		for (auto node : buttonNode->getChildren())
		{
			if (node->getName() == "pauseCheck")
			{
				continue;
			}
			else if (dynamic_cast<ui::Button*>(node))
			{
				dynamic_cast<ui::Button*>(node)->setEnabled(true);
			}
		}
		break;
	case CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		this->getMyTouchDelegate()->onPause();	
		for (auto node : buttonNode->getChildren())
		{
			if (node->getName() == "pauseCheck")
			{
				continue;
			}
			else if (dynamic_cast<ui::Button*>(node))
			{
				dynamic_cast<ui::Button*>(node)->setEnabled(false);
			}
		}
		break;
	}


}

//void TouchLayer::onSettingCallBack(Ref* sender)
//{
//	this->getMyTouchDelegate()->onPause();
//	auto optionLayer = OptionLayer::create();
//	this->addChild(optionLayer);
//}