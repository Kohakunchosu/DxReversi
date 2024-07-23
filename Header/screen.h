#pragma once

#include <DxLib.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <unordered_map>
#include <list>
#include <string>

// �_��ȑ��삪�\�ȉ��z�̃X�N���[���ł���A�ǂ��ɂǂ̉摜���ǂ̂悤�ɔz�u����Ă���̂��Ƃ����������܂ނ��Ƃ��ł���B
class Screen
{
public:
	// �R���X�g���N�^
	Screen();

	// ���z��ʏ�ɉ摜�̍���ƉE���̍��W���w�肵�ĉ摜��ǉ�����B
	int Add(const char* file_path, int x1, int y1, int x2, int y2);

	// ���z��ʏ�ɉ摜�̒��S�_���ʒu���W�Ƃ��ĉ摜��ǉ�����B
	int AddWithC(const char* file_path, int width, int high, int x, int y, float angle);

	// ���z��ʏ�ɉ~��ǉ�����
	int AddCircle(int r, int x, int y, int color, int fill_flag = TRUE);

	// ���z��ʏ�ɕ������ǉ�����
	int AddString(int x, int y, int color, const char* string, ...);

	// �t�H���g�n���h�������ƂɁA�������ǉ�
	int AddStringToHandle(int x, int y, int color, int font_handle, const char* string, ...);

	int AddStringToHandleWithC(int x, int y, int color, int font_handle, const char* string, ...);

	int AddStringWithC(int x, int y, int color, const char* string, ...);

	// ����̕�����̐F��ύX����
	void ChangeStringColor(int handle, int color);

	//  �n���h���Ŏw�肵������̃O���t���ړ�����B������̈ړ��͕s�B
	void Move(int handle, int x, int y, float angle);

	// �w�肳�ꂽ�O���t���őO�ʂɈړ�
	void ToFront(int handle);

	// �w�肳�ꂽ�O���t���Ŕw�ʂɈړ�
	void ToBack(int handle);

	// �n���h���Ŏw�肵������̃O���t���폜����
	void Remove(int handle);

	// �X�N���[����̃O���t�̌���Ԃ�
	int GetGraphNum();

	// ���z���(Screen�^�I�u�W�F�N�g)�����ۂ̃X�N���[���ɉf���o��
	void Display();

	// ���z��ʂ����Z�b�g����B
	void Reset();

	// �摜�̃L���b�V���f�[�^���폜����B�p�t�H�[�}���X�ɑ傫�ȉe�����y�ڂ����߁A�ނ�݂Ɏg���ׂ��ł͂Ȃ��B
	void ClearCache();

private:
	// �摜�t�@�C�����Ƃ��̉�ʏ�ł̕\���̂�������A�Z�b�g�Ŋi�[���邽�߂̂��́B
	class Graph
	{
	public:
		// �摜�̃t�@�C���p�X
		// �t�@�C������NULL�����̏ꍇ�A�}�`�̒ǉ����Ƃ݂Ȃ�
		char file_path[100] = { '\0' };

		int x[4], y[4];

		int width;

		int high;

		int graph_type = 0;

		// �ǉ����ꂽ���̂��}�`�������ꍇ�̌`
		class Circle
		{
		public:
			int x;

			int y;

			int r;

			int color;

			int fill_flag;
		};

		class String
		{
		public:
			int x;

			int y;

			int color;

			std::string string;
		};

		class StringHd
		{
		public:
			int x;

			int y;

			int color;

			int handle;

			std::string string;
		};

		Circle circle;

		String string;

		StringHd string_hd;
	};

	const int MAX_CACHE_SIZE = 100;

	std::list<std::pair<std::string, int>> imageList;
	std::unordered_map<std::string, std::list<std::pair<std::string, int>>::iterator> imageCache;

	std::unordered_map<int, Graph> handle_graph_set;
	std::list<int> handle_list;

	const int IMAGE = 0;
	const int CIRCLE = 1;
	const int BOX = 2;
	const int STR = 3;
	const int STR_HD = 4;

	int GenerateHandle();
};
