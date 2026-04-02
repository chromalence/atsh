.intel_syntax noprefix
.section .text

.global real_write
.global real_read
.global real_chdir
.global real_fork
.global real_exit
.global real_execve
.global real_wait

real_write:
  mov rax, 1
  syscall
  ret

real_read:
  mov rax, 0
  syscall
  ret

real_chdir:
  mov rax, 80;
  syscall
  ret

real_fork:
  mov rax, 57
  syscall
  ret

real_exit:
  mov rax, 60
  syscall 
  ret

real_execve:
  mov rax, 59
  syscall
  ret

real_wait:
  mov rdi, -1 
  xor rsi, rsi
  xor rdx, rdx
  xor r10, r10
  mov rax, 61
  syscall
  ret
