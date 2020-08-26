#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
  char elsePart[6];
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
  elsePart[0] = '\0';
  if (isShortCodeModeEnabled) {
    for (i = range.start; i <= range.end; i++) {
      for (j = range.start; j <= range.end; j++) {
        fprintf(codeFile, "%sif(n==%d&&m==%d)printf(\"%d\\n\");",
          elsePart, i, j, i + j);

        if (elsePart[0] == '\0') {
          strcpy(elsePart, "else ");
        }
      }
    }
  } else {
    for (i = range.start; i <= range.end; i++) {
      for (j = range.start; j <= range.end; j++) {
        fprintf(codeFile, "  %sif (n == %d && m == %d) {\n", elsePart, i, j);
        fprintf(codeFile, "    printf(\"%d\\n\");\n", i + j);
        fprintf(codeFile, "  }\n");
        fprintf(codeFile, "\n");

        if (elsePart[0] == '\0') {
          strcpy(elsePart, "else ");
        }
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

