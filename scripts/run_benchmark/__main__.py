
import sys
import os
from csvtomd import csv_to_table, md_table
from run_benchmark import *



def main(argv):
    thispath =  os.path.dirname(os.path.abspath(__file__))

    root_dir =  os.path.abspath(thispath + "/../../")
    scripts_dir =  os.path.abspath(thispath + "/..")
    ecs_benchmark_cmd =  os.path.abspath(root_dir + "/build/ecs_benchmark")
    doc_dir =  os.path.abspath(root_dir + "/doc")
    doc_csv_dir =  os.path.abspath(doc_dir + "/csv")

    jsonconfigfilename = thispath + "/config.json"

    jsonconfig = ""
    with open(jsonconfigfilename, 'r') as jsonconfigfile:
        jsonconfig=jsonconfigfile.read()
    jsonconfigfile.close()

    config = json.loads(jsonconfig)




    dateinfo = os.popen("date").read()

    osinfo = os.popen("uname -o -r -m").read()

    cpuinfo = os.popen("lscpu -y | grep -i 'Model name'").read()
    cpuinfo = cpuinfo.replace('Model name:', '').strip()
    cpuinfo = cpuinfo.replace("\n", '')

    raminfo = os.popen("lsmem | grep -i 'Total online memory'").read()
    raminfo = raminfo.replace('Total online memory:', '').strip()
    raminfo = raminfo.replace("\n", '')

    print(dateinfo)
    print("OS: " + osinfo)
    print("CPU: " + cpuinfo)
    print("RAM: " + raminfo)
    print("\n")


    ## use /usr/bin/time for more measurement
    format='real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk'

    time_cmd = ''
    if(os.path.exists('/usr/bin/time')):
        time_cmd = '/usr/bin/time -f "'+format+'" '


    if BENCHMARK:
        for fname in config["updates"]:
            cmd = time_cmd+' '+ecs_benchmark_cmd

            cmd = cmd + ' --bench ".*'+fname+'.*update.*"'

            print(cmd + "\n")
            os.system(cmd)
            print("\n")
            print("\n")


        cmd = time_cmd+' '+ecs_benchmark_cmd
        for fname in config["eventbus"]:
            cmd = cmd + ' --bench ".*'+fname+'-eventbus.*" '
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


        cmd = time_cmd+' '+ecs_benchmark_cmd
        for fname in config["10Mentities"]:
            cmd = cmd + ' --bench ".*'+fname+'.*10M\\s+entities.*" '
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")





    csvfiles={}
    csvfiles["update"]={}
    csvfiles["update2"]={}
    csvfiles["eventbus"]={}
    csvfiles["10Mentities"]={}

    data_systems_update_dat =  os.path.abspath(doc_dir + "/data-systems-update.dat")
    cmd = ecs_benchmark_cmd
    for fname in config["plotupdates"]:
        cmd = cmd + ' --bench ".*'+fname+'.*update.*" '
        csvfiles["update"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-update.csv")
    cmd = cmd + '  --plotdata --csvoutput='+doc_csv_dir+' --csvsuffix=update > ' + data_systems_update_dat
    if BENCHMARK and PLOT:
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    data_systems_update_2_dat =  os.path.abspath(doc_dir + "/data-systems-update-2.dat")
    cmd = ecs_benchmark_cmd
    for fname in config["plotupdates2"]:
        cmd = cmd + ' --bench ".*'+fname+'.*update.*" '
        csvfiles["update2"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-update2.csv")
    cmd = cmd + ' --plotdata --csvoutput='+doc_csv_dir+' --csvsuffix=update2 > ' + data_systems_update_2_dat
    if BENCHMARK and PLOT and RUNBENCHMARKUPDATE2:
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    data_eventbus_dat =  os.path.abspath(doc_dir + "/data-eventbus.dat")
    cmd = ecs_benchmark_cmd
    for fname in config["eventbus"]:
        cmd = cmd + ' --bench ".*'+fname+'-eventbus.*" '
        csvfiles["eventbus"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-eventbus-eventbus.csv")
    cmd = cmd + ' --plotdata --csvoutput='+doc_csv_dir+' --csvsuffix=eventbus > ' + data_eventbus_dat
    if BENCHMARK and PLOT:
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    cmd = ecs_benchmark_cmd
    for fname in config["10Mentities"]:
        cmd = cmd + ' --bench ".*'+fname+'.*10M\\s+entities.*" '
        csvfiles["10Mentities"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-10Mentities.csv")
    cmd = cmd + '  --csvoutput='+doc_csv_dir+' --csvsuffix=10Mentities '
    if BENCHMARK and PLOT:
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")



    benchmarkHeaders = {}
    benchmarkRows = {}

    def genBenchmarkData(name, csvfiles, getrowdata):
        benchmarkheadertitle = 'Benchmark'

        retHeaders = []
        names = set()
        retRows = {}

        retHeaders.append(benchmarkheadertitle)

        for fname, filenamecsv in csvfiles.items():
            fnameheader = fname
            ## put your frameworkname to title here #title #header
            if fname == 'entityx1' or fname == 'entityx1-eventbus':
                fnameheader = 'EntityX (master)'
            elif fname == 'entityx2':
                fnameheader = 'EntityX (experimental/compile_time)'
            elif fname == 'entt' or fname == 'entt-eventbus':
                fnameheader = 'EnTT (master)'
            elif fname == 'anax':
                fnameheader = 'Anax'
            elif fname == 'artemis':
                fnameheader = 'Artemis'

            retHeaders.append(fnameheader)
            if os.path.exists(filenamecsv):
                with open(filenamecsv) as csvfile:
                    readCSV = csv.reader(csvfile)
                    for row in readCSV:
                        row[0] = row[0].strip()

                        rowdata = getrowdata(row)
                        name = rowdata['name']
                        nsop = rowdata['value']

                        sop = None
                        if nsop is not None:
                            sop = nsop / (10 ** 9) # convert to floating-point seconds
                            sop = round(sop, 3)

                        if name != '':
                            names.add(name)

                            if retRows.get(name) is None:
                                retRows[name] = {}
                            
                            retRows[name][fnameheader] = "{0:.3f}s".format(sop) if sop is not None else 'N/A'

        for name in names:
            if retRows.get(name) is None:
                retRows[name] = {}
            for fnameheader in retHeaders:
                if fnameheader != benchmarkheadertitle:
                    if retRows.get(name).get(fnameheader) is None:
                        retRows[name][fnameheader] = 'N/A'


        return {'headers': retHeaders, 'rows': retRows}








    benchmarkname = '10Mentities'
    def getrowdata10Mentities(row):
        nsop = None
        rowname = ''

        if row[0] == '1':
            rowname = 'Creating 10M entities'
            nsop = int(row[1])
        elif row[0] == '2':
            rowname = 'Destroying 10M entities'
            nsop = int(row[1])
        elif row[0] == '3':
            rowname = 'Iterating over 10M entities, unpacking one component'
            nsop = int(row[1])
        elif row[0] == '4':
            rowname = 'Iterating over 10M entities, unpacking two components'
            nsop = int(row[1])

        return { 'name': rowname, 'value': nsop }

    benchmark = genBenchmarkData(benchmarkname, csvfiles[benchmarkname], getrowdata10Mentities)
    benchmarkHeaders[benchmarkname] = benchmark['headers']
    benchmarkRows[benchmarkname] = benchmark['rows']



    benchmarkname = 'update'
    def getrowdataUpdate(row):
        nsop = None
        rowname = ''

        if row[0] == '1000000':
            rowname = 'Update  1M entities with 2 Systems'
            nsop = int(row[1])
        elif row[0] == '2000000':
            rowname = 'Update  2M entities with 2 Systems'
            nsop = int(row[1])
        elif row[0] == '5000000':
            rowname = 'Update  5M entities with 2 Systems'
            nsop = int(row[1])
        elif row[0] == '10000000':
            rowname = 'Update 10M entities with 2 Systems'
            nsop = int(row[1])
        elif row[0] == '20000000':
            rowname = 'Update 20M entities with 2 Systems'
            nsop = int(row[1])

        return { 'name': rowname, 'value': nsop }

    benchmark = genBenchmarkData(benchmarkname, csvfiles[benchmarkname], getrowdataUpdate)
    benchmarkHeaders[benchmarkname] = benchmark['headers']
    benchmarkRows[benchmarkname] = benchmark['rows']

    if RUNBENCHMARKUPDATE2:
        benchmarkname = 'update2'
        def getrowdataUpdate2(row):
            nsop = None
            rowname = ''

            if row[0] == '1000000':
                rowname = 'Update  1M entities with 2 Systems'
                nsop = int(row[1])
            elif row[0] == '2000000':
                rowname = 'Update  2M entities with 2 Systems'
                nsop = int(row[1])
            elif row[0] == '5000000':
                rowname = 'Update  5M entities with 2 Systems'
                nsop = int(row[1])
            elif row[0] == '10000000':
                rowname = 'Update 10M entities with 2 Systems'
                nsop = int(row[1])
            elif row[0] == '20000000':
                rowname = 'Update 20M entities with 2 Systems'
                nsop = int(row[1])

            return { 'name': rowname, 'value': nsop }

        benchmark = genBenchmarkData(benchmarkname, csvfiles[benchmarkname], getrowdataUpdate2)
        benchmarkHeaders[benchmarkname] = benchmark['headers']
        benchmarkRows[benchmarkname] = benchmark['rows']
    else:
        benchmarkname = 'update2'
        benchmarkHeaders[benchmarkname] = {}
        benchmarkRows[benchmarkname] = {}


    benchmarkname = 'eventbus'
    def getrowdataEventbus(row):
        nsop = None
        rowname = ''

        if row[0] == '20000':
            rowname = 'publish EventA and EventB  20k times'
            nsop = int(row[1])
        elif row[0] == '50000':
            rowname = 'publish EventA and EventB  50k times'
            nsop = int(row[1])
        elif row[0] == '100000':
            rowname = 'publish EventA and EventB 100k times'
            nsop = int(row[1])
        elif row[0] == '200000':
            rowname = 'publish EventA and EventB 200k times'
            nsop = int(row[1])
        elif row[0] == '500000':
            rowname = 'publish EventA and EventB 500k times'
            nsop = int(row[1])

        return { 'name': rowname, 'value': nsop }

    benchmark = genBenchmarkData(benchmarkname, csvfiles[benchmarkname], getrowdataEventbus)
    benchmarkHeaders[benchmarkname] = benchmark['headers']
    benchmarkRows[benchmarkname] = benchmark['rows']

    for benchmark, csvdata in benchmarkRows.items():
        benchmark_csv =  os.path.abspath(doc_csv_dir + "/" + benchmark + "_results.csv")

        if GENCSVFILES:
            with open(benchmark_csv, 'w') as csvfile:
                csvwriter = csv.writer(csvfile)

                csvwriter.writerow(benchmarkHeaders[benchmark])

                for ylabel, benchdata in csvdata.items():
                    row = [ylabel]
                    for xlabel, value in benchdata.items():
                        row.append(value)

                    csvwriter.writerow(row)

        csvfiles[benchmark]['result'] = benchmark_csv







    if PLOT:

        def genPlotScript(benchmarkname, pltfilename, params):
            plttmpl = ''
            data_plt_tmpl =  os.path.abspath(thispath + "/data.plt.tmpl")
            with open(data_plt_tmpl, 'r') as data_plt_tmplfile:
                plttmpl = data_plt_tmplfile.read()

            headers = []
            i=2
            for h in params['headers']:
                headers.append({
                    'header': h,
                    'col': i
                })
                i = i+1

            params['headers'] = headers

            data_plt = pystache.render(plttmpl, params)

            with open(pltfilename, "w") as data_pltfile:
                data_pltfile.write(data_plt)
        
        pltfiles = {}

        benchmarkname = 'update'
        params = {
            'headers': benchmarkHeaders[benchmarkname],
            'output': 'systems-update-result.png',
            'xlabel': 'Entities',
            'ylabel': 'Time per Operation (ns/op)',
            'title': 'ECS Benchmark System Updates'
        }
        pltfiles[benchmarkname] = os.path.abspath(scripts_dir + "/data-systems-update.plt")

        benchmarkname = 'update2'
        params = {
            'headers': benchmarkHeaders[benchmarkname],
            'output': 'systems-update-result-2.png',
            'xlabel': 'Entities',
            'ylabel': 'Time per Operation (ns/op)',
            'title': 'ECS Benchmark System Updates'
        }
        pltfiles[benchmarkname] = os.path.abspath(scripts_dir + "/data-systems-update-2.plt")

        benchmarkname = 'eventbus'
        params = {
            'headers': benchmarkHeaders[benchmarkname],
            'output': 'eventbus-result.png',
            'xlabel': 'Publish Events',
            'ylabel': 'Time per Operation (ns/op)',
            'title': 'ECS Benchmark Eventbus'
        }
        pltfiles[benchmarkname] = os.path.abspath(scripts_dir + "/data-eventbus.plt")




        os.chdir(doc_dir)
        if os.path.exists(data_systems_update_dat):
            os.system('gnuplot ' + pltfiles['update'])
        if os.path.exists(data_systems_update_2_dat):
            os.system('gnuplot ' + pltfiles['update2'])
        if os.path.exists(data_eventbus_dat):
            os.system('gnuplot ' + pltfiles['eventbus'])
        os.chdir(root_dir)


    if GENREADME:
        mdTable10MEntities = ''
        if os.path.exists(csvfiles['10Mentities']['result']):
            with open(csvfiles['10Mentities']['result'], 'rU') as f:
                table10MEntities = csv_to_table(f, ',')
            mdTable10MEntities = md_table(table10MEntities)
        
        mdTableUpdate2 = ''
        if os.path.exists(csvfiles['update2']['result']):
            with open(csvfiles['update2']['result'], 'rU') as f:
                tableUpdate2 = csv_to_table(f, ',')
            mdTableUpdate2 = md_table(tableUpdate2)

        mdTableUpdate = ''
        if os.path.exists(csvfiles['update']['result']):
            with open(csvfiles['update']['result'], 'rU') as f:
                tableUpdate = csv_to_table(f, ',')
            mdTableUpdate = md_table(tableUpdate)


        if RUNBENCHMARKUPDATE2 and tableUpdate2 != '':
            mdTableUpdate = mdTableUpdate2

        mdTableEventbus = ''
        if os.path.exists(csvfiles['eventbus']['result']):
            with open(csvfiles['eventbus']['result'], 'rU') as f:
                tableEventbus = csv_to_table(f, ',')
            mdTableEventbus = md_table(tableEventbus)

        params = {
            'dateinfo': dateinfo,
            'osinfo': osinfo,
            'cpuinfo': cpuinfo,
            'raminfo': raminfo,
            'table10MEntities': mdTable10MEntities,
            'tableUpdate': mdTableUpdate,
            'tableEventbus': mdTableEventbus
        }

        readmetmpl = ''
        readme_tmpl =  os.path.abspath(thispath + "/README.md.tmpl")
        with open(readme_tmpl, 'r') as readmetmplfile:
            readmetmpl = readmetmplfile.read()

        readme = pystache.render(readmetmpl, params)

        with open("./README.md", "w") as readmefile:
            readmefile.write(readme)





if __name__ == "__main__":
    main(sys.argv)