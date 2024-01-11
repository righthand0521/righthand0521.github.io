# [Tera Term](https://ttssh2.osdn.jp/)

## [TTL command reference](https://ttssh2.osdn.jp/manual/4/en/macro/command/)

```ttl
; ASCII
; '#34'    "  22  &#034; --> &quot;    (double) quotation mark
; '#39'    '  27  &#039; --> &apos;    apostrophe
```

```ttl
if paramcnt != 3 then
    messagebox '.ttl <arg1><arg2>' 'Usage'
    closett
    end
endif
arg1=param2
arg2=param3
```

```ttl
dispstr #$1b"[8;52;180t"  ; change terminal size to 180x52
dispstr #$1B"[3;0;0t"     ; move terminal screen to the X=0, Y=0 coordinate
```

```ttl
getdir currentDir
gettime timestr "%Y%m%d-%H%M%S"
sprintf2 logFile '%s\%s.log' currentDir  timestr
logautoclosemode 1
logopen logFile 1 1 1 1 1
logclose
```

```ttl
connect '192.168.0.1:22 /2 /ssh /auth=password /user=admin /passwd=password'
```

```ttl
fileNeam='text.txt'
oldkeyword='fileContain'    ; use strreplace to replace cmd that file contain
newkeyword='youWant'        ; use strreplace to replace cmd that you want

fileopen fhandle fileNeam 0
pause 1
while 1
    filereadln fhandle line
    if result=1 then
        break
    endif
    strreplace line 1 oldkeyword newkeyword
endwhile
fileclose fhandle
```

## [teraterm-subroutines](https://github.com/kurtmckee/teraterm-subroutines)
