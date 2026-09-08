#pragma once

// ゲームの状態を表す列挙型
// - コメントや画面表示は日本語で行います
enum GameState
{
    // 起動処理中（ローディング等）
    Startup,
    // タイトル画面
    Title,
    // メインメニュー
    MainMenu,
    // ゲームプレイ中
    InGame,
    // 結果表示（リザルト）
    Result,
};
