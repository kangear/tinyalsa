OBJCFLAGS = #-static
CFLAGS = -c -fPIC -Wall
INC = include
OBJECTS = mixer.o pcm.o
LIB = libtinyalsa.so
STATICLIB = libtinyalsa.a
CROSS_COMPILE =

all: $(LIB) $(STATICLIB) tinyplay tinycap tinymix tinypcminfo

tinyplay: $(LIB) tinyplay.o
	$(CROSS_COMPILE)gcc tinyplay.o $(OBJCFLAGS) -L. -ltinyalsa -o tinyplay

tinycap: $(LIB) tinycap.o
	$(CROSS_COMPILE)gcc tinycap.o $(OBJCFLAGS) -L. -ltinyalsa -o tinycap

tinymix: $(LIB) tinymix.o
	$(CROSS_COMPILE)gcc tinymix.o $(OBJCFLAGS) -L. -ltinyalsa -o tinymix

tinypcminfo: $(LIB) tinypcminfo.o
	$(CROSS_COMPILE)gcc tinypcminfo.o $(OBJCFLAGS) -L. -ltinyalsa -o tinypcminfo

$(STATICLIB): $(OBJECTS)
	$(CROSS_COMPILE)ar rcs $(STATICLIB) $(OBJECTS)

$(LIB): $(OBJECTS)
	$(CROSS_COMPILE)gcc -shared $(OBJECTS) -o $(LIB)

.c.o:
	$(CROSS_COMPILE)gcc $(CFLAGS) $< -I$(INC)

clean:
	-rm $(STATICLIB) $(LIB) $(OBJECTS) tinyplay.o tinyplay tinycap.o tinycap \
	tinymix.o tinymix tinypcminfo.o tinypcminfo
