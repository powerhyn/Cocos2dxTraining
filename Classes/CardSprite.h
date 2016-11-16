//create by M3 2016.11.12

#pragma once

#include "cocos2d.h"

USING_NS_CC;

const float CARD_FLIP_ANIMATION_TIME = 1.0f;

typedef std::function<void()> CardAnimationFinishedCallback;

class CardSprite : public Sprite
{
private:
	CardSprite();
	~CardSprite();

public:
	static CardSprite * createWithCardNumber( int number );
	void setVisibleCardNum( bool visible );
	bool isOpened();
	int getCardNumber();

private :
	void onCreateCardNumberLabel( int num );

private:
	std::string intToString( int num );

public:
	void onPlayCardOpenAnimation();
	void onPlayCardClosedAnimation();

	void setCardAnimationFinishCallback( CardAnimationFinishedCallback open, CardAnimationFinishedCallback close );
	void setOpenAnimationFinishCallback( CardAnimationFinishedCallback  f );
	void setCloseAnimationFinishCallback( CardAnimationFinishedCallback  f );

private:
	void onOpenAnimationFinished();
	void onClosedAnimationFinished();

	CardAnimationFinishedCallback _openAnimationFinishedCallback;
	CardAnimationFinishedCallback _closeAnimationFinishedCallback;

private:
	//카드 안에 표시될 숫자 Label
	Label * _pCardNumberLabel;

	//카드의 번호
	int				_nCardNumber;
	//카드 스프라이트의 파일명
	std::string		_strCardFileName;
	//카드 Label의 글자 색상
	Color4B			_c4BLabelColor;
};