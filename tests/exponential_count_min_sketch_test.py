# -*- coding: utf-8 -*-
import unittest

import probstructs as m

class TestExponentialCountMinSketch(unittest.TestCase):
    def test_simple(self):
        ecm_sketch = m.ExponentialCountMinSketch(100, 4, 8)

        ts = 0
        ecm_sketch.inc("aaa", ts, 1)
        ecm_sketch.inc("bbb", ts, 4)
        ecm_sketch.inc("ccc", ts, 8)

        self.assertEqual(1, ecm_sketch.get("aaa", 4, ts))
        self.assertEqual(4, ecm_sketch.get("bbb", 4, ts))
        self.assertEqual(8, ecm_sketch.get("ccc", 4, ts))
        self.assertEqual(0, ecm_sketch.get("ddd", 4, ts))
