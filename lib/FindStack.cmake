
FIND_PROGRAM(STACK_EXECUTABLE stack)

IF (STACK_EXECUTABLE)
    EXECUTE_PROCESS(
        COMMAND stack setup
    )
    SET(STACK_FOUND TRUE)
ELSE (STACK_EXECUTABLE)
	SET(STACK_FOUND FALSE)
ENDIF (STACK_EXECUTABLE)
