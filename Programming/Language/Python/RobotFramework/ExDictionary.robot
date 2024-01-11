*** Settings ***
Documentation
...    | Robot Framework User Guide
...    | https://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html

Library    Collections

*** Variables ***


*** Test Cases ***
Example: Dictionary
    [Tags]    Dictionary

    ${result}=    Keywords: Create Dictionary
    FOR    ${key}    IN    @{result.keys()}
        Log To Console    ${result["${key}"]}
    END
    Log Dictionary    ${result}

    Keywords: Get Dictionary Items    ${result}
    Keywords: Get Dictionary Keys    ${result}
    Keywords: Get Dictionary Values    ${result}
    Keywords: Get From Dictionary    ${result}
    Keywords: Pop From Dictionary    ${result}


*** Keywords ***
Keywords: Create Dictionary
    [Arguments]
    [Return]    ${retVal}

    ${retVal}=    Create Dictionary
    Set To Dictionary    ${retVal}    key1=value_a
    Set To Dictionary    ${retVal}    key2=value_b
    Set To Dictionary    ${retVal}    key3=value_c

Keywords: Get Dictionary Items
    [Arguments]    ${pDictionary}
    [Return]

    # sort_keys is a new option in Robot Framework 3.1.2. Earlier items were always sorted based on keys.
    ${sorted}=    Get Dictionary Items    ${pDictionary}
    Log List    ${sorted}
    Log To Console    ${sorted}

    ${unsorted}=    Get Dictionary Items    ${pDictionary}    sort_keys=False
    Log List    ${unsorted}
    Log To Console    ${unsorted}

Keywords: Get Dictionary Keys
    [Arguments]    ${pDictionary}
    [Return]

    # sort_keys is a new option in Robot Framework 3.1.2. Earlier keys were always sorted.
    ${sorted}=    Get Dictionary Keys    ${pDictionary}
    Log List    ${sorted}
    Log To Console    ${sorted}

    ${unsorted}=    Get Dictionary Keys    ${pDictionary}    sort_keys=False
    Log List    ${unsorted}
    Log To Console    ${unsorted}

Keywords: Get Dictionary Values
    [Arguments]    ${pDictionary}
    [Return]

    # sort_keys is a new option in Robot Framework 3.1.2. Earlier values were always sorted based on keys.
    ${sorted}=    Get Dictionary Values    ${pDictionary}
    Log List    ${sorted}
    Log To Console    ${sorted}

    ${unsorted}=    Get Dictionary Values    ${pDictionary}    sort_keys=False
    Log List    ${unsorted}
    Log To Console    ${unsorted}

Keywords: Get From Dictionary
    [Arguments]    ${pDictionary}
    [Return]

    ${value}=    Get From Dictionary    ${pDictionary}    key1
    Log To Console    ${value}

Keywords: Pop From Dictionary
    [Arguments]    ${pDictionary}
    [Return]

    ${value}=    Pop From Dictionary    ${pDictionary}    key1
    Log To Console    ${value}
