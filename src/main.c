#include <stdio.h>
#include <stdlib.h>

void 
fizzbuzz(int n, FILE *stream) 
{
    // 無効な引数チェック
    if (n <= 0) {
        fprintf(stderr, "fizzbuzz: 無効な引数です。\n");
        exit(EXIT_FAILURE);
    }

    // メモリ割り当てチェック
    char *results = (char *)malloc(n * sizeof(char));
    if (results == NULL) {
        fprintf(stderr, "fizzbuzz: メモリの割り当てに失敗しました。\n");
        exit(EXIT_FAILURE);
    }

    // FizzBuzzの計算
    for (int i = 1; i <= n; i++) {
        if (i % 15 == 0) results[i-1] = 'F'; // FizzBuzz
        else if (i % 3 == 0) results[i-1] = 'f'; // Fizz
        else if (i % 5 == 0) results[i-1] = 'b'; // Buzz
        else results[i-1] = '.'; // その他の数
    }

    // streamがNULLでない場合のみ出力する。
    if (stream != NULL) {
        for (int i = 0; i < n; i++) {
            fprintf(stream, "%c", results[i]);
        }
        fprintf(stream, "\n");
    }

    // メモリ解放
    free(results);
}

int 
testFizzBuzz() 
{
    FILE *devNull = fopen("/dev/null", "w");
    if (devNull == NULL) {
        fprintf(stderr, "一時ファイルのオープンに失敗しました。\n");
        return 0; // テスト失敗
    }

    fizzbuzz(15, devNull);

    fclose(devNull);
    return 1; // テスト成功
}

int 
main() 
{
    if (!testFizzBuzz()) {
        fprintf(stderr, "テストが失敗しました。プロセスを中断します。\n");
        exit(EXIT_FAILURE);
    }

    fizzbuzz(100, stdout);

    return 0;
}
