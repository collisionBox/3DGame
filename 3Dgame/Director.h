#pragma once
class Director final
{
public:

	static void Initalize();// ‰Šú‰»
	static void Finalize();// I—¹ˆ—
	static void Update(float deltaTime);// XV
	static void Draw();// •`‰æ
private:
	Director();
	~Director();

	static Director* instance;
};

