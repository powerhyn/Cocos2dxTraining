//create by M3 2016.11.12

#include "CardMatchingGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CardMatchingGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CardMatchingGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CardMatchingGameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	//리소스 폴더 경로 추가
	FileUtils::getInstance()->addSearchPath( "CardMatching" );

	_winSize = Director::getInstance()->getVisibleSize();
	_originPos = Director::getInstance()->getVisibleOrigin();
    
	onCreateExitMenu();
	initView();

    return true;
}


void CardMatchingGameScene::initView()
{
	onCreateCards();
}

void CardMatchingGameScene::onCreateCards()
{
	auto card = CardSprite::createWithCardNumber( 1 );
	card->setPosition( _winSize  * 0.5f );

	this->addChild( card );
}

void CardMatchingGameScene::onCreateExitMenu()
{
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1( CardMatchingGameScene::menuCloseCallback, this ) );

	closeItem->setPosition( Vec2( _originPos.x + _winSize.width - closeItem->getContentSize().width / 2,
								  _originPos.y + closeItem->getContentSize().height / 2 ) );

	auto menu = Menu::create( closeItem, NULL );
	menu->setPosition( Vec2::ZERO );
	this->addChild( menu, 1 );
}

void CardMatchingGameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
