# -*- coding: utf-8 -*-
import unittest

from probstructs import ExponentialHistorgram

class TestExponentialHistorgram(unittest.TestCase):
    def test_simple(self):
        eh = ExponentialHistorgram(1)
        eh.inc(1, 1)
        self.assertEqual(1, eh.get(1, 1))
        eh.inc(1, 1)
        self.assertEqual(2, eh.get(1, 1))

        eh.inc(2, 1)
        self.assertEqual(1, eh.get(1, 2))

    def test_keyword_args(self):
        eh = ExponentialHistorgram(window=1)
        eh.inc(tick=1, delta=1)
        self.assertEqual(1, eh.get(1, 1))
        eh.inc(tick=1, delta=1)
        self.assertEqual(2, eh.get(window=1, tick=1))

        eh.inc(tick=2, delta=1)
        self.assertEqual(1, eh.get(window=1, tick=2))
