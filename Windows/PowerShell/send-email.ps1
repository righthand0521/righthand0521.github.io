<#
.SYNOPSIS
    Sends an email message
.DESCRIPTION
    This PowerShell script sends an email message.
.PARAMETER From
    Specifies the sender email address
.PARAMETER To
    Specifies the recipient email address
.PARAMETER Subject
    Specifies the subject line
.PARAMETER Body
    Specifies the body message
.EXAMPLE
    PS> ./send-email

    PS> ./send-email.ps1 [[-From] <String>] [[-To] <String>] [[-Subject] <String>] [[-Body] <String>] [[-SMTPServer] <String>] [<CommonParameters>]
    -From <String>
        Specifies the sender email address
        Required?                    false
        Position?                    1
        Default value
        Accept pipeline input?       false
        Accept wildcard characters?  false
    -To <String>
        Specifies the recipient email address
        Required?                    false
        Position?                    2
        Default value
        Accept pipeline input?       false
        Accept wildcard characters?  false
    -Subject <String>
        Specifies the subject line
        Required?                    false
        Position?                    3
        Default value
        Accept pipeline input?       false
        Accept wildcard characters?  false
    -Body <String>
        Specifies the body message
        Required?                    false
        Position?                    4
        Default value
        Accept pipeline input?       false
        Accept wildcard characters?  false
    -SMTPServer <String>
        Required?                    false
        Position?                    5
        Default value
        Accept pipeline input?       false
        Accept wildcard characters?  false
    [<CommonParameters>]
        This script supports the common parameters: Verbose, Debug, ErrorAction, ErrorVariable, WarningAction,
        WarningVariable, OutBuffer, PipelineVariable, and OutVariable.
.LINK
    https://github.com/fleschutz/PowerShell
    https://github.com/fleschutz/PowerShell/blob/main/docs/send-email.md
.NOTES
    Author: Markus Fleschutz | License: CC0
#>

param([string]$From = '', [string]$To = '', [string]$Subject = '', [string]$Body = '', [string]$SMTPServer = '')

try {
    $msg = New-Object Net.Mail.MailMessage

    if ($From -eq '') {
        $From = Read-Host 'Enter sender email address'
    }
    $msg.From = $From
    $msg.ReplyTo = $From

    if ($To -eq '') {
        $To = Read-Host 'Enter recipient email address'
    }
    $msg.To.Add($To)

    if ($Subject -eq '') {
        $Subject = Read-Host 'Enter subject line'
    }
    $msg.subject = $Subject

    if ($Body -eq '') {
        $Body = Read-Host 'Enter body message'
    }
    $msg.body = $Body

    if ($SMTPServer -eq '') {
        $SMTPServer = Read-Host 'Enter SMTP server'
    }
    $smtp = New-Object Net.Mail.SmtpClient($smtpServer)

    $smtp.Send($msg)

    Write-Host 'Success' -ForegroundColor Cyan
    exit 0
}
catch {
    "Error in line $($_.InvocationInfo.ScriptLineNumber): $($Error[0])"
    exit 1
}
