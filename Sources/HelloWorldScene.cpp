#include "HelloWorldScene.h"
#include "CCLuaEngine.h"
#include "Character.h"

USING_NS_CC;

// ��������X�v���C�g�̐e�ɂȂ�m�[�h�i�O���[�o���ϐ��j
Node* g_parent = nullptr;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//�X�v���C�g��z�u����֐�
int lua_cocos2dx_allocation_sprite(lua_State* tolua_S)
{
	LuaEngine* engine = LuaEngine::getInstance();		//�X�N���v�g�G���W�����擾
	LuaStack*  stack  = engine->getLuaStack();			//�G���W���̃X�^�b�N���擾
	lua_State* state = stack->getLuaState();			//�X�^�b�N�̃X�e�[�g���擾

	//��Ԗڂ̈����Ő�΂Ƀt�@�C�������w��
	Sprite * spr = Sprite::create(lua_tostring(tolua_S, 1));
	float x = lua_tonumber(tolua_S, 2);
	float y = lua_tonumber(tolua_S, 3);

	//�X�v���C�g�̍��W���w��
	spr->setPosition(x, y);

	//�e�ɂԂ牺����
	g_parent->addChild(spr);

	return 0;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	score = 0;
    
	//��ʉ𑜓x���擾
    Size visibleSize = Director::getInstance()->getVisibleSize();

	//���W���擾
    Point origin	 = Director::getInstance()->getVisibleOrigin();

	LuaEngine* engine = LuaEngine::getInstance();	//�X�N���v�g�G���W�����擾
	LuaStack*  stack = engine->getLuaStack();		//�G���W���̃X�^�b�N���擾
	lua_State* state = stack->getLuaState();		//�X�^�b�N�̃X�e�[�g���擾

	g_parent = this;		//�X�v���C�g�̐e��ݒ�(HelloWorld��e��)

	//�Q�[�����I������
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	//�ꏊ���w��
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//�^�b�`�J�n���W��\�����郉�x��
	TouchBeganLabel = LabelTTF::create("[TouchBegan](x, y)", "arial", 20);
	TouchBeganLabel->setPosition(ccp(120, 620));
	this->addChild(TouchBeganLabel);

	//�X���C�v���̍��W��\�����郉�x��
	TouchMovedLabel = LabelTTF::create("[TouchMoved](x, y)", "arial", 20);
	TouchMovedLabel->setPosition(ccp(120, 600));
	this->addChild(TouchMovedLabel);

	//�^�c�`�I�����̍��W��\�����郉�x��
	TouchEndedLabel = LabelTTF::create("[TouchEnded](x, y)", "arial", 20);
	TouchEndedLabel->setPosition(ccp(120, 580));
	this->addChild(TouchEndedLabel);

	//lua�p�֐���o�^����
	lua_pushcfunction(state, lua_cocos2dx_allocation_sprite);
	lua_setglobal(state, "cocos2dx_allocation_sprite");

	//�z�u�X�N���v�g�����s
	engine->executeScriptFile("src/allocation.lua");
    
	//�^�b�`���[�h��ݒ肷��
	this->setTouchMode(kCCTouchesOneByOne);

	//�^�b�`��L���ɂ���
	this->setTouchEnabled(true);

	//auto sprite = Sprite::create("majo.png");
	//sprite->setPosition(200, 200);
	//this->addChild(sprite);

	//�L�����N�^�[��\��
	Character* character = new Character;
	character->Initialize();
	this->addChild(character);

	//���t���[���̏�����o�^
	this->scheduleUpdate();

    return true;
}

//�X�V����
void HelloWorld::update(float delta)
{
	score++;

	//���O�o��
	CCLOG("[TouchBegan](%d)", score);
}


//�^�b�`���J�n�����Ƃ��ɉ����̏��������s����
bool HelloWorld::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	//�^�b�`�������W���擾
	Point location = pTouch->getLocation();

	////���O�o��
	//CCLOG("[TouchBegan](%f,%f)", location.x, location.y);

	//��ʏo��
	String * str = String::createWithFormat("[TouchBegan](%d,%d)", static_cast<int>(location.x), static_cast<int>(location.y));
	TouchBeganLabel->setString(str->getCString());

	return true;
}

//�X���C�v���J�n�����Ƃ��ɉ����̏��������s����
void HelloWorld::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	//�^�b�`�������W���擾
	Point location = pTouch->getLocation();

	//��ʏo��
	String * str = String::createWithFormat("[TouchMoved](%d,%d)", static_cast<int>(location.x), static_cast<int>(location.y));
	TouchMovedLabel->setString(str->getCString());
}

//�^�b�`���͂Ȃ����Ƃ��ɉ����̏��������s����
void HelloWorld::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	//�^�b�`�������W���擾
	Point location = pTouch->getLocation();

	//��ʏo��
	String * str = String::createWithFormat("[TouchEnded](%d,%d)", static_cast<int>(location.x), static_cast<int>(location.x));
	TouchEndedLabel->setString(str->getCString());


	//startlocation�@�^�b�`�J�n�ʒu
	//currentPos	 �^�b�`�I���ʒu
	//���̓�̈ʒu�������łƂ鎖�ɂ���ăX���C�v�Ƃ��Ĉ���
	//�^�b�`�������̈ʒu
	Point startlocation = pTouch->getStartLocation();

	// �^�b�`�����ꂽ���̈ʒu
	Point currentPos = pTouch->getLocation();

	// �P�t���[���œ������������Z�o
	float dist = ccpDistance(currentPos, startlocation);

	// �Q�_�̍��W�̍������Z�o����
	Point vec = ccpSub(currentPos, startlocation);

	// �x�N�g���̊p�x				�@    3.14
	float angle = ccpToAngle(vec) * 180 / M_PI;

	//���O�o��
	CCLOG("[TouchEnded](%f,%f)", currentPos.x, currentPos.y);

	//������ւ̃X���C�v�����m
	if (45.0f <= angle && angle < 135.0f)
	{
		CCLOG("top");
	}

	//�������ւ̃X���C�v�����m
	else if (-135.0f <= angle && angle < -45.0f)
	{
		CCLOG("under");
	}

	//�������ւ̃X���C�v�����m
	else if ((135.0f <= angle && angle < 180.0f) || (-180.0f <= angle && angle < -135.0f))
	{
		CCLOG("left");

	}

	//�E�����ւ̃X���C�v�����m
	else if ((0 <= angle && angle < 45.0f) || (-45.0f <= angle && angle < 0)) //right
	{
		CCLOG("right");

	}
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
