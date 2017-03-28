# Copyright (C) 2015 Christopher Gilbert.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
# Locate example sources
#
FILE (GLOB_RECURSE example_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#
# Example build rules
#
IF (NOT CMAKE_CROSSCOMPILING)
	FOREACH (T_FILE ${example_SRCS})
		GET_FILENAME_COMPONENT (T_NAME ${T_FILE} NAME_WE)
		ADD_EXECUTABLE (${T_NAME} ${T_FILE})
		TARGET_LINK_LIBRARIES(${T_NAME} ${ICU_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
	ENDFOREACH (T_FILE ${example_SRCS})
ENDIF (NOT CMAKE_CROSSCOMPILING)