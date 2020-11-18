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

# You should run requirements-dev and requirements-dev-system to be able to run tox
run-tox:
	tox

run-coverage:
	coverage run --source=probstructs -m unittest discover tests/ '*test.py'
	coverage report -m

run-gen-doc: clean install html

clean:
	rm -rfv _build _autosummary

requirements-dev:
	pip install --upgrade -r dev-requirements.txt

requirements-dev-system:
	apt-get install python3.5-dev python3.6-dev python3.7-dev python3.8-dev

pre-release-check: run-tox

release:
	if [ "x$(MSG)" = "x" -o "x$(VERSION)" = "x" ]; then \
		echo "Use make release MSG='some msg' VERSION='1.2.3'"; \
		exit 1; \
	fi; \
	version=`grep __version__ setup.py | sed -r 's/.*= \( *(.*), *(.*), *(.*)\)/\1.\2.\3/'`; \
	if [ "x$$version" = "x" ]; then \
		echo "Unable to extract version"; \
		exit 1; \
	fi; \
	echo "Current version: $$version"; \
	as_number() { \
		total=0; \
		for p in `echo $$1 | tr "." "\n"`; do \
			total=$$(( $$total * 1000 + $$p )); \
		done; \
		echo $$total; \
	}; \
	number_dots=`echo -n $(VERSION) | sed -r 's/[^.]//g' | wc -c`; \
	if [ ! "$${number_dots}" = "2" ]; then \
		echo "Version has to have format X.Y.Z"; \
		echo "Specified version is $(VERSION)"; \
		exit 2; \
	fi; \
	number_version=`as_number $$version`; \
	number_VERSION=`as_number $(VERSION);`; \
	if [ $$number_version -ge $$number_VERSION ]; then \
		echo -n "Specified version $(VERSION) ($$number_VERSION) is lower than"; \
		echo "current version $$version ($$number_version)"; \
		echo "New version has to be greater"; \
		exit 2; \
	fi; \
	short_VERSION=`echo $(VERSION) | cut -f1-2 -d.`; \
	commas_VERSION=`echo $(VERSION) | sed -r 's/\./, /g'`; \
	echo "Short version: $$short_VERSION"; \
	sed -ri 's/version=.*/version="'$(VERSION)'",/' setup.py; \
	sed -ri 's/^release = .*/release = "'$(VERSION)'"/' conf.py; \
	sed -ri 's/^version = .*/version = "'$$short_VERSION'"/' conf.py; \
	sed -ri 's/attr\("__version__"\) = .*/attr("__version__") = "'$(VERSION)'";/' probstructs/main.cpp; \
	git commit setup.py conf.py probstructs/main.cpp -m "Update version to $(VERSION) for new release."; \
	git push; \
	git tag v$(VERSION) -m "$(MSG)"; \
	git push --tags origin master

%:
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)


