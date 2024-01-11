*** Settings ***
Documentation
...    | Robot Framework User Guide
...    | https://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html

Library    OperatingSystem


*** Variables ***


*** Test Cases ***
Example: Keywords
    [Tags]    Keywords

    ${result}=    Run    robot --version
    Set Test Documentation    ${result}
    Repeat Keyword    2    Log To Console    ${result}
    Pass Execution    ${result}


*** Keywords ***
