"""Generate benchmarks graphs and RESULTS.md with benchmark results.

Usage:
  gen-benchmark-report [-c plot.config.json] [--reports-dir=REPORTS_DIR] gen-plots [--plot-lines] <REPORTS>...
  gen-benchmark-report [-c plot.config.json] [--reports-dir=REPORTS_DIR] [-o RESULTS.md] [--img-dir=IMG_DIR] [--skip=N] gen-results-md <REPORTS>...
  gen-benchmark-report [-c plot.config.json] [--reports-dir=REPORTS_DIR] [-i README.md.mustache] [-o README.md] [--img-dir=IMG_DIR] [--skip=N] gen-readme-md <RESULTS>...
  gen-benchmark-report -h | --help
  gen-benchmark-report --version

Commands:
  gen-plots                     plot graphs from reports
  gen-results-md                generate RESULTS.md from reports
  gen-readme-md                 generate README.md from results

Arguments:
  -c plot.config.json           .json config with framework infos [default: ./plot.config.json]
  -o RESULTS.md                 output filename for RESULTS.md [default: RESULTS.md]
  -i README.md.mustache         mustache template filename for README.md [default: README.md.mustache]
  --reports-dir=REPORTS_DIR     reports directory [default: ./reports/]
  --img-dir=IMG_DIR             images directory [default: img/]
  --skip=N                      skip N first entries from results (table)
  --plot-lines                  plot graph as (log) lines, otherwise as histogram
  <REPORTS>...                  list of .json files from google benchmark
  <RESULTS>...                  list of .json files with results `results[key] = "markdown"`

Options:
  -h, --help            show help
  -v, --version         show version

"""
import sys
from docopt import docopt

from .core import main

def cli():
    args = docopt(__doc__)
    main(args)

if __name__ == '__main__':
    sys.exit(cli())