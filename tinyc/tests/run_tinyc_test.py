#!/usr/bin/env python3
"""Small test harness for the tinyc compiler.

Contracts:
- Runs `tinyc <src> -o <outBase>` producing `<outBase>.ll` in the working directory.
- Normalizes LLVM IR a bit (strip comments/blank lines) and compares against an expected .ll.
- Also supports negative tests where compilation is expected to fail (non-zero exit code).

This stays intentionally lightweight: no external Python deps.
"""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def normalize_ir(text: str) -> str:
    # Make comparisons resilient to minor formatting differences.
    lines: list[str] = []
    for ln in text.splitlines():
        # Drop LLVM ';' comments
        ln = re.sub(r";.*$", "", ln).rstrip()
        if not ln:
            continue
        lines.append(ln)
    return "\n".join(lines).strip() + "\n"


def run(cmd: list[str], cwd: Path) -> subprocess.CompletedProcess[str]:
    return subprocess.run(cmd, cwd=str(cwd), text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--tinyc", required=True)
    ap.add_argument("--src", required=True)
    ap.add_argument("--expected")
    ap.add_argument("--expect-fail", action="store_true")
    args = ap.parse_args()

    tinyc = Path(args.tinyc)
    src = Path(args.src)

    if not tinyc.exists():
        print(f"test harness error: tinyc not found at {tinyc}", file=sys.stderr)
        return 2
    if not src.exists():
        print(f"test harness error: source not found at {src}", file=sys.stderr)
        return 2

    expected_path = Path(args.expected) if args.expected else None
    if not args.expect_fail:
        if expected_path is None:
            print("test harness error: --expected is required unless --expect-fail", file=sys.stderr)
            return 2
        if not expected_path.exists():
            print(f"test harness error: expected file not found at {expected_path}", file=sys.stderr)
            return 2

    # Use a temp dir so tests don't write into the source tree.
    with tempfile.TemporaryDirectory(prefix="tinyc_test_") as td:
        td_path = Path(td)

        # Copy source into the temp dir. Some compilers embed filenames.
        local_src = td_path / src.name
        shutil.copyfile(src, local_src)

        out_base = td_path / "out"
        cp = run([str(tinyc), str(local_src), "-o", str(out_base)], cwd=td_path)

        if args.expect_fail:
            if cp.returncode == 0:
                print("expected tinyc to fail, but it succeeded", file=sys.stderr)
                if (out_base.with_suffix(".ll")).exists():
                    print("produced IR:\n" + (out_base.with_suffix(".ll")).read_text(), file=sys.stderr)
                return 1
            return 0

        if cp.returncode != 0:
            print("tinyc failed unexpectedly", file=sys.stderr)
            print("stdout:\n" + cp.stdout, file=sys.stderr)
            print("stderr:\n" + cp.stderr, file=sys.stderr)
            return 1

        got_ll_path = out_base.with_suffix(".ll")
        if not got_ll_path.exists():
            print(f"tinyc succeeded but didn't produce {got_ll_path.name}", file=sys.stderr)
            print("stdout:\n" + cp.stdout, file=sys.stderr)
            print("stderr:\n" + cp.stderr, file=sys.stderr)
            return 1

        got = normalize_ir(got_ll_path.read_text())
        exp = normalize_ir(expected_path.read_text())

        if got != exp:
            print("IR mismatch", file=sys.stderr)
            print("--- expected (normalized)")
            print(exp)
            print("--- got (normalized)")
            print(got)
            return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())

