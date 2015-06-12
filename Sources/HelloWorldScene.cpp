#include "HelloWorldScene.h"
#include "CCLuaEngine.h"
#include "Character.h"

USING_NS_CC;

// 生成するスプライトの親になるノード（グローバル変数）
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

//スプライトを配置する関数
int lua_cocos2dx_allocation_sprite(lua_State* tolua_S)
{
	LuaEngine* engine = LuaEngine::getInstance();		//スクリプトエンジンを取得
	LuaStack*  stack  = engine->getLuaStack();			//エンジンのスタックを取得
	lua_State* state = stack->getLuaState();			//スタックのステートを取得

	//一番目の引数で絶対にファイル名を指定
	Sprite * spr = Sprite::create(lua_tostring(tolua_S, 1));
	float x = lua_tonumber(tolua_S, 2);
	float y = lua_tonumber(tolua_S, 3);

	//スプライトの座標を指定
	spr->setPosition(x, y);

	//親にぶら下げる
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
    
	//画面解像度を取得
    Size visibleSize = Director::getInstance()->getVisibleSize();

	//座標を取得
    Point origin	 = Director::getInstance()->getVisibleOrigin();

	LuaEngine* engine = LuaEngine::getInstance();	//スクリプトエンジンを取得
	LuaStack*  stack = engine->getLuaStack();		//エンジンのスタックを取得
	lua_State* state = stack->getLuaState();		//スタックのステートを取得

	g_parent = this;		//スプライトの親を設定(HelloWorldを親に)

	//ゲームを終了する
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	//場所を指定
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//タッチ開始座標を表示するラベル
	TouchBeganLabel = LabelTTF::create("[TouchBegan](x, y)", "arial", 20);
	TouchBeganLabel->setPosition(ccp(120, 620));
	this->addChild(TouchBeganLabel);

	//スワイプ時の座標を表示するラベル
	TouchMovedLabel = LabelTTF::create("[TouchMoved](x, y)", "arial", 20);
	TouchMovedLabel->setPosition(ccp(120, 600));
	this->addChild(TouchMovedLabel);

	//タツチ終了時の座標を表示するラベル
	TouchEndedLabel = LabelTTF::create("[TouchEnded](x, y)", "arial", 20);
	TouchEndedLabel->setPosition(ccp(120, 580));
	this->addChild(TouchEndedLabel);

	//lua用関数を登録する
	lua_pushcfunction(state, lua_cocos2dx_allocation_sprite);
	lua_setglobal(state, "cocos2dx_allocation_sprite");

	//配置スクリプトを実行
	engine->executeScriptFile("src/allocation.lua");
    
	//タッチモードを設定する
	this->setTouchMode(kCCTouchesOneByOne);

	//タッチを有効にする
	this->setTouchEnabled(true);

	//auto sprite = Sprite::create("majo.png");
	//sprite->setPosition(200, 200);
	//this->addChild(sprite);

	//キャラクターを表示
	Character* character = new Character;
	character->Initialize();
	this->addChild(character);

	//毎フレームの処理を登録
	this->scheduleUpdate();

    return true;
}

//更新処理
void HelloWorld::update(float delta)
{
	score++;

	//ログ出力
	CCLOG("[TouchBegan](%d)", score);
}


//タッチを開始したときに何かの処理を実行する
bool HelloWorld::onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	//タッチした座標を取得
	Point location = pTouch->getLocation();

	////ログ出力
	//CCLOG("[TouchBegan](%f,%f)", location.x, location.y);

	//画面出力
	String * str = String::createWithFormat("[TouchBegan](%d,%d)", static_cast<int>(location.x), static_cast<int>(location.y));
	TouchBeganLabel->setString(str->getCString());

	return true;
}

//スワイプを開始したときに何かの処理を実行する
void HelloWorld::onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	//タッチした座標を取得
	Point location = pTouch->getLocation();

	//画面出力
	String * str = String::createWithFormat("[TouchMoved](%d,%d)", static_cast<int>(location.x), static_cast<int>(location.y));
	TouchMovedLabel->setString(str->getCString());
}

//タッチをはなしたときに何かの処理を実行する
void HelloWorld::onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
	//タッチした座標を取得
	Point location = pTouch->getLocation();

	//画面出力
	String * str = String::createWithFormat("[TouchEnded](%d,%d)", static_cast<int>(location.x), static_cast<int>(location.x));
	TouchEndedLabel->setString(str->getCString());


	//startlocation　タッチ開始位置
	//currentPos	 タッチ終了位置
	//この二つの位置をここでとる事によってスワイプとして扱う
	//タッチした時の位置
	Point startlocation = pTouch->getStartLocation();

	// タッチが離れた時の位置
	Point currentPos = pTouch->getLocation();

	// １フレームで動いた距離を算出
	float dist = ccpDistance(currentPos, startlocation);

	// ２点の座標の差分を算出する
	Point vec = ccpSub(currentPos, startlocation);

	// ベクトルの角度				　    3.14
	float angle = ccpToAngle(vec) * 180 / M_PI;

	//ログ出力
	CCLOG("[TouchEnded](%f,%f)", currentPos.x, currentPos.y);

	//上方向へのスワイプを検知
	if (45.0f <= angle && angle < 135.0f)
	{
		CCLOG("top");
	}

	//下方向へのスワイプを検知
	else if (-135.0f <= angle && angle < -45.0f)
	{
		CCLOG("under");
	}

	//左方向へのスワイプを検知
	else if ((135.0f <= angle && angle < 180.0f) || (-180.0f <= angle && angle < -135.0f))
	{
		CCLOG("left");

	}

	//右方向へのスワイプを検知
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
