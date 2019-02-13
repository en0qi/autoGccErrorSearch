#include <stdio.h>

//コンパイルエラーを発生させるサンプルプログラム

int main(int argc, char const *argv[]) {
	char sample[10]={'\0'};
	printf("%c\n", sample[11]);
	force = strlen(sample);
	char txt[10]=NULL;
	for(i=0;i<14;i++){
		printf("%s",sample[i]);
		sprintf(txt,"%d%s",force,argv[i]);
	}
	char count = argc;
	return 0
}