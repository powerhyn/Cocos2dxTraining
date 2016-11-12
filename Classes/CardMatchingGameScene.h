//create by M3 2016.11.12

#ifndef __CARDMATCHINGGAME_SCENE_H__
#define __CARDMATCHINGGAME_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class CardMatchingGameScene : public cocos2d::Layer
{
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

	void onCreateExitMenu();

private:
	Size _winSize;
	Vec2 _originPos;
};

#endif // __CARDMATCHINGGAME_SCENE_H__
