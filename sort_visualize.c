#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_visualize.h"

int _order_evaluation(int*, int);

int* watched_array;		/*監視対象の配列*/
int watched_array_num;	/*監視対象の配列の要素数*/

void start_sort(void(*sort_func)(int*, int), int* int_array, int array_num) {
	watched_array = int_array;			/*引数の配列を監視対象に加えるため、保管しておく。*/
	watched_array_num = array_num;
	/*初回、表示処理*/
	for (int i = 0; i < array_num; i++) {
		printf(" %5d", int_array[i]);
	}
	sort_func(int_array, array_num);	/*実行する*/

	/*終了を知らせる*/
	printf("\n");
	printf("完了\n");
	/*ソート結果を判定*/
	switch (_order_evaluation(int_array, array_num)) {
	case -1:
		printf("昇順降順の判定ができませんでした：失敗\n");
		break;
	case 1:
		printf("昇順：成功\n");
		break;
	case 2:
		printf("降順：成功\n");
		break;
	}

	return;
}

void visualize_swap(int* a, int* b) {
	/*視覚化された配列の入れ替えアニメーション*/
	int target1 = -1;	/*入れ替え対象その１のインデックス値*/
	int target2 = -1;	/*入れ替え対象その２のインデックス値*/
	/*引数に渡された対象のアドレスを検索*/
	for (int i = 0; i < watched_array_num; i++) {
		/*一致したらそのインデックス値を記録*/
		if (a == watched_array + i) {
			target1 = i;
		}
		else if (b == watched_array + i) {
			target2 = i;
		}
		else if (target1 != -1 && target2 != -1) {
			/*２つの対象についての検索を終えたら、検索終了*/
			break;
		}
	}
	/*アニメーションしつつ表示処理*/
	int frame = abs(target1 - target2) * 6 + 1;	/*アニメーションフレームを設定*/
	/*表示列を文字列情報に変換*/
	/*アニメーション行の表示に用いる文字列*/
	char* swapline = (char*)malloc(sizeof(char) * 6 * watched_array_num + 1);
	char damp_swapline[7];	/*アニメーション行に関連する文字列のキャッシュ*/
	for (int i = 0; i < watched_array_num; i++) {
		/*アニメーション行の表示に用いる文字列を作成*/
		sprintf(damp_swapline, " %-5d", watched_array[i]);
		if (i > 0) {
			strcat(swapline, damp_swapline);
		}
		else {
			strcpy(swapline, damp_swapline);
		}
	}
	/*入れ替え対象の文字列*/
	char target1_str[7];
	char target2_str[7];
	sprintf(target1_str, " %-5d", watched_array[target1]);
	sprintf(target2_str, " %-5d", watched_array[target2]);
	/*アニメーション*/
	int dir = (target2 - target1) / abs(target2 - target1);/*移動方向*/
	for (int i = 1; i < frame; i++) {
		/*入れ替え対象の表示を空白で塗りつぶして消去*/
		for (int j = 0; j < 5; j++) {
			swapline[target1 * 6 + i * dir + j] = ' ';
			swapline[target2 * 6 - i * dir + j] = ' ';
		}
		/*入れ替え対象の現フレームの位置に上書きで描画*/
		for (int j = 0; j < 5; j++) {
			swapline[target1 * 6 + i * dir + j] = target1_str[j];
			swapline[target2 * 6 - i * dir + j] = target2_str[j];
		}
		printf("\r%s", swapline);	/*描画*/
		Sleep(100);				/*待機*/
	}

	/*入れ替え処理*/
	int temp = *a;
	*a = *b;
	*b = temp;

	return;
}

/*
* 並び替えが成功しているか確認する
* @ return -1：失敗 1：昇順　2：降順
 */
int _order_evaluation(int* arr, int arr_num) {
	int order_mode = 0;		/*昇順：1 降順：-1　未判定：0*/
	int value1, value2;	/*昇順降順判定サンプル*/
	for (int i = 0; i < arr_num; i++) {
		/*２つの値をサンプルとして取得*/
		if (i == 0) {
			value1 = arr[i];
			continue;
		}
		else if (order_mode == 0) {
			value2 = arr[i];
		}

		/*判定可能なら判定し、判定済みなら判定通りに並んでいるか確認*/
		if (order_mode == 0) {
			/*未判定*/
			if (value1 != value2) {
				/*判定*/
				order_mode = (value1 < value2) ? 1 : -1;
			}
			else if (order_mode == 1) {
				/*判定済み・昇順の時*/
				/*一つ前の値から確認*/
				if (arr[i - 1] > arr[i]) {
					return -1;	/*失敗判定*/
				}
			}
			else if (order_mode == -1) {
				/*判定済み・降順の時*/
				/*一つ前の値から確認*/
				if (arr[i - 1] > arr[i]) {
					return -1;	/*ソートできてない判定*/
				}
			}
		}
	}
	/*一通り配列を見た結果に従って戻り値を返す*/
	switch (order_mode) {
	case 0:
		return -1;	/*すべての値が同じ*/
	case 1:
		return 1;	/*昇順*/
	case -1:
		return 2;	/*降順*/
	}

	return -1;
}