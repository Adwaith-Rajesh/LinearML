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


import sys
from subprocess import Popen
from subprocess import PIPE
from pathlib import Path


CC = 'gcc'
COM = f'{CC} -I./include -I./src -Wall -Wextra'


def create_folder(path: str) -> None:
    Path(path).mkdir(parents=True, exist_ok=True)


def clear_dirs():
    run_command(f'rm -rf {" ".join(get_files("./build/out", ""))}')


def run_command(cmd: str) -> int:
    print(f'CMD: {cmd}')
    p = Popen(cmd.split(), restore_signals=True, stdout=PIPE)
    p.wait()
    return p.returncode


def get_files(path: str, ext: str) -> list[str]:
    return [str(path.absolute()) for path in Path(path).rglob(f'*{ext}')]


# compile each file to an object file
def create_compilation_commands(paths: list[str]) -> list[str]:
    return [(f'{COM} -fPIC -c {filename} -o ./build/out/{Path(filename).name.replace(".c", ".o")}')
            for filename in paths]


def build_shared_object() -> int:
    obj_files = get_files('./build/out', '.o')
    build_cmd = f'{CC} -shared -fPIC -o liblinearml.so {" ".join(obj_files)}'
    return run_command(build_cmd)


def main() -> int:
    clear_dirs()
    create_folder('./build/out/')

    commands = create_compilation_commands(get_files('./src', '.c'))

    for command in commands:
        rc = run_command(command)
        if rc != 0:
            print(f'Command failed: {command!r}', file=sys.stderr)
            return rc

    if build_shared_object() != 0:
        print('Could not build shared object', file=sys.stderr)

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
