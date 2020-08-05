#!/bin/bash
set -e -u -x

function repair_wheel {
    wheel="$1"
    echo "Repair wheel ${wheel}";
    if ! auditwheel show "$wheel"; then
        echo "Skipping non-platform wheel $wheel"
    else
        auditwheel repair "$wheel" --plat "$PLAT" -w /io/wheelhouse/${PLAT}/ || true
    fi
}


# Install a system package required by our library
# yum install -y atlas-devel

# delete existing builds
rm -rfv wheelhouse/${PLAT}/

# Compile wheels
for PYBIN in /opt/python/*/bin; do
    echo "Building with ${PYBIN}";
    "${PYBIN}/pip" install -r /io/dev-requirements.txt
    "${PYBIN}/pip" wheel /io/ --no-deps -w wheelhouse/${PLAT}/
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/${PLAT}/*.whl; do
    repair_wheel "$whl"
done

# Install packages and test
for PYBIN in /opt/python/*/bin/; do
    "${PYBIN}/pip" install python-manylinux-demo --no-index -f /io/wheelhouse/${PLAT}
    (cd "$HOME"; "${PYBIN}/nosetests" pymanylinuxdemo)
done
