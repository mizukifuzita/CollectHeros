//クラス：キャラクタークラス
//作成者：藤田  瑞稀			
//更新日：2015年6月12日
#pragma once

#include "cocos2d.h"

//キャラクタークラス
class Character : public cocos2d::Layer
{
private:
//メンバー変数
	cocos2d::Sprite* m_char;
	cocos2d::Point   m_pos;

public:
	Character();			//コンストラクタ
	~Character();			//デストラクタ

	void Initialize();		//初期化処理
	void Finalize();		//終了処理

	void Update();			//更新処理
	void Draw();			//描画処理
};