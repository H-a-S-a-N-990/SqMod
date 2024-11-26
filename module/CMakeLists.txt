# Create the Squirrel module
add_library(SqModule MODULE SqBase.hpp Main.cpp
    # SDK
    SDK/sqmod.h
    # VCMP
    VCMP/vcmp.h
    VCMP/vcmp20.h
    VCMP/vcmp21.h
    # Sqrat
    Sqrat/sqratAllocator.h
    Sqrat/sqratArray.h
    Sqrat/sqratClass.h
    Sqrat/sqratClassType.h
    Sqrat/sqratConst.h
    Sqrat/sqratFunction.h
    Sqrat/sqratGlobalMethods.h
    Sqrat/sqratLightObj.h
    Sqrat/sqratMemberMethods.h
    Sqrat/sqratObject.h
    Sqrat/sqratOverloadMethods.h
    Sqrat/sqratScript.h
    Sqrat/sqratTable.h
    Sqrat/sqratTypes.h
    Sqrat/sqratUtil.h
    # Base
    Base/AABB.cpp Base/AABB.hpp
    Base/Circle.cpp Base/Circle.hpp
    Base/Color3.cpp Base/Color3.hpp
    Base/Color4.cpp Base/Color4.hpp
    Base/Quaternion.cpp Base/Quaternion.hpp
    Base/Shared.cpp Base/Shared.hpp
    Base/Sphere.cpp Base/Sphere.hpp
    Base/Vector2.cpp Base/Vector2.hpp
    Base/Vector2i.cpp Base/Vector2i.hpp
    Base/Vector3.cpp Base/Vector3.hpp
    Base/Vector4.cpp Base/Vector4.hpp
    # Core
    Core/Areas.cpp Core/Areas.hpp
    Core/Buffer.cpp Core/Buffer.hpp
    Core/Command.cpp Core/Command.hpp
    Core/Common.cpp Core/Common.hpp
    Core/Entity.cpp Core/Entity.hpp
    Core/Inventory.cpp Core/Inventory.hpp
    Core/Loot.cpp Core/Loot.hpp
    Core/Privilege.cpp Core/Privilege.hpp
    Core/Privilege/Base.cpp Core/Privilege/Base.hpp
    Core/Privilege/Class.cpp Core/Privilege/Class.hpp
    Core/Privilege/Entry.cpp Core/Privilege/Entry.hpp
    Core/Privilege/Unit.cpp Core/Privilege/Unit.hpp
    Core/Routine.cpp Core/Routine.hpp
    Core/Script.cpp Core/Script.hpp
    Core/Signal.cpp Core/Signal.hpp
    Core/Tasks.cpp Core/Tasks.hpp
    Core/ThreadPool.cpp Core/ThreadPool.hpp
    Core/Utility.cpp Core/Utility.hpp
    Core/VecMap.hpp
    # Entity
    Entity/Blip.cpp Entity/Blip.hpp
    Entity/Checkpoint.cpp Entity/Checkpoint.hpp
    Entity/KeyBind.cpp Entity/KeyBind.hpp
    Entity/Object.cpp Entity/Object.hpp
    Entity/Pickup.cpp Entity/Pickup.hpp
    Entity/Player.cpp Entity/Player.hpp
    Entity/Vehicle.cpp Entity/Vehicle.hpp
    # Library
    Library/Chrono.cpp Library/Chrono.hpp
    Library/Chrono/Date.cpp Library/Chrono/Date.hpp
    Library/Chrono/Datetime.cpp Library/Chrono/Datetime.hpp
    Library/Chrono/Time.cpp Library/Chrono/Time.hpp
    Library/Chrono/Timer.cpp Library/Chrono/Timer.hpp
    Library/Chrono/Timestamp.cpp Library/Chrono/Timestamp.hpp
    Library/CURL.cpp Library/CURL.hpp
    Library/Format.cpp Library/Format.hpp
    Library/IO.cpp Library/IO.hpp
    Library/IO/Buffer.cpp Library/IO/Buffer.hpp
    Library/IO/File.cpp Library/IO/File.hpp
    Library/IO/INI.cpp Library/IO/INI.hpp
    Library/IO/Stream.cpp Library/IO/Stream.hpp
    Library/JSON.cpp Library/JSON.hpp
    Library/MMDB.cpp Library/MMDB.hpp
    Library/Net.cpp Library/Net.hpp
    Library/Numeric.cpp Library/Numeric.hpp
    Library/Numeric/Math.cpp Library/Numeric/Math.hpp
    Library/Numeric/Random.cpp Library/Numeric/Random.hpp
    Library/RegEx.cpp Library/RegEx.hpp
    Library/String.cpp Library/String.hpp
    Library/System.cpp Library/System.hpp
    Library/System/Dir.cpp Library/System/Dir.hpp
    Library/System/Env.cpp Library/System/Env.hpp
    Library/System/Path.cpp Library/System/Path.hpp
    Library/UTF8.cpp Library/UTF8.hpp
    Library/Utils.cpp Library/Utils.hpp
    Library/Utils/Announce.cpp Library/Utils/Announce.hpp
    Library/Utils/String.cpp Library/Utils/String.hpp
    Library/Utils/Template.cpp Library/Utils/Template.hpp
    Library/Utils/Vector.cpp Library/Utils/Vector.hpp
    Library/XML.cpp Library/XML.hpp
    Library/ZMQ.cpp Library/ZMQ.hpp
    # Misc
    Misc/Broadcast.cpp
    Misc/Constants.cpp
    Misc/Register.cpp
    Misc/Algo.cpp Misc/Algo.hpp
    Misc/Functions.cpp Misc/Functions.hpp
    Misc/Model.cpp Misc/Model.hpp
    Misc/Player.cpp Misc/Player.hpp
    Misc/Vehicle.cpp Misc/Vehicle.hpp
    Misc/Weapon.cpp Misc/Weapon.hpp
    # POCO
    PocoLib/Crypto.cpp PocoLib/Crypto.hpp
    PocoLib/Data.cpp PocoLib/Data.hpp
    PocoLib/Net.cpp PocoLib/Net.hpp
    PocoLib/Register.cpp PocoLib/Register.hpp
    PocoLib/Time.cpp PocoLib/Time.hpp
    PocoLib/Util.cpp PocoLib/Util.hpp
    #
    Core.cpp Core.hpp
    Logger.cpp Logger.hpp
    Register.cpp
    Exports.cpp
)
# The module requires C++ 17
set_property(TARGET SqModule PROPERTY CXX_STANDARD 17)
# Various definitions required by the plug-in
target_compile_definitions(SqModule PRIVATE SCRAT_USE_EXCEPTIONS=1)
# SDK targeting
if(ENABLE_API21)
    target_compile_definitions(SqModule PRIVATE VCMP_SDK_2_1=1)
