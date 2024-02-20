#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char* xor_encrypt(char* data, char* password, int size) {
  char* encrypted = malloc(size);
  int password_length = strlen(password);
  for (int i = 0; i < size; i++) {
    encrypted[i] = data[i] ^ password[i % password_length];
  }
  return encrypted;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf(2, "Usage: encrypt password filename\n");
    exit();
  }

  char* password = argv[1];
  char* filename = argv[2];

  int fd = openencrypt(filename, O_RDONLY, password);
  if (fd < 0) {
    printf(2, "Failed to open file\n");
    exit();
  }

  struct stat st;
  fstat(fd, &st);
  char* data = malloc(st.size);
  read(fd, data, st.size);
  close(fd);

  char* encrypted = xor_encrypt(data, password, st.size);

  fd = openencrypt(filename, O_CREATE | O_WRONLY, password);
  if (fd < 0) {
    printf(2, "Failed to open file for writing\n");
    exit();
  }

  write(fd, encrypted, st.size);
  close(fd);

  exit();
}