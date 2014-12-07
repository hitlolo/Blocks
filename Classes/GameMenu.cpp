#include "GameMenu.h"

Scene* GameMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = GameMenu::create();

	scene->addChild(layer);

	return scene;

}

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	creditView = nullptr;

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
	CommandCenter::getInstance()->goState(GAME_STATE::GAME);
}

void GameMenu::switchOption(Ref* sender)
{
	auto node = this->getChildByName("optionLayer");

	if (!node)
	{
		auto optionLayer = OptionLayer::create();
		this->addChild(optionLayer);
		optionLayer->setName("optionLayer");
		/*auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2))), FadeIn::create(0.3f), nullptr);
		optionLayer->runAction(action);*/

	}
	else
	{
		removeChild(node);
		

	}
}


void GameMenu::addCreditsView()
{

	std::string file = "UIbg.png";
	creditView = Sprite::create(file);
	creditView->setPosition(originPoint.x + visibleSize.width - creditView->getContentSize().width  , originPoint.y + creditView->getContentSize().height  );
	/*creditView->setOpacity(195);*/
	this->addChild(creditView);

	//:createWithTTF(
	//const std::string& text, 
	//const std::string& fontFile, 
	//float fontSize, 
	//const Size& dimensions /* = Size::ZERO */,
	//TextHAlignment hAlignment /* = TextHAlignment::LEFT */, 
	//TextVAlignment vAlignment /* = TextVAlignment::TOP */)

	//label
	std::string thanks_str = "\nC R E D I T S\n\n---------\ncoding:\nhitlolo\n\nSpecial thanks:\nwww.kenney.nl\n---------";
	std::string font_name = "kenpixel_future.ttf";
	Label* thanks = Label::createWithTTF(thanks_str, font_name, 18);
	thanks->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	thanks->setPosition(originPoint.x + creditView->getContentSize().width / 2, originPoint.y + creditView->getContentSize().height - 100);
	creditView->addChild(thanks);

}

void  GameMenu::showCreditsView(Ref* sender)
{

	if (!creditView)
	{
		this->addCreditsView();
	}
	else
	{
		this->creditView->setVisible(!creditView->isVisible());
	}

#if 0
	CCLOG("CREDITS VIEW!");
#endif

}