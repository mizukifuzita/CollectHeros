//�N���X�F�L�����N�^�[�N���X
//�쐬�ҁF���c  ���H			
//�X�V���F2015�N6��12��
#pragma once

#include "cocos2d.h"

//�L�����N�^�[�N���X
class Character : public cocos2d::Layer
{
private:
//�����o�[�ϐ�
	cocos2d::Sprite* m_char;
	cocos2d::Point   m_pos;

public:
	Character();			//�R���X�g���N�^
	~Character();			//�f�X�g���N�^

	void Initialize();		//����������
	void Finalize();		//�I������

	void Update();			//�X�V����
	void Draw();			//�`�揈��
};