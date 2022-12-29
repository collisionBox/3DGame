#pragma once
class Director final
{
public:

	static void Initalize();// 初期化
	static void Finalize();// 終了処理
	static void Update(float deltaTime);// 更新
	static void Draw();// 描画
private:
	Director();
	~Director();

	static Director* Instance;
};

