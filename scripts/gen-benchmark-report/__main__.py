"""Generate benchmarks graphs and RESULTS.md with benchmark results.

Usage:
  gen-benchmark-report [-c plot.config.json] [--reports-dir=TEMPLATES_DIR] gen-plots <REPORTS>...
  gen-benchmark-report [-c plot.config.json] [--reports-dir=TEMPLATES_DIR] [-o RESULTS.md] [--img-dir=IMG_DIR] [--skip=N] gen-results-md <REPORTS>...
  gen-benchmark-report -h | --help
  gen-benchmark-report --version

Commands:
  gen-plots                     plot graphs from reports
  gen-results-md                generate RESULTS.md from reports

Arguments:
  -c plot.config.json           .json config with framework infos [default: ./plot.config.json]
  -o RESULTS.md                 output filename for RESULTS.md [default: RESULTS.md]
  --reports-dir=REPORTS_DIR     reports directory [default: ./reports/]
  --img-dir=IMG_DIR             images directory [default: img/]
  --skip=N                      skip N first entries from results (table)
  <REPORTS>...                  list of .json files from google benchmark

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


def genResults(config, output_dir, reports):
    frameworks_info = config['frameworks']

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
            components_one = None
            components_two = None
            components_three = None
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

            key = None
            for k, data in config['data'].items():
                if re.search(data['regex'], name):
                    key = k
                    break
            if not key:
                print("WARN: can find key for {:s}".format(name))

            entities = int(benchmark['entities'])
            components_one = int(benchmark['components_one']) if 'components_one' in benchmark else None
            components_two = int(benchmark['components_two']) if 'components_two' in benchmark else None
            components_three = int(benchmark['components_three']) if 'components_three' in benchmark else None

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
                     'entities': entities, 'components_one': components_one, 'components_two': components_two, 'components_three': components_three,
                     'output_png_filename': output_png_filename})

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

def genPlots(config, results):
    frameworks_info = config['frameworks']
    for key, data in results['_data_frame_data'].items():

        title = config['data'][key]['title']
        if not title:
            print("WARN: no plot title for {:s}".format(key))
        else:
            title = key

        fig = px.line(data['df'], x='entities', y=data['y'], labels={
            "value": "time ({})".format(data['unit']),
            "variable": "Frameworks",
        }, title=title, log_y=True)
        fig.write_image(data['output_png_filename'])


def genResultsMd(config, output_dir, results_filename, results, img_dir):
    frameworks_info = config['frameworks']

    results_md_filename = os.path.join(output_dir, results_filename)
    data = {'candidates': [candidate for candidate in frameworks_info.values() if
                           'skip_candidate' not in candidate or not candidate['skip_candidate']],
            'environment': {'os': results['_meta']['os'],
                            'cpu': "{:.2f}GHz @ {:d}Cores".format(results['_meta']['ghz_per_cpu'],
                                                                  results['_meta']['num_cpus']),
                            'ram': results['_meta']['ram']}}

    config_data = config['data']

    summary_df_data = {}
    df_data = {}
    df_index = {}
    small_summary_df_data = {}
    small_df_data = {}
    small_df_index = {}
    skip = int(config['args']['--skip']) if '--skip' in config['args'] and config['args']['--skip'] else None
    for framework, result in results.items():
        if framework == '_meta' or framework == '_data_frame_data':
            continue

        name = frameworks_info[framework]['name']
        summary_df_data[name] = []
        summary_df_index = {}
        small_summary_df_data[name] = []
        small_summary_df_index = {}

        fill_summary = False
        for ek, entries_data in result['entries_data'].items():
            if ek == '_df' or ek == '_df_index':
                continue

            if ek not in df_index:
                df_index[ek] = {}
                small_df_index[ek] = {}

            if not fill_summary and (ek == 'ComplexSystemsUpdate' or ek == 'SystemsUpdate'):
                i = 1
                j = 0
                for edata in entries_data:
                    if (i % 2) == 0 or i == len(entries_data):
                        if i < 12:
                            if not skip or j >= skip:
                                small_summary_df_index[edata['entities']] = config_data[ek]['index'].format(human_format_round(edata['entities']))
                            j = j + 1
                        else:
                            if not skip or j >= skip:
                                summary_df_index[edata['entities']] = config_data[ek]['index'].format(human_format_round(edata['entities']))
                            j = j + 1
                    i = i + 1
                fill_summary = True

            if ek in config_data:
                i = 1
                j = 0
                for edata in entries_data:
                    if (i % 2) == 0 or i == len(entries_data):
                        if i < 12:
                            if not skip or j >= skip:
                                small_df_index[ek][edata['entities']] = config_data[ek]['index'].format(human_format_round(edata['entities']))
                            j = j + 1
                        else:
                            if not skip or j >= skip:
                                df_index[ek][edata['entities']] = config_data[ek]['index'].format(human_format_round(edata['entities']))
                            j = j + 1
                    i = i + 1
            else:
                print("WARN: no info data for {:s}".format(ek))

        fill_summary = False
        for ek, entries_data in result['entries_data'].items():
            if ek not in df_data:
                df_data[ek] = {}
            if name not in df_data[ek]:
                df_data[ek][name] = []
            if ek not in small_df_data:
                small_df_data[ek] = {}
            if name not in small_df_data[ek]:
                small_df_data[ek][name] = []

            if not fill_summary and (ek == 'ComplexSystemsUpdate' or ek == 'SystemsUpdate'):
                for key in summary_df_index.keys():
                    find = False
                    for ed in entries_data:
                        if ed['entities'] == key:
                            summary_df_data[name].append("{:>4d}ms".format(int(ed['time_ms'])))
                            find = True
                            break
                    if not find:
                        summary_df_data[name].append(None)
                for key in small_summary_df_index.keys():
                    find = False
                    for ed in entries_data:
                        if ed['entities'] == key:
                            small_summary_df_data[name].append("{:>8d}ns".format(int(ed['time_ns'])))
                            find = True
                            break
                    if not find:
                        small_summary_df_data[name].append(None)
                fill_summary = True

            for key in df_index[ek].keys():
                find = False
                for ed in entries_data:
                    if ed['entities'] == key:
                        df_data[ek][name].append("{:>4d}ms".format(int(ed['time_ms'])))
                        find = True
                        break
                if not find:
                    df_data[ek][name].append(None)

            for key in small_df_index[ek].keys():
                find = False
                for ed in entries_data:
                    if ed['entities'] == key:
                        small_df_data[ek][name].append("{:>6d}ns".format(int(ed['time_ns'])))
                        find = True
                        break
                if not find:
                    small_df_data[ek][name].append(None)

            if name in df_data[ek] and len(df_data[ek][name]) == 0:
                #print("WARN: no data for {:s} {:s}".format(ek, name))
                del df_data[ek][name]
            if name in small_df_data[ek] and len(small_df_data[ek][name]) == 0:
                #print("WARN: no data for {:s} {:s}".format(ek, name))
                del small_df_data[ek][name]

        if name in summary_df_data and len(summary_df_data[name]) == 0:
            #print("WARN: no (summary) data for {:s}".format(name))
            del summary_df_data[name]
        if name in small_summary_df_data and len(small_summary_df_data[name]) == 0:
            #print("WARN: no (summary) data for {:s}".format(name))
            del small_summary_df_data[name]

    summary_df = None
    if len(summary_df_index) > 0:
        index = summary_df_index.values()
        summary_df = pd.DataFrame(summary_df_data, index=index)

    small_summary_df = None
    if len(small_summary_df_index) > 0:
        index = summary_df_index.values()
        small_summary_df = pd.DataFrame(small_summary_df_data, index=index)

    data['summary'] = {'table': summary_df.to_markdown() if summary_df is not None else None,
                       'small_table': small_summary_df.to_markdown() if small_summary_df is not None else None,
                       'figure_img_src': os.path.join(img_dir, 'SystemsUpdate.png'),
                       'figure_img_alt': 'Summary SystemsUpdate Plot'}

    data['plots'] = {}
    data['results'] = []
    for ek in df_data.keys():
        data['plots'][ek] = {'figure_img_src': os.path.join(img_dir, "{:s}.png".format(ek)),
                             'figure_img_alt': "{:s} Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header']}
    for ek in small_df_data.keys():
        data['plots'][ek] = {'figure_img_src': os.path.join(img_dir, "{:s}.png".format(ek)),
                             'figure_img_alt': "{:s} Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header']}

    for ek, dfd in df_data.items():
        df = None
        if len(df_index[ek]) > 0:
            index = df_index[ek].values()
            df = pd.DataFrame(dfd, index=index)
        if df is not None:
            data['plots'][ek]['table'] =  df.to_markdown()
    for ek, small_dfd in small_df_data.items():
        small_df = None
        if len(small_df_index[ek]) > 0:
            index = small_df_index[ek].values()
            small_df = pd.DataFrame(small_dfd, index=index)
        if small_df is not None:
            data['plots'][ek]['small_table'] =  small_df.to_markdown()

    for ek, dat in data['plots'].items():
        data['results'].append(data['plots'][ek])

    with open(RESULTS_MD_MUSTACHE_FILENAME, 'r') as results_file:
        results_md_template = results_file.read()
        with open(results_md_filename, 'w') as results_md_file:
            results_md_file.write(pystache.render(results_md_template, data))


def main(args):
    # print(args)

    config = {}
    if args['-c']:
        with open(args['-c'], 'r') as info_file:
            config = json.load(info_file)
    config['args'] = args

    output_dir = os.path.abspath(args['--reports-dir']) if args['--reports-dir'] else os.path.abspath('.')

    # print(frameworks_info)

    reports = {}
    if args['<REPORTS>']:
        for report_filename in args['<REPORTS>']:
            with open(report_filename, 'r') as report_file:
                report_data = json.load(report_file)
                reports[report_data['context']['framework.name']] = report_data

    results = genResults(config, output_dir, reports)

    if args['gen-plots']:
        genPlots(config, results)
    elif args['gen-results-md']:
        genResultsMd(config, output_dir, args['-o'], results, args['--img-dir'])


if __name__ == '__main__':
    args = docopt(__doc__)
    main(args)
