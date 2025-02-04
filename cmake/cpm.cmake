# This code is modified from: (as of 5/17/2023)
# https://github.com/cpm-cmake/CPM.cmake/wiki/Downloading-CPM.cmake-in-CMake

function(_configure)
	set(output_root "${PROJECT_BINARY_DIR}/cmake")
	set(output_path "${output_root}/CPM.cmake")

	set(version "0.40.4")  # Versions: https://github.com/cpm-cmake/CPM.cmake/releases
	set(url "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${version}/CPM.cmake")
	set(expected_hash "f1218240e93d332bfda693d92a315449")

	list(APPEND CMAKE_MODULE_PATH "${output_root}")
	list(APPEND CMAKE_PREFIX_PATH "${output_root}")

	# If the file already exists, check its hash.
	# If the hash is not expected, remove the file before re-downloading.
	# This is useful when updating to a new version where the expected
	# hash changes, but a previous version already exists on-disk.
	if(EXISTS "${output_path}")
		file(MD5 "${output_path}" output_hash)

		if(NOT "${output_hash}" STREQUAL "${expected_hash}")
			message(WARNING "CPM.cmake hash mismatch! Removing ${output_path}")
			file(REMOVE "${output_path}")
		endif()
	endif()

	# Download CPM.cmake
	if(NOT EXISTS "${output_path}")
		message(STATUS "Downloading CPM.cmake to ${output_path}")
		file(DOWNLOAD "${url}" "${output_path}")
	endif()

	# Validate hash
	file(MD5 "${output_path}" output_hash)

	if(NOT "${output_hash}" STREQUAL "${expected_hash}")
		string(JOIN "\n " msg " "
			"CPM.cmake hash mismatch! This is suspicious and could warrant further investigation."
			"To continue, update expected_hash: ${CMAKE_CURRENT_LIST_FILE}:0"
			""
			"Expected: ${expected_hash}"
			"Received: ${output_hash}"
			"")
		file(REMOVE "${output_path}")
		message(FATAL_ERROR "${msg}")
	endif()

	include("${output_path}")
endfunction()

include_guard(GLOBAL)
_configure()
