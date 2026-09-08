// =======================================
//  ライブラリ読込
// =======================================
#include <ctime>		// 標準C ライブラリ ヘッダー <time.h>
#include <cstdlib>
#include <cmath>

#include "DxLib.h"		// DxLib
#include "state.h"      // ゲーム状態列挙

//	定数の宣言
#define WINDOW_W 1280	// 画面サイズ　横
#define WINDOW_H 720	// 画面サイズ　縦

// プレイヤー／敵用定数
#define PLAYER_SIZE 28
#define PLAYER_SPEED 4.0
#define ENEMY_RADIUS 18
#define ENEMY_SPEED 2.2
#define ENEMY_DETECT_RADIUS 220.0	// 発見距離
#define ENEMY_LOSE_RADIUS 260.0	// 見失う距離
#define ENEMY_ATTACK_RADIUS 40.0	// 攻撃判定

#define ENEMY_IDLE_TIME 3.0	// Idle から Patrol へ移行する時間（秒）
#define ENEMY_PATROL_RETARGET 3.5	// Patrol 中に目標を再設定する時間
#define ENEMY_SEARCH_TIME 5.0	// Search の最大時間
#define ENEMY_ATTACK_COOLDOWN 1.0	// 攻撃間隔（秒）

// 敵 AI 状態
enum EnemyState
{
    EIdle,
    EPatrol,
    EChase,
    EAttack,
    ESearch,
};


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

	// プレイヤーと敵の初期位置・AI 初期化
	float playerX = WINDOW_W / 2.0f;
	float playerY = WINDOW_H / 2.0f;
	float enemyX = WINDOW_W / 4.0f;
	float enemyY = WINDOW_H / 2.0f;
	EnemyState enemyState = EIdle;
	clock_t enemyStateStart = clock();
	float patrolTargetX = enemyX;
	float patrolTargetY = enemyY;
	float attackCooldown = 0.0f; // 攻撃クールダウン（秒）

	// 結果管理
	bool playerAlive = true;
	bool resultWin = false;
	clock_t inGameStartTime = 0;

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

				// InGame に入る直後の初期化
				if (gameState == InGame)
				{
					// プレイヤーと敵を初期位置に戻す
					playerX = WINDOW_W / 2.0f;
					playerY = WINDOW_H / 2.0f;
					enemyX = WINDOW_W / 4.0f;
					enemyY = WINDOW_H / 2.0f;
					enemyState = EIdle;
					enemyStateStart = now;
					patrolTargetX = enemyX;
					patrolTargetY = enemyY;
					attackCooldown = 0.0f;
					playerAlive = true;
					resultWin = false;
					inGameStartTime = now;
				}
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
        case InGame: {
            // ゲームプレイ処理：プレイヤー移動と敵 AI
            // プレイヤー入力（WASD）
            {
				float dx = 0.0f, dy = 0.0f;
				if (CheckHitKey(KEY_INPUT_W)) dy -= 1.0f;
				if (CheckHitKey(KEY_INPUT_S)) dy += 1.0f;
				if (CheckHitKey(KEY_INPUT_A)) dx -= 1.0f;
				if (CheckHitKey(KEY_INPUT_D)) dx += 1.0f;
				// 正規化
				if (dx != 0.0f || dy != 0.0f)
				{
					float len = sqrtf(dx*dx + dy*dy);
					dx = dx / len * PLAYER_SPEED;
					dy = dy / len * PLAYER_SPEED;
				}
				playerX += dx;
				playerY += dy;
				// 画面内に収める
				if (playerX < PLAYER_SIZE/2) playerX = PLAYER_SIZE/2;
				if (playerX > WINDOW_W - PLAYER_SIZE/2) playerX = WINDOW_W - PLAYER_SIZE/2;
				if (playerY < PLAYER_SIZE/2) playerY = PLAYER_SIZE/2;
				if (playerY > WINDOW_H - PLAYER_SIZE/2) playerY = WINDOW_H - PLAYER_SIZE/2;
			}

			// 敵 AI 更新
			{
				bool requestResult = false;
				bool resultIsWin = false;
				// 時間差分
				float dt = 1.0f / 60.0f; // 固定フレーム想定
				if (attackCooldown > 0.0f) attackCooldown -= dt;

				// 距離計算
				float vx = playerX - enemyX;
				float vy = playerY - enemyY;
				float dist = sqrtf(vx*vx + vy*vy);

				// 視認判定（単純化：距離のみ）
				bool canSee = (dist <= ENEMY_DETECT_RADIUS);
				bool lost = (dist > ENEMY_LOSE_RADIUS);
				bool inAttack = (dist <= ENEMY_ATTACK_RADIUS);

				switch (enemyState)
				{
				case EIdle:
					// 待機中にプレイヤーを発見したら追跡
					if (canSee)
					{
						enemyState = EChase;
						enemyStateStart = now;
					}
					else if (double(now - enemyStateStart) / CLOCKS_PER_SEC >= ENEMY_IDLE_TIME)
					{
						// 一定時間で巡回へ
						enemyState = EPatrol;
						enemyStateStart = now;
						// パトロール目標をランダムに設定
						patrolTargetX = (float)(rand() % (WINDOW_W - 60) + 30);
						patrolTargetY = (float)(rand() % (WINDOW_H - 60) + 30);
					}
					break;
				case EPatrol:
					// プレイヤー発見で追跡
					if (canSee)
					{
						enemyState = EChase;
						enemyStateStart = now;
					}
					// 目標へ向かう
					{
						float tx = patrolTargetX - enemyX;
						float ty = patrolTargetY - enemyY;
						float tl = sqrtf(tx*tx + ty*ty);
						if (tl > 1.0f)
						{
							enemyX += tx / tl * ENEMY_SPEED;
							enemyY += ty / tl * ENEMY_SPEED;
						}
					}
					// 一定時間で別の巡回目標へ
					if (double(now - enemyStateStart) / CLOCKS_PER_SEC >= ENEMY_PATROL_RETARGET)
					{
						enemyStateStart = now;
						patrolTargetX = (float)(rand() % (WINDOW_W - 60) + 30);
						patrolTargetY = (float)(rand() % (WINDOW_H - 60) + 30);
					}
					break;
				case EChase:
					// 攻撃範囲なら攻撃へ
					if (inAttack)
					{
						enemyState = EAttack;
						enemyStateStart = now;
					}
					// 見失ったら探索へ
					else if (lost)
					{
						enemyState = ESearch;
						enemyStateStart = now;
					}
					else
					{
						// プレイヤーへ追跡移動
						if (dist > 1.0f)
						{
							enemyX += vx / dist * ENEMY_SPEED;
							enemyY += vy / dist * ENEMY_SPEED;
						}
					}
					break;
				case EAttack:
					// 攻撃処理（クールダウンで再追跡など）
					if (!inAttack)
					{
						// 攻撃範囲外なら追跡へ
						enemyState = EChase;
						enemyStateStart = now;
					}
					else
					{
						// 攻撃が可能ならダメージ演出など（今回はテキスト）
						if (attackCooldown <= 0.0f)
						{
							attackCooldown = ENEMY_ATTACK_COOLDOWN;
							// 攻撃命中の簡易表示
							DrawFormatString(20, 80, GetColor(255, 100, 100), TEXT("敵が攻撃!"));
						}
					}
					break;
				case ESearch:
					// 探索中、一定時間で巡回へ
					if (canSee)
					{
						enemyState = EChase;
						enemyStateStart = now;
					}
					else if (double(now - enemyStateStart) / CLOCKS_PER_SEC >= ENEMY_SEARCH_TIME)
					{
						enemyState = EPatrol;
						enemyStateStart = now;
						patrolTargetX = (float)(rand() % (WINDOW_W - 60) + 30);
						patrolTargetY = (float)(rand() % (WINDOW_H - 60) + 30);
					}
					else
					{
						// 探索では少しランダムに移動
						float ang = (float)(rand() % 360) * 3.14159f / 180.0f;
						enemyX += cosf(ang) * ENEMY_SPEED * 0.5f;
						enemyY += sinf(ang) * ENEMY_SPEED * 0.5f;
					}
					break;
				}
			}

			// 描画：プレイヤーと敵
			DrawFormatString(20, 20, textColor, TEXT("状態: ゲーム中 (InGame)"));
			DrawFormatString(20, 50, textColor, TEXT("スペースキーでリザルトへ"));
			// プレイヤー（四角）
			DrawBox((int)(playerX - PLAYER_SIZE/2), (int)(playerY - PLAYER_SIZE/2), (int)(playerX + PLAYER_SIZE/2), (int)(playerY + PLAYER_SIZE/2), GetColor(50,200,255), TRUE);
			// 敵（円）
			DrawCircle((int)enemyX, (int)enemyY, ENEMY_RADIUS, GetColor(255,80,80), TRUE);
			// 敵状態表示
			const TCHAR* es = TEXT("Idle");
			switch (enemyState) { case EIdle: es = TEXT("Idle"); break; case EPatrol: es = TEXT("Patrol"); break; case EChase: es = TEXT("Chase"); break; case EAttack: es = TEXT("Attack"); break; case ESearch: es = TEXT("Search"); break; }
            DrawFormatString(20, 100, GetColor(200,200,100), TEXT("敵状態: %s"), es);
        }
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