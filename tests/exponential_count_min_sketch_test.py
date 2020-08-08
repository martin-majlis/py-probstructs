# -*- coding: utf-8 -*-
import unittest

from probstructs import ExponentialCountMinSketch

class TestExponentialCountMinSketch(unittest.TestCase):
    def test_simple(self):
        ecm_sketch = ExponentialCountMinSketch(100, 4, 8)

        ts = 0
        ecm_sketch.inc("aaa", ts, 1)
        ecm_sketch.inc("bbb", ts, 4)
        ecm_sketch.inc("ccc", ts, 8)

        self.assertEqual(1, ecm_sketch.get("aaa", 4, ts))
        self.assertEqual(4, ecm_sketch.get("bbb", 4, ts))
        self.assertEqual(8, ecm_sketch.get("ccc", 4, ts))
        self.assertEqual(0, ecm_sketch.get("ddd", 4, ts))

    def test_keyword_args(self):
        ecm_sketch = ExponentialCountMinSketch(width=100, depth=4, window=8)

        ts = 0
        ecm_sketch.inc(key="aaa", tick=ts, delta=1)
        ecm_sketch.inc(key="bbb", tick=ts, delta=4)
        ecm_sketch.inc(key="ccc", tick=ts, delta=8)

        self.assertEqual(1, ecm_sketch.get(key="aaa", window=4, tick=ts))
        self.assertEqual(4, ecm_sketch.get(key="bbb", window=4, tick=ts))
        self.assertEqual(8, ecm_sketch.get(key="ccc", window=4, tick=ts))
        self.assertEqual(0, ecm_sketch.get(key="ddd", window=4, tick=ts))
