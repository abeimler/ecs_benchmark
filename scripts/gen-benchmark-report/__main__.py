"""Generate benchmarks graphs and RESULTS.md with benchmark results.

Usage:
  gen-benchmark-report [-i config.json] [--reports-dir=TEMPLATES_DIR] gen-plots <REPORTS>...
  gen-benchmark-report [-i config.json] [--reports-dir=TEMPLATES_DIR] [--img-dir=IMG_DIR] gen-results-md <REPORTS>...
  gen-benchmark-report -h | --help
  gen-benchmark-report --version

Commands:
  gen-plots                     plot graphs from reports
  gen-results-md                generate RESULTS.md from reports

Arguments:
  -i info.json                 .json config with framework infos [default: ./info.yml]
  --reports-dir=REPORTS_DIR    reports directory [default: ./reports/]
  --img-dir=IMG_DIR            images directory [default: img/]
  <REPORTS>...                 list of .json files from google benchmark

Options:
  -h, --help            show help
  -v, --version         show version

"""
import sys

from docopt import docopt
import plotly.express as px
import psutil as psu
import pandas as pd
import platform
import pystache
import os
import json
import re

from pprint import pprint


RESULTS_MD_MUSTACHE_FILENAME = os.path.join(os.path.dirname(__file__), 'RESULTS.md.mustache')


def format_bytes(byte):
    for x in ['B', 'KB', 'MB', 'GB', 'TB']:
        if byte < 1024:
            return f"{byte:.2f}{x}"
        byte = byte / 1024


def format_bytes(byte):
    for x in ['B', 'KB', 'MB', 'GB', 'TB']:
        if byte < 1024:
            return f"{byte:.2f}{x}"
        byte = byte / 1024


def human_format(num):
    num = float('{:.3g}'.format(num))
    magnitude = 0
    while abs(num) >= 1000:
        magnitude += 1
        num /= 1000.0
    return '{}{}'.format('{:f}'.format(num).rstrip('0').rstrip('.'), ['', 'K', 'M', 'B', 'T'][magnitude])

def human_format_round(num):
    num = float('{:.3g}'.format(num))
    magnitude = 0
    while abs(num) >= 1000:
        magnitude += 1
        num /= 1000.0
    num_int = int(num)
    num_has_decimal = (num - num_int) > 0.0
    if num_has_decimal:
        return '{}{}'.format('~{:f}'.format(num_int).rstrip('0').rstrip('.'), ['', 'K', 'M', 'B', 'T'][magnitude])
    return '{}{}'.format('{:f}'.format(num).rstrip('0').rstrip('.'), ['', 'K', 'M', 'B', 'T'][magnitude])

def get_total_memory():
    mem = psu.virtual_memory()
    return format_bytes(mem.total)


