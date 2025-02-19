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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/RgbImage.o \
	${OBJECTDIR}/jesus_gutierrez_lopez.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-L/C/Users/Daniel/Desktop/GP\ dll/libs/ogl/lib -L/C/Users/Daniel/Desktop/GP\ dll/libs/soil/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/thanos.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/thanos.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/thanos ${OBJECTFILES} ${LDLIBSOPTIONS} -lSOIL -lopengl32 -lglu32 -lglew32 -lfreeglut

${OBJECTDIR}/RgbImage.o: RgbImage.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Users/Daniel/Desktop/GP\ dll/libs/ogl/include -I/C/Users/Daniel/Desktop/GP\ dll/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RgbImage.o RgbImage.cpp

${OBJECTDIR}/jesus_gutierrez_lopez.o: jesus_gutierrez_lopez.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Users/Daniel/Desktop/GP\ dll/libs/ogl/include -I/C/Users/Daniel/Desktop/GP\ dll/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jesus_gutierrez_lopez.o jesus_gutierrez_lopez.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/Users/Daniel/Desktop/GP\ dll/libs/ogl/include -I/C/Users/Daniel/Desktop/GP\ dll/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
