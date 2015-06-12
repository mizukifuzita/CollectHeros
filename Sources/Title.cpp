#include "Title.h"
#include "HelloWorldScene.h"

USING_NS_CC;

bool Title::init()
{
	//��ʉ𑜓x���擾
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//���W���擾
	Point origin = Director::getInstance()->getVisibleOrigin();

	//���O�o��
	CCLog("x = %f, y = %f", origin.x, origin.y);
	CCLog("width = %f, height = %f", visibleSize.width, visibleSize.height);

	//��x�����Ăяo��
	this->scheduleOnce(schedule_selector(Title::sceneChange), 0.0f);

	//test_sprite = Sprite::create("Test.png");

	//test_sprite->setPosition(Vec2(origin.x + visibleSize.width - test_sprite->getContentSize().width / 2,
	//	origin.y + test_sprite->getContentSize().height / 2));

	//this->addChild(test_sprite);

	return true;
}

Scene* Title::createScene()
{
	// �V�[���������쐬
	auto scene = Scene::create();

	//���C���[�������쐬
	auto layer = Title::create();

	//�V�[���̎q�Ƃ��ă��C���[��ǉ�
	scene->addChild(layer);

	//�V�[����Ԃ�
	return scene;
}

//�V�[���؂�ւ�����
void Title::sceneChange(float delta)
{
	// ���̃V�[����ݒ�
	Scene* nextScene = HelloWorld::createScene();

	// �t�F�[�h���Ԑݒ�
	float duration = 2.0f;

	// �t�F�[�h�C���@���ʂ̐ݒ�
	Scene* pFade = TransitionFade::create(duration, nextScene);

	// �ړ�
	Director::sharedDirector()->replaceScene(pFade);
}