# (C) 2022 StunxFS. All rights reserved. Use of this source code is
# governed by an MIT license that can be found in the LICENSE file.

import subprocess


class ProcessResult:

    def __init__(self, out, err, exit_code):
        self.out = out
        self.err = err
        self.exit_code = exit_code


def execute(*args):
    res = subprocess.run(args, capture_output=True, encoding='utf-8')
    stdout = res.stdout.strip() if res.stdout else ""
    stderr = res.stderr.strip() if res.stderr else ""
    return ProcessResult(stdout, stderr, res.returncode)
