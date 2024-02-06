section .text:
  global _start

_start:
  mov rdx, 60
  mov rdi, 1
  syscall  