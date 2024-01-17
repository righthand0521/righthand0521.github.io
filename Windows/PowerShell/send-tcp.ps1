<#
.SYNOPSIS
    Sends a TCP message to an IP address and port
.DESCRIPTION
    This PowerShell script sends a TCP message to the given IP address and port.
.PARAMETER TargetIP
    Specifies the target IP address
.PARAMETER TargetPort
    Specifies the target port number
.PARAMETER Message
    Specifies the message to send
.EXAMPLE
    PS> ./send-tcp 192.168.100.100 8080 "TEST"

    PS> ./send-tcp.ps1 [[-TargetIP] <String>] [[-TargetPort] <Int32>] [[-Message] <String>] [<CommonParameters>]
    -TargetIP <String>
        Specifies the target IP address
        Required?                    false
        Position?                    1
        Default value
        Accept pipeline input?       false
        Accept wildcard characters?  false
    -TargetPort <Int32>
        Specifies the target port number
        Required?                    false
        Position?                    2
        Default value                0
        Accept pipeline input?       false
        Accept wildcard characters?  false
    -Message <String>
        Specifies the message to send
        Required?                    false
        Position?                    3
        Default value
        Accept pipeline input?       false
        Accept wildcard characters?  false
    [<CommonParameters>]
        This script supports the common parameters: Verbose, Debug, ErrorAction, ErrorVariable, WarningAction,
        WarningVariable, OutBuffer, PipelineVariable, and OutVariable.
.LINK
    https://github.com/fleschutz/PowerShell
    https://github.com/fleschutz/PowerShell/blob/main/docs/send-tcp.md
.NOTES
    Author: Markus Fleschutz | License: CC0
#>

param([string]$TargetIP = '', [int]$TargetPort = 0, [string]$Message = '')

try {
    if ($TargetIP -eq '' ) {
        $TargetIP = Read-Host 'Enter target IP address'
    }
    if ($TargetPort -eq 0 ) {
        $TargetPort = Read-Host 'Enter target port'
    }
    if ($Message -eq '' ) {
        $Message = Read-Host 'Enter message to send'
    }

    $IP = [System.Net.Dns]::GetHostAddresses($TargetIP)
    $Address = [System.Net.IPAddress]::Parse($IP)
    $Socket = New-Object System.Net.Sockets.TCPClient($Address, $TargetPort)
    $Stream = $Socket.GetStream()
    $Writer = New-Object System.IO.StreamWriter($Stream)
    $Message | ForEach-Object {
        $Writer.WriteLine($_)
        $Writer.Flush()
    }
    $Stream.Close()
    $Socket.Close()

    Write-Host 'Success' -ForegroundColor Cyan
    exit 0
}
catch {
    "Error in line $($_.InvocationInfo.ScriptLineNumber): $($Error[0])"
    exit 1
}
