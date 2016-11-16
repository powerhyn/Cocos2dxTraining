//create by M3 2016.11.12

#include "CardMatchingGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace gamescene;

CardMatchingGameScene::CardMatchingGameScene()
	: _bTouchEnabled(true)
	, _listener(nullptr)
{
	_vCardList.reserve( kMaxCardNumber * 2 );

	for ( int i = 0; i < 2; ++i )
		_pSelectedCard[ i ] = nullptr;

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
			if ( card->isOpened() == false )
			{
				card->onPlayCardOpenAnimation();

				addSelectedCard( card );

				_bTouchEnabled = false;			
			}

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
		card->setVisibleCardNum( false );
		card->setCardAnimationFinishCallback( CC_CALLBACK_0( CardMatchingGameScene::onOpenAnimationFinished, this ),
											  CC_CALLBACK_0( CardMatchingGameScene::onClosedAnimationFinished, this ) );

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

void CardMatchingGameScene::addSelectedCard( CardSprite *card )
{
	_pSelectedCard[ 0 ] == nullptr ? _pSelectedCard[ 0 ] = card : _pSelectedCard[ 1 ] = card;
}

void CardMatchingGameScene::initSelectCard()
{
	_pSelectedCard[ 0 ] = _pSelectedCard[ 1 ] = nullptr;
}

bool CardMatchingGameScene::isCardAllSelected()
{
	if ( _pSelectedCard[ 0 ] && _pSelectedCard[ 1 ] )
		return true;

	return false;
}

bool CardMatchingGameScene::isSelectCardNumberEquals()
{
	if ( _pSelectedCard[ 0 ]->getCardNumber() == _pSelectedCard[ 1 ]->getCardNumber() )
		return true;

	return false;
}

void CardMatchingGameScene::onRemoveCorrectCard()
{
	for ( int i = 0; i < 2; ++i )
	{
		auto delay		= DelayTime::create( 0.5f );
		auto remove		= CallFunc::create( std::bind( &CardMatchingGameScene::onRemoveCardVector, this, _pSelectedCard[ i ] ) );
		auto sequence	= Sequence::create( delay, remove, nullptr );

		_pSelectedCard[ i ]->runAction( sequence->clone() );
	}
}

void CardMatchingGameScene::onRemoveCardVector(CardSprite *remove)
{
	_vCardList.eraseObject( remove );
	remove->runAction( RemoveSelf::create() );

	if ( isGameClear() )
	{
		log( "Game clear!" );
	}
}

bool CardMatchingGameScene::isGameClear()
{
	return _vCardList.empty();
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

void CardMatchingGameScene::onOpenAnimationFinished()
{
	_bTouchEnabled = true;

	if ( isCardAllSelected() )
	{
		if ( isSelectCardNumberEquals() )
		{
			onRemoveCorrectCard();
		}
		else
		{
			_pSelectedCard[ 0 ]->onPlayCardClosedAnimation();
			_pSelectedCard[ 1 ]->onPlayCardClosedAnimation();

			_bTouchEnabled = false;
		}

		initSelectCard();
	}
}


void CardMatchingGameScene::onClosedAnimationFinished()
{
	_bTouchEnabled = true;
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
