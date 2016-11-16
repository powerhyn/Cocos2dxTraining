//create by M3 2016.11.12

#ifndef __CARDMATCHINGGAME_SCENE_H__
#define __CARDMATCHINGGAME_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

namespace gamescene
{
	const int kMaxCardNumber	= 4;		//ī�� �ִ� ��ȣ
	const int kMaxCardCol		= 4;		//���ٿ� ���� ī�� ����
	const float kCardPadding	= 15.0f;	//ī�� ������ ����
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
	//���� ȭ�� ����
	void initView();
	//ī�� ����
	void onCreateCards();

	//������ ī���� ����Ʈ�� �޾ƿ�
	std::vector<int> getShuffledCardNum( int maxCardNum );

private:
	//������ ��ư
	void onCreateExitMenu();

private :
	bool onTouchBegan( Touch *touch, Event *touchEvent );

	//��ġ ������ ���
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
	//ī�� ��ü���� ��� cocos2dVector
	Vector<CardSprite *> _vCardList;

private:
	Size _winSize;
	Vec2 _originPos;
};

#endif // __CARDMATCHINGGAME_SCENE_H__