endif()
# Legacy compatibility with official plug-in
if(ENABLE_OFFICIAL)
    target_compile_definitions(SqModule PRIVATE VCMP_ENABLE_OFFICIAL=1)
    target_sources(SqModule PRIVATE Misc/Official.cpp Misc/Official.hpp)
endif()
# Link to windows libraries if on windows
if(WIN32 OR MINGW)
    target_compile_definitions(SqModule PRIVATE _WIN32_WINNT=0x0601)
    target_link_libraries(SqModule wsock32 ws2_32 shlwapi)
endif()
# Link to base libraries
target_link_libraries(SqModule RPMalloc Squirrel fmt::fmt SimpleINI TinyDir xxHash ConcurrentQueue SAJSON CPR UTF8Lib PUGIXML CivetWeb inja maxminddb libzmq-static)
# Link to POCO libraries
target_link_libraries(SqModule Poco::Foundation Poco::Crypto Poco::Data Poco::Net)
# Does POCO have SQLite support?
if(ENABLE_DATA_SQLITE)
    if(NOT POCO_UNBUNDLED)
        # We need to make sqlite3.h available for include. Ugly but POCO doesn't expose this directly.
        target_include_directories(SqModule PRIVATE "${PROJECT_SOURCE_DIR}/vendor/POCO/Data/SQLite/src")
    endif()
    message(STATUS "SQLite was enabled")
    # Link the libraries
    target_link_libraries(SqModule Poco::DataSQLite)
    # Inform the plug-in that it can make use of this library
    target_compile_definitions(SqModule PRIVATE SQMOD_POCO_HAS_SQLITE=1)
    # Include legacy implementation sources
    target_sources(SqModule PRIVATE Library/SQLite.hpp Library/SQLite.cpp)
