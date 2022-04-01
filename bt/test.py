import sys
import subprocess

import pytest

def expected_output(status):
    output = ''
    for i in range(0, 10):
        output += f'#{i}: {status}\n'
    return bytearray(output, encoding='utf-8')

@pytest.mark.parametrize(
    'code, excepted',
    [
        ('std2.cpp', expected_output('Accepted')),
        ('std3.cpp', expected_output('Accepted')),
        ('std4.cpp', expected_output('Accepted')),
    ]
)
def test_submit(code, excepted):
    process = subprocess.run(
        ['thaw', 's', code],
        stdout = subprocess.PIPE,
        stderr = sys.stderr
    )
    assert excepted == process.stdout

