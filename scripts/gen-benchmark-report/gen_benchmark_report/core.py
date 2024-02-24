import sys

from docopt import docopt
import kaleido
import plotly.express as px
import psutil as psu
import pandas as pd
import platform
import pystache
import os
import json
import re


RESULTS_MD_MUSTACHE_FILENAME = os.path.join(os.path.dirname(__file__), 'RESULTS.md.mustache')
GEN_PLOT_IMAGE_WIDTH = 1008
GEN_PLOT_IMAGE_HEIGHT = 720
OUTPUT_IMG_FILENAME_EXT = 'svg'

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


def gen_results(config, output_dir, reports):
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
            time_us = None
            time_ms = None
            time_s = None
            time_min = None
            entities = None
            components_one = None
            components_two = None
            components_three = None
            key = ''
            unit = benchmark['time_unit']
            if unit == 'ns':
                time_ns = int(time)
                time_us = time_ns / 1000.0
                time_ms = time_us / 1000.0
                time_s = time_ms / 1000.0
                time_min = time_s / 60.0
            elif unit == 'ms':
                time_ms = time
                time_ns = time_ms * 1000000.0
                time_us = time_ns / 1000.0
                time_s = time_ms / 1000.0
                time_min = time_s / 60.0
            elif unit == 'us':
                time_us = time
                time_ns = time_us * 1000.0
                time_ms = time_ns / 1000000.0
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
                output_image_filename = os.path.join(output_dir, "{:s}.{:s}".format(key, OUTPUT_IMG_FILENAME_EXT))
                line_output_image_filename = os.path.join(output_dir, "Line{:s}.{:s}".format(key, OUTPUT_IMG_FILENAME_EXT))
                if key not in entries_data:
                    entries_data[key] = []
                entries_data[key].append(
                    {'name': name, 'unit': unit, 'time': time, 'time_ns': time_ns, 'time_us': time_us, 'time_ms': time_ms, 'time_s': time_s,
                     'time_min': time_min,
                     'entities': entities, 'components_one': components_one, 'components_two': components_two,
                     'components_three': components_three,
                     'output_image_filename': output_image_filename, 'line_output_image_filename': line_output_image_filename})

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
                            elif ed['time_ns'] >= 1000.0:
                                if units[ek] != 's' and units[ek] != 'min' and units[ek] != 'ms':
                                    units[ek] = 'us'
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
                            elif unit == 'us':
                                y.append(ed['time_us'])
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
    results['_plot_data_histogram'] = {}
    for framework, result in results.items():
        if framework != '_meta' and framework != '_data_frame_data' and framework != '_plot_data_histogram':
            for ek in result['entries_data'].keys():
                unit = units[ek]
                y = []
                y_us = []
                for e in x:
                    find = False
                    for ed in result['entries_data'][ek]:
                        if ed['entities'] == e:
                            if unit == 'ns':
                                y.append(ed['time_ns'])
                            elif unit == 'us':
                                y.append(ed['time_us'])
                            elif unit == 'ms':
                                y.append(ed['time_ms'])
                            elif unit == 's':
                                y.append(ed['time_s'])
                            elif unit == 'min':
                                y.append(ed['time_min'])
                            y_us.append(ed['time_us'])
                            find = True
                    if not find:
                        y.append(None)
                        y_us.append(None)

                output_image_filename = result['entries_data'][ek][0]['output_image_filename']
                line_output_image_filename = result['entries_data'][ek][0]['line_output_image_filename']
                name = frameworks_info[framework]['name']

                if ek not in results['_data_frame_data']:
                    results['_data_frame_data'][ek] = {}
                if 'df' not in results['_data_frame_data'][ek]:
                    results['_data_frame_data'][ek]['df'] = {}
                if 'y' not in results['_data_frame_data'][ek]:
                    results['_data_frame_data'][ek]['y'] = []

                if ek not in results['_plot_data_histogram']:
                    results['_plot_data_histogram'][ek] = {}
                if 'data' not in results['_plot_data_histogram'][ek]:
                    results['_plot_data_histogram'][ek]['data'] = {
                        'Framework': [],
                        'Entities': [],
                        'Time (us)': [],
                    }

                histo_frameworks = []
                histo_entities = []
                histo_time = []

                for index, entites in enumerate(x):
                    histo_frameworks.append(name)
                    histo_entities.append(entites)
                    histo_time.append(y_us[index])

                ## frame data for line graph
                results['_data_frame_data'][ek]['df'][name] = y
                results['_data_frame_data'][ek]['df']['entities'] = x
                results['_data_frame_data'][ek]['output_image_filename'] = output_image_filename
                results['_data_frame_data'][ek]['line_output_image_filename'] = line_output_image_filename
                results['_data_frame_data'][ek]['unit'] = unit
                results['_data_frame_data'][ek]['name'] = name
                results['_data_frame_data'][ek]['y'].append(name)

                ## frame data for histogram
                results['_plot_data_histogram'][ek]['data']['Framework'] = results['_plot_data_histogram'][ek]['data']['Framework'] + histo_frameworks
                results['_plot_data_histogram'][ek]['data']['Entities'] = results['_plot_data_histogram'][ek]['data']['Entities'] + histo_entities
                results['_plot_data_histogram'][ek]['data']['Time (us)'] = results['_plot_data_histogram'][ek]['data']['Time (us)'] + histo_time

                results['_plot_data_histogram'][ek]['x'] = 'Entities'
                results['_plot_data_histogram'][ek]['y'] = 'Time (us)'
                results['_plot_data_histogram'][ek]['color'] = 'Framework'
                results['_plot_data_histogram'][ek]['barmode'] = 'group'
                results['_plot_data_histogram'][ek]['histfunc'] = 'avg'
                results['_plot_data_histogram'][ek]['labels'] = {'Time (us)': 'Time (us)', 'Entities': 'Entities'}

                # Define custom groups
                custom_groups = {
                    8: '[0, 64]',
                    64: '[64, 256]',
                    256: '[256, 1024]',
                    1024: '[1024, 8192]',
                    8192: '[8192, 16384]',
                    16384: '[16k, 65k]',
                    65536: '[65k, 131k]',
                    131072: '[131k, 524k]',
                    1048576: '1M',
                    2097152: '2M',
                }
                # Create a new column 'EntityGroup' based on the custom groups
                results['_plot_data_histogram'][ek]['data']['EntityGroup'] = pd.cut(results['_plot_data_histogram'][ek]['data']['Entities'], bins=list(custom_groups.keys()) + [float('inf')], labels=list(custom_groups.values()))
                results['_plot_data_histogram'][ek]['data_frame'] = pd.DataFrame(results['_plot_data_histogram'][ek]['data'])

    return results


