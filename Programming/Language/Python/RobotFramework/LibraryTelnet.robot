*** Settings ***
Documentation
...    | Standard Libraries: Telnet
...    | https://robotframework.org/robotframework/latest/libraries/Telnet.html
...
...    A test library providing communication over Telnet connections.
...    Telnet is Robot Framework's standard library that makes it possible to
...    connect to Telnet servers and execute commands on the opened connections.

Library    Telnet    3


*** Variables ***
${HOST}    127.0.0.1
${USERNAME}    root
${PASSWORD}    password


*** Test Cases ***
Example: Telnet
    Open Connection    ${HOST}    prompt=#    prompt_is_regexp=true
    Login    ${USERNAME}    ${PASSWORD}

    ${result}=    Execute Command    lsb_release -a
    Log    ${result}
    Log To Console    ${result}

    Close Connection


*** Keywords ***
