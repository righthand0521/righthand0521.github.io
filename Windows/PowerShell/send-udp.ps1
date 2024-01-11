<#
.SYNOPSIS
    Sends a UDP datagram message to an IP address and port
.DESCRIPTION
    This PowerShell script sends a UDP datagram message to an IP address and port.
.PARAMETER TargetIP
    Specifies the target IP address
.PARAMETER TargetPort
    Specifies the target port number
.PARAMETER Message
    Specifies the message text to send
.EXAMPLE
    PS> ./send-udp 192.168.100.100 8080 "TEST"

    PS> ./send-udp.ps1 [[-TargetIP] <String>] [[-TargetPort] <Int32>] [[-Message] <String>] [<CommonParameters>]
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
        Specifies the message text to send
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
    https://github.com/fleschutz/PowerShell/blob/main/docs/send-udp.md
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
    $EndPoints = New-Object System.Net.IPEndPoint($Address, $TargetPort)
    $Socket = New-Object System.Net.Sockets.UDPClient
    $EncodedText = [Text.Encoding]::ASCII.GetBytes($Message)
    $Socket.Send($EncodedText, $EncodedText.Length, $EndPoints) | Out-Null
    $Socket.Close()

    Write-Host 'Success' -ForegroundColor Cyan
    exit 0
}
catch {
    "Error in line $($_.InvocationInfo.ScriptLineNumber): $($Error[0])"
    exit 1
}
