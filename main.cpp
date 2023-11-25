#include <Novice.h>
#include "Vector2.h"

// Emitter //
#include "FlyingEmitter.h"
#include "RunningEmitter.h"
#include "PlayerDeadEmitter.h"
#include "ClearEmitter.h"
#include "PlayerReviveEmitter.h"
#include "BackGroundEmitter.h"
#include "GetCoinEmitter.h"
#include "ModeChangeEmitter.h"
#include "CheckPointEmitter.h"
#include "ModeChangeEmitter2.h"

const char kWindowTitle[] = "LC1A_18_ナカヌマカツシ_タイトル";

// プレイヤー構造体
struct Player {
	Vector2 pos;
	int size;
	int speed;
};

// プレイヤーのモード
enum PlayerMode {
	RUNNING,
	FLYING
};

// プレイヤーの現在のモード
PlayerMode currentPlayerMode = RUNNING;

// プレイヤーの更新処理を行う関数
void PlayerUpdate(Player& player, char* keys) {
	// キー入力による移動処理
	if (keys[DIK_W]) {
		player.pos.y -= player.speed;
	}

	if (keys[DIK_S]) {
		player.pos.y += player.speed;
	}

	if (keys[DIK_A]) {
		player.pos.x -= player.speed;
	}

	if (keys[DIK_D]) {
		player.pos.x += player.speed;
	}

	// モード変更
	if (keys[DIK_1]) {
		currentPlayerMode = RUNNING;
	}

	if (keys[DIK_2]) {
		currentPlayerMode = FLYING;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 756);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// プレイヤーの定義
	Player player{
		{320,588},
		42,
		8
	};

	int camera = 0;

	// エミッターのインスタンスを生成
	FlyingEmitter flyingEmitter;
	RunningEmitter runningEmitter;
	PlayerDeadEmitter playerDeadEmitter;
	ClearEmitter clearEmitter;
	PlayerReviveEmitter playerReviveEmitter;
	BackGroundEmitter backGroundEmitter;
	GetCoinEmitter getCoinEmitter;
	ModeChangeEmitter modeChangeEmitter;
	CheckPointEmitter checkPointEmitter;
	ModeChangeEmitter2 modeChangeEmitter2;

	// 画像読み込み
	int bgGH = Novice::LoadTexture("./images/bg.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// プレイヤーの更新処理
		PlayerUpdate(player, keys);

		// エミッターの更新処理
		if (currentPlayerMode == RUNNING) { // ランモード
			runningEmitter.Update({ player.pos.x,player.pos.y + (player.size - 10.0f) }); // プレイヤーの左下から出るよう調整
		}

		if (currentPlayerMode == FLYING) { // 飛行モード
			flyingEmitter.Update({ player.pos.x + (player.size / 2),player.pos.y + (player.size / 2) }); //中心位置を調整
		}

		// カメラの移動処理
		if (keys[DIK_A]) {
			camera -= player.speed;
		}
		if (keys[DIK_D]) {
			camera += player.speed;
		}

		// 死亡時パーティクルのエミッター更新処理
		playerDeadEmitter.Update();

		// キーが押された（ゲームではプレイヤーが死亡した）際に死亡パーティクルを生成
		if (keys[DIK_P] && !preKeys[DIK_P]) {
			playerDeadEmitter.Emit({ player.pos.x + player.size / 2,player.pos.y + player.size / 2 }); // 中心座標を合わせる
		}

		// クリアパーティクルのエミッター更新処理
		clearEmitter.Update();

		// プレイヤー復活エミッターの更新処理
		playerReviveEmitter.Update();

		if (keys[DIK_R] && !preKeys[DIK_R]) {
			playerReviveEmitter.Emit({ player.pos.x + player.size / 2,player.pos.y + player.size / 2 });
		}

		// 背景エミッターの更新処理
		backGroundEmitter.Update(player.pos);

		// コイン取得エミッターの更新処理
		getCoinEmitter.Update();
		if (keys[DIK_C] && !preKeys[DIK_C]) {
			getCoinEmitter.Emit({ player.pos.x + player.size / 2, player.pos.y + player.size / 2 });
		}

		// モード変更エミッターの更新処理
		modeChangeEmitter.Update({ 0,0 });
		modeChangeEmitter2.Update({ 0,0 });
		if (keys[DIK_B] && !preKeys[DIK_B]) {
			modeChangeEmitter.Emit({ player.pos.x + player.size / 2, player.pos.y + player.size / 2 });
			modeChangeEmitter2.Emit({ player.pos.x + player.size / 2, player.pos.y + player.size / 2 });
		}

		// チェックポイントエミッターの更新処理
		checkPointEmitter.Update();
		if (keys[DIK_G] && !preKeys[DIK_G]) {
			checkPointEmitter.Emit({ player.pos.x + player.size / 2, player.pos.y + player.size / 2 });
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*clearEmitter.Draw();*/

		playerReviveEmitter.Draw();

		// 背景の描画（見た目だけ）
		Novice::DrawSprite(
			0 - camera, 0,
			bgGH,
			1.0f, 1.0f,
			0.0f,
			0xFFFFFFFF
		);

		// 床の描画（見た目だけ）
		Novice::DrawBox(
			0 - camera, 630,
			3840, 126,
			0.0f,
			BLACK,
			kFillModeSolid
		);

		// 背景エミッターの描画処理
		/*backGroundEmitter.Draw(camera);*/

		playerDeadEmitter.Draw();

		getCoinEmitter.Draw();

		modeChangeEmitter.Draw(camera);
		modeChangeEmitter2.Draw(camera);

		checkPointEmitter.Draw(camera);

		//// エミッターの描画処理
		//if (currentPlayerMode == RUNNING) { //ランモード
		//	runningEmitter.Draw(camera);
		//}

		//if (currentPlayerMode == FLYING) { //飛行モード
		//	flyingEmitter.Draw(camera);
		//}

		// プレイヤーの描画
		Novice::DrawBox(
			(int)player.pos.x - camera, (int)player.pos.y,
			player.size, player.size,
			0.0f,
			WHITE,
			kFillModeSolid
		);

		// デバッグ用
		if (currentPlayerMode == RUNNING) {
			Novice::ScreenPrintf(0, 0, "Mode:RUNNING");
		}
		if (currentPlayerMode == FLYING) {
			Novice::ScreenPrintf(0, 0, "Mode:FLYING");
		}

		Novice::ScreenPrintf(0, 20, "x:%.f y:%.f", player.pos.x, player.pos.y);
		/*Novice::ScreenPrintf(0, 40, "camera:%d", camera);*/

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
