#!/usr/bin/python

import os
import json
import csv
#import .csvtomd

thispath =  os.path.dirname(os.path.abspath(__file__))

root_dir =  os.path.abspath(thispath + "/../../")
ecs_benchmark =  os.path.abspath(root_dir + "/build/ecs_benchmark")
doc_dir =  os.path.abspath(root_dir + "/doc")
doc_csv_dir =  os.path.abspath(doc_dir + "/csv")

jsonconfigfilename = thispath + "/config.json"

jsonconfig = ""
with open(jsonconfigfilename, 'r') as jsonconfigfile:
    jsonconfig=jsonconfigfile.read()
jsonconfigfile.close()

config = json.loads(jsonconfig)

ONLYPLOT=False



os.system('date')
os.system('uname -a')
print("\n")

## use /usr/bin/time for more measurement
format='real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk'
pformat='real %%e user %%U sys %%S   %%E elapsed    CPU: %%P  Max.Memory: %%Mk'

timecmd=''
if os.path.exists('/usr/bin/time'):
    timecmd='/usr/bin/time -f "'+format+'" '


if not ONLYPLOT:
    for fname in config["updates"]:
        cmd = '/usr/bin/time -f "'+format+'" '+ecs_benchmark+' --bench ".*'+fname+'.*update.*"'
        print(cmd + "\n")
        os.system(cmd)
        print("\n")
        print("\n")


    cmd = '/usr/bin/time -f "'+format+'" '+ecs_benchmark+' '
    for fname in config["eventbus"]:
        cmd = cmd + '--bench ".*'+fname+'-eventbus.*" '
    print(cmd + "\n")
    os.system(cmd)
    print("\n")
    print("\n")


    cmd = '/usr/bin/time -f "'+format+'" '+ecs_benchmark+' '
    for fname in config["10Mentities"]:
        cmd = cmd + '--bench ".*'+fname+'.*10M\\s+entities.*" '
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
cmd = ''+ecs_benchmark+' '
for fname in config["plotupdates"]:
    cmd = cmd + '--bench ".*'+fname+'.*update.*" '
    csvfiles["update"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-update.csv")
cmd = cmd + '  --plotdata --csvoutput='+doc_csv_dir+' --csvsuffix=update > ' + data_systems_update_dat
print(cmd + "\n")
os.system(cmd)
print("\n")
print("\n")


data_systems_update_2_dat =  os.path.abspath(doc_dir + "/data-systems-update-2.dat")
cmd = './build/ecs_benchmark '
for fname in config["plotupdates2"]:
    cmd = cmd + '--bench ".*'+fname+'.*update.*" '
    csvfiles["update2"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-update2.csv")
cmd = cmd + '  --plotdata --csvoutput='+doc_csv_dir+' --csvsuffix=update2 > ' + data_systems_update_2_dat
print(cmd + "\n")
os.system(cmd)
print("\n")
print("\n")


data_eventbus_dat =  os.path.abspath(doc_dir + "/data-eventbus.dat")
cmd = './build/ecs_benchmark '
for fname in config["eventbus"]:
    cmd = cmd + '--bench ".*'+fname+'-eventbus.*" '
    csvfiles["eventbus"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-eventbus.csv")
cmd = cmd + '  --plotdata --csvoutput='+doc_csv_dir+' --csvsuffix=eventbus > ' + data_eventbus_dat
print(cmd + "\n")
os.system(cmd)
print("\n")
print("\n")


cmd = './build/ecs_benchmark '
for fname in config["10Mentities"]:
    cmd = cmd + '--bench ".*'+fname+'.*10M\\s+entities.*" '
    csvfiles["10Mentities"][fname] = os.path.abspath(doc_csv_dir + "/" + fname + "-10Mentities.csv")
cmd = cmd + '  --csvoutput='+doc_csv_dir+' --csvsuffix=10Mentities '
print(cmd + "\n")
os.system(cmd)
print("\n")
print("\n")


os.chdir(doc_dir)
os.system('gnuplot ../scripts/data-systems-update.plt')
os.system('gnuplot ../scripts/data-systems-update-2.plt')
os.system('gnuplot ../scripts/data-eventbus.plt')
os.chdir(root_dir)


#print(csvfiles)