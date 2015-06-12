#include "Title.h"
#include "HelloWorldScene.h"

USING_NS_CC;

bool Title::init()
{
	//画面解像度を取得
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//座標を取得
	Point origin = Director::getInstance()->getVisibleOrigin();

	//ログ出力
	CCLog("x = %f, y = %f", origin.x, origin.y);
	CCLog("width = %f, height = %f", visibleSize.width, visibleSize.height);

	//一度だけ呼び出す
	this->scheduleOnce(schedule_selector(Title::sceneChange), 0.0f);

	//test_sprite = Sprite::create("Test.png");

	//test_sprite->setPosition(Vec2(origin.x + visibleSize.width - test_sprite->getContentSize().width / 2,
	//	origin.y + test_sprite->getContentSize().height / 2));

	//this->addChild(test_sprite);

	return true;
}

Scene* Title::createScene()
{
	// シーンを自動作成
	auto scene = Scene::create();

	//レイヤーを自動作成
	auto layer = Title::create();

	//シーンの子としてレイヤーを追加
	scene->addChild(layer);

	//シーンを返す
	return scene;
}

//シーン切り替え処理
void Title::sceneChange(float delta)
{
	// 次のシーンを設定
	Scene* nextScene = HelloWorld::createScene();

	// フェード時間設定
	float duration = 2.0f;

	// フェードイン　効果の設定
	Scene* pFade = TransitionFade::create(duration, nextScene);

	// 移動
	Director::sharedDirector()->replaceScene(pFade);
}