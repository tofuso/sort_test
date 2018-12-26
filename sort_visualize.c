#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "sort_visualize.h"
#define ARRAY_NUM 10

void bubble_sort(int*, int);
void quick_sort(int*, int);
void _q_sort(int*, int, int);


/*
int型配列を監視して、ソートの様子を表示するプログラム
*/
int main() {
	//int arr[ARRAY_NUM] = { 24, 33, 22, 10, 22, 12, 55, 10, 100, 12 };
	int arr[ARRAY_NUM] = { 0,100,0,10,1,2,3,2,1,0 };
	
	start_sort(bubble_sort, arr, ARRAY_NUM);

	return 0;
}

void quick_sort(int* arr, int arr_num) {
	/*初期位置*/
	/*1つ目の項を左マーカーに設定*/
	/*最後の項を右マーカーに設定*/
	_q_sort(arr, 0, arr_num - 1);
}

/*クイックソート*/
void _q_sort(int* arr, int left, int right) {
	/*マーカーを設定*/
	int l_marker = left;
	int r_marker = right;
	int pivot = arr[right];
	while (1) {
		/*左マーカー値がピボット値より大きくなるまで右へ移動*/
		while (arr[l_marker] < pivot) {
			l_marker++;
		}
		/*右マーカー値がピボット値より小さくなるまで左へ移動*/
		while (arr[r_marker] > pivot) {
			r_marker--;
		}
		if (l_marker == r_marker) {
			/*右マーカーと左マーカーが被ったら探索終了*/
			break;
		}
		else if (l_marker > r_marker) {
			/*右マーカーと左マーカーが超えてしまったら、一つ巻き戻して探索終了*/
			l_marker--;
			r_marker++;
			break;
		}
		else {
			/*arr[r_marker]<=arr[pivot]<=arr[l_marker]のときは左右マーカーを入れ替え*/
			visualize_swap(arr + l_marker, arr + r_marker);
			/*それぞれのマーカーを一つ進める*/
			l_marker++;
			r_marker--;
		}
	}
	if (left < r_marker - 1) {
		/*左端と右マーカから一つ左へ移動したものが重なったり、超えていなければ左領域に再帰的実行*/
		_q_sort(arr, left, r_marker - 1);
	}
	if (right > l_marker + 1) {
		/*右端と左マーカーから右へ一つ移動したものが、重なったり超えてなければ右領域に再帰的実行*/
		_q_sort(arr, l_marker + 1, right);
	}

	return;
}

/*一般的なバブルソート*/
void bubble_sort(int* arr, int arr_num) {
	for (int i = 0; i < arr_num; i++) {
		for (int j = 0; j < arr_num - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				visualize_swap(arr + j, arr + j + 1);	/*入れ替え*/
			}
		}
	}

	return;
}
