#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 

	int score;

	//更新処理
	void update(float delta)override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	//タッチイベント用関数の宣言
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);			//  タッチを開始したときに何かの処理を実行する
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);			//スワイプを開始したときに何かの処理を実行する
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);			//  タッチをはなしたときに何かの処理を実行する

	//座標を表示するテキストフィールド
	cocos2d::LabelTTF* descriptionLabel;
	cocos2d::LabelTTF* TouchBeganLabel;
	cocos2d::LabelTTF* TouchMovedLabel;
	cocos2d::LabelTTF* TouchEndedLabel;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
