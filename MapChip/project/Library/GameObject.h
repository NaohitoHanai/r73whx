#pragma once
/// <summary>
/// �Q�[���I�u�W�F�N�g�̊��N���X
/// </summary>
/// <author>N.Hanai</author>

#include <DxLib.h>
#include <string>
#include "SceneBase.h"
#include "ObjectManager.h"
#include "Time.h"

class GameObject
{
public:
	GameObject() : tag(""), destroy(false), drawOrder(0) { ObjectManager::Push(this); }
	virtual ~GameObject() {}

	/// <summary>
	/// ���t���[���̍X�V�����̂��߂ɌĂ΂�܂�
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// ���t���[���̕`�揈���̂��߂ɌĂ΂�܂�
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// �����̃C���X�^���X���폜���鎞�ɌĂяo���Ă�������
	/// �����Update�̑O�ɍ폜����܂�
	/// </summary>
	void DestroyMe() { destroy = true; }

	bool DestroyRequested() { return destroy; }

	/// <summary>
	/// �`��̗D�揇�ʂ��w�肵�܂�
	/// ���l�������قǁA�ォ��`�悳���̂ŁA
	/// 2D�ł���΁A��O�ɕ\������܂�
	/// �����w�肵�Ȃ���΂O�ł�
	/// </summary>
	/// <param name="odr">�`�揇��</param>
	void SetDrawOrder(int order) {
		drawOrder = order;
		ObjectManager::SortByDrawOrder();
	}

	inline int GetDrawOrder() {	return drawOrder; }

	/// <summary>
	/// �^�O������
	/// �^�O�͂P�����t���邱�Ƃ��ł��܂�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	void SetTag(std::string _tag) { tag = _tag; }

	/// <summary>
	/// �w�肳�ꂽ�^�O�Ɠ�������Ԃ�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	/// <returns>�����ł����true</returns>
	bool IsTag(std::string _tag) const { return tag == _tag; }
private:
	std::string tag;     // �^�O
	bool destroy;
	int drawOrder;
};
