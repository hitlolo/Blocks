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


	auto leftButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("leftButton"));
	if (leftButton)
	{
		leftButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onLeft, this));
	}

	auto rightButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("rightButton"));
	if (rightButton)
	{
		rightButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onRight, this));
	}

	auto rotateButton = dynamic_cast<ui::Button*> (rootNode->getChildByName("rotateButton"));
	if (rotateButton)
	{
		rotateButton->addClickEventListener(CC_CALLBACK_1(TouchLayer::onRotation, this));
	}

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