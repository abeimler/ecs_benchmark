
import sys
import os
import pprint
import csv
import pystache

from csvtomd import csv_to_table, md_table
from run_benchmark import config



def replaceCol10Mentities(row):
    if row[0] == '1':
        row[0] = 'Creating 10M entities'
        return row
    elif row[0] == '2':
        row[0] = 'Destroying 10M entities'
        return row
    elif row[0] == '3':
        row[0] = 'Iterating over 10M entities, unpacking one component'
        return row
    elif row[0] == '4':
        row[0] = 'Iterating over 10M entities, unpacking two components'
        return row

    return None


def replaceColUpdate(row):
    if row[0] == '1000000':
        row[0] = 'Update  1M entities with 2 Systems'
        return row
    elif row[0] == '2000000':
        row[0] = 'Update  2M entities with 2 Systems'
        return row
    elif row[0] == '5000000':
        row[0] = 'Update  5M entities with 2 Systems'
        return row
    elif row[0] == '10000000':
        row[0] = 'Update 10M entities with 2 Systems'
        return row
    elif row[0] == '20000000':
        row[0] = 'Update 20M entities with 2 Systems'
        return row

    return None

def replaceColUpdate2(row):
    if row[0] == '1000000':
        row[0] = 'Update  1M entities with 2 Systems'
        return row
    elif row[0] == '2000000':
        row[0] = 'Update  2M entities with 2 Systems'
        return row
    elif row[0] == '5000000':
        row[0] = 'Update  5M entities with 2 Systems'
        return row
    elif row[0] == '10000000':
        row[0] = 'Update 10M entities with 2 Systems'
        return row
    elif row[0] == '20000000':
        row[0] = 'Update 20M entities with 2 Systems'
        return row

    return None

def replaceColEventbus(row):
    if row[0] == '20000':
        row[0] = 'publish EventA and EventB  20k times'
        return row
    elif row[0] == '50000':
        row[0] = 'publish EventA and EventB  50k times'
        return row
    elif row[0] == '100000':
        row[0] = 'publish EventA and EventB 100k times'
        return row
    elif row[0] == '200000':
        row[0] = 'publish EventA and EventB 200k times'
        return row
    elif row[0] == '500000':
        row[0] = 'publish EventA and EventB 500k times'
        return row

    return None


def replaceColHeader(row, suffix):
    for rindex in range(len(row)):
        for fname in config["info"].keys():
            framework = config["info"][fname]
            col = row[rindex]
            if col == fname + suffix:
                row[rindex] = framework["name"]
                break
    return row


def updateCSV(filenamecsv, suffix, replaceCols, newfilenamecsv=None):
    if not newfilenamecsv:
        newfilenamecsv = filenamecsv
    if filenamecsv and os.path.exists(filenamecsv):
        newrows = []
        with open(filenamecsv, mode='r') as csvfile:
            csv_reader = csv.reader(csvfile, delimiter=';', quotechar='"')
            if csv_reader:
                headerrow = next(csv_reader)
                headerrow = replaceColHeader(headerrow, suffix)
                newrows.append(headerrow)
                for row in csv_reader:
                    row = replaceCols(row)
                    if row:
                        newrows.append(row)
        if len(newrows) > 0:
            with open(newfilenamecsv, mode='w') as csvfile:
                csv_writer = csv.writer(csvfile, delimiter=';', quotechar='"', quoting=csv.QUOTE_MINIMAL)
                for newrow in newrows:
                    csv_writer.writerow(newrow)


def makePlotScript(thispath, benchmarkname, pltfilename, params):
    plttmpl = ''
    data_plt_tmpl =  os.path.abspath(thispath + "/data.plt.tmpl")
    with open(data_plt_tmpl, 'r') as data_plt_tmplfile:
        plttmpl = data_plt_tmplfile.read()

    headers = []
    i=2
    for h in params['headers']:
        if h != 'Benchmark':
            headers.append({
                'header': h,
                'col': i
            })
            i = i+1

    params['headers'] = headers

    data_plt = pystache.render(plttmpl, params)

    with open(pltfilename, "w") as data_pltfile:
        data_pltfile.write(data_plt)


