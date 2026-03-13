#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flag();
void show(char *data);
char *read(char *path);
int search(char code[]);
int dfs(int i, int j, int index, char code[]);

char grid[5][5] = {{97, 98, 99, 100, 101},
                   {102, 111, 114, 103, 104},
                   {105, 106, 105, 107, 108},
                   {109, 110, 115, 111, 112},
                   {113, 114, 0, 115, 116}};

void main(int argc, char *argv[]) {
  int i;
  char c[512];
  char buff[1024];

  if (argc > 1 && strlen(argv[1]) / 2 >= 5) {
    for (i = 0; i < strlen(argv[1]) / 2; i++) {
      sscanf(&argv[1][i * 2], "%2hhx", &buff[i]);
    }
    memcpy(c, buff, strlen(buff) + 1);
    if (search(c)) {
      flag();
    } else {
      printf(">>> %s \n", c);
    }
  }

  printf("exiting....\n");
}

void flag() {
  char *path = "/etc/passwd";
  char *content;

  content = read(path);
  show(content);
}

void show(char *data) { printf(data); }

char *read(char *path) {
  static char content[8192];

  FILE *file = fopen(path, "r");

  if (file == NULL) {
    printf("Error opening file");
    return NULL;
  }

  fread(content, sizeof(content), 1, file);

  fclose(file);

  return content;
}

int search(char code[]) {
  for (int i = 0; i < (sizeof(grid) / sizeof(grid[0])); i++) {
    for (int j = 0; j < (sizeof(grid[0]) / sizeof(grid[0][0])); j++) {
      if (dfs(i, j, 0, code))
        return 1;
    }
  }
  return 0;
}

int dfs(int i, int j, int index, char code[]) {
  if (grid[i][j] != code[index])
    return 0;

  if (index == strlen(code))
    return 1;

  char character = grid[i][j];
  grid[i][j] = '*';

  int coord[4][2] = {{i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1}};
  for (int counter = 0; counter < 4; counter++) {
    int r = coord[counter][0];
    int c = coord[counter][1];

    if (r >= 0 && r < (sizeof(grid) / sizeof(grid[0])) && c >= 0 &&
        c < (sizeof(grid[0]) / sizeof(grid[0][0]))) {
      if (dfs(r, c, index + 1, code))
        return 1;
    }
  }

  grid[i][j] = character;
  return 0;
}
