//create by M3 2016.11.12

#ifndef __CARDMATCHINGGAME_SCENE_H__
#define __CARDMATCHINGGAME_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

namespace gamescene
{
	const int kMaxCardNumber	= 4;		//카드 최대 번호
	const int kMaxCardCol		= 4;		//한줄에 들어가는 카드 숫자
	const float kCardPadding	= 15.0f;	//카드 사이의 간격
}

class CardMatchingGameScene : public cocos2d::Layer
{
public :
	CardMatchingGameScene();
	~CardMatchingGameScene();

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC( CardMatchingGameScene );

private:
	//게임 화면 구성
	void initView();
	//카드 생성
	void onCreateCards();

	//섞여진 카드의 리스트를 받아옴
	std::vector<int> getShuffledCardNum( int maxCardNum );

private:
	//나가기 버튼
	void onCreateExitMenu();

private :
	bool onTouchBegan( Touch *touch, Event *touchEvent );

	//터치 리스너 등록
	void setTouchListener();

	EventListenerTouchOneByOne * _listener;
	bool						 _bTouchEnabled;

private :
	void addSelectedCard( CardSprite * card );
	void initSelectCard();
	bool isCardAllSelected();
	bool isSelectCardNumberEquals();

	void onRemoveCorrectCard();
	void onRemoveCardVector( CardSprite *card );

	CardSprite *		 _pSelectedCard[ 2 ];

private :
	bool isGameClear();

private :
	void onOpenAnimationFinished();
	void onClosedAnimationFinished();

private :
	//카드 객체들이 담길 cocos2dVector
	Vector<CardSprite *> _vCardList;

private:
	Size _winSize;
	Vec2 _originPos;
};

#endif // __CARDMATCHINGGAME_SCENE_H__
