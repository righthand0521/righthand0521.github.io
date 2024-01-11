*** Settings ***
Documentation
...    | Robot Framework User Guide
...    | https://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html

Library    String


*** Variables ***


*** Test Cases ***
Example: For Loop
    [Tags]    For

    Keywords: For Loop In Range    3
    Keywords: For Loop In Elements


*** Keywords ***
Keywords: For Loop In Range
    [Arguments]    ${pRange}
    [Return]

    FOR    ${pLength}    IN RANGE    1    ${pRange}
        ${random string}=    Generate Random String    ${pLength}
    END

Keywords: For Loop In Elements
    [Arguments]
    [Return]

    @{itemList}=    Create List    Good Element 1    Break On Me    Good Element 2
    FOR    ${pElement}    IN    @{itemList}
        Run Keyword If    '${pElement}' == 'Break On Me'    Exit For Loop
        ${pElement}=    Replace String    ${pElement}    ${SPACE}    ${EMPTY}
    END
