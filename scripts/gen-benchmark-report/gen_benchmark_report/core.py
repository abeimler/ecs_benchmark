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
import pprint
import numpy as np


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
            unit = benchmark['time_unit']
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
            plot_config_data = None
            for k, data in config['data'].items():
                if re.search(data['regex'], name):
                    key = k
                    plot_config_data = data
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
                     'output_image_filename': output_image_filename, 'line_output_image_filename': line_output_image_filename,
                     'plot_config_data': plot_config_data})

        result_plot_data = {}
        for k in entries.keys():
            sorted(entries_data[k], key=lambda e: e['entities'])
            result_plot_data[k] = {'data': [], 'index': sorted(entries[k].keys())}
            for m in result_plot_data[k]['index']:
                result_plot_data[k]['data'].append(entries[k][m])
        name = frameworks_info[framework]['name']
        results[framework] = {'entries': entries, 'entries_data': entries_data, 'plot_data': result_plot_data,
                              'unit': entries_unit, 'framework': framework,
                              'label': name, 'version': version, 'plot_config_data': plot_config_data}

    results['_meta'] = {'ghz_per_cpu': mhz_per_cpu / 1000.0, 'mhz_per_cpu': mhz_per_cpu, 'num_cpus': num_cpus,
                        'os': platform.system(), 'ram': get_total_memory()}

    x_entites = []
    for framework, result in results.items():
        if '_meta' != framework:
            for ek, data in result['plot_data'].items():
                x_entites.extend(list(data['index']))
    x_entites = list(dict.fromkeys(x_entites))
    x_entites.sort()

    units = {}
    for framework, result in results.items():
        if '_meta' != framework:
            for ek in result['entries'].keys():
                units[ek] = 'ns'
                for e in x_entites:
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

    # normalize unit
    unit = 's'
    for framework, result in results.items():
        if '_meta' != framework:
            results[framework]['plot_data']['_df'] = {}
            for ek in result['entries'].keys():
                y = []
                x = []
                for e in x_entites:
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
                            x.append(e)

                name = frameworks_info[framework]['name']
                data_frame = {name: y}
                results[framework]['plot_data']['_df'][ek] = pd.DataFrame(data_frame, index=x)
                results[framework]['plot_data']['_df_index'] = x

    results['_data_frame_data'] = {}
    results['_plot_data_line'] = {}
    results['_plot_data_histogram'] = {}
    for framework, result in results.items():
        if framework != '_meta' and framework != '_data_frame_data' and framework != '_plot_data_histogram' and framework != '_plot_data_line':
            for ek in result['entries_data'].keys():
                y_absolut = []
                y_us_absolut = []
                y_per_entity = []
                y_us_per_entity = []
                x = []
                for e in x_entites:
                    for ed in result['entries_data'][ek]:
                        if ed['entities'] == e:
                            if unit == 'ns':
                                if ed['entities'] > 0:
                                    y_per_entity.append(ed['time_ns'] / ed['entities'])
                                else:
                                    y_per_entity.append(ed['time_ns'])
                                y_absolut.append(ed['time_ns'])
                            elif unit == 'us':
                                if ed['entities'] > 0:
                                    y_per_entity.append(ed['time_us'] / ed['entities'])
                                else:
                                    y_per_entity.append(ed['time_us'])
                                y_absolut.append(ed['time_us'])
                            elif unit == 'ms':
                                if ed['entities'] > 0:
                                    y_per_entity.append(ed['time_ms'] / ed['entities'])
                                else:
                                    y_per_entity.append(ed['time_ms'])
                                y_absolut.append(ed['time_ms'])
                            elif unit == 's':
                                if ed['entities'] > 0:
                                    y_per_entity.append(ed['time_s'] / ed['entities'])
                                else:
                                    y_per_entity.append(ed['time_s'])
                                y_absolut.append(ed['time_s'])
                            elif unit == 'min':
                                if ed['entities'] > 0:
                                    y_per_entity.append(ed['time_min'] / ed['entities'])
                                else:
                                    y_per_entity.append(ed['time_min'])
                                y_absolut.append(ed['time_min'])
                            if ed['entities'] > 0:
                                y_us_per_entity.append(ed['time_us'] / ed['entities'])
                            else:
                                y_us_per_entity.append(ed['time_us'])
                            # @Note: time / entities = cost per entity
                            y_us_absolut.append(ed['time_us'])
                            x.append(ed['entities'])

                output_image_filename = result['entries_data'][ek][0]['output_image_filename']
                line_output_image_filename = result['entries_data'][ek][0]['line_output_image_filename']
                name = frameworks_info[framework]['name']
                plot_config_data = result['plot_config_data']

                if ek not in results['_data_frame_data']:
                    results['_data_frame_data'][ek] = {}
                if 'df' not in results['_data_frame_data'][ek]:
                    results['_data_frame_data'][ek]['df'] = {}
                if 'y' not in results['_data_frame_data'][ek]:
                    results['_data_frame_data'][ek]['y'] = []

                if ek not in results['_plot_data_line']:
                    results['_plot_data_line'][ek] = {}
                if 'df' not in results['_plot_data_line'][ek]:
                    results['_plot_data_line'][ek]['df'] = {}
                if 'y' not in results['_plot_data_line'][ek]:
                    results['_plot_data_line'][ek]['y'] = []

                if ek not in results['_plot_data_histogram']:
                    results['_plot_data_histogram'][ek] = {}
                if 'data' not in results['_plot_data_histogram'][ek]:
                    results['_plot_data_histogram'][ek]['data'] = {
                        'Framework': [],
                        'Entities': [],
                        'Time': [],
                    }

                histo_frameworks = []
                histo_entities = []
                histo_time = []

                for index, entites in enumerate(x):
                    histo_frameworks.append(name)
                    histo_entities.append(entites)
                    histo_time.append(y_per_entity[index])

                ## frame data for line graph
                results['_data_frame_data'][ek]['df'][name] = y_per_entity
                results['_data_frame_data'][ek]['df']['entities'] = x
                results['_data_frame_data'][ek]['output_image_filename'] = output_image_filename
                results['_data_frame_data'][ek]['line_output_image_filename'] = line_output_image_filename
                results['_data_frame_data'][ek]['unit'] = unit
                results['_data_frame_data'][ek]['name'] = name
                results['_data_frame_data'][ek]['y'].append(name)
                results['_data_frame_data'][ek]['xaxis_title'] = plot_config_data['line']['xaxis_title'] if plot_config_data and 'line' in plot_config_data else 'Entities'
                results['_data_frame_data'][ek]['yaxis_title'] = plot_config_data['line']['yaxis_title'] if plot_config_data and 'line' in plot_config_data else 'Time cost per entity'
                ## frame for second line graph
                results['_plot_data_line'][ek]['df'][name] = y_absolut
                results['_plot_data_line'][ek]['df']['entities'] = x
                results['_plot_data_line'][ek]['output_image_filename'] = output_image_filename
                results['_plot_data_line'][ek]['line_output_image_filename'] = line_output_image_filename
                results['_plot_data_line'][ek]['unit'] = unit
                results['_plot_data_line'][ek]['name'] = name
                results['_plot_data_line'][ek]['y'].append(name)
                results['_plot_data_line'][ek]['xaxis_title'] = plot_config_data['line2']['xaxis_title'] if plot_config_data and 'line2' in plot_config_data else 'Entities'
                results['_plot_data_line'][ek]['yaxis_title'] = plot_config_data['line2']['yaxis_title'] if plot_config_data and 'line2' in plot_config_data else 'Time for all entities'

                ## frame data for histogram
                results['_plot_data_histogram'][ek]['data']['Framework'] = results['_plot_data_histogram'][ek]['data']['Framework'] + histo_frameworks
                results['_plot_data_histogram'][ek]['data']['Entities'] = results['_plot_data_histogram'][ek]['data']['Entities'] + histo_entities
                results['_plot_data_histogram'][ek]['data']['Time'] = results['_plot_data_histogram'][ek]['data']['Time'] + histo_time

                results['_plot_data_histogram'][ek]['x'] = 'Entities'
                results['_plot_data_histogram'][ek]['y'] = 'Time'
                results['_plot_data_histogram'][ek]['color'] = 'Framework'
                results['_plot_data_histogram'][ek]['barmode'] = 'group'
                results['_plot_data_histogram'][ek]['histfunc'] = 'avg'
                results['_plot_data_histogram'][ek]['labels'] = {'Time': "Time ({})".format(unit), 'Entities': 'Entities', 'EntityGroup': 'Entities'}
                results['_plot_data_histogram'][ek]['xaxis_title'] = plot_config_data['histogram']['xaxis_title'] if plot_config_data and 'histogram' in plot_config_data else 'Entities (avg)'
                results['_plot_data_histogram'][ek]['yaxis_title'] = plot_config_data['histogram']['yaxis_title'] if plot_config_data and 'histogram' in plot_config_data else 'Time cost per entity'
                results['_plot_data_histogram'][ek]['output_image_filename'] = output_image_filename
                results['_plot_data_histogram'][ek]['unit'] = unit

                # Define custom groups
                if 0 in x and len(x) == 1:
                    custom_groups = {
                        0: 'NoEntities (baseline)',
                    }
                elif 0 in x:
                    custom_groups = {
                        0: 'NoEntities (baseline)',
                        0: '[8, 128]',
                        128: '[256, 1024]',
                        1024: '[2048, 8192]',
                        8192: '[16k, 65k]',
                        65536: '[131k, 524k]',
                        524288: '1M',
                        1048576: '2M',
                    }
                else:
                    custom_groups = {
                        0: '[8, 128]',
                        128: '[256, 1024]',
                        1024: '[2048, 8192]',
                        8192: '[16k, 65k]',
                        65536: '[131k, 524k]',
                        524288: '1M',
                        1048576: '2M',
                    }
                # Create a new column 'EntityGroup' based on the custom groups
                results['_plot_data_histogram'][ek]['data']['EntityGroup'] = pd.cut(results['_plot_data_histogram'][ek]['data']['Entities'], bins=list(custom_groups.keys()) + [float('inf')], labels=list(custom_groups.values()))
                results['_plot_data_histogram'][ek]['data_frame'] = pd.DataFrame(results['_plot_data_histogram'][ek]['data'])
                results['_plot_data_histogram'][ek]['df'] = results['_plot_data_histogram'][ek]['data_frame']

    return results


