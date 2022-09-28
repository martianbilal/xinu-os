        .text
        .global getpidxasm
getpidxasm:
    pushl %eax
    pushl %ecx
    pushl %edx
    int $46
    popl %edx
    popl %ecx
    popl %eax
    ret