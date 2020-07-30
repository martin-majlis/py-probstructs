import probstructs as m

assert m.__version__ == '0.2.0'
assert m.add(1, 2) == 3
assert m.subtract(1, 2) == -1

h = m.Hash(1)
val = h.hash("aaa")
assert val == 390644701, f"Was: {val}"

# CM

cm_sketch = m.CountMinSketch(100, 4)
cm_sketch.inc("aaa", 1)
cm_sketch.inc("bbb", 5)
cm_sketch.inc("aaa", 2)

assert cm_sketch.get("aaa") == 3
assert cm_sketch.get("bbb") == 5
assert cm_sketch.get("ccc") == 0

# EH

eh = m.ExponentialHistorgram(1)
eh.inc(1, 1)
assert eh.get(1, 1) == 1
eh.inc(1, 1)
assert eh.get(1, 1) == 2

eh.inc(2, 1)
eh.get(1, 2) == 1

# ECM

ecm_sketch = m.ExponentialCountMinSketch(100, 4, 8);
assert ecm_sketch

ts = 0;
ecm_sketch.inc("aaa", ts, 1)
ecm_sketch.inc("bbb", ts, 4)
ecm_sketch.inc("ccc", ts, 8)

assert ecm_sketch.get("aaa", 4, ts) == 1
assert ecm_sketch.get("bbb", 4, ts) == 4
assert ecm_sketch.get("ccc", 4, ts) == 8
assert ecm_sketch.get("ddd", 4, ts) == 0

print('Success!!!')
