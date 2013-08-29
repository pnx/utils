
FILES = $(filter-out ., $(filter-out .., $(wildcard .*)))

INSTALL_PATH = /etc/skel

ifeq ($(DRYRUN), 1)
CP=@echo dryrun: cp
else
CP=cp
endif

.phony: all install

all : install

install : $(FILES)
	$(CP) $(FILES) $(INSTALL_PATH)
