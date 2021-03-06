file(GLOB_RECURSE cpp_files "./**/*.cpp")
file(GLOB_RECURSE h_files "./**/*.h")
file(GLOB_RECURSE mm_files "./**/*.mm")

add_library(eleusis SHARED ${cpp_files} ${h_files} ${mm_files})

target_include_directories(eleusis PUBLIC "./")
target_include_directories(eleusis PUBLIC "./00_eventing")
target_include_directories(eleusis PUBLIC "./01_os_backend")
target_include_directories(eleusis PUBLIC "./02_visual_parameters")
target_include_directories(eleusis PUBLIC "./03_noding")
target_include_directories(eleusis PUBLIC "./04_visual_primitives")
target_include_directories(eleusis PUBLIC "./04_visual_primitives/01_shapes")
target_include_directories(eleusis PUBLIC "./04_visual_primitives/02_text_block/01_text_block_impl")
target_include_directories(eleusis PUBLIC "./04_visual_primitives/02_text_block/01_select_edit")
target_include_directories(eleusis PUBLIC "./05_animation")
target_include_directories(eleusis PUBLIC "./07_controls/01_control_common")
target_include_directories(eleusis PUBLIC "./08_utilities")

target_include_directories(eleusis PUBLIC "${GTK_ROOT}/include/cairo")
target_include_directories(eleusis PUBLIC "${GTK_ROOT}/include/pango-1.0")
target_include_directories(eleusis PUBLIC "${GTK_ROOT}/include/glib-2.0")
target_include_directories(eleusis PUBLIC "${GTK_ROOT}/include/harfbuzz")
target_include_directories(eleusis PUBLIC "${GTK_ROOT}/lib/glib-2.0/include")

target_link_libraries(eleusis PUBLIC "${GTK_ROOT}/lib/${LIB_PREFIX}cairo.${LIB_EXTENSION}")
target_link_libraries(eleusis PUBLIC "${GTK_ROOT}/lib/${LIB_PREFIX}pango-1.0.${LIB_EXTENSION}")
target_link_libraries(eleusis PUBLIC "${GTK_ROOT}/lib/${LIB_PREFIX}pangocairo-1.0.${LIB_EXTENSION}")
target_link_libraries(eleusis PUBLIC "${GTK_ROOT}/lib/${LIB_PREFIX}gobject-2.0.${LIB_EXTENSION}")

if (WIN32)
	add_definitions(-DELEUSIS_EXPORTS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /GS /W3 /Gy /Zc:wchar_t /Zi /Gm- /fp:precise /errorReport:prompt /WX- /Zc:forScope /Gd /Oi /EHsc /nologo")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL /Zc:inline")
endif (WIN32)

if (APPLE)
	find_library(COCOA_LIBRARY Cocoa)
	target_link_libraries(eleusis PUBLIC ${COCOA_LIBRARY})
	find_library(QUARTZ_CORE_LIBRARY QuartzCore)
	target_link_libraries(eleusis PUBLIC ${QUARTZ_CORE_LIBRARY})
endif (APPLE)

