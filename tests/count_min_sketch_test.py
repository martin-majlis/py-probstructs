# -*- coding: utf-8 -*-
import unittest

from probstructs import CountMinSketch

class TestCountMinSketch(unittest.TestCase):
    def test_simple(self):
        cm_sketch = CountMinSketch(100, 4)
        cm_sketch.inc("aaa", 1)
        cm_sketch.inc("bbb", 5)
        cm_sketch.inc("aaa", 2)

        self.assertEqual(3, cm_sketch.get("aaa"))
        self.assertEqual(5, cm_sketch.get("bbb"))
        self.assertEqual(0, cm_sketch.get("ccc"))

    def test_keyword_args(self):
        cm_sketch = CountMinSketch(width=100, depth=4)
        cm_sketch.inc(key="aaa", delta=1)
        cm_sketch.inc(key="bbb", delta=5)
        cm_sketch.inc(key="aaa", delta=2)

        self.assertEqual(3, cm_sketch.get(key="aaa"))
        self.assertEqual(5, cm_sketch.get(key="bbb"))
        self.assertEqual(0, cm_sketch.get(key="ccc"))