endif()
# Do we have built-in MYSQL enabled?
if (NOT ENABLE_BUILTIN_MYSQL_C)
    find_package(MySQL)
endif()
# Does POCO have MySLQ support?
if(ENABLE_BUILTIN_MYSQL_C OR MYSQL_FOUND)
    message(STATUS "MySQL was enabled")
    # Link the libraries
    target_link_libraries(SqModule Poco::DataMySQL)
    # Inform the plug-in that it can make use of this library
    target_compile_definitions(SqModule PRIVATE SQMOD_POCO_HAS_MYSQL=1)
    # Include legacy implementation sources
    target_sources(SqModule PRIVATE Library/MySQL.hpp Library/MySQL.cpp)
endif()
# Does POCO have PostgreSQL support?
find_package(PostgreSQL)
if(POSTGRESQL_FOUND)
    # Link the libraries
    target_link_libraries(SqModule Poco::DataPostgreSQL)
    # Inform the plug-in that it can make use of this library
    target_compile_definitions(SqModule PRIVATE SQMOD_POCO_HAS_POSTGRESQL=1)
endif()
# Is Discord support enabled?
if(ENABLE_DISCORD)
target_link_libraries(SqModule dpp)
target_sources(SqModule PRIVATE
    Library/Discord.cpp Library/Discord.hpp
    Library/Discord/Application.hpp Library/Discord/Application.cpp
    Library/Discord/Automod.hpp Library/Discord/Automod.cpp
    Library/Discord/Channel.hpp Library/Discord/Channel.cpp
    Library/Discord/Client.hpp Library/Discord/Client.cpp
    Library/Discord/Cluster.hpp Library/Discord/Cluster.cpp
    Library/Discord/Command.hpp Library/Discord/Command.cpp
    Library/Discord/Constants.hpp Library/Discord/Constants.cpp
    Library/Discord/Events.hpp Library/Discord/Events.cpp
    Library/Discord/Guild.hpp Library/Discord/Guild.cpp
    Library/Discord/Integration.hpp Library/Discord/Integration.cpp
    Library/Discord/Message.hpp Library/Discord/Message.cpp
    Library/Discord/Misc.hpp Library/Discord/Misc.cpp
    Library/Discord/Presence.hpp Library/Discord/Presence.cpp
    Library/Discord/Role.hpp Library/Discord/Role.cpp
    Library/Discord/User.hpp Library/Discord/User.cpp
    Library/Discord/Utilities.hpp Library/Discord/Utilities.cpp
)
# Inform the plug-in that discord is enabled
target_compile_definitions(SqModule PRIVATE SQMOD_DISCORD=1)
endif()
# Determine if build mode
if(${CMAKE_BUILD_TYPE} MATCHES "(Release)+")
    target_compile_definitions(SqModule PRIVATE NDEBUG=1)
else()
    target_compile_definitions(SqModule PRIVATE _DEBUG=1 SQMOD_EXCEPTLOC=1)
