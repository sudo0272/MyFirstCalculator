#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  int start;
  int end;
} Range;

void add(int *target, int a, int b, char *operator) {
  *operator = '+';
  *target = a + b;
}

void subtract(int *target, int a, int b, char *operator) {
  *operator = '-';
  *target = a - b;
}

void multiply(int *target, int a, int b, char *operator) {
  *operator = '*';
  *target = a * b;
}

void divide(int *target, int a, int b, char *operator) {
  *operator = '/';
  *target = a / b;
}

void modulo(int *target, int a, int b, char *operator) {
  *operator = '%';
  *target = a % b;
}

int main() {
  Range range;
  char shortCodeMode;
  bool isShortCodeModeEnabled;
  char codePath[256];
  FILE *codeFile;
  char elsePart[6];
  void (*calculator[])(int *, int, int, char *) = {
    add, subtract, multiply, divide, modulo
  };
  char operator;
  int calculationResult;
  unsigned int i;
  int j;
  int k;

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

  for (i = 0; i < 5; i++) {
    if (isShortCodeModeEnabled) {
      for (j = range.start; j <= range.end; j++) {
        for (k = range.start; k <= range.end; k++) {
          (*calculator[i])(&calculationResult, j, k, &operator);

          fprintf(codeFile,
                  "if(n==%d&&m==%d)printf(\"%d %c %d = %d\\n\");",
                  j, k, j, operator, k, calculationResult
          );
        }
      }
    } else {
      elsePart[0] = '\0';

      for (j = range.start; j <= range.end; j++) {
        for (k = range.start; k <= range.end; k++) {
          (*calculator[i])(&calculationResult, j, k, &operator);

          fprintf(codeFile, "  %sif (n == %d && m == %d) {\n", elsePart, j, k);
          fprintf(codeFile,
                  "    printf(\"%d %c %d = %d\\n\");\n",
                  j, operator, k, calculationResult
          );
          fprintf(codeFile, "  }\n");
          fprintf(codeFile, "\n");

          if (elsePart[0] == '\0') {
            strcpy(elsePart, "else ");
          }
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

  fclose(codeFile);

  return 0;
}

