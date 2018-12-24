# sort_test
自分で書いたソートプログラムの動き方を実際に見て確認できるファイルです。
`#include "sort_visualize.h"`等で読み込んで使えます。  

## 使用例

```main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "sort_visualize.h"
#define ARRAY_NUM 10

void bubble_sort(int*, int);

/*
int型配列を監視して、ソートの様子を表示するプログラム
*/
int main() {
	int arr[ARRAY_NUM] = { 24, 33, 22, 10, 22, 12, 55, 10, 100, 12 };
	start_sort(bubble_sort, arr, ARRAY_NUM);

	return 0;
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
```

### 動作
![example](/contents/sort_test.gif)

## 使い方 
1. `#include "sort_visualize.h"`等で読み込みます。
1. 自分でソートのプログラムを書きます。 
1. 要素と要素を入れ換えるときに、`visualize_swap(a, b)`を用いて入れ替えます。
1. 実行は`sort_start(func, int_array, num)`を使って、自作のソート関数と、ソートに使うint型配列と、その要素の数を渡せばOKです。