# Function to generate tick values and labels for logarithmic scale with "µs" units
def generate_log_ticks(min_val, max_val, base=10):
    ticks = []
    labels = []

    # Generate ticks for the range from min_val to max_val
    current_val = min_val
    while current_val <= max_val:
        if current_val < 1:
            ticks.append(current_val)
            labels.append(f'{current_val:g}µ')
        else:
            ticks.append(current_val)
            labels.append(str(int(current_val)))
            for i in range(1, base):
                exponent = int(np.floor(np.log10(current_val)))
                next_val = (i * 10**exponent) / base
                if next_val < max_val:
                    ticks.append(next_val)
                    if i == 1:
                        labels.append(f'{int(next_val):g}')
                    else:
                        labels.append(str(int(next_val)))
                else:
                    break
        current_val *= base

    return ticks, labels

def gen_plots(config, results):
    frameworks_info = config['frameworks']

    color_discrete_map = {}
    for framework_key, framework in frameworks_info.items():
        if 'color' in framework:
            color_discrete_map[framework['name']] = framework['color']

    frame_data_sizes = []
    for key, data in results['_data_frame_data'].items():
        for df_key, df_data in results['_data_frame_data'][key]['df'].items():
            frame_data_sizes.append(len(results['_data_frame_data'][key]['df']['entities']))
        for df_key, df_data in results['_plot_data_line'][key]['df'].items():
            frame_data_sizes.append(len(results['_plot_data_line'][key]['df']['entities']))
    frame_data_size = min(frame_data_sizes)

    for key, data in results['_data_frame_data'].items():
        title = config['data'][key]['title']
        if not title:
            title = key
            print("WARN: no plot title for {:s}".format(key))

        if '--plot-lines' in config['args'] and config['args']['--plot-lines']:
            fig = px.line(data['df'], x='entities', y=data['y'], labels={
                "value": "Time ({})".format(data['unit']),
                "variable": "Frameworks",
            }, title=title, log_y=True, log_x=True, color_discrete_map=color_discrete_map)
            fig.write_image(file=data['output_image_filename'], format=None, width=GEN_PLOT_IMAGE_WIDTH, height=GEN_PLOT_IMAGE_HEIGHT)
            print("INFO: gen line plot '{:s}': {:s}".format(title, data['output_image_filename']))
        else:
            for df_key, df_data in results['_data_frame_data'][key]['df'].items():
                results['_data_frame_data'][key]['df'][df_key] = results['_data_frame_data'][key]['df'][df_key][:frame_data_size]
            for df_key, df_data in results['_plot_data_line'][key]['df'].items():
                results['_plot_data_line'][key]['df'][df_key] = results['_plot_data_line'][key]['df'][df_key][:frame_data_size]

            ## line graph
            fig_lines = px.line(results['_plot_data_line'][key]['df'], x='entities', y=results['_plot_data_line'][key]['y'], labels={
                "value": "Time ({})".format(results['_plot_data_line'][key]['unit']),
                "variable": "Frameworks",
            }, title=title, log_y=True, log_x=True, color_discrete_map=color_discrete_map)

            ### Update layout
            fig_lines.update_layout(
                title=title,
                xaxis_title=results['_plot_data_line'][key]['xaxis_title'],
                yaxis_title=results['_plot_data_line'][key]['yaxis_title'],
            )
            if results['_plot_data_line'][key]['unit'] == 's':
                # Update y-axis ticks for logarithmic scale with "s" units
                fig_lines.update_yaxes(
                    type='log',
                    tickmode='array',
                    tickvals=[1e-9, 1e-8, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1e0, 1e1],
                    ticktext=['1ns', '10ns', '100ns', '1µ', '10µ', '100µ', '1ms', '10ms', '100ms', '1s', '10s'],  # Corresponding tick labels
                )

            # Write image
            fig_lines.write_image(file=results['_plot_data_line'][key]['line_output_image_filename'], format=None, width=GEN_PLOT_IMAGE_WIDTH, height=GEN_PLOT_IMAGE_HEIGHT)
            print("INFO: gen line plot '{:s}': {:s}".format(title, results['_plot_data_line'][key]['line_output_image_filename']))

            ## histogram
            fig_histo = px.histogram(
                results['_plot_data_histogram'][key]['data_frame'],
                x='EntityGroup',
                y='Time',
                color='Framework',
                barmode=results['_plot_data_histogram'][key]['barmode'],
                labels=results['_plot_data_histogram'][key]['labels'],
                log_y=True,
                histfunc=results['_plot_data_histogram'][key]['histfunc'],
                color_discrete_map=color_discrete_map,
            )

            ### Update layout
            fig_histo.update_layout(
                title=title,
                xaxis_title=results['_plot_data_histogram'][key]['xaxis_title'],
                yaxis_title=results['_plot_data_histogram'][key]['yaxis_title'],
            )
            if results['_plot_data_histogram'][key]['unit'] == 's':
                # Update y-axis ticks for logarithmic scale with "s" units
                fig_histo.update_yaxes(
                    type='log',
                    tickmode='array',
                    tickvals=[1e-9, 1e-8, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1e0],
                    ticktext=['1ns', '10ns', '100ns', '1µ', '10µ', '100µ', '1ms', '10ms', '100ms', '1s'],  # Corresponding tick labels
                )

            # Write image
            fig_histo.write_image(file=results['_plot_data_histogram'][key]['output_image_filename'], format=None, width=GEN_PLOT_IMAGE_WIDTH, height=GEN_PLOT_IMAGE_HEIGHT)
            print("INFO: gen histogram plot '{:s}': {:s}".format(title, results['_plot_data_histogram'][key]['output_image_filename']))



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
        if framework == '_meta' or framework == '_data_frame_data' or framework == '_plot_data_histogram' or framework == '_plot_data_line':
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
                    if (i % 2) == 0 or i == len(entries_data) or edata['entities'] == 8 or edata['entities'] == 16 or edata['entities'] == 32 or edata['entities'] == 64:
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
                    if (i % 2) == 0 or i == len(entries_data) or edata['entities'] == 8 or edata['entities'] == 16 or edata['entities'] == 32 or edata['entities'] == 64:
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
                             'line_figure_img_src': os.path.join(img_dir, "{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'line_figure_img_alt': "{:s} Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header'], 'title': config_data[ek]['title'],
                             'line': config_data[ek]['line'], 'line2': config_data[ek]['line2'], 'histogram': config_data[ek]['histogram']}
    for ek in small_df_data.keys():
        data['plots'][ek] = {'figure_img_src': os.path.join(img_dir, "{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'figure_img_alt': "{:s} Plot".format(ek),
                             'line_figure_img_src': os.path.join(img_dir, "Line{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'line_figure_img_alt': "{:s} Line Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header'], 'title': config_data[ek]['title'],
                             'line': config_data[ek]['line'], 'line2': config_data[ek]['line2'], 'histogram': config_data[ek]['histogram']}
    for ek in smaller_df_data.keys():
        data['plots'][ek] = {'figure_img_src': os.path.join(img_dir, "{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'figure_img_alt': "{:s} Plot".format(ek),
                             'line_figure_img_src': os.path.join(img_dir, "Line{:s}.{:s}".format(ek, OUTPUT_IMG_FILENAME_EXT)),
                             'line_figure_img_alt': "{:s} Line Plot".format(ek),
                             'key': ek, 'header': config_data[ek]['header'], 'title': config_data[ek]['title'],
                             'line': config_data[ek]['line'], 'line2': config_data[ek]['line2'], 'histogram': config_data[ek]['histogram']}

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

_Graph shows cost per entity, tables shows total cost. lower is faster._

{{smaller_table}}

{{small_table}}

{{table}}
"""

# @TODO: make table header for "Cost per entity", ... more 'dynamic'
        result_benchmark_md_template_alt = """
  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![{{figure_img_alt}}]({{figure_img_src}})  |  ![{{line_figure_img_alt}}]({{line_figure_img_src}})  


_Tables shows total cost. lower is faster._

{{smaller_table}}

{{small_table}}

{{table}}
"""
        result_benchmark_md_map = {}
        for benchmark in data['results']:
            title = benchmark['header']
            key = ''
            key_alt = ''
            for data_key, config_data in config['data'].items():
                if config_data['header'] == title:
                    key = data_key
                    key_alt = data_key + 'Alt'
            if key != '':
                result_benchmark_md_map[key] = pystache.render(result_benchmark_md_template, benchmark)
                result_benchmark_md_map[key_alt] = pystache.render(result_benchmark_md_template_alt, benchmark)

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
