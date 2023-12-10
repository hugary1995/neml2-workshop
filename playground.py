from pathlib import Path
import shutil

file_associations = {".cxx": "// ", ".h": "// ", ".i": "# "}
remove_begin = "REMOVE_BEGIN"
remove_end = "REMOVE_END"

orig = Path("examples")
dest = Path("playground")

if __name__ == "__main__":
    if dest.exists():
        shutil.rmtree(dest)
    dest.mkdir(parents=True, exist_ok=True)

    for file in orig.rglob("*"):
        if file.is_dir():
            continue
        if file.suffix not in file_associations:
            continue

        out = dest / file.relative_to(orig)
        with open(file) as file_to_read, open(out, "w") as file_to_write:
            remove_begin_comment = file_associations[file.suffix] + remove_begin
            remove_end_comment = file_associations[file.suffix] + remove_end
            should_copy = True
            for line in file_to_read:
                if line.strip().startswith(remove_begin_comment):
                    should_copy = False
                if should_copy:
                    file_to_write.write(line)
                if line.strip().startswith(remove_end_comment):
                    should_copy = True
            print("Done populating", str(out))
