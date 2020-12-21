#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void zip_file(FILE *file_in, FILE *file_out);
void unzip_file(FILE *file_in, FILE *file_out);

void zip_file(FILE *file_in, FILE *file_out)
{
  int count, first_byte, second_byte, res;

  first_byte = getc(file_in);
  second_byte = first_byte;
  while (second_byte != EOF)
  {
    // если прошлый байт равен текущему, то count увеличивается
    // если последовательность байт больше 254, то цикл начинается заново
    for (count = 0; second_byte == first_byte && count < 255; count++)
    {
      second_byte = getc(file_in); // установает следующую переменную для сравнения
    }
    // запись байтов в новый файл
    putc(count, file_out);
    putc(first_byte, file_out);
    first_byte = second_byte;
  }
  fclose(file_in);
  fclose(file_out);
  fprintf(stderr, "Файл успешно архивирован!\n");
}

void unzip_file(FILE *file_in, FILE *file_out)
{
  int count, first_byte, second_byte;

  for (count = 0; second_byte != EOF; count = 0)
  {
    first_byte = getc(file_in);  // берёт первый байт grab
    second_byte = getc(file_in); // берёт второй байт grab
    // записывает в новый байт файл count раз
    do
    {
      putc(second_byte, file_out);
      count++;
    } while (count < first_byte);
  }
  fclose(file_in);
  fclose(file_out);
  fprintf(stderr, "Файл успешно разархивирован!\n");
}

int main(void)
{
  FILE *file_in, *file_out;
  char file_name_in[FILENAME_MAX], file_name_out[FILENAME_MAX];
  int res;

  printf("\n");
  printf("[1] - Архивировать\n");
  printf("[2] - Разархивировать\n");
  printf("[3] - Выйти\n");
  printf("\n");
  do
  {
    printf("Введите команду: ");
    scanf("%d", &res);
  } while (isalpha(res));

  if (res == 3)
    exit(EXIT_SUCCESS);

  printf("Введите путь файла для архивиции, либо путь ранее заархивированного файла: ");
  scanf("%s", file_name_in);
  printf("Введите имя файла, где будет результат выполнения действия: ");
  scanf("%s", file_name_out);
  // открывает файл для чтения
  while ((file_in = fopen(file_name_in, "rb")) == NULL)
  {
    fprintf(stderr, "Не Удается Открыть Файл! \"%s\"\n", file_name_in);
    printf("Введите имя файла для архивиции, либо имя ранее заархивированного файла: ");
    scanf(" %s", file_name_in);
  }
  // открывает файл для записи
  while ((file_out = fopen(file_name_out, "wb")) == NULL)
  {
    fprintf(stderr, "Ошибка, файл не создан! \"%s\"\n", file_name_out);
    printf("Введите имя файла, где будет результат выполнения действия: ");
    scanf("%s", file_name_out);
  }
  if (res == 1)
  {
    zip_file(file_in, file_out);
  }
  else if (res == 2)
  {
    unzip_file(file_in, file_out);
  }
  putchar('\n');

  return 0;
}
