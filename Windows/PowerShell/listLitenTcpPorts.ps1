# PowerShell 小工具 - 列舉傾聽的 TCP Port 與其對應程式
# https://blog.darkthread.net/blog/list-listening-port-w-ps/

$dict = @{}
Get-WmiObject Win32_Process | ForEach-Object {
    $path = $_.ExecutablePath
    if (!$path) {
        $path = $_.Name
    }
    $dict['P' + $_.ProcessId] = $path + ' ' + $_.CommandLine
}
$wp = [Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()
$iisInfo = @{}
if (-Not $wp.IsInRole([Security.Principal.WindowsBuiltInRole]"Administrator")) {
    Write-Host "Need administrator privileges to show more information." -ForegroundColor Yellow
}
else {
    Import-Module WebAdministration
    Get-ChildItem -Path "IIS:\Sites" | ForEach-Object {
        $siteName = $_.Name
        $_.Bindings | ForEach-Object {
            $_.Collection | ForEach-Object {
                $p = $_.bindingInformation.Split(':')
                $socket = $p[0].Replace('*', '::') + ':' + $p[1]
                if ($p[2]) {
                    $bindHost = "(Host=$($p[2])) "
                }
                $iisInfo[$socket] += 'IIS:\' + $siteName + $bindHost
            }
        }
    }
}
Get-NetTCPConnection -State Listen | Sort-Object { $_.LocalPort } |
ForEach-Object {
    $process = Get-Process -Id $_.OwningProcess
    $procPath = $process.Path
    $socket = "$($_.LocalAddress):$($_.LocalPort)"
    if (!$procPath) {
        if ($iisInfo[$socket]) {
            $procPath = $iisInfo[$socket]
        }
        else {
            $procPath = $dict['P' + $process.Id]
        }
    }
    [PSCustomObject]@{
        ProcessName = $process.Name
        PID         = $process.Id
        Socket      = "$($_.LocalAddress):$($_.LocalPort)"
        Path        = $procPath
    }
}