def genResults(frameworks_info, output_dir, reports):
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
            time_s = None
            time_min = None
            entities = None
            entities_minimal = None
            key = ''
            unit = benchmark['time_unit']
            if benchmark['time_unit'] == 'ns':
                time_ns = int(time)
                time_ms = time_ns / 1000000.0
                time_s = time_ms / 1000.0
                time_min = time_s / 60.0
            elif benchmark['time_unit'] == 'ms':
                time_ns = int(time * 1000000.0)
                time_ms = time
                time_s = time_ms / 1000.0
                time_min = time_s / 60.0

            if re.search(r'^BM_(.*)_CreateEntities\/', name):
                key = 'CreateEntities'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_DestroyEntities\/', name):
                key = 'DestroyEntities'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_UnpackOneComponentConst\/', name):
                key = 'UnpackOneComponentConst'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_UnpackOneComponent\/', name):
                key = 'UnpackOneComponent'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_UnpackTwoComponentsFromMixedEntities\/', name):
                key = 'UnpackTwoComponentsFromMixedEntities'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None
            elif re.search(r'^BM_(.*)_UnpackTwoComponents\/', name):
                key = 'UnpackTwoComponents'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_UnpackThreeComponentsFromMixedEntities\/', name):
                key = 'UnpackThreeComponentsFromMixedEntities'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None
            elif re.search(r'^BM_(.*)_RemoveAddComponent\/', name):
                key = 'RemoveAddComponent'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_ComplexSystemsUpdateMixedEntities\/', name):
                key = 'ComplexSystemsUpdateMixedEntities'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_ComplexSystemsUpdate\/', name):
                key = 'ComplexSystemsUpdate'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None
            elif re.search(r'^BM_(.*)_SystemsUpdateMixedEntities\/', name):
                key = 'SystemsUpdateMixedEntities'
                entities = int(benchmark['entities'])
            elif re.search(r'^BM_(.*)_SystemsUpdate\/', name):
                key = 'SystemsUpdate'
                entities = int(benchmark['entities'])
                entities_minimal = int(benchmark['entities_minimal']) if 'entities_minimal' in benchmark else None

            if key:
                if key not in entries:
                    entries[key] = {}
                entries[key][entities] = time_ms
                entries_unit = 'ms'
                output_png_filename = os.path.join(output_dir, "{:s}.png".format(key))
                if key not in entries_data:
                    entries_data[key] = []
                entries_data[key].append(
                    {'name': name, 'unit': unit, 'time': time, 'time_ns': time_ns, 'time_ms': time_ms, 'time_s': time_s, 'time_min': time_min,
                     'entities': entities, 'entities_minimal': entities_minimal, 'output_png_filename': output_png_filename})

        result_plot_data = {}
        for k in entries.keys():
            sorted(entries_data[k], key=lambda e: e['entities'])
            result_plot_data[k] = {'data': [], 'index': sorted(entries[k].keys())}
            for m in result_plot_data[k]['index']:
                result_plot_data[k]['data'].append(entries[k][m])
        name = frameworks_info[framework]['name']
        results[framework] = {'entries': entries, 'entries_data': entries_data, 'plot_data': result_plot_data,
                              'unit': entries_unit, 'framework': framework,
                              'label': name, 'version': version}

    results['_meta'] = {'ghz_per_cpu': mhz_per_cpu / 1000.0, 'mhz_per_cpu': mhz_per_cpu, 'num_cpus': num_cpus,
                        'os': platform.system(), 'ram': get_total_memory()}

    x = []
    for framework, result in results.items():
        if '_meta' != framework:
            for ek, data in result['plot_data'].items():
                x.extend(list(data['index']))
    x = list(dict.fromkeys(x))
    x.sort()

    units = {}
    for framework, result in results.items():
        if '_meta' != framework:
            for ek in result['entries'].keys():
                units[ek] = 'ns'
                for e in x:
                    for ed in result['entries_data'][ek]:
                        if ed['entities'] == e:
                            if ed['time_s'] >= 60.0:
                                units[ek] = 'min'
                                break
                            elif ed['time_s'] >= 2.0:
                                if units[ek] != 'min':
                                    units[ek] = 's'
                                    break
                            elif ed['time_ms'] >= 10.0:
                                if units[ek] != 's' and units[ek] != 'min':
                                    units[ek] = 'ms'
                                    break

    for framework, result in results.items():
        if '_meta' != framework:
            results[framework]['plot_data']['_df'] = {}
            results[framework]['plot_data']['_df_index'] = x
            for ek in result['entries'].keys():
                unit = units[ek]
                y = []
                for e in x:
                    find = False
                    for ed in result['entries_data'][ek]:
                        if ed['entities'] == e:
                            if unit == 'ns':
                                y.append(ed['time_ns'])
                            elif unit == 'ms':
                                y.append(ed['time_ms'])
                            elif unit == 's':
                                y.append(ed['time_s'])
                            elif unit == 'min':
                                y.append(ed['time_min'])
                            find = True
                    if not find:
                        y.append(None)

                name = frameworks_info[framework]['name']
                data_frame = {name: y}
                results[framework]['plot_data']['_df'][ek] = pd.DataFrame(data_frame, index=x)

    results['_data_frame_data'] = {}
    for framework, result in results.items():
        if framework != '_meta' and framework != '_data_frame_data':
            for ek in result['entries_data'].keys():
                unit = units[ek]
                y = []
                for e in x:
                    find = False
                    for ed in result['entries_data'][ek]:
                        if ed['entities'] == e:
                            if unit == 'ns':
                                y.append(ed['time_ns'])
                            elif unit == 'ms':
                                y.append(ed['time_ms'])
                            elif unit == 's':
                                y.append(ed['time_s'])
                            elif unit == 'min':
                                y.append(ed['time_min'])
                            find = True
                    if not find:
                        y.append(None)

                output_png_filename = result['entries_data'][ek][0]['output_png_filename']
                name = frameworks_info[framework]['name']

                if ek not in results['_data_frame_data']:
                    results['_data_frame_data'][ek] = {}
                if 'df' not in results['_data_frame_data'][ek]:
                    results['_data_frame_data'][ek]['df'] = {}
                if 'y' not in results['_data_frame_data'][ek]:
                    results['_data_frame_data'][ek]['y'] = []

                results['_data_frame_data'][ek]['df'][name] = y
                results['_data_frame_data'][ek]['df']['entities'] = x
                results['_data_frame_data'][ek]['output_png_filename'] = output_png_filename
                results['_data_frame_data'][ek]['unit'] = unit
                results['_data_frame_data'][ek]['name'] = name
                results['_data_frame_data'][ek]['y'].append(name)


    return results

