"""Generate benchmarks graphs and README with benchmark results.

Usage:
  gen-benchmark-report [-i config.json] [--reports-dir=TEMPLATES_DIR] gen-plot <REPORTS>...
  gen-benchmark-report -h | --help
  gen-benchmark-report --version

Arguments:
  -i info.json                 .json config with framework infos [default: ./info.yml]
  --reports-dir=REPORTS_DIR    reports directory [default: ./reports/]

Options:
  -h, --help            show help
  -v, --version         show version

"""
from docopt import docopt
import plotly.express as px
import matplotlib.pyplot as plt
import pandas as pd
import plotly.graph_objects as go
import os
import json
import re

RESULTS_MUSTACHE_FILENAME = os.path.join(os.path.dirname(__file__), 'RESULTS.md.mustache')

def main(args):
    #print(args)

    frameworks_info = {}
    if args['-i']:
        with open(args['-i'], 'r') as info_file:
            info_data = json.load(info_file)
            frameworks_info = info_data['frameworks']

    output_dir = os.path.abspath(args['--reports-dir']) if args['--reports-dir'] else os.path.abspath('.')

    #print(frameworks_info)

    reports = {}
    if args['<REPORTS>']:
        for report_filename in args['<REPORTS>']:
            with open(report_filename, 'r') as report_file:
                report_data = json.load(report_file)
                reports[report_data['context']['framework.name']] = report_data

    num_cpus = 0
    mhz_per_cpu = 0

    results = {}
    for framework, report in reports.items():
        num_cpus = report['context']['num_cpus']
        mhz_per_cpu = report['context']['mhz_per_cpu']
        version = report['context']['framework.version'] if 'framework.version' in report['context'] else None

        entries = {}
        entries_unit = None
        entries_data = {}
        for benchmark in report['benchmarks']:
            name = benchmark['name']
            time = benchmark['real_time']
            time_ns = None
            time_ms = None
            entities = None
            entities_minimal = None
            entities_mo = None
            entities_mdo = None
            key = ''
            unit = benchmark['time_unit']
            if benchmark['time_unit'] == 'ns':
                time_ns = int(time)
                time_ms = time_ns / 1000000.0
            elif benchmark['time_unit'] == 'ms':
                time_ns = int(time * 1000000.0)
                time_ms = time

            if re.search(r'BM_(.*)_CreateEntities', name):
                key = 'CreateEntities'
                entities = int(benchmark['entities'])
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None
            elif re.search(r'BM_(.*)_DestroyEntities', name):
                key = 'DestroyEntities'
                entities = int(benchmark['entities'])
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None
            elif re.search(r'BM_(.*)_UnpackOneComponent', name):
                key = 'UnpackOneComponent'
                entities = int(benchmark['entities'])
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None
            elif re.search(r'BM_(.*)_UnpackTwoComponents', name):
                key = 'UnpackTwoComponents'
                entities = int(benchmark['entities'])
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None
            elif re.search(r'BM_(.*)_UnpackTwoComponentsFromMixedEntities', name):
                key = 'UnpackTwoComponentsFromMixedEntities'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None
            elif re.search(r'BM_(.*)_UnpackThreeComponentsFromMixedEntities', name):
                key = 'UnpackThreeComponentsFromMixedEntities'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None
            elif re.search(r'BM_(.*)_SystemsUpdate', name):
                key = 'SystemsUpdate'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None
            elif re.search(r'BM_(.*)_ComplexSystemsUpdate', name):
                key = 'ComplexSystemsUpdate'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None
                entities_mo = int(benchmark['entities_mo']) if 'entities_mo' in benchmark else None
                entities_mdo = int(benchmark['entities_mdo']) if 'entities_mdo' in benchmark else None

            if key:
                if key not in entries:
                    entries[key] = {}
                entries[key][entities] = time_ms
                entries_unit = 'ms'
                output_png_filename = os.path.join(output_dir, "{:s}.png".format(key))
                entries_data[key] = {'name': name, 'unit': unit, 'time': time, 'time_ns': time_ns, 'time_ms': time_ms, 'entities': entities, 'entities_minimal': entities_minimal, 'entities_mo': entities_mo, 'entities_mdo': entities_mdo, 'output_png_filename': output_png_filename}

        result_plot_data = {}
        for k in entries.keys():
            result_plot_data[k] = []
            for m in sorted(entries[k].keys()):
                result_plot_data[k].append(entries[k][m])
        name = frameworks_info[framework]['name']
        results[framework] = {'entries': entries, 'entries_data': entries_data, 'plot_data': result_plot_data, 'unit': entries_unit, 'framework': framework, 'label': name, 'version': version}

    results['_meta'] = {'mhz_per_cpu': mhz_per_cpu, 'num_cpus': num_cpus}

    #print(results)

    if args['gen-plot']:
        plot_data = {}
        for framework, result in results.items():
            if '_meta' != framework:
                for ek in result['entries'].keys():
                    x = list(result['entries'][ek].keys())
                    y = result['plot_data'][ek]
                    output_png_filename = result['entries_data'][ek]['output_png_filename']
                    unit = result['unit']
                    name = frameworks_info[framework]['name']

                    if ek not in plot_data:
                        plot_data[ek] = {}
                    if 'df' not in plot_data[ek]:
                        plot_data[ek]['df'] = {}

                    plot_data[ek]['df'][name] = y
                    plot_data[ek]['df']['entities'] = x
                    plot_data[ek]['output_png_filename'] = output_png_filename
                    plot_data[ek]['unit'] = unit
                    plot_data[ek]['name'] = name

        for key, data in plot_data.items():
            y = list(data['df'].keys())
            y.remove('entities')
            fig = px.line(data['df'], x="entities", y=y, labels={
                 "value": "time ({})".format(data['unit']),
                 "variable": "Frameworks",
             }, title=key, log_y=True)
            fig.write_image(data['output_png_filename'])




if __name__ == '__main__':
    args = docopt(__doc__)
    main(args)

