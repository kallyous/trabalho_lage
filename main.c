#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  int pid = fork();

  if (pid == 0) {
    printf("Processo filho iniciado.\n");
  }
  else if(pid > 0) {
    int i;
    for (i = 0; i < 10; i++) {
      sleep(1);

      char bash_cmd[256];
      sprintf(bash_cmd, "ps v %i | grep -v MEM | awk '{print $9}'", pid );

      char buffer[1000];
      FILE *pipe;
      int len;
      pipe = popen(bash_cmd, "r");

      if (NULL == pipe) {
        perror("pipe");
        exit(1);
      }

      char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
      len = strlen(bash_cmd);
      bash_cmd[len-1] = '\0';
      pclose(pipe);

      printf("mem_usage == %s", mem_usage);

    }
    _exit(1);
  }
  else {
    printf("Erro!\n");
    return 255;
  }

  return 0;
}
