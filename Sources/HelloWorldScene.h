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

	//�X�V����
	void update(float delta)override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	//�^�b�`�C�x���g�p�֐��̐錾
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);			//  �^�b�`���J�n�����Ƃ��ɉ����̏��������s����
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);			//�X���C�v���J�n�����Ƃ��ɉ����̏��������s����
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);			//  �^�b�`���͂Ȃ����Ƃ��ɉ����̏��������s����

	//���W��\������e�L�X�g�t�B�[���h
	cocos2d::LabelTTF* descriptionLabel;
	cocos2d::LabelTTF* TouchBeganLabel;
	cocos2d::LabelTTF* TouchMovedLabel;
	cocos2d::LabelTTF* TouchEndedLabel;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
