BINDIR = bin
BINARY = lakota

VERSION := 0.1.0

CFLAGS := -static -O3 -Wall \
	-Dgit_sha=$(shell git rev-parse HEAD) \
	-Dapp_version=$(VERSION)

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
