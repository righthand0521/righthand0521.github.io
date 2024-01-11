*** Settings ***
Documentation
...    | http://robotframework.org/SSHLibrary/SSHLibrary.html
...    |
...    | https://github.com/robotframework/SSHLibrary
...    | pip install --upgrade robotframework-sshlibrary
...
...    SSHLibrary is a Robot Framework test library for SSH and SFTP.
...    This document explains how to use keywords provided by SSHLibrary.
...    For information about installation, support, and more please visit the project page.
...    For more information about Robot Framework, see http://robotframework.org.

Library    SSHLibrary


*** Variables ***
${HOST}    127.0.0.1
${USERNAME}    root
${PASSWORD}    password


*** Test Cases ***
Example: SSH
    [Teardown]    Close All Connections

    Open Connection    ${HOST}
    Login    ${USERNAME}    ${PASSWORD}

    ${result}=    Execute Command    lsb_release -a
    Log    ${result}
    Log To Console    ${result}

    Close Connection


*** Keywords ***
