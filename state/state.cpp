// =======================================
//  ライブラリ読込
// =======================================
#include <ctime>		// 標準C ライブラリ ヘッダー <time.h>

#include "DxLib.h"		// DxLib
#include "state.h"      // ゲーム状態列挙

//	定数の宣言
#define WINDOW_W 1280	// 画面サイズ　横
#define WINDOW_H 720	// 画面サイズ　縦


// ------------------------------
// WinMain
// ------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	// =======================================
	//  初期化処理
	// =======================================
	// ログの書き出しを無効化
	SetOutApplicationLogValidFlag(FALSE);	// ログの書き出しを無効化

	// ウィンドウモードの設定
	ChangeWindowMode(TRUE);					// ウインドウモードを有効化

	// ウィンドウサイズとカラービットの設定
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	// ウィンドウのタイトル
	SetMainWindowText(TEXT("DxLib Template"));
	// 背景色の設定
	SetBackgroundColor(128, 128, 128);
	
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)	
	{
		return -1;							// エラーが起きたら直ちに終了
	}

	// ウィンドウ描画モード設定
	SetDrawScreen(DX_SCREEN_BACK);			// 裏画面に描画する

	

	// ゲーム状態の初期化
	GameState gameState = Startup;            // 現在のゲーム状態
	clock_t stateStartTime = clock();         // 状態開始時刻
	bool prevSpacePressed = false;            // スペースの前フレーム状態

	// ------------------------------
	//  ゲームループ
	// ------------------------------
	while (ProcessMessage() == 0)
	{
		// リフレッシュレートを設定するための処理
		clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;

		// マウスカーソル表示設定
		SetMouseDispFlag(FALSE);

		// printfDxの初期化
		clsDx();

		// 画面上の描画を初期化（画面を消去）
		ClearDrawScreen();


		// =======================================
		//  入力処理
		// =======================================
		// スペースキーが押された瞬間を検出して状態を進める
		bool spacePressed = (CheckHitKey(KEY_INPUT_SPACE) != 0);
		bool spaceJustPressed = (spacePressed && !prevSpacePressed);




		// =======================================
		//  状態更新と画面描画処理
		// =======================================
		// 状態ごとの更新
		clock_t now = clock();
		double elapsed = double(now - stateStartTime) / CLOCKS_PER_SEC;

		if (gameState == Startup)
		{
			// Startup は自動で 2 秒後にタイトルへ遷移
			if (elapsed >= 2.0)
			{
				gameState = Title;
				stateStartTime = now;
			}
		}
		else
		{
			// スペースで次の状態へ移行（Title->MainMenu->InGame->Result->Title のループ）
			if (spaceJustPressed)
			{
				switch (gameState)
				{
				case Title: gameState = MainMenu; break;
				case MainMenu: gameState = InGame; break;
				case InGame: gameState = Result; break;
				case Result: gameState = Title; break;
				default: gameState = Title; break;
				}
				stateStartTime = now;
			}
		}

		// 画面描画
		const int textColor = GetColor(255, 255, 255);
		switch (gameState)
		{
		case Startup:
			DrawFormatString(20, 20, textColor, TEXT("状態: 起動中 (Startup)"));
			DrawFormatString(20, 50, textColor, TEXT("自動的にタイトルに移動します: %.1f 秒経過"), elapsed);
			break;
		case Title:
			DrawFormatString(20, 20, textColor, TEXT("状態: タイトル (Title)"));
			DrawFormatString(20, 50, textColor, TEXT("スペースキーでメインメニューへ"));
			break;
		case MainMenu:
			DrawFormatString(20, 20, textColor, TEXT("状態: メインメニュー (MainMenu)"));
			DrawFormatString(20, 50, textColor, TEXT("スペースキーでゲーム開始へ"));
			break;
		case InGame:
			DrawFormatString(20, 20, textColor, TEXT("状態: ゲーム中 (InGame)"));
			DrawFormatString(20, 50, textColor, TEXT("スペースキーでリザルトへ"));
			break;
		case Result:
			DrawFormatString(20, 20, textColor, TEXT("状態: リザルト (Result)"));
			DrawFormatString(20, 50, textColor, TEXT("スペースキーでタイトルへ戻る"));
			break;
		}

        // ステータス表示（デバッグ用）
        DrawFormatString(20, WINDOW_H - 40, textColor, TEXT("ESCで終了 | 現在の状態: %d | 経過: %.2f s"), (int)gameState, elapsed);





		// =======================================
		//  音声再生処理
		// =======================================

		




		// リフレッシュレートが一定になるまで待つ処理
		while (clock() < check_fps) {}

		// 裏画面の描画を表に反映
		ScreenFlip();


		// ESCキーでループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		// 前フレームのキー状態を保存
		prevSpacePressed = spacePressed;

	}

	// =======================================
	//  終了処理
	// =======================================
	// ＤＸライブラリ使用の終了処理
	DxLib_End();							// ＤＸライブラリ使用の終了処理

	// ソフトの終了
	return 0;			 
}