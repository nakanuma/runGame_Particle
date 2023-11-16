#include <Novice.h>
#include "Vector2.h"

// Emitter //
#include "FlyingEmitter.h"
#include "RunningEmitter.h"
#include "PlayerDeadEmitter.h"
#include "ClearEmitter.h"
#include "PlayerReviveEmitter.h"

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
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// プレイヤーの定義
	Player player{
		{640,360},
		42,
		4
	};

	// エミッターのインスタンスを生成
	FlyingEmitter flyingEmitter;
	RunningEmitter runningEmitter;
	PlayerDeadEmitter playerDeadEmitter;
	ClearEmitter clearEmitter;
	PlayerReviveEmitter playerReviveEmitter;

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
			runningEmitter.Update({ player.pos.x,player.pos.y + (player.size - 9.0f) }); // プレイヤーの左下から出るよう調整
		}

		if (currentPlayerMode == FLYING) { // 飛行モード
			flyingEmitter.Update({ player.pos.x + (player.size / 2),player.pos.y + (player.size / 2) }); //中心位置を調整
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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//// エミッターの描画処理
		//if (currentPlayerMode == RUNNING) { //ランモード
		//	runningEmitter.Draw();
		//}

		//if (currentPlayerMode == FLYING) { //飛行モード
		//	flyingEmitter.Draw();
		//}

		playerDeadEmitter.Draw();
		/*clearEmitter.Draw();*/

		playerReviveEmitter.Draw();

		// プレイヤーの描画
		Novice::DrawBox(
			(int)player.pos.x, (int)player.pos.y,
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
