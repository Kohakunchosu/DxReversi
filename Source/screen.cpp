#include <DxLib.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <unordered_map>
#include <list>
#include <string>
#include "screen.h"

int Screen::AddStringToHandleWithC(int x, int y, int color, int font_handle, const char* string, ...)
{
	va_list arg;

	va_start(arg, string);

	char str[256];

	vsprintf_s(str, string, arg);

	va_end(arg);

	Graph graph;

	int width = GetDrawStringWidth((TCHAR*)string, strlen(str));

	graph.graph_type = STR_HD;

	graph.string_hd.string.assign(str);

	graph.string_hd.color = color;

	graph.string_hd.handle = font_handle;

	graph.string_hd.x = x - (width / 2);

	graph.string_hd.y = y;

	// ハンドル生成
	int new_handle = GenerateHandle();

	// ハンドルとグラフのセットに追加
	handle_graph_set[new_handle] = graph;

	// グラフの重ね合わせをハンドルの順序として保存
	handle_list.emplace_back(new_handle);

	return new_handle;
}

int Screen::AddStringToHandle(int x, int y, int color, int font_handle, const char* string, ...)
{
	va_list arg;

	va_start(arg, string);

	char str[256];

	vsprintf_s(str, string, arg);

	va_end(arg);

	Graph graph;

	graph.graph_type = STR_HD;

	graph.string_hd.string.assign(str);

	graph.string_hd.color = color;

	graph.string_hd.handle = font_handle;

	graph.string_hd.x = x;

	graph.string_hd.y = y;

	// ハンドル生成
	int new_handle = GenerateHandle();

	// ハンドルとグラフのセットに追加
	handle_graph_set[new_handle] = graph;

	// グラフの重ね合わせをハンドルの順序として保存
	handle_list.emplace_back(new_handle);

	return new_handle;
}

void Screen::ChangeStringColor(int handle, int color)
{
	handle_graph_set[handle].string.color = color;
}

int Screen::AddString(int x, int y, int color, const char* string, ...)
{
	va_list arg;

	va_start(arg, string);

	char str[256];

	vsprintf_s(str, string, arg);

	va_end(arg);

	Graph graph;

	graph.graph_type = STR;

	graph.string.string.assign(str);

	graph.string.color = color;

	graph.string.x = x;

	graph.string.y = y;

	// ハンドル生成
	int new_handle = GenerateHandle();

	// ハンドルとグラフのセットに追加
	handle_graph_set[new_handle] = graph;

	// グラフの重ね合わせをハンドルの順序として保存
	handle_list.emplace_back(new_handle);

	return new_handle;
}

int Screen::AddStringWithC(int x, int y, int color, const char* string, ...)
{
	va_list arg;

	va_start(arg, string);

	char str[256];

	vsprintf_s(str, string, arg);

	va_end(arg);

	Graph graph;

	graph.graph_type = STR;

	graph.string.string.assign(str);

	int width = GetDrawStringWidth((TCHAR*)string, strlen(str));

	graph.string.color = color;

	graph.string.x = x - (width / 2);

	graph.string.y = y;

	// ハンドル生成
	int new_handle = GenerateHandle();

	// ハンドルとグラフのセットに追加
	handle_graph_set[new_handle] = graph;

	// グラフの重ね合わせをハンドルの順序として保存
	handle_list.emplace_back(new_handle);

	return new_handle;
}

void Screen::ToBack(int handle)
{
	handle_list.remove(handle);
	handle_list.emplace_front(handle);
}

void Screen::ToFront(int handle)
{
	handle_list.remove(handle);
	handle_list.emplace_back(handle);
}

