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
	//게임 화면 구성
	void initView();
	//카드 생성
	void onCreateCards();

	void onCreateExitMenu();

private:
	Size _winSize;
	Vec2 _originPos;
};

#endif // __CARDMATCHINGGAME_SCENE_H__