def gen_plots(config, results):
    frameworks_info = config['frameworks']
    for key, data in results['_data_frame_data'].items():
        title = config['data'][key]['title']
        if not title:
            print("WARN: no plot title for {:s}".format(key))
        else:
            title = key

        if '--plot-lines' in config['args'] and config['args']['--plot-lines']:
            fig = px.line(data['df'], x='entities', y=data['y'], labels={
                "value": "time ({})".format(data['unit']),
                "variable": "Frameworks",
            }, title=title, log_y=True, log_x=True)
            fig.write_image(file=data['output_image_filename'], format=None, width=GEN_PLOT_IMAGE_WIDTH, height=GEN_PLOT_IMAGE_HEIGHT)
            print("INFO: gen line plot '{:s}': {:s}".format(title, data['output_image_filename']))
        else:
            ## line graph
            fig_lines = px.line(data['df'], x='entities', y=data['y'], labels={
                "value": "time ({})".format(data['unit']),
                "variable": "Frameworks",
            }, title=title, log_y=True, log_x=True)
            fig_lines.write_image(file=data['line_output_image_filename'], format=None, width=GEN_PLOT_IMAGE_WIDTH, height=GEN_PLOT_IMAGE_HEIGHT)
            print("INFO: gen line plot '{:s}': {:s}".format(title, data['line_output_image_filename']))

            ## histogram
            fig_histo = px.histogram(
                results['_plot_data_histogram'][key]['data_frame'],
                x='EntityGroup',
                y='Time (us)',
                color='Framework',
                barmode='group',
                labels={'Time (us)': 'Time (us)', 'Entities': 'Entities', 'EntityGroup': 'Entities'},
                log_y=True,
                histfunc='avg',
            )
            ### Update layout
            fig_histo.update_layout(
                title=title,
                xaxis_title='Entities (grouped)',
                yaxis_title='Time (us)',
            )
            fig_histo.write_image(file=data['output_image_filename'], format=None, width=GEN_PLOT_IMAGE_WIDTH, height=GEN_PLOT_IMAGE_HEIGHT)
            print("INFO: gen histogram plot '{:s}': {:s}".format(title, data['output_image_filename']))



