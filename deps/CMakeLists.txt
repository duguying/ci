# get and build pcre

ADD_CUSTOM_COMMAND(
	OUTPUT pcre.zip
	COMMAND ${WGET} http://sourceforge.net/projects/gnuwin32/files/pcre/7.0/pcre-7.0-lib.zip/download -O pcre.zip -o download.log
	DEPENDS ${WGET}
	COMMENT "downloading pcre, please wait..."
)

ADD_CUSTOM_TARGET(pcre ALL
	DEPENDS ${CMAKE_BINARY_DIR}/pcre.zip
	COMMAND ${UNZIP} -X -n -q ${CMAKE_BINARY_DIR}/pcre.zip
	COMMENT "unzipping pcre, please wait..."
)

FIND_PATH(
   PCRE_PATH
   pcre.lib
   ${CMAKE_CURRENT_SOURCE_DIR}/build/*/lib/
   ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/
   DEPENDS pcre
)



