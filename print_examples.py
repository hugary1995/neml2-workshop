#!/usr/bin/env python

from pathlib import Path
import shutil
import subprocess

ex_dir = Path("examples")
out_dir = Path("examples-pdf")
language = {".h": "cpp", ".cxx": "cpp", ".i": "python"}


if __name__ == "__main__":
    if not shutil.which("enscript"):
        raise Exception(
            "'enscript' will be used to convert source code to PostScript, but it cannot be found in PATH."
        )
    if not shutil.which("ps2pdf"):
        raise Exception(
            "'ps2pdf' will be used to convert PostScript to PDF, but it cannot be found in PATH."
        )

    if out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    for file in ex_dir.rglob("*"):
        if file.is_dir():
            continue
        if file.suffix not in language:
            continue

        ofile = out_dir / file.relative_to(ex_dir)

        # source code to PS
        args = [
            "enscript",
            "-o",
            str(ofile) + ".ps",
            "-E{}".format(language[file.suffix]),
            "--color",
            str(file),
        ]
        print(" ".join(args))
        subprocess.run(
            args, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
        )

        # PS to pdf
        args = [
            "ps2pdf",
            str(ofile) + ".ps",
            str(ofile) + ".pdf",
        ]
        print(" ".join(args))
        subprocess.run(
            args, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
        )

        print("-" * 79)
