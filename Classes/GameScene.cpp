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
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Tetris.wav");
	auto background = Sprite::create("bg.png");
	float scale_x = visibleSize.width / background->getContentSize().width;
	float scale_y = visibleSize.height / background->getContentSize().height;
	background->setScaleX(scale_x);
	background->setScaleY(scale_y);
	background->setAnchorPoint(Point(0.5, 0.5));
	background->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2);
	this->addChild(background);


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

	auto touchLayer = TouchLayer::create();
	this->addChild(touchLayer);
	touchLayer->setMyTouchDelegate(gameBoard);

}

GameScene::~GameScene()
{
	this->removeAllChildrenWithCleanup(true);
}
