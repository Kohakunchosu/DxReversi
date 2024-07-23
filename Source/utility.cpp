#include "stdlib.h"
#include "funcs.h"

int Utility::Arr::Max(int* a, int yo)
{
	int max = a[0];

	for (int k = 0; k < yo; k++)
	{
		for (int k1 = 0; k1 < yo; k1++)
		{
			if (a[k1] > max)
			{
				max = a[k1];
			}
		}
	}
	return max;
}

int Utility::Arr::MaxIndex(int* a, int yo)
{
	int max = a[0];
	int nmax = 0;

	for (int k = 0; k < yo; k++)
	{
		if (a[k] > max)
		{
			max = a[k];
			nmax = k;
		}
	}
	return nmax;
}

// ÀÛg‚í‚ê‚Ä‚¢‚é‚Ì‚Í‚±‚Á‚¿
int Utility::Arr::MaxIndexRand(int arr[], int n)
{
	int Max = arr[0];
	int Maxn = 0;

	for (int i = 0; i < n; i++)
	{
		if (arr[i] > Max)
		{
			Max = arr[i];
			Maxn = i;
		}
	}

	int* num;
	num = new int[n];

	int ct = 0;

	// Å‘å’l‚ªŠÜ‚Ü‚ê‚é—v‘f‚ª‚Ù‚©‚É‚È‚¢‚©’Tõ
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == arr[Maxn])
		{
			num[ct] = i;
			ct++;
		}
	}

	return num[Utility::RandBetween(0, ct - 1)];
}

int Utility::Arr::Min(int* a, int yo)
{
	int min = a[0];

	for (int k = 0; k < yo; k++)
	{
		for (int k1 = 0; k1 < yo; k1++)
		{
			if (a[k1] < min)
			{
				min = a[k1];
			}
		}
	}
	return min;
}

float Utility::Arr::Ave(int arr[], int n)
{
	float sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
	}
	return sum / (float)n;
}

int Utility::Arr::Sum(int arr[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
	}
	return sum;
}

int Utility::RandBetween(int minimum, int maximum)
{
	return minimum + rand() % (maximum - minimum + 1);
}

float Utility::RandBetweenF(float min, float max)
{
	float random = ((float)rand() / (float)(RAND_MAX)) * (max - min) + min; // —”‚Ì¶¬
	return random;
}
