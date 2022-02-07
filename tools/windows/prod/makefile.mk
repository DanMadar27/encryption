include ../config.mk


SRC = ..\..\..\src
LIB = ..\..\..\lib
RES = ..\..\..\res
OBJ = ..\..\..\obj\windows\prod
BUILD = ..\..\..\build\windows\prod


APP = ${BUILD}\app.exe


MAIN_C = ${SRC}\main.c
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


TEST_ENCRYPTION_C = ${SRC}\test_encryption.c
TEST_ENCRYPTION_H = ${LIB}\test_encryption.h
TEST_ENCRYPTION_O = ${OBJ}\test_encryption.o


INPUT_OPERATIONS_C = ${SRC}\input_operations.c
INPUT_OPERATIONS_H = ${LIB}\input_operations.h
INPUT_OPERATIONS_O = ${OBJ}\input_operations.o


KEYS_DOMAIN_H = ${RES}\keys_domain.h


NUMBERS_H = ${RES}\numbers.h


OBJECTS = ${MAIN_O} ${TEST_ENCRYPTION_O} ${ENCRYPTION_O} \
				${MATH_OPERATIONS_O} ${STRING_OPERATIONS_O} \
				${INPUT_OPERATIONS_O}


.PHONY: all
all:    ${APP}


${APP}: ${OBJECTS}
	${CC} ${STD} ${CFLAGS} -o ${APP} ${OBJECTS}


${MAIN_O}: ${MAIN_C} ${TEST_ENCRYPTION_H} ${ENCRYPTION_H} \
			${${INPUT_OPERATIONS_H} ${KEYS_DOMAIN_H} ${NUMBERS_H}

	${CC} ${STD} ${CFLAGS} -o ${MAIN_O} -c ${MAIN_C}


${TEST_ENCRYPTION_O}: ${TEST_ENCRYPTION_C} ${TEST_ENCRYPTION_H}\
						${ENCRYPTION_H} ${COMMON_KEY_H} ${MATH_OPERATIONS_H} \
						${KEYS_DOMAIN_H} ${NUMBERS_H}

	${CC} ${STD} ${CFLAGS} -o ${TEST_ENCRYPTION_O} -c ${TEST_ENCRYPTION_C}


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


.PHONY: clean
clean:
		${RM} ${APP} ${OBJECTS}