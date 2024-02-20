#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char* xor_decrypt(char* data, char* password, int size) {
  char* decrypted = malloc(size);
  int password_length = strlen(password);
  for (int i = 0; i < size; i++) {
    decrypted[i] = data[i] ^ password[i % password_length];
  }
  return decrypted;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf(2, "Usage: decrypt password filename\n");
    exit();
  }

  char* password = argv[1];
  char* filename = argv[2];

  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    printf(2, "Failed to open file\n");
    exit();
  }

  struct stat st;
  fstat(fd, &st);
  char* data = malloc(st.size);
  read(fd, data, st.size);

  //need to check the password with a system call 
  //if the password is wrong, the file will not be decrypted
  int check = checkPassword(fd, password);
  if (check < 0){
    printf(2, "Error: Wrong password\n");
    exit();
  }
  close(fd);
  //need to create checkPassword system call in order to check the password
  char* decrypted = xor_decrypt(data, password, st.size);

  fd = open(filename, O_CREATE | O_WRONLY);
  if (fd < 0) {
    printf(2, "Failed to open file for writing\n");
    exit();
  }

  write(fd, decrypted, st.size);
  close(fd);

  exit();
}