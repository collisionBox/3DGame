#pragma once
class Director final
{
public:

	static void Initalize();// ������
	static void Finalize();// �I������
	static void Update(float deltaTime);// �X�V
	static void Draw();// �`��
private:
	Director();
	~Director();

	static Director* instance;
};

