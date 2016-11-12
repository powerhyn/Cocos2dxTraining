//create by M3 2016.11.12

#include "CardSprite.h"

USING_NS_CC;

CardSprite::CardSprite()
: _pCardNumberLabel(nullptr)
, _nCardNumber(-1)
, _strCardFileName("card.png")
, _c4BLabelColor(Color4B::BLACK)
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
	this->addChild( _pCardNumberLabel, 1, "NumberLabel" );
}

// 숫자를 문자로 변환시켜주는 함수
std::string CardSprite::intToString( int num )
{
	std::string ret = "";

	ret = StringUtils::format( "%d", num );

	return ret;
}
