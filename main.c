#include <stdio.h>
#include <stdbool.h>

typedef struct {
  int start;
  int end;
} Range;

int main() {
  Range range;
  char shortCodeMode;
  bool isShortCodeModeEnabled;
  char codePath[256];
  FILE *codeFile;
  int i;
  int j;

  printf("Enter the range of numbers to be able to be calculated by splitting "
         "them with space\n");
  printf("> ");
  scanf("%d %d", &range.start, &range.end);

  getchar(); // flush

  printf("Enter the file which the codes be written\n");
  printf("> ");
  scanf("%s", codePath);

  getchar();// flush

  printf("Enable short-code mode? (Y/n)\n");
  printf("> ");
  scanf("%c", &shortCodeMode);

  getchar(); // flush

  switch (shortCodeMode) {
    case 'Y':
    case 'y':
    case '\n':
      isShortCodeModeEnabled = true;

      break;

    default: // includes N and n
      isShortCodeModeEnabled  = false;

      break;
  }
  
  codeFile = fopen(codePath, "w");
  
  if (isShortCodeModeEnabled) {
    fprintf(codeFile, "n,m;");
    fprintf(codeFile, "main(){");
    fprintf(codeFile, "scanf(\"%%d %%d\",&n,&m);");
  } else {
    fprintf(codeFile, "#include <stdio.h>\n");
    fprintf(codeFile, "\n");
    fprintf(codeFile, "int main() {\n");
    fprintf(codeFile, "  int n;\n");
    fprintf(codeFile, "  int m;\n");
    fprintf(codeFile, "\n");
    fprintf(codeFile, "  scanf(\"%%d %%d\", &n, &m);\n");
    fprintf(codeFile, "\n");
  }

  // Addition
  if (isShortCodeModeEnabled) {
    for (i = range.start; i <= range.end; i++) {
      for (j = range.start; j <= range.end; j++) {
        fprintf(codeFile, "if(n==%d&&m==%d)printf(\"%d\\n\");", i, j, i + j);
      }
    }
  } else {
    for (i = range.start; i <= range.end; i++) {
      for (j = range.start; j <= range.end; j++) {
        fprintf(codeFile, "  if (n == %d && m == %d) {\n", i, j);
        fprintf(codeFile, "    printf(\"%d\\n\");\n", i + j);
        fprintf(codeFile, "  }\n");
        fprintf(codeFile, "\n");
      }
    }
  }

  if (isShortCodeModeEnabled) {
    fprintf(codeFile, "return 0;}");
  } else {
    fprintf(codeFile, "  return 0;\n");
    fprintf(codeFile, "}\n");
    fprintf(codeFile, "\n");
  }

  return 0;
}

