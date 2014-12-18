#include "HUDLayer.h"


bool HUDLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addLayer();
	return true;
}

HUDLayer::HUDLayer()
{
	lineNum = 0;
	comboNum = 0;
	scoreNum = 0;
}

HUDLayer::~HUDLayer()
{
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}

void HUDLayer::addLayer()
{
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Point(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);

	
	this->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2));
	Node *rootNode = CSLoader::createNode("scoreNode.csb");
	rootNode->setAnchorPoint(Point::ZERO);
	//rootNode->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2));
	this->addChild(rootNode);

	auto hudRoot = dynamic_cast<Node*>(rootNode->getChildByName("hudRoot"));
	auto hud = dynamic_cast<Node*>(hudRoot->getChildByName("hudNode"));

	curLine = dynamic_cast<Text*>(hud->getChildByName("textCurLine"));
	curScore = dynamic_cast<Text*>(hud->getChildByName("textCurScore"));
	curSpeed = dynamic_cast<Text*>(hud->getChildByName("textCurSpeed"));
	curCombo = dynamic_cast<Text*>(hud->getChildByName("textCurCombo"));

	curSpeed->setText(String::createWithFormat("%d", CommandCenter::getInstance()->getSpeedLevel())->getCString());
}


void HUDLayer::addLine(int add_line)
{
	int combo = add_line - 1;
	int tem = lineNum;
	lineNum += add_line;
	if (tem % 20 > lineNum % 20)
	{
		this->addSpeed();
	}
	
	curLine->setText(String::createWithFormat("%d", lineNum)->getCString());
	
	Vector<FiniteTimeAction*> vector_action;
	for (int i = 0; i < combo; i++)
	{
		auto action = Sequence::create(CCCallFunc::create(CC_CALLBACK_0(HUDLayer::addCombo, this)), DelayTime::create(0.1f / add_line), nullptr);
		vector_action.pushBack(action);

	}

	//几次combo就几倍积分
	for (int i = 0; i < add_line * add_line; i++)
	{
		auto action = Sequence::create(CCCallFunc::create(CC_CALLBACK_0(HUDLayer::addScore, this)), DelayTime::create(0.1f / (add_line * add_line)), nullptr);
		vector_action.pushBack(action);

	}
	

	auto action = Sequence::create(vector_action);
	this->runAction(action);

}

void HUDLayer::addCombo()
{
	comboNum += 1;
	curCombo->setText(String::createWithFormat("%d", comboNum)->getCString());
}

void HUDLayer::addScore()
{
	//每次10分
	DiscJockey::getInstance()->playAddScoreEffect();
	scoreNum += 10;
	curScore->setText(String::createWithFormat("%d", scoreNum)->getCString());
}

void HUDLayer::addSpeed()
{
	int speed = CommandCenter::getInstance()->getSpeedLevel() + 1;
	CommandCenter::getInstance()->setSpeedLevel(speed);
	curSpeed->setText(String::createWithFormat("%d", speed)->getCString());
}