#!/usr/bin/python

import sys
import os
import json

thispath =  os.path.dirname(os.path.abspath(__file__))

jsonconfigfilename = thispath + "/config.json"

jsonconfig = ""
with open(jsonconfigfilename, 'r') as jsonconfigfile:
    jsonconfig=jsonconfigfile.read()
jsonconfigfile.close()

config = json.loads(jsonconfig)


## settings
SIMPLEBENCHMARK=bool(config['simplebenchmark'])
BENCHMARK=bool(config['benchmark'])
RUNBENCHMARKUPDATE2=bool(config['runbenchmarkupdate2'])
PLOT=bool(config['plot'])
GENCSVFILES=bool(config['gencsvfiles'])
GENREADME=bool(config['genreadme'])

