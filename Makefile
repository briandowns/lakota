GO = go

BINDIR = bin
CLI_BINARY = lakota-cli
API_BINARY = lakota-api

.PHONY: cli
cli: $(BINDIR)
	$(GO) build -o $(BINDIR)/$(CLI_BINARY) cmd/cli/*.go

.PHONY: api
api: $(BINDIR)
	$(GO) build -o $(BINDIR)/$(API_BINARY) cmd/api/*.go

$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: clean
clean: 
	rm -f $(BINDIR)/*
	$(GO) clean
