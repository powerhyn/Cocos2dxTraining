//create by M3 2016.11.12

#include "CardMatchingGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace gamescene;

CardMatchingGameScene::CardMatchingGameScene()
{
	_vCardList.reserve( kMaxCardNumber * 2 );
}

CardMatchingGameScene::~CardMatchingGameScene()
{

}

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
    
	setTouchListener();

	onCreateExitMenu();
	initView();

    return true;
}

void CardMatchingGameScene::setTouchListener()
{
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2( CardMatchingGameScene::onTouchBegan, this );
	_listener->setSwallowTouches( true ); //아래에 있는 레이어의 터치를 막음

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( _listener, this );
}

bool CardMatchingGameScene::onTouchBegan( Touch *touch, Event *touchEvent )
{
	if ( !_bTouchEnabled || _vCardList.empty() )
		return false;

	Vec2 touchPos = touch->getLocation();

	for ( auto card : _vCardList )
	{
		if ( !card )
			continue;

		Rect box = card->getBoundingBox();

		if ( box.containsPoint( touchPos ) )
		{
			card->setVisibleCardNum( false );
			return true;
		}
	}

	return false;
}


void CardMatchingGameScene::initView()
{
	onCreateCards();
}

void CardMatchingGameScene::onCreateCards()
{
	std::vector<int> cardNums	= getShuffledCardNum( kMaxCardNumber );
	Vec2 startPos				= Vec2( 350.0f, 300.0f );

	for ( int i = 0; i < kMaxCardNumber * 2; ++i )
	{
		auto card = CardSprite::createWithCardNumber( cardNums[ i ] );
		Vec2 pos  = Vec2( ( card->getContentSize().width + kCardPadding ) * ( i % kMaxCardCol ),
						 ( card->getContentSize().height + kCardPadding ) * ( i / kMaxCardCol ));

		card->setPosition( startPos + pos );
		card->setTag( cardNums[ i ] );
		_vCardList.pushBack( card );

		this->addChild( card );
	}
}

std::vector<int> CardMatchingGameScene::getShuffledCardNum( int maxCardNum )
{
	std::vector<int> ret;

	for ( int i = 0; i < maxCardNum * 2; ++i )
	{
		ret.push_back( i / 2 );
	}

	std::random_shuffle( ret.begin(), ret.end() );

	return ret;
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
