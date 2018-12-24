/**
* @file sort_visualize.h
* @brief int型配列のソートを視覚化する（したい）
*/

/**
 * @fn
 * ソート関数を与えられた配列に対して実行する
 * @brief ソート関数実行
 * @param (sort_func) ソートを実行する関数。引数にはint型配列と配列の要素数が与えられる。
 * @param (array) ソートを行う対象
 * @param (array_num) arrayの要素数
 */
void start_sort(void(*sort_func)(int*, int), int*, int);

/**
 * @fn
 * ソート関数内で位置を入れ替えるときに実行すると入れ替えアニメーションが見られる。
 * @brief ソート内のアニメーション付き入れ替え関数
 * @param (a) 入れ換える対象
 * @param (b) 入れ換える対象
*/
void visualize_swap(int*, int*);
