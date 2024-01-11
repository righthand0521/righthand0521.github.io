*** Settings ***
Documentation
...    | Robot Framework User Guide
...    | https://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html


Library    Collections


*** Variables ***


*** Test Cases ***
Example: Template
    [Tags]    Template

    [Template]    Keywords: Template
        2
        0

*** Keywords ***
Keywords: Template
    [Arguments]    ${pKey}
    [Return]

    ${itemDictionary}=    Create Dictionary    0=First Name    2=Email
    ${value} =    Get From Dictionary    ${itemDictionary}    ${pKey}
    Log To Console    ${value}
