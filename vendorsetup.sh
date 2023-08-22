# ROM source patches

color="\033[0;32m"
end="\033[0m"

echo -e "${color}Applying patches !${end}"
sleep 1

# Patch bootanimation lag
rm -rf frameworks/native/libs/renderengine/threaded/RenderEngineThreaded.cpp

cp device/xiaomi/merlin/patches/frameworks/native/libs/renderengine/threaded/RenderEngineThreaded.cpp frameworks/native/libs/renderengine/threaded/
