.PHONY: help build test build_test

help:
# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -E '^[a-zA-Z0-9_%/-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

build:
build: ## Build executables
	$(MAKE) -C src

test:
test: ## Test rbtree implementation
	$(MAKE) -C test test

build_test:
build_test: ## Build a test executable without running the tests.
	$(MAKE) -C test build_test

clean:
clean: ## Clear build environment
	$(MAKE) -C src clean
	$(MAKE) -C test clean