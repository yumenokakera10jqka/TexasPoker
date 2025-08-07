#pragma once


#define ROUND_MAX 4		//ラウンド数
#define PLAYER_MAX 4	//プレイヤー数
#define HANDCARD_MAX 2	//ハンドカードの最大枚数
#define TABLECARD_MAX 5 //テーブルカードの最大枚数
#define CARDSET_MAX ( HANDCARD_MAX + TABLECARD_MAX )	//ハンドカードとテーブルカードの最大合計枚数
														//ここからYAKUCARD_NUM枚数を選んで役を作る
#define YAKUCARD_NUM 5			//役を作るときに対象となるカードの枚数
#define TABLECARD_MINNUM 3		//テーブルにカードがある場合の最小枚数

