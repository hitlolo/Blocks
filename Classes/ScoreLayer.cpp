#include "ScoreLayer.h"


bool ScoreLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addLayer();
	return true;
}

void ScoreLayer::addLayer()
{
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Point(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);

	
	this->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2));
	Node *rootNode = CSLoader::createNode("scoreNode.csb");//传入Studio2.x的资源路径
	rootNode->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2));
	this->addChild(rootNode);

}