# OMNIWEAVER workflow

The GitHub Actions workflow for OMNIWEAVER lives at
`.github/workflows/omniweaver.yml` in the
[snjackson044-droid/OmniWeaver](https://github.com/snjackson044-droid/OmniWeaver)
repo, on the `main` branch.

## What it does

On every push and pull request to `main` that touches `omniweaver.cpp`,
`scripts/omniweaver-check.sh`, or the workflow file itself, it runs one
job, **Build and smoke test**, on `ubuntu-latest`:

1. **Compile** — `g++ -std=c++17 -Wall -Wextra -o omniweaver omniweaver.cpp`
   with all warnings enabled. The program currently compiles with no
   warnings, so keep it that way.
2. **Smoke test 1 — start up, status, and shut down** — runs the program
   with `status` then `quit` and checks the output contains `OMNIWEAVER`,
   `Version: 1.0.0`, `Core: ONLINE`, `Registered systems: 4`, and
   `OmniWeaver shutting down.`
3. **Smoke test 2 — MathEngine (5 multiply 10)** — runs the program with
   `calc multiply 5 10` and checks the output contains
   `Calculation: 5 multiply 10 = 50`.
4. **Smoke test 3 — MemoryEngine (remember and recall)** — runs the
   program with `remember test note` then `recall` and checks the output
   contains `MemoryEngine: Information stored successfully.` and
   `test note`.

## Running the same checks locally

```sh
sh scripts/omniweaver-check.sh
```

That script mirrors the workflow exactly: same compiler flags, same
three smoke tests, same expected output. Run it before pushing. The
program writes `omniweaver_log.txt`, `omniweaver_memory.txt`, and
`omniweaver_archive.txt` at runtime, so the script runs the smoke
tests in a temp directory to keep the repo clean.

## Adding the workflow file

The workflow file itself cannot be pushed by Muse through the GitHub
API — GitHub blocks creating `.github/workflows/*` files that way
(403 "Resource not accessible by integration"). This is the same
limitation hit with the FoxMail API workflow and the CALL-VARS workflow.

So the workflow file is added manually, on the GitHub website:

1. Open the repo at
   https://github.com/snjackson044-droid/OmniWeaver/new/main?filename=.github%2Fworkflows%2Fomniweaver.yml
2. Paste in the contents of `.github/workflows/omniweaver.yml`
   (the file is also attached in chat when the workflow is delivered).
3. Make sure the filename is exactly `.github/workflows/omniweaver.yml`
   — not `Omniweaveryml`, not `omniweaver`, and with the `.yml` ending.
4. Commit directly to `main`.

Once that commit lands, the workflow runs on the next push to `main`
that touches the paths above.

## Adding a new check

1. Add the check to `scripts/omniweaver-check.sh` first, and run it
   locally until it passes.
2. Mirror the same step in `.github/workflows/omniweaver.yml`.
3. Push the script change, then update the workflow file on the
   GitHub website the same way as above.