def gen_results_md(config, output_dir, results_filename, results, img_dir):
    frameworks_info = config['frameworks']

    data = {'candidates': [candidate for candidate in frameworks_info.values() if
                           'skip_candidate' not in candidate or not candidate['skip_candidate']],
            'environment': {'os': results['_meta']['os'],
                            'cpu': "{:.2f}GHz @ {:d}Cores".format(results['_meta']['ghz_per_cpu'],
                                                                  results['_meta']['num_cpus']),
                            'ram': results['_meta']['ram']}}

    config_data = config['data']

    results_md_filename = os.path.join(output_dir, results_filename)

    summary_df_data = {}
    df_data = {}
    df_index = {}
    small_summary_df_data = {}
    small_df_data = {}
    small_df_index = {}
    smaller_summary_df_data = {}
    smaller_df_data = {}
    smaller_df_index = {}
    skip = int(config['args']['--skip']) if '--skip' in config['args'] and config['args']['--skip'] else None
    for framework, result in results.items():
        if framework == '_meta' or framework == '_data_frame_data' or framework == '_plot_data_histogram':
            continue

        name = frameworks_info[framework]['name']
        summary_df_data[name] = []
        summary_df_index = {}
        small_summary_df_data[name] = []
        small_summary_df_index = {}
        smaller_summary_df_data[name] = []
        smaller_summary_df_index = {}

        fill_summary = False
        for ek, entries_data in result['entries_data'].items():
            if ek == '_df' or ek == '_df_index':
                continue

            if ek not in df_index:
                df_index[ek] = {}
                small_df_index[ek] = {}
                smaller_df_index[ek] = {}

            if not fill_summary and (ek == 'ComplexSystemsUpdate' or ek == 'SystemsUpdate'):
                i = 1
                j = 0
                for edata in entries_data:
                    if (i % 2) == 0 or i == len(entries_data):
                        if edata['entities'] <= 128:
                            if not skip or j >= skip:
                                smaller_summary_df_index[edata['entities']] = config_data[ek]['index'].format(
                                    human_format_round(edata['entities']))
                            j = j + 1
                        elif edata['entities'] <= 16384:
                            if not skip or j >= skip:
                                small_summary_df_index[edata['entities']] = config_data[ek]['index'].format(
                                    human_format_round(edata['entities']))
                            j = j + 1
                        else:
                            if not skip or j >= skip:
                                summary_df_index[edata['entities']] = config_data[ek]['index'].format(
                                    human_format_round(edata['entities']))
                            j = j + 1
                    i = i + 1
                fill_summary = True

            if ek in config_data:
                i = 1
                j = 0
                for edata in entries_data:
                    if (i % 2) == 0 or i == len(entries_data):
                        if edata['entities'] <= 128:
                            if not skip or j >= skip:
                                smaller_df_index[ek][edata['entities']] = config_data[ek]['index'].format(
                                    human_format_round(edata['entities']))
                            j = j + 1
                        elif edata['entities'] <= 16384:
                            if not skip or j >= skip:
                                small_df_index[ek][edata['entities']] = config_data[ek]['index'].format(
                                    human_format_round(edata['entities']))
                            j = j + 1
                        else:
                            if not skip or j >= skip:
                                df_index[ek][edata['entities']] = config_data[ek]['index'].format(
                                    human_format_round(edata['entities']))
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
            if ek not in smaller_df_data:
                smaller_df_data[ek] = {}
            if name not in smaller_df_data[ek]:
                smaller_df_data[ek][name] = []

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
                            small_summary_df_data[name].append("{:>6d}us".format(int(ed['time_us'])))
                            find = True
                            break
                    if not find:
                        small_summary_df_data[name].append(None)
                for key in smaller_summary_df_index.keys():
                    find = False
                    for ed in entries_data:
                        if ed['entities'] == key:
                            smaller_summary_df_data[name].append("{:>6d}ns".format(int(ed['time_ns'])))
                            find = True
                            break
                    if not find:
                        smaller_summary_df_data[name].append(None)
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
                        small_df_data[ek][name].append("{:>6d}us".format(int(ed['time_us'])))
                        find = True
                        break
                if not find:
                    small_df_data[ek][name].append(None)

            for key in smaller_df_index[ek].keys():
                find = False
                for ed in entries_data:
                    if ed['entities'] == key:
                        smaller_df_data[ek][name].append("{:>6d}ns".format(int(ed['time_ns'])))
                        find = True
                        break
                if not find:
                    smaller_df_data[ek][name].append(None)

            if name in df_data[ek] and len(df_data[ek][name]) == 0:
                # print("WARN: no data for {:s} {:s}".format(ek, name))
                del df_data[ek][name]
            if name in small_df_data[ek] and len(small_df_data[ek][name]) == 0:
                # print("WARN: no data for {:s} {:s}".format(ek, name))
                del small_df_data[ek][name]
            if name in smaller_df_data[ek] and len(smaller_df_data[ek][name]) == 0:
                # print("WARN: no data for {:s} {:s}".format(ek, name))
                del smaller_df_data[ek][name]

        if name in summary_df_data and len(summary_df_data[name]) == 0:
            # print("WARN: no (summary) data for {:s}".format(name))
            del summary_df_data[name]
        if name in small_summary_df_data and len(small_summary_df_data[name]) == 0:
            # print("WARN: no (summary) data for {:s}".format(name))
            del small_summary_df_data[name]
        if name in smaller_summary_df_data and len(smaller_summary_df_data[name]) == 0:
            # print("WARN: no (summary) data for {:s}".format(name))
            del smaller_summary_df_data[name]

    summary_df = None
    if len(summary_df_index) > 0:
        index = summary_df_index.values()
        summary_df = pd.DataFrame(summary_df_data, index=index)

    small_summary_df = None
    if len(small_summary_df_index) > 0:
        index = small_summary_df_index.values()
        small_summary_df = pd.DataFrame(small_summary_df_data, index=index)

    smaller_summary_df = None
    if len(smaller_summary_df_index) > 0:
        index = smaller_summary_df_index.values()
        smaller_summary_df = pd.DataFrame(smaller_summary_df_data, index=index)

    data['summary'] = {'table': summary_df.to_markdown() if summary_df is not None else None,
                       'small_table': small_summary_df.to_markdown() if small_summary_df is not None else None,
                       'smaller_table': smaller_summary_df.to_markdown() if smaller_summary_df is not None else None,
                       'figure_img_src': os.path.join(img_dir, "{:s}.{:s}".format('SystemsUpdate', OUTPUT_IMG_FILENAME_EXT)),
                       'figure_img_alt': 'Summary SystemsUpdate Plot'}

    data['plots'] = {}
    data['results'] = []
    for ek in df_data.keys():
        data['plots'][ek] = {'figure_img_src': os.path.join(img_dir, "{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'figure_img_alt': "{:s} Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header']}
    for ek in small_df_data.keys():
        data['plots'][ek] = {'figure_img_src': os.path.join(img_dir, "{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'figure_img_alt': "{:s} Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header']}
    for ek in smaller_df_data.keys():
        data['plots'][ek] = {'figure_img_src': os.path.join(img_dir, "{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'figure_img_alt': "{:s} Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header']}

    for ek, dfd in df_data.items():
        df = None
        if len(df_index[ek]) > 0:
            index = df_index[ek].values()
            df = pd.DataFrame(dfd, index=index)
        if df is not None:
            data['plots'][ek]['table'] = df.to_markdown()
    for ek, small_dfd in small_df_data.items():
        small_df = None
        if len(small_df_index[ek]) > 0:
            index = small_df_index[ek].values()
            small_df = pd.DataFrame(small_dfd, index=index)
        if small_df is not None:
            data['plots'][ek]['small_table'] = small_df.to_markdown()
    for ek, smaller_dfd in smaller_df_data.items():
        smaller_df = None
        if len(smaller_df_index[ek]) > 0:
            index = smaller_df_index[ek].values()
            smaller_df = pd.DataFrame(smaller_dfd, index=index)
        if smaller_df is not None:
            data['plots'][ek]['smaller_table'] = smaller_df.to_markdown()

    for ek, dat in data['plots'].items():
        data['results'].append(data['plots'][ek])

    with open(RESULTS_MD_MUSTACHE_FILENAME, 'r') as results_file:
        results_md_template = results_file.read()
        with open(results_md_filename, 'w') as results_md_file:
            results_md_file.write(pystache.render(results_md_template, data))
            print("INFO: gen result {:s}".format(results_md_filename))

        result_benchmark_md_template = """
![{{figure_img_alt}}]({{figure_img_src}})

_(lower is better)_

{{smaller_table}}

{{small_table}}

{{table}}
"""

        result_benchmark_md_map = {}
        for benchmark in data['results']:
            title = benchmark['header']
            key = ''
            for data_key, config_data in config['data'].items():
                if config_data['header'] == title:
                    key = data_key
            if key != '':
                result_benchmark_md_map[key] = pystache.render(result_benchmark_md_template, benchmark)

        result_md_json_filename = os.path.join(output_dir, results_filename + ".json")
        with open(result_md_json_filename, 'w', encoding='utf-8') as file_json:
            json.dump(result_benchmark_md_map, file_json, ensure_ascii=False, indent=4)
            print("INFO: gen result (json) {:s}".format(result_md_json_filename))


def gen_readme_md(config, output_dir, readme_md_template_filename, readme_md_filename, input_results, img_dir):
    with open(readme_md_template_filename, 'r') as readme_md_template_file:
        readme_md_template = readme_md_template_file.read()
        with open(readme_md_filename, 'w') as readme_md_file:
            readme_md_file.write(pystache.render(readme_md_template, input_results))
            print("INFO: gen README {:s}".format(readme_md_filename))

def main(args):
    # print(args)

    config = {}
    if args['-c']:
        with open(args['-c'], 'r') as info_file:
            config = json.load(info_file)
    config['args'] = args

    output_dir = os.path.abspath(args['--reports-dir']) if args['--reports-dir'] else os.path.abspath('.')

    # print(frameworks_info)

    if args['gen-plots']:
        reports = {}
        if args['<REPORTS>']:
            for report_filename in args['<REPORTS>']:
                with open(report_filename, 'r') as report_file:
                    print("INFO: load report {:s}".format(report_filename))
                    report_data = json.load(report_file)
                    reports[report_data['context']['framework.name']] = report_data

        results = gen_results(config, output_dir, reports)

        gen_plots(config, results)
    elif args['gen-results-md']:
        reports = {}
        if args['<REPORTS>']:
            for report_filename in args['<REPORTS>']:
                with open(report_filename, 'r') as report_file:
                    print("INFO: load report {:s}".format(report_filename))
                    report_data = json.load(report_file)
                    reports[report_data['context']['framework.name']] = report_data

        results = gen_results(config, output_dir, reports)

        gen_results_md(config, output_dir, args['-o'], results, args['--img-dir'])
    elif args['gen-readme-md']:
        input_results = {}
        if args['<RESULTS>']:
            for result_filename in args['<RESULTS>']:
                with open(result_filename, 'r') as result_file:
                    print("INFO: load result {:s}".format(result_filename))
                    result_data = json.load(result_file)
                    input_results = input_results | result_data

        frameworks_info = config['frameworks']

        # TODO: get hardware info
        meta = {'ghz_per_cpu': 0 / 1000.0, 'mhz_per_cpu': 0, 'num_cpus': 0,
                            'os': platform.system(), 'ram': get_total_memory()}

        input_results['candidates'] = [candidate for candidate in frameworks_info.values() if 'skip_candidate' not in candidate or not candidate['skip_candidate']]
        input_results['environment'] = {'os': meta['os'],
                                'cpu': "{:.2f}GHz @ {:d}Cores".format(meta['ghz_per_cpu'],
                                                                      meta['num_cpus']),
                                'ram': meta['ram']}

        gen_readme_md(config, output_dir, args['-i'], args['-o'], input_results, args['--img-dir'])
