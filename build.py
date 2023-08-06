#!/usr/bin/env python3

'''
LinearML - A Linear Algebra and Machine Learning "Library" in C
Copyright (c) 2023 Adwaith Rajesh <adwaithrajesh3180[at]gmail[dot]com>

LICENSE: MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
'''


from subprocess import Popen
from subprocess import PIPE
from pathlib import Path


def create_folder(path: str) -> None:
    Path(path).mkdir(parents=True, exist_ok=True)


def run_command(cmd: str) -> int:
    p = Popen(cmd, restore_signals=True, stdout=PIPE)
    p.wait()
    return p.returncode


def get_c_files() -> list[str]:
    return [str(path.absolute()) for path in Path('./src').rglob('*.c')]


def crate_compilation_commands(paths: list[str]) -> list[str]:
    return [(f'gcc {filename} -o ./build/out/{Path(filename).name.replace(".c", ".o")}')
            for filename in paths]


def main() -> int:
    # print(run_command('gcc'))
    create_folder('./build')
    print(crate_compilation_commands(get_c_files()))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
