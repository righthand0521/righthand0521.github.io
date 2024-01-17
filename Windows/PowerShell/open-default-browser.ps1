<#
.SYNOPSIS
    Opens the default browser
.DESCRIPTION
    This PowerShell script launches the default Web browser, optional with a given URL.
.PARAMETER URL
    Specifies the URL
.EXAMPLE
    PS> ./open-default-browser

    PS> ./open-default-browser.ps1 [[-URL] <String>] [<CommonParameters>]
    -URL <String>
        Specifies the URL
        Required?                    false
        Position?                    1
        Default value                http://www.fleschutz.de
        Accept pipeline input?       false
        Accept wildcard characters?  false
    [<CommonParameters>]
        This script supports the common parameters: Verbose, Debug, ErrorAction, ErrorVariable, WarningAction,
        WarningVariable, OutBuffer, PipelineVariable, and OutVariable.
.LINK
    https://github.com/fleschutz/PowerShell
    https://github.com/fleschutz/PowerShell/blob/main/docs/open-default-browser.md
.NOTES
    Author: Markus Fleschutz | License: CC0
#>

param([string]$URL = 'https://www.google.com/')

try {
    Start-Process $URL

    Write-Host 'Success' -ForegroundColor Cyan
    exit 0
}
catch {
    "Error in line $($_.InvocationInfo.ScriptLineNumber): $($Error[0])"
    exit 1
}
