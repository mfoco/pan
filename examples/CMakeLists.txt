
add_subdirectory(numerical_diff)

if(WITH_PYTHON)
	add_subdirectory(forward_diff)
	add_subdirectory(eigen_interaction)
endif(WITH_PYTHON)