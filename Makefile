BINDIR = bin
BINARY = lakota

VERSION := v0.1.1
CFLAGS := -O3 -Wall \
	-Dgit_sha=$(shell git rev-parse HEAD) \
	-Dapp_version=$(VERSION)              \
	-Dbin_name=$(BINARY)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), "Linux")
	CFLAGS += -static
endif

$(BINDIR)/$(BINARY): clean
	$(CC) $(CFLAGS) -o $@ main.c words.c

$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: image-build
image-build:
	docker build -t briandowns/lakota:$(VERSION) .

.PHONY: image-push
image-push:
	docker push briandowns/lakota:$(VERSION)

.PHONY: clean
clean: 
	rm -f $(BINDIR)/*
