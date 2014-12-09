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

ScoreLayer::ScoreLayer()
{
	lineNum = 0;
	comboNum = 0;
	scoreNum = 0;
}

ScoreLayer::~ScoreLayer()
{
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
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

	curLine = dynamic_cast<Text*>(rootNode->getChildByName("textCurLine"));
	curScore = dynamic_cast<Text*>(rootNode->getChildByName("textCurScore"));
	curSpeed = dynamic_cast<Text*>(rootNode->getChildByName("textCurSpeed"));
	curCombo = dynamic_cast<Text*>(rootNode->getChildByName("textCurCombo"));


}


void ScoreLayer::addLine(int add_line)
{
	int combo = add_line - 1;
	int tem = lineNum;
	lineNum += add_line;
	if (tem % 20 > lineNum % 20)
	{
		this->addSpeed();
	}
	
	
	//if (lineNum % 20 == 0)
	//{
	//	
	//	CCLOG("SPEED UP");
	//}
	curLine->setText(String::createWithFormat("%d", lineNum)->getCString());
	
	Vector<FiniteTimeAction*> vector_action;
	for (int i = 0; i < combo; i++)
	{
		CCLOG("%f,", 0.1f / add_line);
		auto action = Sequence::create(CCCallFunc::create(CC_CALLBACK_0(ScoreLayer::addCombo, this)), DelayTime::create(0.1f / add_line), nullptr);
		vector_action.pushBack(action);

	}

	//几次combo就几倍积分
	for (int i = 0; i < add_line * add_line; i++)
	{
		auto action = Sequence::create(CCCallFunc::create(CC_CALLBACK_0(ScoreLayer::addScore, this)), DelayTime::create(0.1f / (add_line * add_line)), nullptr);
		vector_action.pushBack(action);

	}
	

	auto action = Sequence::create(vector_action);
	this->runAction(action);

}

void ScoreLayer::addCombo()
{
	comboNum += 1;
	curCombo->setText(String::createWithFormat("%d", comboNum)->getCString());
}

void ScoreLayer::addScore()
{
	//每次10分
	DiscJockey::getInstance()->playAddScoreEffect();
	scoreNum += 10;
	curScore->setText(String::createWithFormat("%d", scoreNum)->getCString());
}

void ScoreLayer::addSpeed()
{
	speedLevel += 1;
	curSpeed->setText(String::createWithFormat("%d", speedLevel)->getCString());
}