def genPlots(frameworks_info, results):
    for key, data in results['_data_frame_data'].items():

        title = key
        if key == 'CreateEntities':
            title = 'Create Entities'
        elif key == 'DestroyEntities':
            title = 'Destroy Entities'
        elif key == 'UnpackOneComponentConst':
            title = 'Get one (const) component from Entity'
        elif key == 'UnpackOneComponent':
            title = 'Get one (non-const) component from Entity'
        elif key == 'UnpackTwoComponents':
            title = 'Get two components from Entity'
        elif key == 'UnpackThreeComponentsFromMixedEntities':
            title = 'Get three components from Entity'
        elif key == 'RemoveAddComponent':
            title = 'Remove and add component from Entity'
        elif key == 'SystemsUpdate':
            title = 'Update Systems (2 Systems)'
        elif key == 'SystemsUpdateMixedEntities':
            title = 'Update Systems (2 Systems, mixed components)'
        elif key == 'ComplexSystemsUpdate':
            title = 'Update Systems (3 Systems)'
        elif key == 'ComplexSystemsUpdateMixedEntities':
            title = 'Update Systems (3 Systems, mixed components)'

        fig = px.line(data['df'], x='entities', y=data['y'], labels={
            "value": "time ({})".format(data['unit']),
            "variable": "Frameworks",
        }, title=title, log_y=True)
        fig.write_image(data['output_png_filename'])


