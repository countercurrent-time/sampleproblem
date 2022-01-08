#include<cstdio>
int main(int argc, char** argv) {
  int a = 1, b = 1;
	for (int i = 0; i < argc; i++)
    for (int j = 0; argv[i][j] != '\0'; j++) {
      a = (long long)a * 10781 + argv[i][j] % 2147483647ll;
      b = (long long)b * 10001 + argv[i][j] % 2147483647ll;
    }
  printf("%d %d", a, b);
	return 0;
}
