CPMAddPackage(NAME allegro
	GITHUB_REPOSITORY liballeg/allegro5
	GIT_TAG 5.2.10.0

	OPTIONS "WANT_DOCS OFF"
	OPTIONS "WANT_DEMO OFF"
	OPTIONS "WANT_EXAMPLES OFF"
	OPTIONS "WANT_TESTS OFF"

	OPTIONS "WANT_TTF OFF"
	OPTIONS "WANT_MEMFILE OFF"
	OPTIONS "WANT_PHYSFS OFF"
	OPTIONS "WANT_VIDEO OFF"
	
	OPTIONS "WANT_STATIC_RUNTIME OFF"

	EXCLUDE_FROM_ALL TRUE
	SYSTEM TRUE
)


get_target_property(link_libraries allegro LINK_LIBRARIES)
#list(APPEND link_libraries freetype)
set_target_properties(allegro PROPERTIES LINK_LIBRARIES "${link_libraries}")

function(append_allegro_include_dir dir)
	get_target_property(include_dirs allegro INTERFACE_INCLUDE_DIRECTORIES)
	list(APPEND include_dirs "${dir}")
	set_target_properties(allegro PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${include_dirs}")
endfunction()

append_allegro_include_dir("$<BUILD_INTERFACE:${ALLEGRO_SOURCE_DIR}/include>")
append_allegro_include_dir("$<BUILD_INTERFACE:${CPM_PACKAGE_allegro_BINARY_DIR}/include>")

append_allegro_include_dir("$<BUILD_INTERFACE:${ALLEGRO_SOURCE_DIR}/addons/font>")
append_allegro_include_dir("$<BUILD_INTERFACE:${ALLEGRO_SOURCE_DIR}/addons/native_dialog>")
append_allegro_include_dir("$<BUILD_INTERFACE:${ALLEGRO_SOURCE_DIR}/addons/primitives>")
#append_allegro_include_dir("$<BUILD_INTERFACE:${ALLEGRO_SOURCE_DIR}/addons/ttf>")

#get_target_property(test allegro_monolith INTERFACE_INCLUDE_DIRECTORIES)
#message(FATAL_ERROR "allegro_monolith include dirs: ${test}")
