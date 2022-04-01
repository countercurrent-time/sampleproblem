import sys
import subprocess

import pytest

@pytest.mark.parametrize(
    'code, excepted',
    [
        ('test_ac.py', b'Accepted\n'),
        ('test_wa.py', b'Wrong Answer\n'),
        ('test_pe.py', b'Presentation Error\n'),
        ('test_re.py', b'Runtime Error\n'),
        ('test_tle.py', b'Time Limit Exceeded\n'),
        ('test_ce.cpp', b'Compilation Error\n')
    ]
)
def test_submit(code, excepted):
    process = subprocess.run(
        ['thaw', 's', code],
        stdout = subprocess.PIPE,
        stderr = sys.stderr
    )
    assert excepted == process.stdout

