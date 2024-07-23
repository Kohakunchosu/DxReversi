#pragma once

#include <DxLib.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <unordered_map>
#include <list>
#include <string>

// 柔軟な操作が可能な仮想のスクリーンであり、どこにどの画像がどのように配置されているのかといった情報を含むことができる。
class Screen
{
public:
	// コンストラクタ
	Screen();

	// 仮想画面上に画像の左上と右下の座標を指定して画像を追加する。
	int Add(const char* file_path, int x1, int y1, int x2, int y2);

	// 仮想画面上に画像の中心点を位置座標として画像を追加する。
	int AddWithC(const char* file_path, int width, int high, int x, int y, float angle);

	// 仮想画面上に円を追加する
	int AddCircle(int r, int x, int y, int color, int fill_flag = TRUE);

	// 仮想画面上に文字列を追加する
	int AddString(int x, int y, int color, const char* string, ...);

	// フォントハンドルをもとに、文字列を追加
	int AddStringToHandle(int x, int y, int color, int font_handle, const char* string, ...);

	int AddStringToHandleWithC(int x, int y, int color, int font_handle, const char* string, ...);

	int AddStringWithC(int x, int y, int color, const char* string, ...);

	// 特定の文字列の色を変更する
	void ChangeStringColor(int handle, int color);

	//  ハンドルで指定した特定のグラフを移動する。文字列の移動は不可。
	void Move(int handle, int x, int y, float angle);

	// 指定されたグラフを最前面に移動
	void ToFront(int handle);

	// 指定されたグラフを最背面に移動
	void ToBack(int handle);

	// ハンドルで指定した特定のグラフを削除する
	void Remove(int handle);

	// スクリーン上のグラフの個数を返す
	int GetGraphNum();

	// 仮想画面(Screen型オブジェクト)を実際のスクリーンに映し出す
	void Display();

	// 仮想画面をリセットする。
	void Reset();

	// 画像のキャッシュデータを削除する。パフォーマンスに大きな影響を及ぼすため、むやみに使うべきではない。
	void ClearCache();

private:
	// 画像ファイル名とその画面上での表示のされ方を、セットで格納するためのもの。
	class Graph
	{
	public:
		// 画像のファイルパス
		// ファイル名がNULL文字の場合、図形の追加だとみなす
		char file_path[100] = { '\0' };

		int x[4], y[4];

		int width;

		int high;

		int graph_type = 0;

		// 追加されたものが図形だった場合の形
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
