#include <stdio.h>
#include <conio.h>
#include <unistd.h>  // usleep();
#include <stdlib.h>  // system("clear");
#define width 80
#define hight 25
#define WIN_SCORE 21



void printField(int player_one_racket, int player_two_racket, int ball_x, int ball_y,
                int player_one_score, int player_two_score);

int main() {
  int player_one_score = 0;
  int player_two_score = 0;

  while (player_one_score <= WIN_SCORE && player_two_score <= WIN_SCORE) {
    int player_one_racket = hight/2;
    int player_two_racket = hight/2;
    int ball_x = width/2;
    int ball_y = hight/2;
    int touch_racket = 0;
    int touch_field = 0;

    while (1) {
      // Если мяч попал в забор
      if (ball_y <= 1) {
        ball_y = 1;
        touch_field = 1;
      } else if (ball_y >= hight-1) {
        ball_y = hight-1;
        touch_field = 2;
      }
      // Если мяч попал в ракетку
      if (player_one_racket+1 >= ball_y && player_one_racket-1 <= ball_y && ball_x == 2) {
        touch_racket = 1;
      } else if (player_two_racket+1 >= ball_y && player_two_racket-1 <= ball_y && ball_x == width-2) {
        touch_racket = 2;
      }
      // Направления движения шара
      if (touch_racket == 1) ball_x += 1;
      if (touch_racket == 2 || !touch_racket) ball_x -= 1;
      if (touch_field == 1) ball_y += 1;
      if (touch_field == 2 || !touch_field) ball_y -= 1;

      printField(player_one_racket, player_two_racket, ball_x, ball_y, player_one_score, player_two_score);
      // usleep(100000);  // понизить частоту обработки дейсвтий

      while (kbhit()) {  // kbhit() позволяет не ждать ввод в stdin
        char move = getch();
        switch (move) {
        case 'A':
        case 'a':
          player_one_racket--;
          break;
        case 'Z':
        case 'z':
          player_one_racket++;
          break;
        case 'K':
        case 'k':
          player_two_racket--;
          break;
        case 'M':
        case 'm':
          player_two_racket++;
          break;
        default:
          return 0;
          break;
        }
      }
      system("clear");
      /*
      Не работают на моей машине следующие команды:
      clrscr();
      printf("\e[1;1H\e[2J\n");
      printf("\033[2J\033[1;1H");
      */

      // Не позволяет выйти ракетке за пределы поля
      if (player_one_racket < 2) player_one_racket = 2;
      if (player_one_racket > hight-2) player_one_racket = hight-2;
      if (player_two_racket < 2) player_two_racket = 2;
      if (player_two_racket > hight-2) player_two_racket = hight-2;

      // Если мяч попал в ворота
      if (ball_x < 1) {
        player_two_score++;
        break;
      } else if (ball_x > width-1) {
        player_one_score++;
        break;
      }
    }

    // Вывод поздравления победителя
    if (player_one_score == WIN_SCORE) {
      printf("Congratulations!!! First player win!!!\n");
      return 0;
    } else if (player_two_score == WIN_SCORE) {
      printf("Congratulations!!! Second player win!!!\n");
      return 0;
    }
  }
  return 0;
}

void printField(int player_one_racket, int player_two_racket, int ball_x, int ball_y,
                int player_one_score, int player_two_score) {
  for (int line = -4; line <= hight; line++) {
    for (int column = 0; column <= width; column++) {
      if (line == -4 || !line || line == hight) {
        printf("\033[32m%c\033[0m", '=');
        continue;
      } else if (!column || column == width) {
        printf("\033[32m%c\033[0m", '|');
        continue;
      }
      if (line == -2 && column == 15) {
        printf("\033[91mLeft player: %d\033[0m", player_one_score);
        column += 14;
      }
      if (line == -2 && column == 50) {
        printf("\033[94mRight player: %d\033[0m", player_two_score);
        column += 15;
      }
      if (column == 1 && (line >= player_one_racket-1 && line <= player_one_racket+1)) {
        printf("\033[91m%c\033[0m", ']');
        continue;
      } else if (column == width-1 && (line >= player_two_racket-1 && line <= player_two_racket+1)) {
        printf("\033[94m%c\033[0m", '[');
        continue;
      }
      if (column == ball_x && line == ball_y) {
        printf("\033[33m%c\033[0m", 'O');
        continue;
      }
      printf(" ");
    }
    printf("\n");
  }
}
