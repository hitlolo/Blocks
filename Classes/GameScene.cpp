#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	
	addLayers();
	
	return true;
}

void GameScene::addLayers()
{
	
	auto background = Sprite::createWithSpriteFrameName("bg.png");
	float scale_x = visibleSize.width / background->getContentSize().width;
	float scale_y = visibleSize.height / background->getContentSize().height;
	background->setScaleX(scale_x);
	background->setScaleY(scale_y);
	background->setAnchorPoint(Point(0.5, 0.5));
	background->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	this->addChild(background);

	for (int i = 0; i < 20; i++)
	{
		auto starNode = Sprite::create("particle01.png");
		this->addChild(starNode);//假设this是即将显示的scene 
		starVector.push_back(starNode);
		starNode->setPosition(RandomGenerator::getInstance()->getRandomPosition());
	
	}

#if 0
	auto gameBoard = LayerColor::create(Color4B(125, 126, 125, 255), BLOCK_WIDTH * BOARD_WIDTH, BLOCK_WIDTH * BOARD_HEIGHT);
//	gameBoard->setContentSize(Size(BLOCK_WIDTH * BOARD_WIDTH, BLOCK_WIDTH * BOARD_HEIGHT));
	gameBoard->setAnchorPoint(Point(0, 0));
	gameBoard->ignoreAnchorPointForPosition(false);
//	gameBoard->setPosition(originPoint.x + visibleSize.width / 2 -12, originPoint.y + visibleSize.height / 2);
	gameBoard->setPosition(384, 48);
	this->addChild(gameBoard);
	CCLOG("%f,%f", gameBoard->getPositionX(), gameBoard->getPositionY());
#endif

	auto gameBoard = GameBoard::create();
	this->addChild(gameBoard);

	auto HUDLayer = HUDLayer::create();
	this->addChild(HUDLayer);

	gameBoard->setHUD(HUDLayer);
	

	auto touchLayer = TouchLayer::create();
	this->addChild(touchLayer);
	touchLayer->setMyTouchDelegate(gameBoard);

}
