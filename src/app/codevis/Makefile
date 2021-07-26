TARGET				:= $(DIR_DEBUG_BIN)/run

#LIB					:= -lGL -lGLX -lGLU -lglut -lX11
LIB					:= -lvulkan -lX11

INC 			     = -I$(DIR_PROJECT)/src/ -I$(DIR_PROJECT)/src/environment/lib/ -I$(DIR_PROJECT)/src/system/ \
-I$(DIR_PROJECT)/src/environment/lib/boost/any/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/signals2/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/assert/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/config/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/function/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/preprocessor/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/throw_exception/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/integer/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/static_assert/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/type_index/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/container_hash/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/core/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/type_traits/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/detail/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/functional/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/bind/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/mpl/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/smart_ptr/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/iterator/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/variant/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/move/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/callable_traits/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/utility/include/   \
-I$(DIR_PROJECT)/src/environment/lib/boost/optional/include/   \
-I$(DIR_PROJECT)/src/environment/lib/glm/  

DIR_APP				:= $(DIR_PROJECT)/src/app/codevis
DIR_ENGINE			:= $(DIR_PROJECT)/src/system


SOURCE_DIRS 		:= $(DIR_ENGINE) \
$(DIR_APP) \
$(DIR_ENGINE)/subsystem/os \
$(DIR_ENGINE)/subsystem/graphics \
$(DIR_ENGINE)/subsystem/graphics/vulkan \
$(DIR_ENGINE)/subsystem/graphics/vulkan/wrap \
$(DIR_ENGINE)/subsystem/graphics/vulkan/wrap/pipeline \
$(DIR_ENGINE)/subsystem/camera \
$(DIR_ENGINE)/subsystem/core \
$(DIR_PROJECT)/src/environment/lib/glm/detail 

OBJ_DIRS				:= $(subst $(DIR_PROJECT), $(DIR_DEBUG_OBJ), $(SOURCE_DIRS))

SEARCH_CPP_WILDCARDS 	:= $(addsuffix /*.cpp,$(SOURCE_DIRS))

VPATH 					:= $(SOURCE_DIRS)

CPP_LIST				:= $(wildcard $(SEARCH_CPP_WILDCARDS))
OBJ_LIST				:= $(subst $(DIR_PROJECT), $(DIR_DEBUG_OBJ), $(patsubst %.cpp,%.o,$(CPP_LIST)))
DEPEND_LIST				:= $(OBJ_LIST:%.o=%.d)

all: ;

Debug: make_dir $(DEPEND_LIST) $(OBJ_LIST)
	@echo "--- codevis-Debug ---"
	$(COMPILER) -o  $(TARGET) $(OBJ_LIST) $(LIB)
	@echo


$(DEPEND_LIST): $(DIR_DEBUG_OBJ)%.d: $(DIR_PROJECT)%.cpp
	@echo "--- " $(notdir $@) " ---"
#	$(COMPILER) -c -M -MT "$(patsubst %.d,%.o,$@)"  $(CPP_FLAGS) $(INC)  $< > $@
	-rm $(patsubst %.d,%.o,$@)
	@echo ""

include $(wildcard $(DEPEND_LIST))

#make_dir $(OBJECTS)
$(OBJ_LIST): $(DIR_DEBUG_OBJ)%.o: $(DIR_PROJECT)%.cpp
	@echo "--- " $(notdir $@) " ---"
	$(COMPILER) -c -MD -MT "$@" $(CPP_FLAGS) $(INC)  $<
	mv $(DIR_PROJECT)/$(basename $(notdir $@)).d  $(patsubst %.o,%.d,$@)
	mv $(DIR_PROJECT)/$(notdir $@) $@
	@echo ""









.PHONY: make_dir clean clean_obj clean_target run


make_dir:
	-mkdir -p $(OBJ_DIRS) $(DIR_DEBUG_BIN)

clean_obj:
	@echo "--- clean_obj ---"
	-rm  $(OBJ_LIST) $(DEPEND_LIST)
	@echo

clean_target:
	@echo "--- clean_target ---"
	-rm $(TARGET)
	@echo

clean: clean_obj clean_target
	@echo "--- clean ---"
	@echo

run: Debug
	@echo "--- run ---"
	$(TARGET)
	@echo
