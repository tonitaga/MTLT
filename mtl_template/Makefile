BUILD_FOLDER_NAME="build"
CMAKE_PROJECT_NAME="mtl-template"
MTL_INSTALL_PATH="src/extern"

install_mtl:
	@cmake -S . -B ${BUILD_FOLDER_NAME}

build: install_mtl
	@cmake --build ${BUILD_FOLDER_NAME}

run:
	@${BUILD_FOLDER_NAME}/${CMAKE_PROJECT_NAME}

clean:
	@rm -rf ${BUILD_FOLDER_NAME}

uninstall_mtl:
	@rm -rf ${MTL_INSTALL_PATH}