# Adding test executables.
list(APPEND tests
	 app_test.cpp
	 cube.cpp
     )

# Enabling testing.
include(CTest)

# Iterating through the list of tests, adding target for each test and linking it,
# and adding its argument-less invocation to CTest.
foreach(test ${tests})
    # Get name without extension.
    get_filename_component(out_name ${test} NAME_WE)

    add_executable(${out_name} ${test})
	target_link_libraries(${out_name} PUBLIC GraphicsEngine ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glm glfw compiler_flags)

    # Add ./out_name to the list of tests performed by CTest, under the name TEST_out_name.
    add_test(NAME "TEST_${out_name}" COMMAND ${out_name})
endforeach()

# Copy resource files
add_custom_target(test_resources_folder ALL)
add_custom_command(TARGET test_resources_folder PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E create_symlink
				   ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)


