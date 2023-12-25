#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  FILE *pipe = NULL;
  const char cmd[] = "find ./";
  char buf[256];
  char *line;
  
  pipe = popen(cmd, "r");
  if(!pipe){
    perror("popen");
    exit(1);
  }

  while(1){
    line = fgets(buf, 256 - 1, pipe);
    if(!line){
      break;
    }
    fprintf(stdout, "%s", line);
  }
  pclose(pipe);

  return 0;
}

