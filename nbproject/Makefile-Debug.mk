#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/982968635/MurmurHash32.o \
	${OBJECTDIR}/memo_command_interpreter.o \
	${OBJECTDIR}/_ext/982968635/MurmurHash64A.o \
	${OBJECTDIR}/_ext/1431108635/memo.o \
	${OBJECTDIR}/_ext/853948430/random.o \
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/memo100

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/memo100: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/memo100 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/982968635/MurmurHash32.o: ../hashing/MurmurHash32.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/982968635
	${RM} $@.d
	$(COMPILE.c) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/982968635/MurmurHash32.o ../hashing/MurmurHash32.c

${OBJECTDIR}/memo_command_interpreter.o: memo_command_interpreter.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/memo_command_interpreter.o memo_command_interpreter.c

${OBJECTDIR}/_ext/982968635/MurmurHash64A.o: ../hashing/MurmurHash64A.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/982968635
	${RM} $@.d
	$(COMPILE.c) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/982968635/MurmurHash64A.o ../hashing/MurmurHash64A.c

${OBJECTDIR}/_ext/1431108635/memo.o: ../memoization/memo.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1431108635
	${RM} $@.d
	$(COMPILE.c) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1431108635/memo.o ../memoization/memo.c

${OBJECTDIR}/_ext/853948430/random.o: ../random/random.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/853948430
	${RM} $@.d
	$(COMPILE.c) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/853948430/random.o ../random/random.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/cuckoo_hashing_test_3_byte_key_9_byte_value.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/cuckoo_hashing_test_fill_table.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/generate_artificial_operation_sequence_feedback.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/generate_operation_sequence_without_feedback.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/hashing_test_read_write_delete.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/linear_probe_test_3_byte_key_9_byte_value.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/linear_probe_test_fill_table.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/cuckoo_hashing_test_3_byte_key_9_byte_value.o: tests/cuckoo_hashing_test_3_byte_key_9_byte_value.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/cuckoo_hashing_test_3_byte_key_9_byte_value.o tests/cuckoo_hashing_test_3_byte_key_9_byte_value.c


${TESTDIR}/tests/cuckoo_hashing_test_fill_table.o: tests/cuckoo_hashing_test_fill_table.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/cuckoo_hashing_test_fill_table.o tests/cuckoo_hashing_test_fill_table.c


${TESTDIR}/tests/generate_artificial_operation_sequence_feedback.o: tests/generate_artificial_operation_sequence_feedback.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/generate_artificial_operation_sequence_feedback.o tests/generate_artificial_operation_sequence_feedback.c


${TESTDIR}/tests/generate_operation_sequence_without_feedback.o: tests/generate_operation_sequence_without_feedback.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/generate_operation_sequence_without_feedback.o tests/generate_operation_sequence_without_feedback.c


${TESTDIR}/tests/hashing_test_read_write_delete.o: tests/hashing_test_read_write_delete.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/hashing_test_read_write_delete.o tests/hashing_test_read_write_delete.c


${TESTDIR}/tests/linear_probe_test_3_byte_key_9_byte_value.o: tests/linear_probe_test_3_byte_key_9_byte_value.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/linear_probe_test_3_byte_key_9_byte_value.o tests/linear_probe_test_3_byte_key_9_byte_value.c


${TESTDIR}/tests/linear_probe_test_fill_table.o: tests/linear_probe_test_fill_table.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.c) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/linear_probe_test_fill_table.o tests/linear_probe_test_fill_table.c


${OBJECTDIR}/_ext/982968635/MurmurHash32_nomain.o: ${OBJECTDIR}/_ext/982968635/MurmurHash32.o ../hashing/MurmurHash32.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/982968635
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/982968635/MurmurHash32.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/982968635/MurmurHash32_nomain.o ../hashing/MurmurHash32.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/982968635/MurmurHash32.o ${OBJECTDIR}/_ext/982968635/MurmurHash32_nomain.o;\
	fi

${OBJECTDIR}/memo_command_interpreter_nomain.o: ${OBJECTDIR}/memo_command_interpreter.o memo_command_interpreter.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/memo_command_interpreter.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/memo_command_interpreter_nomain.o memo_command_interpreter.c;\
	else  \
	    ${CP} ${OBJECTDIR}/memo_command_interpreter.o ${OBJECTDIR}/memo_command_interpreter_nomain.o;\
	fi

${OBJECTDIR}/_ext/982968635/MurmurHash64A_nomain.o: ${OBJECTDIR}/_ext/982968635/MurmurHash64A.o ../hashing/MurmurHash64A.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/982968635
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/982968635/MurmurHash64A.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/982968635/MurmurHash64A_nomain.o ../hashing/MurmurHash64A.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/982968635/MurmurHash64A.o ${OBJECTDIR}/_ext/982968635/MurmurHash64A_nomain.o;\
	fi

${OBJECTDIR}/_ext/1431108635/memo_nomain.o: ${OBJECTDIR}/_ext/1431108635/memo.o ../memoization/memo.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1431108635
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1431108635/memo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1431108635/memo_nomain.o ../memoization/memo.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1431108635/memo.o ${OBJECTDIR}/_ext/1431108635/memo_nomain.o;\
	fi

${OBJECTDIR}/_ext/853948430/random_nomain.o: ${OBJECTDIR}/_ext/853948430/random.o ../random/random.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/853948430
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/853948430/random.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/853948430/random_nomain.o ../random/random.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/853948430/random.o ${OBJECTDIR}/_ext/853948430/random_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/memo100

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