def genResultsMd(output_dir, frameworks_info, results, img_dir):
    results_md_filename = os.path.join(output_dir, 'RESULTS.md')
    data = {'candidates': [candidate for candidate in frameworks_info.values() if
                           'skip_candidate' not in candidate or not candidate['skip_candidate']],
            'environment': {'os': results['_meta']['os'],
                            'cpu': "{:.2f}GHz @ {:d}Cores".format(results['_meta']['ghz_per_cpu'],
                                                                  results['_meta']['num_cpus']),
                            'ram': results['_meta']['ram']}}

    summary_df_data = {}
    df_data = {}
    df_index = {}
    for framework, result in results.items():
        if framework == '_meta' or framework == '_data_frame_data':
            continue

        name = frameworks_info[framework]['name']
        summary_df_data[name] = []
        summary_df_index = {}

        for ek, entries_data in result['entries_data'].items():
            if ek == '_df' or ek == '_df_index':
                continue

            if ek not in df_index:
                df_index[ek] = {}

            if ek == 'ComplexSystemsUpdate':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        summary_df_index[edata['entities']] = "Update {:>5s} entities with 3 Systems".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'SystemsUpdate':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        summary_df_index[edata['entities']] = "Update {:>5s} entities with 2 Systems".format(human_format_round(edata['entities']))
                    i = i + 1

            if ek == 'SystemsUpdate':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Update {:>5s} entities with 2 Systems".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'ComplexSystemsUpdate':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Update {:>5s} entities with 3 Systems".format(human_format_round(edata['entities']))
                    i = i + 1
            if ek == 'CreateEntities':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Create {:>5s} entities with two Components".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'DestroyEntities':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Destroy {:>5s} entities with two Components".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'UnpackOneComponentConst':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Unpack one (const) Component in {:>5s} entities".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'UnpackOneComponent':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Unpack one Component in {:>5s} entities".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'UnpackTwoComponents':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Unpack two Component in {:>5s} entities".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'UnpackThreeComponentsFromMixedEntities':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Unpack three Component in {:>5s} entities".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'RemoveAddComponent':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Remove and Add a Component in {:>5s} entities".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'SystemsUpdate':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Update {:>5s} entities with 2 Systems".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'SystemsUpdateMixedEntities':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Update {:>5s} entities with 2 Systems".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'ComplexSystemsUpdate':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Update {:>5s} entities with 3 Systems".format(human_format_round(edata['entities']))
                    i = i + 1
            elif ek == 'ComplexSystemsUpdateMixedEntities':
                i = 1
                for edata in entries_data:
                    if i % 2 == 0 or i >= 16:
                        df_index[ek][edata['entities']] = "Update {:>5s} entities with 3 Systems".format(human_format_round(edata['entities']))
                    i = i + 1

        for ek, entries_data in result['entries_data'].items():
            if ek not in df_data:
                df_data[ek] = {}
            if name not in df_data[ek]:
                df_data[ek][name] = []

            if ek == 'ComplexSystemsUpdate' or ek == 'SystemsUpdate':
                for key in summary_df_index.keys():
                    find = False
                    for ed in entries_data:
                        if ed['entities'] == key:
                            summary_df_data[name].append("{:>4d}ms".format(int(ed['time_ms'])))
                            find = True
                            break
                    if not find:
                        summary_df_data[name].append(None)

            for key in df_index[ek].keys():
                find = False
                for ed in entries_data:
                    if ed['entities'] == key:
                        df_data[ek][name].append("{:>4d}ms".format(int(ed['time_ms'])))
                        find = True
                        break
                if not find:
                    df_data[ek][name].append(None)

    if len(summary_df_index) > 0:
        index = summary_df_index.values()
        summary_df = pd.DataFrame(summary_df_data, index=index)
        data['summary'] = {'table': summary_df.to_markdown(),
                           'figure_img_src': os.path.join(img_dir, 'SystemsUpdate.png'),
                           'figure_img_alt': 'Summary SystemsUpdate Plot'}

    data['plots'] = {}
    for ek, dfd in df_data.items():
        index = df_index[ek].values()
        if len(index) > 0:
            df = pd.DataFrame(dfd, index=index)
            data['plots'][ek] = {'table': df.to_markdown(),
                                 'figure_img_src': os.path.join(img_dir, "{:s}.png".format(ek)),
                                 'figure_img_alt': "{:s} Plot".format(ek)}

    with open(RESULTS_MD_MUSTACHE_FILENAME, 'r') as results_file:
        results_md_template = results_file.read()
        with open(results_md_filename, 'w') as results_md_file:
            results_md_file.write(pystache.render(results_md_template, data))


def main(args):
    # print(args)

    frameworks_info = {}
    if args['-i']:
        with open(args['-i'], 'r') as info_file:
            info_data = json.load(info_file)
            frameworks_info = info_data['frameworks']

    output_dir = os.path.abspath(args['--reports-dir']) if args['--reports-dir'] else os.path.abspath('.')

    # print(frameworks_info)

    reports = {}
    if args['<REPORTS>']:
        for report_filename in args['<REPORTS>']:
            with open(report_filename, 'r') as report_file:
                report_data = json.load(report_file)
                reports[report_data['context']['framework.name']] = report_data

    results = genResults(frameworks_info, output_dir, reports)

    if args['gen-plots']:
        genPlots(frameworks_info, results)
    elif args['gen-results-md']:
        genResultsMd(output_dir, frameworks_info, results, args['--img-dir'])


if __name__ == '__main__':
    args = docopt(__doc__)
    main(args)
