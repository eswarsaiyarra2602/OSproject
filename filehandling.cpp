#include <stdio.h>
#include <string.h>
#include<stdlib.h>

int file_exists(const char *filename) {      // function to check whether 
  FILE *fp = fopen(filename, "r");          //file exists or not
  if (fp == NULL) {
    return 0;
  }
  fclose(fp);
  return 1;
}

void replace_word(char *str, const char *old_word, const char *new_word, int replace_all) {
  char *pos = str;
  int old_word_len = strlen(old_word);            
  int new_word_len = strlen(new_word);
 
  if (replace_all) {         //replace_all is a flag given from user input
    while ((pos = strstr(pos, old_word)) != NULL) {
      memmove(pos + new_word_len, pos + old_word_len, strlen(pos + old_word_len) + 1);
      memcpy(pos, new_word, new_word_len);
      pos += new_word_len;
    }
  } else {
    if ((pos = strstr(pos, old_word)) != NULL) {
      memmove(pos + new_word_len, pos + old_word_len, strlen(pos + old_word_len) + 1);
      memcpy(pos, new_word, new_word_len);
    }
  }
}

int replace_word_in_file(const char *filename, const char *old_word, const char *new_word, int replace_all) {
  if (!file_exists(filename)) {
    return 1;
  }

  FILE *input = fopen(filename, "r");
  if (input == NULL) {
    return 2;
  }

  char temp_filename[] = "temp.txt";
  FILE *output = fopen(temp_filename, "w");
  if (output == NULL) {
    fclose(input);
    return 3;
  }

  char buffer[BUFSIZ];

  while (fgets(buffer, sizeof(buffer), input) != NULL) {
    replace_word(buffer, old_word, new_word, replace_all);
    fputs(buffer, output);
  }

  fclose(input);
  fclose(output);

  if (remove(filename) != 0) {
    return 4;
  }

  if (rename(temp_filename, filename) != 0) {
    return 5;
  }

  return 0;
}

int main() {
  printf("\n\n\t\t\t\t ------ Eshwar Sai Welcomes You To His Project -----");
  while (1) {
    printf("\n\n\t\t\t\t\t*** Kindly Enter Your Choice *** \n");

    char choice[BUFSIZ];
    printf("\t\t\t\t\t    1. Print the file\n");
    printf("\t\t\t\t\t    2. Replace a word in the file\n");
    printf("\t\t\t\t\t    3. Exit\n");
    printf("\t\t\t\t\t    Enter your choice: ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';

    if (strcmp(choice, "1") == 0) {
      char filename[BUFSIZ];
      printf("\t\t\t\tEnter the name of the text file to be printed: ");
      fgets(filename, sizeof(filename), stdin);
      filename[strcspn(filename, "\n")] = '\0';

      FILE *file = fopen(filename, "r");
      if (file) {
        char buffer[BUFSIZ];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
          printf("%s", buffer);
        }
        fclose(file);
      } else {
        printf("\t\t\t\t\tThe file '%s' does not exist.\n", filename);
      }
    } else if (strcmp(choice, "2") == 0) {
      char filename[BUFSIZ];
      printf("\t\t\t\tEnter the name of the text file to be modified: ");
      fgets(filename, sizeof(filename), stdin);
      filename[strcspn(filename, "\n")] = '\0';

      char old_word[BUFSIZ];
      printf("\t\t\t\tEnter the word to be replaced: ");
      fgets(old_word, sizeof(old_word), stdin);
      old_word[strcspn(old_word, "\n")] = '\0';

      char new_word[BUFSIZ];
      printf("\t\t\t\tEnter the new word: ");
      fgets(new_word, sizeof(new_word), stdin);
      new_word[strcspn(new_word, "\n")] = '\0';

      char replace_all[BUFSIZ];
      printf("\t\t\t\tReplace all occurrences of the word? (y/n): ");
      fgets(replace_all, sizeof(replace_all), stdin);
      replace_all[strcspn(replace_all, "\n")] = '\0';

      int result = replace_word_in_file(filename, old_word, new_word, (replace_all[0] == 'y'));

      if (result == 0) {
        printf("\t\tThe word '%s' has been replaced with the word '%s' in the file '%s'.\n", old_word, new_word, filename);
      } else if (result == 1) {
        printf("\t\t\t\tThe file '%s' does not exist.\n", filename);
      } else if (result == 2) {
        printf("\t\t\t\tAn error occurred while opening the file '%s'.\n", filename);
      }
    } else if (strcmp(choice, "3") == 0) {
      // Exit
      break;
    } else {
      printf("\t\t\t\t\t******Invalid entry******\n");
    }
  }

  return 0;
}