endif()
# Strip binary
set_target_properties(SqModule PROPERTIES LINK_FLAGS_RELEASE -s)
# Force 32-bit binaries when necessary
if(FORCE_32BIT_BIN)
    set_target_properties(SqModule PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()
# Don't prefix the module binary.
set_target_properties(SqModule PROPERTIES PREFIX "")
# Customize module binary name/
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
        set_target_properties(SqModule PROPERTIES OUTPUT_NAME "mod_squirrel_64")
    else()
        set_target_properties(SqModule PROPERTIES OUTPUT_NAME "mod_squirrel_32")
    endif()
else(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
        set_target_properties(SqModule PROPERTIES OUTPUT_NAME "mod_squirrel_64")
    else()
        set_target_properties(SqModule PROPERTIES OUTPUT_NAME "mod_squirrel_32")
    endif()
endif(WIN32)
# Include current directory in the search path
target_include_directories(SqModule PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(SqModule PRIVATE ${CMAKE_CURRENT_LIST_DIR}/SDK)
target_include_directories(SqModule PRIVATE ${CMAKE_CURRENT_LIST_DIR}/VCMP)
target_include_directories(SqModule PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Sqrat)
# Include PCRE directory in the header search path
if (POCO_UNBUNDLED)
    find_package(PCRE REQUIRED)
    target_link_libraries(SqModule PRIVATE Pcre::Pcre)
else()
    # Get the foundation source folder path
    get_target_property(POCO_FOUNDATION_SOURCE_DIR Foundation SOURCE_DIR)
    target_include_directories(SqModule PRIVATE "${POCO_FOUNDATION_SOURCE_DIR}/src")
endif()
# Copy module into the plug-ins folder
add_custom_command(TARGET SqModule POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SqModule> "${PROJECT_SOURCE_DIR}/bin/plugins")
# Copy DPP into the bin folder
if (ENABLE_DISCORD)
    if (WIN32 OR MINGW)
        add_custom_command(TARGET SqModule POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:dpp> "${PROJECT_SOURCE_DIR}/bin")
    endif()
endif()
# Copy several dependent DLLs on windows to make distribution easier (used mainly by people that distribute builds)
if(WIN32 AND MINGW AND COPY_DEPENDENCIES)
    get_filename_component(MINGW_BIN_PATH ${CMAKE_C_COMPILER} DIRECTORY REALPATH)
    if(NOT IS_DIRECTORY ${MINGW_BIN_PATH})
        get_filename_component(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} DIRECTORY REALPATH)
    endif()
    # Make sure the deps folder exists
    file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/deps")
    # Copy dependencies into the deps folder (only so it can be distributed with the DLL)
    file(COPY "${MINGW_BIN_PATH}/zlib1.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libpq.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libzstd.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libpsl-5.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libffi-8.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libcurl-4.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libssh2-1.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libidn2-0.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libintl-8.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libxml2-2.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/liblzma-5.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libgmp-10.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libiconv-2.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libmariadb.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libtasn1-6.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libnettle-8.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libsodium-23.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libgnutls-30.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libhogweed-6.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libp11-kit-0.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libbrotlidec.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libbrotlicommon.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libunistring-5.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libnghttp2-14.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libwinpthread-1.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    file(COPY "${MINGW_BIN_PATH}/libstdc++-6.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
        file(COPY "${MINGW_BIN_PATH}/libgcc_s_seh-1.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
        file(COPY "${MINGW_BIN_PATH}/libssl-3-x64.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
        file(COPY "${MINGW_BIN_PATH}/libcrypto-3-x64.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    else()
        file(COPY "${MINGW_BIN_PATH}/libssl-3.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
        file(COPY "${MINGW_BIN_PATH}/libcrypto-3.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    endif()
    if(POCO_UNBUNDLED)
        file(COPY "${MINGW_BIN_PATH}/libexpat-1.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
        file(COPY "${MINGW_BIN_PATH}/libsqlite3-0.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin/deps")
    endif()
endif()
