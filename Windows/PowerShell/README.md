# [PowerShell](https://learn.microsoft.com/zh-tw/powershell/?view=powershell-7.3)

- [wiki](https://zh.wikipedia.org/wiki/PowerShell)
- [如何使用 PowerShell 檔](https://learn.microsoft.com/zh-tw/powershell/scripting/how-to-use-docs?view=powershell-7.4)

## [在 Windows 上安裝 PowerShell](https://learn.microsoft.com/zh-tw/powershell/scripting/install/installing-powershell-on-windows?view=powershell-7.4)

## [about_PowerShell_Editions](https://learn.microsoft.com/zh-tw/powershell/module/microsoft.powershell.core/about/about_powershell_editions?view=powershell-7.4&WT.mc_id=DT-MVP-5003022)

```ps1
$PSVersionTable
```

```ps1
get-host
```

## [PowerShell 「系統上已停用指令碼執行」解決方法](https://hackercat.org/windows/powershell-cannot-be-loaded-because-the-execution-of-scripts-is-disabled-on-this-system)

```ps1
Get-ExecutionPolicy
Set-ExecutionPolicy <Unrestricted>

- AllSigned: 可執行已簽署的腳本
- Bypass: 不會封鎖任何項目，且不會顯示警告或提示
- Default: 設定預設執行原則。(用戶端會是Restricted，伺服器會是RemoteSigned。)
- RemoteSigned: 本機撰寫的腳本不必簽署可執行，遠端下載的腳本需簽署才可執行
- Restricted: 不允許執行腳本。
- Undefined: 無定義
- Unrestricted: 所有腳本都可以執行
```

```ps1
Get-ExecutionPolicy -List
Set-ExecutionPolicy -Scope <CurrentUser> <Unrestricted>

- MachinePolicy: 由電腦的所有使用者的群組原則設定。
- UserPolicy: 由電腦目前使用者的群組原則設定。
- Process: Process 範圍只會影響目前的 PowerShell 會話。
- CurrentUser: 執行原則只會影響目前的使用者。
- LocalMachine: 執行原則會影響目前電腦上的所有使用者。
```

```ps1
powershell -ep bypass
```

- [Get-ExecutionPolicy](https://learn.microsoft.com/zh-tw/powershell/module/microsoft.powershell.security/get-executionpolicy?view=powershell-7.3&viewFallbackFrom=powershell-7)
- [Set-ExecutionPolicy](https://learn.microsoft.com/zh-tw/powershell/module/microsoft.powershell.security/set-executionpolicy?view=powershell-7.3&viewFallbackFrom=powershell-7)

## Reference

- [fleschutz/PowerShell](https://github.com/fleschutz/PowerShell/tree/main)
