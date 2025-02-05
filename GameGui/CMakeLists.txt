set(target "gui")

add_library(${target} STATIC
    color3.hpp
    
    guiincludes.hpp

    guibase.cpp
    guibase.hpp

    guibutton.cpp
    guibutton.hpp

    guiframe.cpp
    guiframe.hpp

    guiimagebutton.cpp
    guiimagebutton.hpp

    guiimageelement.cpp
    guiimageelement.hpp

    guiimagelabel.cpp
    guiimagelabel.hpp

    guilabel.cpp
    guilabel.hpp

    guiobject.cpp
    guiobject.hpp

    guipasswordtextbox.cpp
    guipasswordtextbox.hpp
    
    guiscreen.cpp
    guiscreen.hpp

    guiselectionservice.cpp
    guiselectionservice.hpp

    guitextbox.cpp
    guitextbox.hpp

    guitextbutton.cpp
    guitextbutton.hpp

    guitextelement.cpp
    guitextelement.hpp

    guitextlabel.cpp
    guitextlabel.hpp

    observer.hpp
)

target_include_directories(${target}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${target}
    PRIVATE
        allegro
        allegro_color
        allegro_primitives
        allegro_image
        allegro_ttf
)

project_dll_export(${target})
