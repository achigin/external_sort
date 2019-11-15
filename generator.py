#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import os
import random


def write_random_lowercase(n, f):
    min_lc = ord(b'a')
    len_lc = 26
    ba = bytearray(os.urandom(n))
    for i, b in enumerate(ba):
        ba[i] = min_lc + b % len_lc
    f.write(ba)


def populate_args():
    parser = argparse.ArgumentParser(description="Generate big files.")
    parser.add_argument("-o", dest="file_name", action="store", required=True, help="output file name")
    parser.add_argument("-l", dest="line_count", action="store", required=True, type=int, help="line count")
    parser.add_argument("--max", dest="max_size", action="store", required=True, type=int, help="max line size in MB")
    parser.add_argument("--min", dest="min_size", action="store", required=True, type=int, help="min line size in MB")

    args = parser.parse_args()
    return args


def main():
    args = populate_args()
    args.max_size *= 1024 * 1024
    args.min_size *= 1024 * 1024
    assert (args.max_size >= 1)
    assert (args.min_size >= 1)
    assert (args.max_size >= args.min_size)
    with open(args.file_name, "wb") as output:
        for _ in xrange(args.line_count):
            write_random_lowercase(random.randint(args.min_size, args.max_size), output)
            output.write('\n')


if __name__ == "__main__":
    main()
