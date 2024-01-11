*** Settings ***
Documentation
...    | Robot Framework User Guide
...    | https://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html


*** Variables ***


*** Test Cases ***
Example: Reserved Variables
    [Tags]    Variables

    Log To Console    ${{robot.__version__}}

    Log To Console    ${SUITE NAME}
    Log To Console    ${TEST NAME}
    Log To Console    ${TEST TAGS}

    Log To Console    ${TRUE}
    Log To Console    ${FALSE}
    Log To Console    ${EMPTY}

    # An absolute path to the directory where the test data file is located.
    # This variable is case-sensitive.
    Log To Console    ${CURDIR}

    # An absolute path to the system temporary directory.
    # In UNIX-like systems this is typically /tmp,
    # and in Windows c:\Documents and Settings\<user>\Local Settings\Temp.
    Log To Console    ${TEMPDIR}

    # An absolute path to the directory where test execution was started from.
    Log To Console    ${EXECDIR}

    # The system directory path separator.
    # / in UNIX-like systems and \ in Windows.
    Log To Console    ${/}

    # The system path element separator.
    # : in UNIX-like systems and ; in Windows.
    Log To Console    ${:}

    # The system line separator.
    # \n in UNIX-like systems and \r\n in Windows.
    Log To Console    ${\n}


*** Keywords ***
