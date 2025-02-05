#find_package(Freetype REQUIRED)

set(target "client")

add_executable(${target}
    actordrawer.cpp
    actordrawer.hpp

    bitmapservice.cpp
    bitmapservice.hpp

    bitmapset.cpp
    bitmapset.hpp

    client.cpp
    client.hpp

    fontservice.cpp
    fontservice.hpp

    game.cpp
    game.hpp

    gamestate.hpp

    gamestateaccountcreation.cpp
    gamestateaccountcreation.hpp

    gamestateaccountcreationawaitresponse.cpp
    gamestateaccountcreationawaitresponse.hpp

    gamestatecharactercreation.cpp
    gamestatecharactercreation.hpp

    gamestatecharactercreationawaitresponse.cpp
    gamestatecharactercreationawaitresponse.hpp

    gamestatecharacterview.cpp
    gamestatecharacterview.hpp

    gamestateinit.cpp
    gamestateinit.hpp

    gamestateloginawaitresponse.cpp
    gamestateloginawaitresponse.hpp

    gamestateplaying.cpp
    gamestateplaying.hpp

    gamestatequit.cpp
    gamestatequit.hpp

    gamestateserverconnect.cpp
    gamestateserverconnect.hpp

    gamestatetitle.cpp
    gamestatetitle.hpp

    observer.hpp

    screenmaker.hpp
    screenmakeraccountcreation.cpp
    screenmakeraccountcreationresponsewait.cpp
    screenmakercharactercreation.cpp
    screenmakercharactercreationawaitresponse.cpp
    screenmakercharacterview.cpp
    screenmakerempty.cpp
    screenmakerlogin.cpp
    screenmakerplaying.cpp
    screenmakertitle.cpp

    main.cpp
)
target_include_directories(${target}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${target}
	PRIVATE
		gameworld
		util
		network
		gui

		#freetype

		allegro
		allegro_color
		allegro_primitives
		allegro_image
		allegro_ttf
)
