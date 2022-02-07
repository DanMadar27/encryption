include ../../../config.mk


ROOT = ..\..\..\..\..
TEST_ROOT = ${ROOT}\test\messages
SERVER_ROOT = ${TEST_ROOT}\server

SRC = ${ROOT}\src
SRC_SERVER = ${SERVER_ROOT}\src

LIB = ${ROOT}\lib
LIB_SERVER = ${SERVER_ROOT}\lib

RES = ${ROOT}\res
RES_TEST = ${TEST_ROOT}\res

OBJ = ${ROOT}\obj\windows\test\messages\server

BUILD = ${ROOT}\build\windows\test\messages\server


APP = ${BUILD}\app.exe


MAIN_C = ${SRC_SERVER}\main.c
MAIN_O = ${OBJ}\main.o


ENCRYPTION_C = ${SRC}\encryption.c
ENCRYPTION_H = ${LIB}\encryption.h
ENCRYPTION_O = ${OBJ}\encryption.o


COMMON_KEY_H = ${LIB}\common_key.h


MATH_OPERATIONS_C = ${SRC}\math_operations.c
MATH_OPERATIONS_H = ${LIB}\math_operations.h
MATH_OPERATIONS_O = ${OBJ}\math_operations.o


STRING_OPERATIONS_C = ${SRC}\string_operations.c
STRING_OPERATIONS_H = ${LIB}\string_operations.h
STRING_OPERATIONS_O = ${OBJ}\string_operations.o


INPUT_OPERATIONS_C = ${SRC}\input_operations.c
INPUT_OPERATIONS_H = ${LIB}\input_operations.h
INPUT_OPERATIONS_O = ${OBJ}\input_operations.o


SERVER_C = ${SRC_SERVER}\server.c
SERVER_H = ${LIB_SERVER}\server.h
SERVER_O = ${OBJ}\server.o


KEYS_DOMAIN_H = ${RES}\keys_domain.h


NUMBERS_H = ${RES}\numbers.h


CONNECTION_H = ${RES_TEST}\connection.h


MESSAGES_H = ${RES_TEST}\messages.h


OBJECTS = ${MAIN_O} ${SERVER_O} ${ENCRYPTION_O} ${INPUT_OPERATIONS_O} \
				${MATH_OPERATIONS_O} ${STRING_OPERATIONS_O}


.PHONY: all
all:    ${APP}


${APP}: ${OBJECTS}
	${CC} ${STD} ${CFLAGS} -o ${APP} ${OBJECTS}


${MAIN_O}: ${MAIN_C} ${SERVER_H}
	${CC} ${STD} ${CFLAGS} -o ${MAIN_O} -c ${MAIN_C}


${ENCRYPTION_O}: ${ENCRYPTION_C} ${ENCRYPTION_H} ${COMMON_KEY_H} \
				${MATH_OPERATIONS_H} ${STRING_OPERATIONS_H} \
				${KEYS_DOMAIN_H} ${NUMBERS_H}

	${CC} ${STD} ${CFLAGS} -o ${ENCRYPTION_O} -c ${ENCRYPTION_C} 


${MATH_OPERATIONS_O}: ${MATH_OPERATIONS_C} \
				${MATH_OPERATIONS_H} ${STRING_OPERATIONS_H} \
				${NUMBERS_H}

	${CC} ${STD} ${CFLAGS} -o ${MATH_OPERATIONS_O} -c ${MATH_OPERATIONS_C}


${STRING_OPERATIONS_O}: ${STRING_OPERATIONS_C} ${STRING_OPERATIONS_H} \
						${NUMBERS_H}
	
	${CC} ${STD} ${CFLAGS} -o ${STRING_OPERATIONS_O} -c ${STRING_OPERATIONS_C}


${INPUT_OPERATIONS_O}: ${INPUT_OPERATIONS_C} ${INPUT_OPERATIONS_H} ${NUMBERS_H}
	${CC} ${STD} ${CFLAGS} -o ${INPUT_OPERATIONS_O} -c ${INPUT_OPERATIONS_C}


${SERVER_O}: ${SERVER_C} ${SERVER_H} ${ENCRYPTION_H} ${INPUT_OPERATIONS_H} \
							${CONNECTION_H} ${MESSAGES_H} \
							${KEYS_DOMAIN_H} ${NUMBERS_H}
	
	${CC} ${STD} ${CFLAGS} -o ${SERVER_O} -c ${SERVER_C}


.PHONY: clean
clean:
		${RM} ${APP} ${OBJECTS}