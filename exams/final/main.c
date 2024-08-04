#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "final.h"

extern void deobfuscate(char *buffer, size_t length);
extern int open_file(const char *filename);
extern void write_to_file(int fd, const char *buffer, size_t length);
extern int open_read_obfuscated_file(const char *filename, char *buffer, size_t length);

const char *obfuscated_text = "xRdx/9!x,7x?7xfRxuuuuuuuuuuuRxxxxxxxxxxxRxxxxxxxxxxxp77qRxxxxxxxxxxxxpqxxxxxxxqwRxxxxxxxxxxxxxxxx$$uuuu/x$Rxxxxxxxxxxxxxxxx$$xxxxx$$R";
char buffer[255] = {0};
char test_buffer[255] = {0};

void read_file_contents(const char *filename)
{
   memset(buffer, 0, sizeof(buffer));

   // open file and read contents
   FILE *fp = fopen(filename, "r");
   if (fp)
   {
      int result = fread(buffer, sizeof(buffer), sizeof(char), fp);
      fclose(fp);
   }
   else
   {
      printf("Unable to open %s\n", filename);
   }
}

void deobfuscate_buffer()
{
   memset(test_buffer, 0, sizeof(test_buffer));
   for (int i = 0; i < strlen(obfuscated_text); i++)
   {
      test_buffer[i] = obfuscated_text[i] ^ 'X';
   }
}

int check_permissions(int fd)
{
   struct stat file_stat;

   if (fstat(fd, &file_stat) < 0)
   {
      perror("fstat");
      return -1;
   }

   mode_t permissions = file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

   // Check if permissions are 0644
   if (permissions != 0644)
   {
      return -2;
   }

   return 0;
}

int check_open_mode(int fd)
{
   int flags = fcntl(fd, F_GETFL);
   if (flags == -1)
   {
      perror("fcntl");
      return -1;
   }

   if ((flags & O_ACCMODE) != O_RDWR)
   {
      return -2;
   }

   return 0;
}

int main()
{
   memset(buffer, 0, sizeof(buffer));
   int read_len = open_read_obfuscated_file("obfuscated.txt", buffer, strlen(obfuscated_text));
   if (buffer != NULL)
   {
      printf("* BONUS: Read in obfuscated file *\n");
      printf("** Checking file contents **\n");
      int mem_res = memcmp(obfuscated_text, buffer, strlen(obfuscated_text));
      EQ_I(mem_res, 0);
   }
   else
   {
      // instructor code: read in obfuscated text file
      // store results in `buffer`.
      read_file_contents("obfuscated.txt");
   }

   // instructor code: deobfuscate buffer
   deobfuscate_buffer();

   printf("* First Test: Deobfuscation *\n");
   // student code: process buffer
   deobfuscate(buffer, strlen(buffer));
   // check deobfuscation results
   int mem_res = memcmp(test_buffer, buffer, strlen(obfuscated_text));
   EQ_I(mem_res, 0);

   // clear results
   asm("xor %rax,%rax");

   printf("* Second Test: Open/Create file w/ O_RDWR and mode 0644 *\n");
   int fd = open_file("deobfuscated.txt");
   printf("** Checking file descriptor **\n");
   VALID_FD(fd);
   printf("** Checking file permissions **\n");
   int perm_res = check_permissions(fd);
   EQ_I(perm_res, 0);
   printf("** Checking file mode **\n");
   int mode_res = check_open_mode(fd);
   EQ_I(mode_res, 0);

   // clear results
   asm("xor %rax,%rax");

   printf("* Third Test: Checking file contents *\n");
   write_to_file(fd, buffer, strlen(obfuscated_text));
   // instructor code to read in deobfuscated.txt
   // results stored in buffer
   read_file_contents("deobfuscated.txt");
   // check contents
   mem_res = memcmp(test_buffer, buffer, strlen(obfuscated_text));
   EQ_I(mem_res, 0);

   if (mem_res == 0)
   {
      // print final result
      printf("%s\n", buffer);
   }

   return 0;
}
