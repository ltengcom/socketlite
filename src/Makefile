#****************************************************************************
#
# Makefile for socketlite
# bolide zhang
# bolidezhang@gmail.com
#
# This is a GNU make (gmake) makefile
#****************************************************************************

# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG          := NO

# PROFILE can be set to YES to include profiling info, or NO otherwise
PROFILE        := NO

# USE_STL can be used to turn on STL support. NO, then STL
# will not be used. YES will include the STL files.
USE_STL := YES

# WIN32_ENV
WIN32_ENV := YES
#****************************************************************************

CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

# ifeq (YES, ${WIN32_ENV})
#   RM     := del
# else
#   RM     := rm -f
# endif

DEBUG_CFLAGS     := -Wall -Wno-format -g -DDEBUG -DSOCKETLITE_LOG_USE_LOG4CPLUS -DSOCKETLITE_USE_OPENSSL -DSOCKETLITE_USE_THRIFT -DSOCKETLITE_CPLUSPLUS_STD_TR1
RELEASE_CFLAGS   := -Wall -Wno-unknown-pragmas -Wno-format -O3 -DSOCKETLITE_LOG_USE_LOG4CPLUS -DSOCKETLITE_USE_OPENSSL -DSOCKETLITE_USE_THRIFT -DSOCKETLITE_CPLUSPLUS_STD_TR1

DEBUG_CXXFLAGS   := ${DEBUG_CFLAGS}
RELEASE_CXXFLAGS := ${RELEASE_CFLAGS}

DEBUG_LDFLAGS    := -g
RELEASE_LDFLAGS  := -O3

ifeq (YES, ${DEBUG})
   CFLAGS       := ${DEBUG_CFLAGS}
   CXXFLAGS     := ${DEBUG_CXXFLAGS}
   LDFLAGS      := ${DEBUG_LDFLAGS}
else
   CFLAGS       := ${RELEASE_CFLAGS}
   CXXFLAGS     := ${RELEASE_CXXFLAGS}
   LDFLAGS      := ${RELEASE_LDFLAGS}
endif

ifeq (YES, ${PROFILE})
   CFLAGS   := ${CFLAGS} -pg -O3
   CXXFLAGS := ${CXXFLAGS} -pg -O3
   LDFLAGS  := ${LDFLAGS} -pg
endif

#****************************************************************************
# Preprocessor directives
#****************************************************************************

ifeq (YES, ${USE_STL})
  DEFS := -DUSE_STL
else
  DEFS :=
endif

#****************************************************************************
# Include paths
#****************************************************************************

#INCS := -I/usr/include/g++-2 -I/usr/local/include
INCS := -I../deps/boost -I/usr/local/include -I../include -I./thrift -I./thrift/transport -I./thrift/protocol
LIBS := -lpthread 

#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

CFLAGS   := ${CFLAGS}   ${DEFS}
CXXFLAGS := ${CXXFLAGS} ${DEFS}

#****************************************************************************
# Targets of the build
#****************************************************************************

OUTPUT := libsocketlite.a

all: ${OUTPUT}


#****************************************************************************
# Source files
#****************************************************************************

SRCS := SL_Application.cpp \
SL_Crypto_AES.cpp \
SL_Crypto_Base64.cpp \
SL_Crypto_CRTRand.cpp \
SL_Crypto_Hex.cpp \
SL_Crypto_MD5.cpp \
SL_Crypto_RaknetRand.cpp \
SL_Crypto_SHA1.cpp \
SL_OS_API.cpp \
SL_OS_File.cpp \
SL_Random.cpp \
SL_Seda_TimerQueue.cpp \
SL_Socket_CommonAPI.cpp \
SL_Socket_Handler.cpp \
SL_Socket_INET_Addr.cpp \
SL_Socket_Iocp_Message_Handler.cpp \
SL_Socket_Message_Handler.cpp \
SL_Socket_SendControl_HandlerManager.cpp \
SL_Socket_TcpClient_AutoConnect.cpp \
SL_Thread_Group.cpp \
./thrift/TApplicationException.cpp \
./thrift/transport/TBufferTransports.cpp \
./thrift/Thrift.cpp



# Add on the sources for libraries
SRCS := ${SRCS}

OBJS := $(addsuffix .o,$(basename ${SRCS}))

#****************************************************************************
# Output
#****************************************************************************

${OUTPUT}: ${OBJS}
#	${LD} -o $@ ${LDFLAGS} ${OBJS} ${LIBS} ${EXTRA_LIBS}
	$(AR) $@ $(OBJS)
	cp ${OUTPUT} ../lib/socketlite
#****************************************************************************
# common rules
#****************************************************************************

# Rules for compiling source files to object files
%.o : %.cpp
	${CXX} -c -std=c++0x ${CXXFLAGS} ${INCS} $< -o $@

%.o : %.c
	${CC} -c -std=c++0x ${CFLAGS} ${INCS} $< -o $@

dist:
	bash makedistlinux

clean:
	${RM} core ${OBJS} ${OUTPUT}

depend:
	#makedepend ${INCS} ${SRCS}

%.o: %.h
