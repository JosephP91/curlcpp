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
CND_PLATFORM=GNU48-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CurlEasy.o \
	${OBJECTDIR}/CurlHeader.o \
	${OBJECTDIR}/CurlHttpPost.o \
	${OBJECTDIR}/CurlInterface.o \
	${OBJECTDIR}/CurlMessage.o \
	${OBJECTDIR}/CurlMulti.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lcurl -pedantic
CXXFLAGS=-lcurl -pedantic

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcurlcpp.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcurlcpp.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcurlcpp.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -dynamiclib -install_name libcurlcpp.${CND_DLIB_EXT} -fPIC

${OBJECTDIR}/CurlEasy.o: nbproject/Makefile-${CND_CONF}.mk CurlEasy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CurlEasy.o CurlEasy.cpp

${OBJECTDIR}/CurlHeader.o: nbproject/Makefile-${CND_CONF}.mk CurlHeader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CurlHeader.o CurlHeader.cpp

${OBJECTDIR}/CurlHttpPost.o: nbproject/Makefile-${CND_CONF}.mk CurlHttpPost.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CurlHttpPost.o CurlHttpPost.cpp

${OBJECTDIR}/CurlInterface.o: nbproject/Makefile-${CND_CONF}.mk CurlInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CurlInterface.o CurlInterface.cpp

${OBJECTDIR}/CurlMessage.o: nbproject/Makefile-${CND_CONF}.mk CurlMessage.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CurlMessage.o CurlMessage.cpp

${OBJECTDIR}/CurlMulti.o: nbproject/Makefile-${CND_CONF}.mk CurlMulti.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CurlMulti.o CurlMulti.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcurlcpp.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
