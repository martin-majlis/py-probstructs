LIB_NAME=probstructs
LIB_VERSION=0.3.1

src/src/prob_structs.h: download-probstructs

download-probstructs:
	curl -o /tmp/v$(LIB_VERSION).tar.gz https://codeload.github.com/martin-majlis/$(LIB_NAME)/tar.gz/v$(LIB_VERSION) && \
	(cd /tmp; tar -xzf /tmp/v$(LIB_VERSION).tar.gz) && \
	cp -r /tmp/$(LIB_NAME)-$(LIB_VERSION)/src src/$(LIB_NAME)

install:
	pip3 install .

test:
	python3 tests/test.py
