//create by M3 2016.11.12

#include "CardSprite.h"

USING_NS_CC;

CardSprite::CardSprite()
: _pCardNumberLabel(nullptr)
, _nCardNumber(-1)
, _strCardFileName("card.png")
, _c4BLabelColor(Color4B::BLACK)
, _openAnimationFinishedCallback(nullptr)
, _closeAnimationFinishedCallback(nullptr)
{
}

CardSprite::~CardSprite()
{

}

// 카드의 번호를 입력받아 카드를 생성하는 함수
// Sprite 객체를 생성 후 카드 번호와 Label을 생성
CardSprite * CardSprite::createWithCardNumber( int number )
{
	CardSprite * card = new ( std::nothrow ) CardSprite();
	
	if ( card && card->initWithFile( card->_strCardFileName ) )
	{
		card->_nCardNumber = number;

		card->onCreateCardNumberLabel( number );
		card->autorelease();

		return card;
	}

	CC_SAFE_DELETE( card );

	return nullptr;
}

// 카드의 번호를 표시 해줄 Label
void CardSprite::onCreateCardNumberLabel( int num )
{
	_pCardNumberLabel = Label::createWithTTF( intToString(num) , "fonts/Marker Felt.ttf", 24 );
	_pCardNumberLabel->setPosition( this->getContentSize() * 0.5f );
	_pCardNumberLabel->setTextColor( _c4BLabelColor );
	_pCardNumberLabel->setScaleX( -1.0f );

	this->addChild( _pCardNumberLabel, 1, "NumberLabel" );
}

// 숫자를 문자로 변환시켜주는 함수
std::string CardSprite::intToString( int num )
{
	std::string ret = "";

	ret = StringUtils::format( "%d", num );

	return ret;
}

int CardSprite::getCardNumber()
{
	return _nCardNumber;
}

void CardSprite::setVisibleCardNum( bool visible )
{
	if ( _pCardNumberLabel )
		_pCardNumberLabel->setVisible( visible );
}

bool CardSprite::isOpened()
{
	if ( _pCardNumberLabel )
		return _pCardNumberLabel->isVisible();

	return false;
}

void CardSprite::onPlayCardOpenAnimation()
{
	auto rotationHalf	= RotateTo::create( CARD_FLIP_ANIMATION_TIME * 0.5f, Vec3( 0, 100, 0 ) );
	auto visibleNum		= CallFunc::create( std::bind( &CardSprite::setVisibleCardNum, this, true ) );
	auto rotation		= RotateTo::create( CARD_FLIP_ANIMATION_TIME * 0.5f, Vec3( 0, 180, 0 ) );
	auto callback		= CallFunc::create( CC_CALLBACK_0( CardSprite::onOpenAnimationFinished, this ) );
	auto sequence		= Sequence::create( rotationHalf, visibleNum, rotation, callback, nullptr );

	this->runAction( sequence );
}

void CardSprite::onPlayCardClosedAnimation()
{
	auto rotationHalf	= RotateTo::create( CARD_FLIP_ANIMATION_TIME * 0.5f, Vec3( 0, 100, 0 ) );
	auto invisibleNum	= CallFunc::create( std::bind( &CardSprite::setVisibleCardNum, this, false ) );
	auto rotation		= RotateTo::create( CARD_FLIP_ANIMATION_TIME * 0.5f, Vec3( 0, 0, 0 ) );
	auto callback		= CallFunc::create( CC_CALLBACK_0( CardSprite::onClosedAnimationFinished, this ) );
	auto sequence		= Sequence::create( rotationHalf, invisibleNum, rotation, callback, nullptr );

	this->runAction( sequence );
}

void CardSprite::setCardAnimationFinishCallback( CardAnimationFinishedCallback open, CardAnimationFinishedCallback close )
{
	setOpenAnimationFinishCallback( open );
	setCloseAnimationFinishCallback( close );
}

void CardSprite::setOpenAnimationFinishCallback( CardAnimationFinishedCallback func )
{
	if ( func )
		_openAnimationFinishedCallback = func;
}

void CardSprite::setCloseAnimationFinishCallback( CardAnimationFinishedCallback func )
{
	if ( func )
		_closeAnimationFinishedCallback = func;
}

void CardSprite::onOpenAnimationFinished()
{
	log( "open animation finish !" );

	if ( _openAnimationFinishedCallback )
		_openAnimationFinishedCallback();
}

void CardSprite::onClosedAnimationFinished()
{
	log( "closeed animation finish !" );

	if ( _closeAnimationFinishedCallback )
		_closeAnimationFinishedCallback();
}