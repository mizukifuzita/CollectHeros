//クラス：タイトルシーンクラス
//作成者：藤田  瑞稀			
//更新日：2015年6月11日			

//二重インクルード防止
#pragma once

//.h(ヘッダーファイル)読み込み
#include "cocos2d.h"

//タイトルシーンクラス
class Title : public cocos2d::Layer
{
private:
//メンバー変数
	cocos2d::Sprite* m_title_s;						//メンバー変数					

public:
	
	virtual bool init();							//初期化処理

	static cocos2d::Scene* createScene();			//シーンの作成
	void sceneChange(float delta);					//シーン切り替え処理

	CREATE_FUNC(Title);
};