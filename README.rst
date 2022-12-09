Probabilistic Structures
========================

``Probstructs`` is easy to use Python wrapper for C++ library `probstructs`_ . It supports Exponential Histograms, Count Min Sketch (CM-Sketch), and Exponential Count Min Sketch (ECM-Sketch).

.. _probstructs: https://github.com/martin-majlis/probstructs

|build-status| |docs| |version| |pyversions| |github-stars-flat|

Installation
------------

With pip:

.. code-block:: bash

    pip install probstructs

From source:

.. code-block:: bash

    pip install .

Classes
-------

CountMinSketch
^^^^^^^^^^^^^^

Count–min sketch (CM sketch) is a probabilistic data structure that serves as a frequency table of events in a stream of data. It uses hash functions to map events to frequencies, but unlike a hash table uses only sub-linear space, at the expense of overcounting some events due to collisions.

C++ documentation: https://probstructs.readthedocs.io/en/latest/classes.html#countminsketch

.. code-block:: python

    from probstructs import CountMinSketch

    cm_sketch = CountMinSketch(100, 4)
    cm_sketch.inc("aaa", 1)
    cm_sketch.inc("bbb", 5)
    cm_sketch.inc("aaa", 2)

    print(cm_sketch.get("aaa"))
    # 3
    print(cm_sketch.get("bbb"))
    # 5
    print(cm_sketch.get("ccc"))
    # 0


    cm_sketch = CountMinSketch(width=100, depth=4)
    cm_sketch.inc(key="bbb", delta=5)
    print(cm_sketch.get(key="bbb"))
    # 5

ExponentialHistorgram
^^^^^^^^^^^^^^^^^^^^^

Exponential histogram (EH) is a probabilistic data structure that serves as a frequency counter for specific elements in the last N elements from stream..

C++ documentation: https://probstructs.readthedocs.io/en/latest/classes.html#exponentialhistorgram

.. code-block:: python

    from probstructs import ExponentialHistorgram


    eh = ExponentialHistorgram(1)
    eh.inc(1, 1)
    print(eh.get(1, 1))
    # 1
    eh.inc(1, 1)
    print(eh.get(1, 1))
    # 2
    eh.inc(2, 1)
    print(eh.get(1, 2))
    # 1

    eh = ExponentialHistorgram(window=1)
    eh.inc(tick=1, delta=1)
    print(eh.get(window=1, tick=1))
    # 1
    eh.inc(tick=1, delta=1)
    print(eh.get(window=1, tick=1))
    # 2
    eh.inc(tick=2, delta=1)
    print(eh.get(window=1, tick=2))
    # 1

ExponentialCountMinSketch
^^^^^^^^^^^^^^^^^^^^^^^^^

Exponential count-min sketch (ECM-Sketch) combines CM-Sketch with EH to count number of different elements in the last N elements in the stream.

C++ documentation: https://probstructs.readthedocs.io/en/latest/classes.html#exponentialcountminsketch

.. code-block:: python

    from probstructs import ExponentialCountMinSketch


    ecm_sketch = ExponentialCountMinSketch(100, 4, 8)

    ts = 0
    ecm_sketch.inc("aaa", ts, 1)
    ecm_sketch.inc("bbb", ts, 4)
    ecm_sketch.inc("ccc", ts, 8)

    print(ecm_sketch.get("aaa", 4, ts))
    # 1
    print(ecm_sketch.get("bbb", 4, ts))
    # 4
    print(ecm_sketch.get("ccc", 4, ts))
    # 8
    print(ecm_sketch.get("ddd", 4, ts))
    # 0

    ecm_sketch = ExponentialCountMinSketch(width=100, depth=4, window=8)

    ts = 0
    ecm_sketch.inc(key="aaa", tick=ts, delta=1)
    ecm_sketch.inc(key="bbb", tick=ts, delta=4)
    ecm_sketch.inc(key="ccc", tick=ts, delta=8)

    print(ecm_sketch.get(key="aaa", window=4, tick=ts))
    # 1
    print(ecm_sketch.get(key="bbb", window=4, tick=ts))
    # 4
    print(ecm_sketch.get(key="ccc", window=4, tick=ts))
    # 8
    print(ecm_sketch.get(key="ddd", window=4, tick=ts))
    # 0


Other Badges
------------

|cc-badge| |cc-issues| |coveralls| |version| |pyversions| |implementations|
|github-downloads| |github-tag| |github-release|
|github-commits-since-latest| |github-forks| |github-stars| |github-watches|
|github-commit-activity| |github-last-commit| |github-code-size| |github-repo-size|
|pypi-license| |pypi-wheel| |pypi-format| |pypi-pyversions| |pypi-implementations|
|pypi-status| |pypi-downloads-dd| |pypi-downloads-dw| |pypi-downloads-dm|
|libraries-io-sourcerank| |libraries-io-dependent-repos|

.. PYPI-BEGIN

.. toctree::
   :maxdepth: 3
   :caption: Contents:

   CHANGES
   API
   DEVELOPMENT

:ref:`genindex`

.. PYPI-END


