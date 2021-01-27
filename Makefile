TARGET_FILE = database.exe

INCLUDE_FOLDER = includes
SOURCE_FOLDER  = sources
OBJECT_FOLDER = objects

SOURCE_FILES = 	main.c \
				string_func.c \
				file_operations.c \
				typedef.c

OBJECT_FILES = $(SOURCE_FILES:.c=.o) 

SOURCE_PATH = $(addprefix $(SOURCE_FOLDER)/,$(SOURCE_FILES))
OBJECT_PATH = $(addprefix $(OBJECT_FOLDER)/,$(OBJECT_FILES))


.PHONY: build	
build : $(TARGET_FILE)

$(TARGET_FILE) : $(OBJECT_PATH)
	cc -I $(INCLUDE_FOLDER) -o $(TARGET_FILE) $(OBJECT_PATH)

$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c

# create objects folder if it does not exist
	mkdir -p objects
	
	cc -I $(INCLUDE_FOLDER) -c -o $@  $<

clean:
	rm -v -f $(OBJECT_PATH)

