include ../../../config.mk


ROOT = ../../../../../
TEST_ROOT = ${ROOT}test/files/
DECRYPT_ROOT = ${TEST_ROOT}decrypt/


SRC = ${ROOT}src/
SRC_TEST = ${TEST_ROOT}src/
SRC_DECRYPT = ${DECRYPT_ROOT}src/


LIB = ${ROOT}lib/
LIB_TEST = ${TEST_ROOT}lib/

RES = ${ROOT}res/
RES_TEST = ${TEST_ROOT}res/


OBJ = ${ROOT}obj/linux/test/files/decrypt/

BUILD = ${ROOT}build/linux/test/files/decrypt/


APP = ${BUILD}app.out


MAIN_C = ${SRC_DECRYPT}main.c
MAIN_O = ${OBJ}main.o


ENCRYPTION_C = ${SRC}encryption.c
ENCRYPTION_H = ${LIB}encryption.h
ENCRYPTION_O = ${OBJ}encryption.o


COMMON_KEY_H = ${LIB}common_key.h


MATH_OPERATIONS_C = ${SRC}math_operations.c
MATH_OPERATIONS_H = ${LIB}math_operations.h
MATH_OPERATIONS_O = ${OBJ}math_operations.o


STRING_OPERATIONS_C = ${SRC}string_operations.c
STRING_OPERATIONS_H = ${LIB}string_operations.h
STRING_OPERATIONS_O = ${OBJ}string_operations.o


FILES_OPERATIONS_C = ${SRC_TEST}files_operations.c
FILES_OPERATIONS_H = ${LIB_TEST}files_operations.h
FILES_OPERATIONS_O = ${OBJ}files_operations.o


PATHS_H = ${RES_TEST}paths.h


RANDOM_GENERATOR_H = ${RES_TEST}random_generator.h


KEYS_DOMAIN_H = ${RES}keys_domain.h


NUMBERS_H = ${RES}numbers.h


OBJECTS = ${MAIN_O} ${FILES_OPERATIONS_O} ${ENCRYPTION_O} \
				${MATH_OPERATIONS_O} ${STRING_OPERATIONS_O}


.PHONY: all
all:    ${APP}


${APP}: ${OBJECTS}
	${CC} ${STD} ${CFLAGS} -o ${APP} ${OBJECTS}


${MAIN_O}: ${MAIN_C} ${FILES_OPERATIONS_H} ${ENCRYPTION_H} \
						${MATH_OPERATIONS_H} ${KEYS_DOMAIN_H} \
						${NUMBERS_H} ${PATHS_H} ${RANDOM_GENERATOR_H}
						
	${CC} ${STD} ${CFLAGS} -o ${MAIN_O} -c ${MAIN_C}


${FILES_OPERATIONS_O}: ${FILES_OPERATIONS_C} ${FILES_OPERATIONS_H} \
							${NUMBERS_H}

	${CC} ${STD} ${CFLAGS} -o ${FILES_OPERATIONS_O} -c ${FILES_OPERATIONS_C}


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


.PHONY: clean
clean:
		${RM} ${APP} ${OBJECTS}