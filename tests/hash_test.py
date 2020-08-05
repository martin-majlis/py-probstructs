# -*- coding: utf-8 -*-
import unittest

import probstructs as m

class TestHash(unittest.TestCase):
    def test_simple(self):
        h = m.Hash(1)
        self.assertEqual(390644701, h.hash("aaa"))

    def test_no_conflict(self):
        for i in range(10):
            vals = {
                j: m.Hash(j).hash("aaa - " + str(i))
                for j in range(10)
            }
            self.assertEqual(len(vals.keys()), len(set(vals.values())))