LIB_NAME=probstructs
LIB_VERSION=0.4.0

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = python3 -msphinx
SPHINXPROJ    = Wikipedia-API
SOURCEDIR     = .
BUILDDIR      = _build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)


download-probstructs:
	rm -rfv probstructs/$(LIB_NAME) && \
	make probstructs/probstructs/probstructs.h

probstructs/probstructs/probstructs.h:
	curl -o /tmp/v$(LIB_VERSION).tar.gz https://codeload.github.com/martin-majlis/$(LIB_NAME)/tar.gz/v$(LIB_VERSION) && \
	(cd /tmp; tar -xzf /tmp/v$(LIB_VERSION).tar.gz) && \
	cp -r /tmp/$(LIB_NAME)-$(LIB_VERSION)/probstructs probstructs/$(LIB_NAME)

install: probstructs/probstructs/probstructs.h
	pip3 install .

build:
	python3 setup.py bdist_wheel

pypi-build:
	export DOCKER_IMAGE=quay.io/pypa/manylinux2010_x86_64 && \
	export PLAT=manylinux2010_x86_64 && \
	docker pull $$DOCKER_IMAGE && \
	docker run --rm -e PLAT=$$PLAT -v `pwd`:/io $$DOCKER_IMAGE $$PRE_CMD /io/travis/build-wheels.sh || date
	ls -lrtR wheelhouse
	export DOCKER_IMAGE=quay.io/pypa/manylinux1_i686 && \
	export PRE_CMD=linux32 && \
	export PLAT=manylinux1_i686 && \
	docker pull $$DOCKER_IMAGE && \
	docker run --rm -e PLAT=$$PLAT -v `pwd`:/io $$DOCKER_IMAGE $$PRE_CMD /io/travis/build-wheels.sh || date
	ls -lrtR wheelhouse
	export DOCKER_IMAGE=quay.io/pypa/manylinux1_x86_64 && \
	export PLAT=manylinux1_x86_64 && \
	docker pull $$DOCKER_IMAGE && \
	docker run --rm -e PLAT=$$PLAT -v `pwd`:/io $$DOCKER_IMAGE $$PRE_CMD /io/travis/build-wheels.sh || date
	ls -lrtR wheelhouse


pypi-upload:
	for f in `find wheelhouse -type f`; do \
		echo $$f; \
		python3 -m twine upload $$f; \
	done;

pypi-html:
	python3 setup.py --long-description | rst2html.py > pypi-doc.html


run-tests:
	python3 -m unittest discover tests/ '*test.py'

run-tox:
	tox

run-coverage:
	coverage run --source=probstructs -m unittest discover tests/ '*test.py'
	coverage report -m

run-gen-doc: clean install html

%:
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

clean:
	rm -rfv _build _autosummary
