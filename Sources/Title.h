//�N���X�F�^�C�g���V�[���N���X
//�쐬�ҁF���c  ���H			
//�X�V���F2015�N6��11��			

//��d�C���N���[�h�h�~
#pragma once

//.h(�w�b�_�[�t�@�C��)�ǂݍ���
#include "cocos2d.h"

//�^�C�g���V�[���N���X
class Title : public cocos2d::Layer
{
private:
//�����o�[�ϐ�
	cocos2d::Sprite* m_title_s;						//�����o�[�ϐ�					

public:
	
	virtual bool init();							//����������

	static cocos2d::Scene* createScene();			//�V�[���̍쐬
	void sceneChange(float delta);					//�V�[���؂�ւ�����

	CREATE_FUNC(Title);
};