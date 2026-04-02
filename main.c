long real_write(int fd, const void *buf, unsigned long count);
long real_read(int fd, void *buf, unsigned long count);
long real_chdir(const char *path);
long real_fork(void);
long real_execve(const char *path, char *const argv[], char *const envp[]);
int real_strcmp(const char *s1, const char *s2);
char *real_strsep(char **stringp, const char *delim);
void real_exit(int status);
long real_wait(void);

void _start(void) {
  char input[1024];
  for (;;) { /* loop */
  real_write(1, "> ", 2);
  char *envp[] = { 0 };
  char *token;
  char *p;
  int n = real_read(0, input, 1023);
  if (n <= 0) continue;
  input[n-1] = '\0'; 
  
  char *argv[64];

  int i = 0;
  p = input;
  while (i < 63 && (token = real_strsep(&p, " ")) != 0) {
    if (*token != '\0') {
      argv[i++] = token;
    }
  }
  argv[i] = 0;
    
  if (i == 0) { continue; }

  if (real_strcmp(argv[0], "exit") == 0 ) { break; }
  else if (real_strcmp(argv[0], "cd") == 0) {
      if (argv[1] != 0) real_chdir(argv[1]);
      continue; 
  }

  if (real_fork() == 0) {
    real_execve(argv[0], argv, envp);
    real_exit(1);
  } else {
    real_wait(); 
  }
  }
  real_exit(0);
}

__asm__(
".intel_syntax noprefix\n" 
".global real_write\n"
".global real_read\n"
".global real_chdir\n"
".global real_fork\n"
".global real_exit\n"
".global real_execve\n"
"real_write: mov rax, 1; syscall; ret\n" 
"real_read: mov rax, 0; syscall; ret\n" 
"real_chdir: mov rax, 80; syscall; ret\n" 
"real_fork: mov rax, 57; syscall; ret\n"
"real_exit:  mov rax, 60; syscall; ret\n"
"real_execve: mov rax, 59; syscall; ret\n"
"real_wait:\n"
"    mov rdi, -1\n"    
"    xor rsi, rsi\n"  
"    xor rdx, rdx\n" 
"    xor r10, r10\n" 
"    mov rax, 61\n"
"    syscall\n"
"    ret\n"
".att_syntax\n"
);

int real_strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(unsigned char *)s1 - *(unsigned char *)s2;
}
char *real_strsep(char **stringp, const char *delim) {
  char *start = *stringp;
  if (start == 0) return 0;
  char *p = start;
  while (*p != '\0' && *p != *delim) {
    p++;
  }
  if (*p == '\0') {
    *stringp = 0;
  }
  else {
    *p = '\0';
    *stringp = p + 1;
  }
  return start;
}