int Screen::AddCircle(int r, int x, int y, int color, int fill_flag)
{
	Graph graph;

	graph.graph_type = CIRCLE;
	graph.circle.r = r;
	graph.circle.x = x;
	graph.circle.y = y;
	graph.circle.color = color;
	graph.circle.fill_flag = fill_flag;

	// ハンドル生成
	int new_handle = GenerateHandle();

	// ハンドルとグラフのセットに追加
	handle_graph_set[new_handle] = graph;

	// グラフの重ね合わせをハンドルの順序として保存
	handle_list.emplace_back(new_handle);

	return new_handle;
}

void Screen::Move(int handle, int x, int y, float angle)
{
	float x1[4], y1[4];

	// 左上点
	x1[0] = (float)x - (float)handle_graph_set[handle].width / 2.0;
	y1[0] = (float)y - (float)handle_graph_set[handle].high / 2.0;

	// 右下点
	x1[2] = (float)x + (float)handle_graph_set[handle].width / 2.0;
	y1[2] = (float)y + (float)handle_graph_set[handle].high / 2.0;

	// 左下点
	x1[3] = x1[0];
	y1[3] = y1[2];

	// 右上点
	x1[1] = x1[2];
	y1[1] = y1[0];

	float r = pow((float)handle_graph_set[handle].width * (float)handle_graph_set[handle].width +
		(float)handle_graph_set[handle].high * (float)handle_graph_set[handle].high,
		1.0 / 2.0) /
		2.0;

	angle = (angle / 360.0) * 2 * 3.14159265;

	for (int i = 0; i < 4; i++)
	{
		float nx, ny;
		nx = (cos(angle) * (x1[i] - x) - sin(angle) * (y1[i] - y)) + x;
		ny = (sin(angle) * (x1[i] - x) + cos(angle) * (y1[i] - y)) + y;

		x1[i] = nx;
		y1[i] = ny;
	}

	for (int i = 0; i < 4; i++)
	{
		handle_graph_set[handle].x[i] = x1[i];
		handle_graph_set[handle].y[i] = y1[i];
	}
}

int Screen::AddWithC(const char* file_path, int width, int high, int x, int y, float angle)
{
	Graph graph;

	strncpy_s(graph.file_path, file_path, 100);

	graph.width = width;
	graph.high = high;

	float x1[4], y1[4];

	// 左上点
	x1[0] = (float)x - (float)width / 2.0;
	y1[0] = (float)y - (float)high / 2.0;

	// 右下点
	x1[2] = (float)x + (float)width / 2.0;
	y1[2] = (float)y + (float)high / 2.0;

	// 左下点
	x1[3] = x1[0];
	y1[3] = y1[2];

	// 右上点
	x1[1] = x1[2];
	y1[1] = y1[0];

	float r = pow((float)width * (float)width + (float)high * (float)high, 1.0 / 2.0) / 2.0;

	angle = (angle / 360.0) * 2 * 3.14159265;

	for (int i = 0; i < 4; i++)
	{
		float nx, ny;
		nx = (cos(angle) * (x1[i] - x) - sin(angle) * (y1[i] - y)) + x;
		ny = (sin(angle) * (x1[i] - x) + cos(angle) * (y1[i] - y)) + y;

		x1[i] = nx;
		y1[i] = ny;
	}

	for (int i = 0; i < 4; i++)
	{
		graph.x[i] = x1[i];
		graph.y[i] = y1[i];
	}

	// ハンドル生成
	int new_handle = GenerateHandle();

	// ハンドルとグラフのセットに追加
	handle_graph_set[new_handle] = graph;

	// グラフの重ね合わせをハンドルの順序として保存
	handle_list.emplace_back(new_handle);

	return new_handle;
}

void Screen::ClearCache()
{
	InitGraph();
	imageCache.clear();
	imageList.clear();
}

void Screen::Remove(int handle)
{
	handle_graph_set.erase(handle);

	handle_list.remove(handle);
}

