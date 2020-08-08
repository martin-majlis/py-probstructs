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

.. PYPI-BEGIN

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   CHANGES

:ref:`genindex`

.. PYPI-END




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