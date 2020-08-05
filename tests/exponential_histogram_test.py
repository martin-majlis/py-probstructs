# -*- coding: utf-8 -*-
import unittest

import probstructs as m

class TestExponentialHistorgram(unittest.TestCase):
    def test_simple(self):
        eh = m.ExponentialHistorgram(1)
        eh.inc(1, 1)
        self.assertEqual(1, eh.get(1, 1))
        eh.inc(1, 1)
        self.assertEqual(2, eh.get(1, 1))

        eh.inc(2, 1)
        self.assertEqual(1, eh.get(1, 2))