int Screen::GenerateHandle()
{
	static int init = 1;
	static int new_handle = 0;

	if (init)
	{
		init = 0;
		return new_handle;
	}

	// 新たに生成したハンドルが既存のハンドルと被っていないか確認
	// かぶっていなければループを抜ける
	// かぶっていた場合ハンドルを変更してまた確認 ...

	for (;;)
	{
		new_handle++;
		if (handle_graph_set.find(new_handle) == handle_graph_set.end())
		{
			break;
		}
	}

	return new_handle;
}

Screen::Screen()
{
	SetDrawScreen(DX_SCREEN_BACK);
}

void Screen::Reset()
{
	handle_graph_set.clear();
	handle_list.clear();
}

void Screen::Display()
{
	ClearDrawScreen();

	for (int i : handle_list)
	{
		// グラフタイプが画像ならキャッシュとる
		if (handle_graph_set[i].graph_type == IMAGE)
		{
			int g_handle;

			// キャッシング処理、キャッシュされてる画像は新たにromから読み込まない
			auto it = imageCache.find(handle_graph_set[i].file_path);
			if (it != imageCache.end())
			{
				g_handle = it->second->second;
				imageList.splice(imageList.begin(), imageList, it->second);
			}
			else
			{
				TCHAR* filePath = (TCHAR*)handle_graph_set[i].file_path;
				g_handle = LoadGraph((TCHAR*)handle_graph_set[i].file_path);

				if (imageCache.size() >= MAX_CACHE_SIZE)
				{
					DeleteGraph(imageList.back().second);
					imageCache.erase(imageList.back().first);
					imageList.pop_back();
				}

				imageList.emplace_front(handle_graph_set[i].file_path, g_handle);
				imageCache[handle_graph_set[i].file_path] = imageList.begin();
			}

			DrawModiGraph(handle_graph_set[i].x[0], handle_graph_set[i].y[0], handle_graph_set[i].x[1], handle_graph_set[i].y[1],
				handle_graph_set[i].x[2], handle_graph_set[i].y[2], handle_graph_set[i].x[3], handle_graph_set[i].y[3],
				g_handle, TRUE);
		}

		if (handle_graph_set[i].graph_type == CIRCLE)
		{
			DrawCircle(handle_graph_set[i].circle.x, handle_graph_set[i].circle.y, handle_graph_set[i].circle.r,
				handle_graph_set[i].circle.color, handle_graph_set[i].circle.fill_flag);
		}

		if (handle_graph_set[i].graph_type == STR)
		{
			DrawString(handle_graph_set[i].string.x, handle_graph_set[i].string.y,
				(TCHAR*)handle_graph_set[i].string.string.c_str(),
				handle_graph_set[i].string.color);
		}

		if (handle_graph_set[i].graph_type == STR_HD)
		{
			DrawStringToHandle(handle_graph_set[i].string_hd.x, handle_graph_set[i].string_hd.y,
				(TCHAR*)handle_graph_set[i].string_hd.string.c_str(),
				handle_graph_set[i].string_hd.color,
				handle_graph_set[i].string_hd.handle);
		}
	}

	ScreenFlip();
}

int Screen::Add(const char* file_path, int x1, int y1, int x2, int y2)
{
	Graph graph;

	strncpy_s(graph.file_path, file_path, 100);

	graph.x[0] = x1;
	graph.y[0] = y1;

	graph.x[2] = x2;
	graph.y[2] = y2;

	// 左下点
	graph.x[3] = graph.x[0];
	graph.y[3] = graph.y[2];

	// 右上点
	graph.x[1] = graph.x[2];
	graph.y[1] = graph.y[0];

	graph.width = abs(x2 - x1);
	graph.high = abs(y2 - y1);

	// ハンドル生成
	int new_handle = GenerateHandle();

	// ハンドルとグラフのセットに追加
	handle_graph_set[new_handle] = graph;

	// グラフの重ね合わせをハンドルの順序として保存
	handle_list.emplace_back(new_handle);

	return new_handle;
}

int Screen::GetGraphNum()
{
	return (int)handle_list.size();
}
