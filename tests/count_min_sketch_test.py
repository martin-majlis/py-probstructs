# -*- coding: utf-8 -*-
import unittest

import probstructs as m

class TestCountMinSketch(unittest.TestCase):
    def test_simple(self):
        cm_sketch = m.CountMinSketch(100, 4)
        cm_sketch.inc("aaa", 1)
        cm_sketch.inc("bbb", 5)
        cm_sketch.inc("aaa", 2)

        self.assertEqual(3, cm_sketch.get("aaa"))
        self.assertEqual(5, cm_sketch.get("bbb"))
        self.assertEqual(0, cm_sketch.get("ccc"))
