set(
	PCRE_TEST 
	${TEST_DIR}/pcre.cc
	${SRC_DIR}/utils/pcre.cc
)
add_executable(test_pcre ${PCRE_TEST})
target_link_libraries(test_pcre pcred)

ADD_TEST(T_CONF "./bin/test_pcre")