def main(argv):
    thispath =  os.path.dirname(os.path.abspath(__file__))

    root_dir =  os.path.abspath(thispath + "/../../")
    scripts_dir =  os.path.abspath(thispath + "/..")
    ecs_benchmark_cmd =  os.path.abspath(root_dir + "/build/app/ecs_benchmark")
    doc_dir =  os.path.abspath(root_dir + "/doc")
    doc_csv_dir =  os.path.abspath(doc_dir + "/csv")





    dateinfo = os.popen("date").read()
    dateinfo = dateinfo.replace("\n", '')

    osinfo = os.popen("uname -o -r -m").read()
    osinfo = osinfo.replace("\n", '')

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


    if config["simplebenchmark"]:
        updatebenchmarks = config["update"]
        if config["simplebenchmark"]:
            updatebenchmarks = config["updatelong"]
        for fname in updatebenchmarks:
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
    csvfiles["update"]=""
    csvfiles["updatelong"]=""
    csvfiles["eventbus"]=""
    csvfiles["10Mentities"]=""

    data_systems_update_dat =  os.path.abspath(doc_dir + "/data-systems-update.dat")
    cmd = ecs_benchmark_cmd
    for fname in config["update"]:
        cmd = cmd + ' --bench ".*'+fname+'.*update.*" '
    if config["gencsvfiles"]:
        cmd = cmd + ' --csvoutput='+doc_csv_dir+' --csvprefix=update --csvunit seconds '
        csvfiles["update"] = os.path.abspath(doc_csv_dir + "/update.csv")
        csvfiles["printupdate"] = os.path.abspath(doc_csv_dir + "/print.update.csv")
    if config["plot"]:
        cmd = cmd + ' --plotdata > ' + data_systems_update_dat

    if config["benchmark"] and (config["gencsvfiles"] or config["plot"]):
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    data_systems_update_2_dat =  os.path.abspath(doc_dir + "/data-systems-update-long.dat")
    cmd = ecs_benchmark_cmd
    for fname in config["updatelong"]:
        cmd = cmd + ' --bench ".*'+fname+'.*update.*" '
    if config["gencsvfiles"]:
        cmd = cmd + ' --csvoutput='+doc_csv_dir+' --csvprefix=updatelong --csvunit seconds '
        csvfiles["updatelong"] = os.path.abspath(doc_csv_dir + "/updatelong.csv")
        csvfiles["printupdatelong"] = os.path.abspath(doc_csv_dir + "/print.updatelong.csv")
    if config["plot"]:
        cmd = cmd + ' --plotdata > ' + data_systems_update_2_dat

    if config["benchmark"] and (config["runbenchmarkupdatelong"] and (config["gencsvfiles"] or config["plot"])):
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    data_eventbus_dat =  os.path.abspath(doc_dir + "/data-eventbus.dat")
    cmd = ecs_benchmark_cmd
    for fname in config["eventbus"]:
        cmd = cmd + ' --bench ".*'+fname+'-eventbus.*" '
    if config["gencsvfiles"]:
        cmd = cmd + ' --csvoutput='+doc_csv_dir+' --csvprefix=eventbus --csvunit seconds '
        csvfiles["eventbus"] = os.path.abspath(doc_csv_dir + "/eventbus.csv")
        csvfiles["printeventbus"] = os.path.abspath(doc_csv_dir + "/print.eventbus.csv")
    if config["plot"]:
        cmd = cmd + ' --plotdata > ' + data_eventbus_dat

    if config["benchmark"] and (config["gencsvfiles"] or config["plot"]):
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    cmd = ecs_benchmark_cmd
    for fname in config["10Mentities"]:
        cmd = cmd + ' --bench ".*'+fname+'.*10M\\s+entities.*" '
    if config["gencsvfiles"]:
        cmd = cmd + ' --csvoutput='+doc_csv_dir+' --csvprefix=10Mentities --csvunit seconds '
        csvfiles["10Mentities"] = os.path.abspath(doc_csv_dir + "/10Mentities.csv")
        csvfiles["print10Mentities"] = os.path.abspath(doc_csv_dir + "/print.10Mentities.csv")
    
    if config["benchmark"] and config["gencsvfiles"]:
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    
    if config["gencsvfiles"]:
        if csvfiles["update"]:
            updateCSV(csvfiles["update"], "update", replaceColUpdate, csvfiles["printupdate"])
        if csvfiles["updatelong"]:
            updateCSV(csvfiles["updatelong"], "update", replaceColUpdate2, csvfiles["printupdatelong"])
        if csvfiles["eventbus"]:
            updateCSV(csvfiles["eventbus"], "eventbus", replaceColEventbus, csvfiles["printeventbus"])
        if csvfiles["10Mentities"]:
            updateCSV(csvfiles["10Mentities"], "10Mentities", replaceCol10Mentities, csvfiles["print10Mentities"])


    if config["plot"]:
        pltfiles = {}

        if os.path.exists(data_systems_update_dat):
            benchmarkname = 'update'
            ## header name in plot is different, so correct it ...
            headers = []
            for f in config[benchmarkname]:
                headers.append(f + 'update')
            headers.sort() # need to be in alphabetic order
            params = {
                'headers': headers, 
                'output': os.path.relpath(doc_dir + '/systems-update-result.png', doc_dir),
                'xlabel': 'Entities',
                'ylabel': 'Time per Operation (ns/op)',
                'title': 'ECS Benchmark System Updates',
                'data_dat':  os.path.relpath(data_systems_update_dat, doc_dir)
            }
            pltfiles[benchmarkname] = os.path.abspath(scripts_dir + "/data-systems-update.plt")
            makePlotScript(thispath, benchmarkname, pltfiles[benchmarkname], params)

        if config["runbenchmarkupdatelong"]:
            if os.path.exists(data_systems_update_2_dat):
                benchmarkname = 'updatelong'
                ## header name in plot is different, so correct it ...
                headers = []
                for f in config[benchmarkname]:
                    headers.append(f + 'update')
                headers.sort() # need to be in alphabetic order
                params = {
                    'headers': headers, 
                    'output': os.path.relpath(doc_dir + '/systems-update-result-long.png', doc_dir),
                    'xlabel': 'Entities',
                    'ylabel': 'Time per Operation (ns/op)',
                    'title': 'ECS Benchmark System Updates',
                    'data_dat':  os.path.relpath(data_systems_update_2_dat, doc_dir)
                }
                pltfiles[benchmarkname] = os.path.abspath(scripts_dir + "/data-systems-update-long.plt")
                makePlotScript(thispath, benchmarkname, pltfiles[benchmarkname], params)

        if os.path.exists(data_eventbus_dat):
            benchmarkname = 'eventbus'
            ## header name in plot is different, so correct it ...
            headers = []
            for f in config[benchmarkname]:
                headers.append(f + '-eventbus')
            headers.sort() # need to be in alphabetic order
            params = {
                'headers': headers, 
                'output': os.path.relpath(doc_dir + '/eventbus-result.png', doc_dir),
                'xlabel': 'Publish Events',
                'ylabel': 'Time per Operation (ns/op)',
                'title': 'ECS Benchmark Eventbus',
                'data_dat':  os.path.relpath(data_eventbus_dat, doc_dir)
            }
            pltfiles[benchmarkname] = os.path.abspath(scripts_dir + "/data-eventbus.plt")
            makePlotScript(thispath, benchmarkname, pltfiles[benchmarkname], params)



        os.chdir(doc_dir)
        for benchmarkname, pltfile in pltfiles.items():
            os.system('gnuplot ' + pltfile)
        os.chdir(root_dir)


    if config["genreadme"]:
        mdTable10MEntities = ''
        if os.path.exists(csvfiles['print10Mentities']):
            with open(csvfiles['print10Mentities'], 'r') as f:
                table10MEntities = csv_to_table(f, ';')
            mdTable10MEntities = md_table(table10MEntities)
        
        mdTableUpdate2 = ''
        if os.path.exists(csvfiles['printupdatelong']):
            with open(csvfiles['printupdatelong'], 'r') as f:
                tableUpdate2 = csv_to_table(f, ';')
            mdTableUpdate2 = md_table(tableUpdate2)

        mdTableUpdate = ''
        if os.path.exists(csvfiles['update']):
            with open(csvfiles['printupdate'], 'r') as f:
                tableUpdate = csv_to_table(f, ';')
            mdTableUpdate = md_table(tableUpdate)


        if config["runbenchmarkupdatelong"] and tableUpdate2 != '':
            mdTableUpdate = mdTableUpdate2

        mdTableEventbus = ''
        if os.path.exists(csvfiles['eventbus']):
            with open(csvfiles['printeventbus'], 'r') as f:
                tableEventbus = csv_to_table(f, ';')
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

        with open(root_dir + "/README.md", "w") as readmefile:
            readmefile.write(readme)





if __name__ == "__main__":
    main(sys.argv)