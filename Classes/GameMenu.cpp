#include "GameMenu.h"

Scene* GameMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = GameMenu::create();

	layer->setDJ(DiscJockey::getInstance());

	scene->addChild(layer);

	return scene;

}

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addMenu();

	
	return true;
}

void GameMenu::addMenu()
{
	originPoint = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("bg.png");
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
		starNode->setPosition(RandomGenerator::getInstance()->getRandomPosition());

	}
	
	//Label* Label::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
	auto title = Label::createWithTTF("B L O C K S", "kenpixel_future.ttf", 100);
	title->setPosition(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 10 * 8);
	title->enableOutline(Color4B(25,26,25,155),5);
	this->addChild(title);

	Node *menuNode = CSLoader::createNode("menuNode.csb");//传入Studio2.x的资源路径
	menuNode->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height / 2));
	this->addChild(menuNode);
	menuNode->setName("menuNode");

	

	auto playButton = dynamic_cast<ui::Button*> (menuNode->getChildByName("buttonPlay"));
	if (playButton)
	{
		playButton->addClickEventListener(CC_CALLBACK_1(GameMenu::startGame, this));
	}

	auto optionButton = dynamic_cast<ui::Button*> (menuNode->getChildByName("buttonOption"));
	if (optionButton)
	{
		optionButton->addClickEventListener(CC_CALLBACK_1(GameMenu::switchOption, this));
	}

	auto creditButton = dynamic_cast<ui::Button*> (menuNode->getChildByName("buttonCredit"));
	if (creditButton)
	{
		creditButton->addClickEventListener(CC_CALLBACK_1(GameMenu::showCreditsView, this));
	}
}

GameMenu::~GameMenu()
{
	this->removeAllChildrenWithCleanup(true);
}


void GameMenu::startGame(Ref* sender)
{
	getDJ()->playClickEffect();
	CommandCenter::getInstance()->goState(GAME_STATE::GAME);
}

void GameMenu::switchOption(Ref* sender)
{
	getDJ()->playClickEffect();

	auto optionLayer = OptionLayer::create();
	this->addChild(optionLayer);
		
}


void GameMenu::showCreditsView(Ref* sender)
{
	getDJ()->playClickEffect();
	auto node = this->getChildByName("creditLayer");

	if (!node)
	{
		auto creditLayer = CreditLayer::create();
		this->addChild(creditLayer);
		creditLayer->setName("creditLayer");

	}
	else
	{
		removeChild(node);

	}

}
