include ../../../config.mk


ROOT = ..\..\..\..\..
TEST_ROOT = ${ROOT}\test\messages
CLIENT_ROOT = ${TEST_ROOT}\client

SRC = ${ROOT}\src
SRC_CLIENT = ${CLIENT_ROOT}\src

LIB = ${ROOT}\lib
LIB_CLIENT = ${CLIENT_ROOT}\lib

RES = ${ROOT}\res
RES_TEST = ${TEST_ROOT}\res

OBJ = ${ROOT}\obj\windows\test\messages\client

BUILD = ${ROOT}\build\windows\test\messages\client


APP = ${BUILD}\app.exe


MAIN_C = ${SRC_CLIENT}\main.c
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


CLIENT_C = ${SRC_CLIENT}\client.c
CLIENT_H = ${LIB_CLIENT}\client.h
CLIENT_O = ${OBJ}\client.o


KEYS_DOMAIN_H = ${RES}\keys_domain.h


NUMBERS_H = ${RES}\numbers.h


CONNECTION_H = ${RES_TEST}\connection.h


MESSAGES_H = ${RES_TEST}\messages.h


OBJECTS = ${MAIN_O} ${CLIENT_O} ${ENCRYPTION_O} ${INPUT_OPERATIONS_O} \
				${MATH_OPERATIONS_O} ${STRING_OPERATIONS_O}


.PHONY: all
all:    ${APP}


${APP}: ${OBJECTS}
	${CC} ${STD} ${CFLAGS} -o ${APP} ${OBJECTS}


${MAIN_O}: ${MAIN_C} ${CLIENT_H}
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


${CLIENT_O}: ${CLIENT_C} ${CLIENT_H} ${ENCRYPTION_H} ${INPUT_OPERATIONS_H} \
							${CONNECTION_H} ${MESSAGES_H} \
							${KEYS_DOMAIN_H} ${NUMBERS_H}

	${CC} ${STD} ${CFLAGS} -o ${CLIENT_O} -c ${CLIENT_C}


.PHONY: clean
clean:
		${RM} ${APP} ${OBJECTS}