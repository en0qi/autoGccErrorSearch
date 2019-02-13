//Yuki NOAKI
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char cmdline[128]={'\0'};
  char buf[1024]={'\0'};//標準出力一次保存用文字列 
  char txt[10300]={'\0'};//標準出力全保存用文字列
  char words[1024]={'\0'};//URL一次生成用文字列
  char message[1024]={'\0'};//エラー一覧出力用文字列
  char url[2048]={'\0'};//ファイナライズされたURL格納文字列
  if(argc<3){
    printf("Usage:erropen gcc [-option] hoge.c\n");
    return 1;}
  else{
  for(int i=1;i<argc;i++){
    sprintf(cmdline,"%s %s",cmdline,argv[i]);
  }
  sprintf(cmdline, "%s 2>&1",cmdline);
    fp = popen(cmdline, "r"); //子プロセス生成・終了,コマンド入力結果をstreamに保存 
    int lines=0;
    while(fgets(buf,sizeof(buf),fp)!=NULL){//streamからbufへ転記
      //行数カウント
      strcat(txt,buf);//書き込み用文字列に出力文字列から新たな行を追加
    }
    pclose(fp);
    char sep[]=" ";
    char *tok;
    tok=strtok(txt,sep);
    printf("\x1b[36m");printf("\x1b[1m");
    printf("Error list\n");
    printf("------------------------------------\n");
    printf("\x1b[0m");
    printf("\x1b[39m");
    while(tok!=NULL){	
      if(strcmp(tok,"warning:")==0||strcmp(tok,"error:")==0){
        printf("\x1b[35m"); //エラー種別を色付き表示
        printf("\x1b[1m");  
        printf("%s", tok);
        printf("\x1b[0m");  
        printf("\x1b[39m");   
        for(int j=0;j<10;j++){//エラー文抽出
	  tok=strtok(NULL,sep);
	  sprintf(message,"%s %s",message,tok);//画面出力
	  if(strstr(tok,"‘")==NULL){//URL生成_’具体的な変数名’を除外
	    sprintf(words,"%s+%s",words,tok);//スペースを+に置き換えて検索URLに対応
	    if(strstr(tok,"\n")!=NULL)break;//改行があった場合は次のエラー文に行くためBreakする
	  }
	}//エラー文抽出ここまで
	//エラー一覧を画面出力
        printf("\x1b[1m"); 
        printf("%s ", message);
        printf("\x1b[0m");
        printf("\n");
        sprintf(url,"http://www.google.co.jp/search?hl=ja&source=hp&q=%s",words);//URL生成
	lines++;
	int pid;
    	pid = fork();
	if(pid == 0){
	  execlp("/usr/bin/xdg-open", "xdg-open", url, NULL);//子プロセスでブラウザ立ち上げ
	  perror("execl failed");
	}
      }
      memset(message,'\0',1024);
      memset(words,'\0',1024);
      tok=strtok(NULL,sep);
    }
    printf("\x1b[36m");printf("\x1b[1m");//プログラム終了・成功のお知らせ
    printf("------------------------------------\n");
    printf("\nComplete. %d errors.\n\n\n", lines);
    printf("\x1b[0m");
    printf("\x1b[39m");
    return 0;
  }
}
