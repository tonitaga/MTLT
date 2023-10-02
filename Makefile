CXX_GCC=g++.exe
COMPILER_CXX_GCC_LOCATION_BACKSLASH := $(shell g++ -v 2>&1 | grep COLLECT_GCC | sed 's/.*=//')
COMPILER_CXX_GCC_LOCATION_SLASH := $(subst \,/,$(COMPILER_CXX_GCC_LOCATION_BACKSLASH))
COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_BACKSLASH := $(subst bin/$(CXX_GCC),include,$(COMPILER_CXX_GCC_LOCATION_SLASH))
COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH := $(subst \,/,$(COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_BACKSLASH))
INSTALLED_FILES_LOCATION=$(COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH)/matrix

ifeq ($(shell uname -s),Darwin)
    CXX_GCC=g++
	COMPILER_CXX_GCC_LOCATION_SLASH="usr/bin/g++"
	COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH="/usr/include/"
	INSTALLED_FILES_LOCATION=$(COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH)/matrix
endif

ifeq ($(shell uname -s),Linux)
    CXX_GCC=g++
	COMPILER_CXX_GCC_LOCATION_SLASH="usr/bin/g++"
	COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH="/usr/include/"
	INSTALLED_FILES_LOCATION=$(COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH)matrix
endif

HEADERS_LOCATION := $(wildcard matrix)

.PHONY: tests clean


install:
	@cat materials/.info.txt
	@sleep 2
	@echo G++ COMPILER LOCATION:                $(COMPILER_CXX_GCC_LOCATION_SLASH)
	@echo G++ COMPILER INCLUDE FOLDER LOCATION: $(COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH)
	@echo
	@echo
	@echo "Do you agree to move the library header files to the include folder of the g++ compiler? [y/n]"

	@read -r response; \
    if [ "$$response" = "y" ]; then \
        cp -r $(HEADERS_LOCATION) $(COMPILER_CXX_GCC_INCLUDE_FOLDER_LOCATION_SLASH);  \
        echo "Installation finished successfully! Thanks"; \
    else \
        echo "Installation aborted."; \
    fi

uninstall:
	@echo "MATRIX TEMPLATE LIBRARY FILES LOCATION": $(INSTALLED_FILES_LOCATION)
	@echo
	@echo
	@echo "Are you sure to remove them? [y/n]"
	@read -r response; \
    if [ "$$response" = "y" ]; then \
        rm -rf $(INSTALLED_FILES_LOCATION);  \
        echo "Uninstallation finished successfully! See you later"; \
    else \
        echo "Uninstallation aborted."; \
    fi

test:
	@cmake -S . -B ./test_build
	@cmake --build ./test_build
	@./test_build/Matrix_Library_CPP_TEST
	@rm -rf ./test_build