.. |cc-badge| image:: https://codeclimate.com/github/martin-majlis/py-probstructs/badges/gpa.svg
    :target: https://codeclimate.com/github/martin-majlis/py-probstructs
    :alt: Code Climate

.. |cc-issues| image:: https://codeclimate.com/github/martin-majlis/py-probstructs/badges/issue_count.svg
    :target: https://codeclimate.com/github/martin-majlis/py-probstructs
    :alt: Issue Count

.. |cc-coverage| image:: https://api.codeclimate.com/v1/badges/6e2c24d72438b39e5c26/test_coverage
    :target: https://codeclimate.com/github/martin-majlis/py-probstructs
    :alt: Test Coverage

.. |build-status| image:: https://travis-ci.org/martin-majlis/py-probstructs.svg?branch=master
    :alt: build status
    :target: https://travis-ci.org/martin-majlis/py-probstructs

.. |docs| image:: https://readthedocs.org/projects/py-probstructs/badge/?version=latest
    :target: http://py-probstructs.readthedocs.io/en/latest/?badge=latest
    :alt: Documentation Status

.. |version| image:: https://img.shields.io/pypi/v/probstructs.svg?style=flat
	:target: https://pypi.python.org/pypi/probstructs
	:alt: Version

.. |pyversions| image:: https://img.shields.io/pypi/pyversions/probstructs.svg?style=flat
	:target: https://pypi.python.org/pypi/probstructs
	:alt: Py Versions

.. |github-stars-flat| image:: https://img.shields.io/github/stars/martin-majlis/py-probstructs.svg?style=flat&label=Stars
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: GitHub stars

.. |implementations| image:: https://img.shields.io/pypi/implementation/wikipedia-api.svg?style=flat
    :target: https://pypi.python.org/pypi/py-probstructs
	:alt: Implementations

.. |github-downloads| image:: https://img.shields.io/github/downloads/martin-majlis/py-probstructs/total.svg
	:target: https://github.com/martin-majlis/py-probstructs/releases
	:alt: Downloads

.. |github-tag| image:: https://img.shields.io/github/tag/martin-majlis/py-probstructs.svg
	:target: https://github.com/martin-majlis/py-probstructs/tags
	:alt: Tags

.. |github-release| image:: https://img.shields.io/github/release/martin-majlis/py-probstructs.svg
	:target: https://github.com/martin-majlis/py-probstructs/

.. |github-commits-since-latest| image:: https://img.shields.io/github/commits-since/martin-majlis/py-probstructs/latest.svg
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: Github commits (since latest release)

.. |github-forks| image:: https://img.shields.io/github/forks/martin-majlis/py-probstructs.svg?style=social&label=Fork
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: GitHub forks

.. |github-stars| image:: https://img.shields.io/github/stars/martin-majlis/py-probstructs.svg?style=social&label=Stars
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: GitHub stars

.. |github-watches| image:: https://img.shields.io/github/watchers/martin-majlis/py-probstructs.svg?style=social&label=Watch
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: GitHub watchers

.. |github-commit-activity| image:: https://img.shields.io/github/commit-activity/y/martin-majlis/py-probstructs.svg
	:target: https://github.com/martin-majlis/py-probstructs/commits/master
	:alt: GitHub commit activity the past week, 4 weeks, year

.. |github-last-commit| image:: https://img.shields.io/github/commits/martin-majlis/py-probstructs/last.svg
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: Last commit

.. |github-code-size| image:: https://img.shields.io/github/languages/code-size/martin-majlis/py-probstructs.svg
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: GitHub code size in bytes

.. |github-repo-size| image:: https://img.shields.io/github/repo-size/martin-majlis/py-probstructs.svg
	:target: https://github.com/martin-majlis/py-probstructs/
	:alt: GitHub repo size in bytes

.. |pypi-license| image:: https://img.shields.io/pypi/l/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi License

.. |pypi-wheel| image:: https://img.shields.io/pypi/wheel/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi Wheel

.. |pypi-format| image:: https://img.shields.io/pypi/format/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi Format

.. |pypi-pyversions| image:: https://img.shields.io/pypi/pyversions/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi PyVersions

.. |pypi-implementations| image:: https://img.shields.io/pypi/implementation/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi Implementations

.. |pypi-status| image:: https://img.shields.io/pypi/status/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi Status

.. |pypi-downloads-dd| image:: https://img.shields.io/pypi/dd/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi Downloads - Day

.. |pypi-downloads-dw| image:: https://img.shields.io/pypi/dw/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi Downloads - Week

.. |pypi-downloads-dm| image:: https://img.shields.io/pypi/dm/py-probstructs.svg
	:target: https://pypi.python.org/pypi/py-probstructs/
	:alt: PyPi Downloads - Month

.. |libraries-io-sourcerank| image:: https://img.shields.io/librariesio/sourcerank/pypi/py-probstructs.svg
	:target: https://libraries.io/pypi/py-probstructs
	:alt: Libraries.io - SourceRank

.. |libraries-io-dependent-repos| image:: https://img.shields.io/librariesio/dependent-repos/pypi/py-probstructs.svg
	:target: https://libraries.io/pypi/py-probstructs
	:alt: Libraries.io - Dependent Repos