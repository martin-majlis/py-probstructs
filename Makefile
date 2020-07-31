LIB_NAME=probstructs
LIB_VERSION=0.3.1

src/src/prob_structs.h: download-probstructs

download-probstructs:
	curl -o /tmp/v$(LIB_VERSION).tar.gz https://codeload.github.com/martin-majlis/$(LIB_NAME)/tar.gz/v$(LIB_VERSION) && \
	(cd /tmp; tar -xzf /tmp/v$(LIB_VERSION).tar.gz) && \
	cp -r /tmp/$(LIB_NAME)-$(LIB_VERSION)/src src/$(LIB_NAME)

install:
	pip3 install .

build:
	python3 setup.py bdist_wheel

pypi-build:
	export DOCKER_IMAGE=quay.io/pypa/manylinux2010_x86_64 && \
	export PLAT=manylinux2010_x86_64 && \
	docker pull $$DOCKER_IMAGE && \
	docker run --rm -e PLAT=$$PLAT -v `pwd`:/io $$DOCKER_IMAGE $$PRE_CMD /io/travis/build-wheels.sh || date
	ls -l wheelhouse
	export DOCKER_IMAGE=quay.io/pypa/manylinux1_i686 && \
	export PRE_CMD=linux32 && \
	export PLAT=manylinux1_i686 && \
	docker pull $$DOCKER_IMAGE && \
	docker run --rm -e PLAT=$$PLAT -v `pwd`:/io $$DOCKER_IMAGE $$PRE_CMD /io/travis/build-wheels.sh || date
	ls -l wheelhouse
	export DOCKER_IMAGE=quay.io/pypa/manylinux1_x86_64 && \
	export PLAT=manylinux1_x86_64 && \
	docker pull $$DOCKER_IMAGE && \
	docker run --rm -e PLAT=$$PLAT -v `pwd`:/io $$DOCKER_IMAGE $$PRE_CMD /io/travis/build-wheels.sh || date
	ls -lrt wheelhouse
	

pypi-upload:
	for f in `find wheelhouse -type f`; do \
		echo $$f; \
		python3 -m twine upload $$f; \
	done;

foo:
	export FOO=10 && echo $$FOO
	echo $$FOO

test:
	python3 tests/test.py

