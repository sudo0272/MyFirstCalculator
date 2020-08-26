#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  int start;
  int end;
} Range;

typedef enum {
  SUCCESS,
  UNDEFINED
} CalculationError;

CalculationError add(int *target, int a, int b, char *operator) {
  *operator = '+';
  *target = a + b;

  return SUCCESS;
}

CalculationError subtract(int *target, int a, int b, char *operator) {
  *operator = '-';
  *target = a - b;

  return SUCCESS;
}

CalculationError multiply(int *target, int a, int b, char *operator) {
  *operator = '*';
  *target = a * b;

  return SUCCESS;
}

CalculationError divide(int *target, int a, int b, char *operator) {
  *operator = '/';

  if (b == 0) {
    return UNDEFINED;
  }

  *target = a / b;
  
  return SUCCESS;
}

CalculationError modulo(int *target, int a, int b, char *operator) {
  *operator = '%';

  if (b == 0) {
    return UNDEFINED;
  }

  *target = a % b;

  return SUCCESS;
}

int main() {
  Range range;
  char shortCodeMode;
  bool isShortCodeModeEnabled;
  char codePath[256];
  FILE *codeFile;
  char elsePart[6];
  CalculationError (*calculator[])(int *, int, int, char *) = {
    add, subtract, multiply, divide, modulo
  };
  char operator;
  int calculationResult;
  CalculationError calculationError;
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
          calculationError = (*calculator[i])(&calculationResult, j, k, &operator);

          fprintf(codeFile,
                  "if(n==%d&&m==%d)printf(\"%d %c %d = ",
                  j, k, j, operator, k
          );

          switch (calculationError) {
            case SUCCESS:
              fprintf(codeFile, "%d", calculationResult);
              break;

            case UNDEFINED:
              fprintf(codeFile, "UNDEFINED");
              break;
          }

          fprintf(codeFile, " \\n\");");
        }
      }
    } else {
      elsePart[0] = '\0';

      for (j = range.start; j <= range.end; j++) {
        for (k = range.start; k <= range.end; k++) {
          calculationError = (*calculator[i])(&calculationResult, j, k, &operator);

          fprintf(codeFile, "  %sif (n == %d && m == %d) {\n", elsePart, j, k);

          fprintf(codeFile,
                  "    printf(\"%d %c %d = ",
                  j, operator, k
          );

          switch (calculationError) {
            case SUCCESS:
              fprintf(codeFile, "%d", calculationResult);
              break;

            case UNDEFINED:
              fprintf(codeFile, "UNDEFINED");
              break;
          }

          fprintf(codeFile, "\\n\");\n");

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

