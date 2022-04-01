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
        ('test_ac.py', expected_output('Accepted')),
        ('test_wa.py', expected_output('Wrong Answer')),
        ('test_pe.py', expected_output('Presentation Error')),
        ('test_re.py', expected_output('Runtime Error')),
    ]
)
def test_submit(code, excepted):
    process = subprocess.run(
        ['thaw', 's', code],
        stdout = subprocess.PIPE,
        stderr = sys.stderr
    )
    assert excepted == process.stdout

